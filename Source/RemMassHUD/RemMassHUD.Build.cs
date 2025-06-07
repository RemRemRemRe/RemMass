// Copyright RemRemRemRe. All Rights Reserved.

using UnrealBuildTool;

public class RemMassHUD : ModuleRules
{
	public RemMassHUD(ReadOnlyTargetRules target) : base(target)
	{
		CppCompileWarningSettings.ShadowVariableWarningLevel = WarningLevel.Error;
		IncludeOrderVersion = EngineIncludeOrderVersion.Latest;
		DefaultBuildSettings = BuildSettingsVersion.Latest;
		CppStandard = CppStandardVersion.EngineDefault;
		CppCompileWarningSettings.UnsafeTypeCastWarningLevel = WarningLevel.Warning;
		
		CppCompileWarningSettings.NonInlinedGenCppWarningLevel = WarningLevel.Warning;
		bUseUnity = false;
		
		PrivateDependencyModuleNames.AddRange(
			[
				"Core",
				"CoreUObject",
				"Engine",
				"UMG",
				
				"MassEntity",
				"MassSpawner",
				"MassActors",
				"GameplayTags",
				"DeveloperSettings",
				
				"RemCommon",
				"RemMass",
				"RemMassAbility",
				"RemMassMovement",
				"RemWidgetComponent",
			]
		);
	}
}
