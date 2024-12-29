// Copyright RemRemRemRe. All Rights Reserved.

using UnrealBuildTool;

public class RemMassHUD : ModuleRules
{
	public RemMassHUD(ReadOnlyTargetRules target) : base(target)
	{
		ShadowVariableWarningLevel = WarningLevel.Error;
		IncludeOrderVersion = EngineIncludeOrderVersion.Latest;
		DefaultBuildSettings = BuildSettingsVersion.Latest;
		CppStandard = CppStandardVersion.EngineDefault;
		UnsafeTypeCastWarningLevel = WarningLevel.Warning;
		
		bEnableNonInlinedGenCppWarnings = true;
		bUseUnity = false;
		
		PrivateDependencyModuleNames.AddRange(
			new[]
			{
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
			}
		);
	}
}
