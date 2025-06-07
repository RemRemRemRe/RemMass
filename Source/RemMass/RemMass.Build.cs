// Copyright RemRemRemRe. All Rights Reserved.

using UnrealBuildTool;

public class RemMass : ModuleRules
{
	public RemMass(ReadOnlyTargetRules target) : base(target)
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
				"MassSpawner",
				"MassActors",
				"GameplayTags",
				
				"RemCommon",
			]
		);
	}
}
