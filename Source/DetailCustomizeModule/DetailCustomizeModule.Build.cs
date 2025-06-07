using UnrealBuildTool;

public class DetailCustomizeModule : ModuleRules
{
    public DetailCustomizeModule(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

        PrivateDependencyModuleNames.AddRange(new string[] {
            "Core", "CoreUObject", "Engine", "UnrealEd",
            "PropertyEditor", "Slate", "SlateCore", "EditorStyle", "TowerDefence"
        });
        
        PublicIncludePaths.Add("DetailCustomizeModule/Public");

        PrivateIncludePaths.Add("DetailCustomizeModule/Private");
    }
}