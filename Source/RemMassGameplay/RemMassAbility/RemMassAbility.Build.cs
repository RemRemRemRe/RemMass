// Copyright RemRemRemRe, All Rights Reserved.


namespace UnrealBuildTool.Rules
{
	public class RemMassAbility : ModuleRules
	{
		public RemMassAbility(ReadOnlyTargetRules target) : base(target)
		{
			PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
			ShadowVariableWarningLevel = WarningLevel.Error;
			IncludeOrderVersion = EngineIncludeOrderVersion.Latest;
			DefaultBuildSettings = BuildSettingsVersion.Latest;
			CppStandard = CppStandardVersion.Cpp20;

			bEnableNonInlinedGenCppWarnings = true;

			PrivateDependencyModuleNames.AddRange(
				new[]
				{
					"Core",
					"CoreUObject",
					"Engine",
					
					"MassEntity",
					"MassCommon",
					"MassSpawner",
					"StructUtils",
					"DeveloperSettings",
					"GameplayTags",
					
					"RemCommon",
					"RemMass",
					"RemUniversalData",
				}
			);
		}
	}
}
