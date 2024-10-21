
using UnrealBuildTool;
using System.Collections.Generic;

public class ActionCombatEditorTarget : TargetRules
{
	public ActionCombatEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V4;
		IncludeOrderVersion = EngineIncludeOrderVersion.Unreal5_3;
		ExtraModuleNames.Add("ActionCombat");
	}
}
