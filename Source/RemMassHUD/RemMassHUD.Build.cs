// Copyright RemRemRemRe. All Rights Reserved.

using UnrealBuildTool;
using Rem.BuildRule;

public class RemMassHUD : ModuleRules
{
	public RemMassHUD(ReadOnlyTargetRules target) : base(target)
	{
        RemSharedModuleRules.Apply(this);
		
		PrivateDependencyModuleNames.AddRange(
			[
				"Core",
				"CoreUObject",
				"Engine",
				"UMG",
				
				"MassEntity",
				"MassSpawner",
				"MassActors",
				"GameplayTags",
				"DeveloperSettings",
				
				"RemCommon",
				"RemMass",
				"RemMassAbility",
				"RemMassMovement",
				"RemWidgetComponent",
			]
		);
	}
}
