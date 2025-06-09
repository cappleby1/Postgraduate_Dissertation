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
            "UMG",         // Add this
            "Slate",       // Add this if you use Slate UI widgets
            "SlateCore"    // Add this if you use Slate UI widgets
        });

        PrivateDependencyModuleNames.AddRange(new string[] { });

        // If you want, uncomment and add other modules as needed
    }
}
