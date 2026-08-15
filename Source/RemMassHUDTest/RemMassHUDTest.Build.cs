// Copyright RemRemRemRe. 2026. All Rights Reserved.

using UnrealBuildTool;
using Rem.BuildRule;

public class RemMassHUDTest : ModuleRules
{
	public RemMassHUDTest(ReadOnlyTargetRules target) : base(target)
	{
		RemSharedModuleRules.Apply(this);

		PrivateDependencyModuleNames.AddRange(
			[
				"Core",
				"CoreUObject",
				"Engine",
				"UMG",

				"GameplayTags",
				"MassCore",
				"MassEntity",
				"MassSpawner",

				"RemCommon",
				"RemMass",
				"RemMassHUD",
				"RemWidgetComponent",
			]
		);
	}
}
