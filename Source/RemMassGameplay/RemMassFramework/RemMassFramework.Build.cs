// Copyright RemRemRemRe. All Rights Reserved.

using UnrealBuildTool;
using Rem.BuildRule;

public class RemMassFramework : ModuleRules
{
	public RemMassFramework(ReadOnlyTargetRules target) : base(target)
	{
        RemSharedModuleRules.Apply(this);
		
		PrivateDependencyModuleNames.AddRange(
			[
				"Core",
				"CoreUObject",
				"Engine",
				
				"DeveloperSettings",
				"MassActors",
				"GameplayAbilities",
				"MassEntity",
				
				"RemCommon",
			]
		);
	}
}
