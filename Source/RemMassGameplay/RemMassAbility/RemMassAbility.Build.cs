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
					
					"MassEntity",
					"MassCommon",
					"MassMovement",
					"MassSpawner",
					"MassActors",
					"StructUtils",
					"DeveloperSettings",
					"GameplayTags",
					"MassAIBehavior",
					"StateTreeModule",
					
					"RemCommon",
					"RemMass",
					"RemUniversalData",
					"RemMassInventory",
					"RemEventScheduler",
				}
			);
		}
	}
}
