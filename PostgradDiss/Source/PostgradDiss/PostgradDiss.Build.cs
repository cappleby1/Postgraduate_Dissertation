using UnrealBuildTool;

public class PostgradDiss : ModuleRules
{
    public PostgradDiss(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[] {
            "Core",
            "CoreUObject",
            "Engine",
            "InputCore",
			"UMG",          
            "Slate",
            "SlateCore" 
        });

        PrivateDependencyModuleNames.AddRange(new string[] { });
    }
}
