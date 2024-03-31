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
					"StructUtils",
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
}
