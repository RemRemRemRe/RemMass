// Copyright RemRemRemRe. All Rights Reserved.

using UnrealBuildTool;

public class RemMassFramework : ModuleRules
{
	public RemMassFramework(ReadOnlyTargetRules target) : base(target)
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
				
				"DeveloperSettings",
				"MassActors",
				"GameplayAbilities",
				"MassEntity",
				
				"RemCommon",
				"RemInputHandling",
				"RemUniversalData",
			}
		);
	}
}
