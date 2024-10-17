
using UnrealBuildTool;

public class ActionCombat : ModuleRules
{
	public ActionCombat(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "AIModule" });

		PrivateDependencyModuleNames.AddRange(new string[] { "EnhancedInput", "AnimGraphRuntime" });
	}
}
