// Copyright RemRemRemRe. All Rights Reserved.

using UnrealBuildTool;
using Rem.BuildRule;

public class RemMassAbility : ModuleRules
{
	public RemMassAbility(ReadOnlyTargetRules target) : base(target)
	{
        RemSharedModuleRules.Apply(this);

		PrivateDependencyModuleNames.AddRange(
			[
				"Core",
				"CoreUObject",
				"Engine",

				"MassEntity",
				"MassCommon",
				"MassMovement",
				"MassSpawner",
				"MassActors",
				"DeveloperSettings",
				"GameplayTags",
				"MassAIBehavior",
				"StateTreeModule",

				"RemCommon",
				"RemMass",
				"RemMassInventory",
			]
		);
	}
}
