#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/TextureDefines.h"
#include "SC_Test.generated.h"


USTRUCT(BlueprintType)
struct FLCViewerCaptureSlot
{
	GENERATED_BODY()

	UPROPERTY() TObjectPtr<USkeletalMeshComponent> MeshComponent = nullptr;
	UPROPERTY() TObjectPtr<USceneCaptureComponent2D> SceneCapture = nullptr;
	UPROPERTY() TObjectPtr<UTextureRenderTarget2D> RenderTarget = nullptr;
	UPROPERTY() TObjectPtr<UMaterialInstanceDynamic> MaterialInstance = nullptr;
	UPROPERTY() TWeakObjectPtr<UImage> BoundImage = nullptr;

	UPROPERTY() bool bPendingSetup = false;
};

UCLASS()
class ASC_Test : public AActor
{
	GENERATED_BODY()

public:
	ASC_Test(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

	UFUNCTION(BlueprintCallable, Category = LC)
	void EnableCapture(int32 index, class UImage* imageWidget);


protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = LC, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class USkeletalMeshComponent> ViewMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = LC, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class USceneCaptureComponent2D> SceneCapture;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = LC, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UMaterialInterface> CaptureMaterialAsset;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = LC, meta = (AllowPrivateAccess = "true"))
	FName CaptureTextureParamName = TEXT("Texture");

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = LC, meta = (AllowPrivateAccess = "true"))
	float CaptureTextureRate = 2.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = LC, meta = (AllowPrivateAccess = "true"))
	TEnumAsByte<TextureFilter> CaptureTextureFilter = TF_Nearest;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = LC, meta = (AllowPrivateAccess = "true"))
	FTransform TransCam = FTransform::Identity;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = LC, meta = (AllowPrivateAccess = "true"))
	float FovCam = 20.f;

	UPROPERTY(Transient)
	FLCViewerCaptureSlot ViewSlot;

private:
	void TrySetupSlotRenderTarget();
};
