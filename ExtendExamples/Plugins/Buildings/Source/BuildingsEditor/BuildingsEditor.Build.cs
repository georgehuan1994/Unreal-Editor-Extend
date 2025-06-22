using UnrealBuildTool;

public class BuildingsEditor : ModuleRules
{
    public BuildingsEditor(ReadOnlyTargetRules Target) : base(Target)
    {
        
        PublicDependencyModuleNames.AddRange(
            new string[]
            {
                "InputCore",
                "Buildings",
            }
        );

        PrivateDependencyModuleNames.AddRange(
            new string[]
            {
                "Core",
                "CoreUObject",
                "Engine",
                "UnrealEd",
                "Slate",
                "SlateCore",
                "Buildings",
                "AssetDefinition",
                "AdvancedPreviewScene"
            }
        );
    }
}