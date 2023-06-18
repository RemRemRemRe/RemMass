// Copyright Epic Games, Inc. All Rights Reserved.


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
			CppStandard = CppStandardVersion.Cpp20;

			bEnableNonInlinedGenCppWarnings = true;

			PrivateDependencyModuleNames.AddRange(
				new[]
				{
					"Core",
					/*"CoreUObject",
					"Engine",*/
					
					/*"Slate",
					"SlateCore",
					"UnrealEd",
					"PropertyEditor",
					"EditorStyle",
					"InputCore",*/
					
					/*"UMG",*/
					
					/*"RemCommon",*/
					
					// ... add private dependencies that you statically link with here ...
				}
			);
		}
	}
}
