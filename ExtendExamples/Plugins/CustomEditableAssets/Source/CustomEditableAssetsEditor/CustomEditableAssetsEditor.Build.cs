using UnrealBuildTool;

public class CustomEditableAssetsEditor : ModuleRules
{
	public CustomEditableAssetsEditor(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				"AssetTools",
				"SlateCore",
				"Slate",
				"UnrealEd",
				"AssetDefinition",
				"CustomEditableAssetsRuntime",
			}
		);

		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"CoreUObject",
				"Engine",
				"CustomEditableAssetsRuntime",
				"AdvancedPreviewScene",
			}
		);
	}
}