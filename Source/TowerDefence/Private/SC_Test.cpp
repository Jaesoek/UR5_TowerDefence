#include "SC_Test.h"

#include "Components/Image.h"
#include "Components/SceneComponent.h"
#include "Components/SceneCaptureComponent2D.h"
#include "Engine/TextureRenderTarget2D.h"
#include "Materials/MaterialInstanceDynamic.h"

ASC_Test::ASC_Test(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = true;

	USceneComponent* root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = root;

	ViewMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("ViewMesh"));
	SceneCapture = CreateDefaultSubobject<USceneCaptureComponent2D>(TEXT("SceneCapture"));

	if (ViewMesh)
	{
		ViewMesh->SetupAttachment(RootComponent);
		ViewMesh->bEditableWhenInherited = true;
	}

	if (SceneCapture)
	{
		SceneCapture->SetupAttachment(ViewMesh ? ViewMesh : RootComponent);
		SceneCapture->bEditableWhenInherited = true;

		SceneCapture->CaptureSource = ESceneCaptureSource::SCS_FinalColorHDR;
		SceneCapture->PrimitiveRenderMode = ESceneCapturePrimitiveRenderMode::PRM_UseShowOnlyList;

		SceneCapture->HiddenActors.Empty();
		SceneCapture->HiddenComponents.Empty();
		SceneCapture->bCaptureEveryFrame = false;
		SceneCapture->bCaptureOnMovement = false;
		SceneCapture->bAlwaysPersistRenderingState = true;
		SceneCapture->bUseRayTracingIfEnabled = false;
		SceneCapture->MaxViewDistanceOverride = 0.f;
		SceneCapture->CaptureSortPriority = 1;
		SceneCapture->FOVAngle = 20.f;
	}

	ViewSlot.MeshComponent = ViewMesh;
	ViewSlot.SceneCapture = SceneCapture;
}

void ASC_Test::BeginPlay()
{
	Super::BeginPlay();
}

void ASC_Test::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	TrySetupSlotRenderTarget();

	FLCViewerCaptureSlot& slot = ViewSlot;
	USceneCaptureComponent2D* pActiveCapture = nullptr;
	pActiveCapture = slot.SceneCapture.Get();
	if (pActiveCapture && pActiveCapture->TextureTarget)
	{
		pActiveCapture->CaptureScene();
	}
}

void ASC_Test::EnableCapture(int32 index, UImage* imageWidget)
{
	ViewSlot.BoundImage = imageWidget;
	ViewSlot.bPendingSetup = (imageWidget != nullptr);
}

void ASC_Test::TrySetupSlotRenderTarget()
{
	FLCViewerCaptureSlot& slot = ViewSlot;
	if (!slot.bPendingSetup || !slot.BoundImage.IsValid())
	{
		return;
	}

	UImage* imageWidget = slot.BoundImage.Get();
	if (!imageWidget)
	{
		slot.bPendingSetup = false;
		return;
	}

	const FVector2D pixelSize =
		imageWidget->GetCachedGeometry().GetAbsoluteSize() * CaptureTextureRate;
	if (pixelSize.X <= 0.f || pixelSize.Y <= 0.f)
	{
		return;
	}

	int32 width = FMath::Max(2, FMath::RoundToInt(pixelSize.X));
	int32 height = FMath::Max(2, FMath::RoundToInt(pixelSize.Y));
	width = FMath::DivideAndRoundUp(width, 2) * 2;
	height = FMath::DivideAndRoundUp(height, 2) * 2;

	UTextureRenderTarget2D* rt = NewObject<UTextureRenderTarget2D>(this);
	if (!rt)
	{
		slot.bPendingSetup = false;
		return;
	}

	rt->ClearColor = FLinearColor::Transparent;
	rt->RenderTargetFormat = ETextureRenderTargetFormat::RTF_RGBA8;
	rt->bForceLinearGamma = false;
	rt->bAutoGenerateMips = true;
	rt->InitAutoFormat(width, height);
	rt->AddressX = TA_Clamp;
	rt->AddressY = TA_Clamp;
	rt->Filter = CaptureTextureFilter;
	rt->UpdateResourceImmediate(true);

	slot.RenderTarget = rt;


	// SC 설정
	if (IsValid(slot.SceneCapture))
	{
		USceneCaptureComponent2D* capture = slot.SceneCapture.Get();
		capture->TextureTarget = rt;

		capture->ShowOnlyActors.Empty();
		capture->ShowOnlyComponents.Empty();

		if (USkeletalMeshComponent* pMesh = slot.MeshComponent.Get())
		{
			capture->ShowOnlyComponent(pMesh);
		}

		const FTransform camTrans = TransCam;
		capture->SetRelativeLocation(camTrans.GetLocation());
		capture->SetRelativeRotation(camTrans.Rotator());
		capture->FOVAngle = FovCam;
	}

	if (CaptureMaterialAsset)
	{
		UMaterialInstanceDynamic* mid = slot.MaterialInstance.Get();
		if (!mid)
		{
			mid = UMaterialInstanceDynamic::Create(CaptureMaterialAsset, this);
			slot.MaterialInstance = mid;
		}

		if (mid)
		{
			mid->SetTextureParameterValue(CaptureTextureParamName, rt);
			imageWidget->SetBrushFromMaterial(mid);
		}
	}

	slot.bPendingSetup = false;
}
