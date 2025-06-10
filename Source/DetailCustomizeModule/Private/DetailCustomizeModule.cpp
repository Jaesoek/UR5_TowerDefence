#include "DetailCustomizeModule.h"
#include "Modules/ModuleManager.h"
#include "DetailGrid.h"

IMPLEMENT_MODULE(FDetailCustomizeModule, DetailCustomizeModule)

void FDetailCustomizeModule::StartupModule()
{
	FPropertyEditorModule& PropertyEditor =
		FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");
	PropertyEditor.RegisterCustomClassLayout("Grid",
		FOnGetDetailCustomizationInstance::CreateStatic(&FDetailGrid::MakeInstance));
}

void FDetailCustomizeModule::ShutdownModule()
{
}
