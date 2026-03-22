// Copyright RemRemRemRe. All Rights Reserved.

using UnrealBuildTool;
using Rem.BuildRule;

public class RemMass : ModuleRules
{
	public RemMass(ReadOnlyTargetRules target) : base(target)
	{
        RemSharedModuleRules.Apply(this);
		
		PrivateDependencyModuleNames.AddRange(
			[
				"Core",
				
				"CoreUObject",
				"Engine",
				
				"MassEntity",
				"MassSpawner",
				"MassActors",
				"GameplayTags",
				
				"RemCommon",
			]
		);
	}
}
