// Copyright RemRemRemRe. All Rights Reserved.

using UnrealBuildTool;

public class RemMassAbility : ModuleRules
{
	public RemMassAbility(ReadOnlyTargetRules target) : base(target)
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

				"MassEntity",
				"MassCommon",
				"MassMovement",
				"MassSpawner",
				"MassActors",
				"DeveloperSettings",
				"GameplayTags",
				"MassAIBehavior",
				"StateTreeModule",

				"RemCommon",
				"RemMass",
				"RemUniversalData",
				"RemMassInventory",
				"RemEventScheduler",
				"RemStateTree",
			]
		);
	}
}
