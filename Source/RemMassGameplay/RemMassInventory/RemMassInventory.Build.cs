// Copyright RemRemRemRe. All Rights Reserved.

using UnrealBuildTool;
using Rem.BuildRule;

public class RemMassInventory : ModuleRules
{
	public RemMassInventory(ReadOnlyTargetRules target) : base(target)
	{
        RemSharedModuleRules.Apply(this);
		
		PrivateDependencyModuleNames.AddRange(
			[
				"Core",
				"CoreUObject",
				"Engine",
				
				"MassEntity",
				"MassSpawner",
				"GameplayTags",
				
				"RemMass",
				"RemCommon",
			]
		);
	}
}
