// Copyright RemRemRemRe. All Rights Reserved.

using UnrealBuildTool;
using Rem.BuildRule;

public class RemMassMovement : ModuleRules
{
	public RemMassMovement(ReadOnlyTargetRules target) : base(target)
	{
        RemSharedModuleRules.Apply(this);
		
		PrivateDependencyModuleNames.AddRange(
			[
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
			]
		);
	}
}
