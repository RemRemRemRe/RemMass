// Copyright RemRemRemRe, All Rights Reserved.


namespace UnrealBuildTool.Rules
{
	public class RemMass : ModuleRules
	{
		public RemMass(ReadOnlyTargetRules target) : base(target)
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
					"MassSpawner",
					"MassActors",
					"StructUtils",
					"GameplayTags",
					
					"RemCommon",
				}
			);
		}
	}
}
