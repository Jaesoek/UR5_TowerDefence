// Fill out your copyright notice in the Description page of Project Settings.


#include "DetailTowerAsset.h"
#include "Tower/TowerAsset.h"
#include "DetailLayoutBuilder.h"
#include "DetailCategoryBuilder.h"
#include "DetailWidgetRow.h"
#include "Widgets/Input/SButton.h"
#include "Widgets/Input/SComboBox.h"
#include "Widgets/Text/STextBlock.h"
#include "PropertyHandle.h"
#include "Templates/SharedPointer.h"

TSharedRef<IDetailCustomization> FDetailTowerAsset::MakeInstance()
{
	return MakeShareable(new FDetailTowerAsset);
}

void FDetailTowerAsset::CustomizeDetails(IDetailLayoutBuilder& DetailBuilder)
{
	IDetailCategoryBuilder& Category = DetailBuilder.EditCategory("Attack Module");

	TSharedRef<IPropertyHandle> ClassHandle =
		DetailBuilder.GetProperty(GET_MEMBER_NAME_CHECKED(UTowerAsset, AttackCompClass));

	TSharedRef<IPropertyHandle> TargetHandle =
		DetailBuilder.GetProperty(GET_MEMBER_NAME_CHECKED(UTowerAsset, BulletMesh));

	Category.AddProperty(ClassHandle);
	Category.AddProperty(TargetHandle)
		.Visibility(TAttribute<EVisibility>::CreateLambda([ClassHandle]()
			{
				UObject* Selected = nullptr;
				ClassHandle->GetValue(Selected);
				if (Selected && Selected->GetName().Contains(TEXT("Projectile")))
				{
					return EVisibility::Visible;
				}
				return EVisibility::Collapsed;
			}));

	// Refresh
	ClassHandle->SetOnPropertyValueChanged(
		FSimpleDelegate::CreateLambda(
			[&DetailBuilder]()
			{
				DetailBuilder.ForceRefreshDetails();
			}
		)
	);
}
