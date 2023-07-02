// Copyright RemRemRemRe, All Rights Reserved.


namespace UnrealBuildTool.Rules
{
	public class RemMassHUD : ModuleRules
	{
		public RemMassHUD(ReadOnlyTargetRules target) : base(target)
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
					"UMG",
					
					"MassEntity",
					"MassSpawner",
					"MassActors",
					"StructUtils",
					"GameplayTags",
					"DeveloperSettings",
					
					"RemCommon",
					"RemMass",
					"RemMassAbility",
					"RemMassMovement",
					"RemWidgetComponent",
					"RemUniversalData",
				}
			);
		}
	}
}
