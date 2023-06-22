// Copyright RemRemRemRe, All Rights Reserved.


namespace UnrealBuildTool.Rules
{
	public class RemMassMovement : ModuleRules
	{
		public RemMassMovement(ReadOnlyTargetRules target) : base(target)
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
					
					"MassMovement",
					"MassLOD",
					
					"RemCommon",
					"RemMass",
				}
			);
		}
	}
}
