// Copyright RemRemRemRe, All Rights Reserved.

#pragma once

#include "Containers/StringView.h"
#include "UObject/NameTypes.h"

namespace Rem::Mass::ProcessorGroup::Name
{

	inline FName Initializer{TEXTVIEW("Rem.Mass.Initializer")};

	inline FName Player{TEXTVIEW("Rem.Mass.Player")};
	inline FName SpawnProjectile{TEXTVIEW("Rem.Mass.Spawn.Projectile")};
	inline FName Movement{TEXTVIEW("Rem.Mass.Movement")};
	inline FName NearbyMonsterData{TEXTVIEW("Rem.Mass.NearbyMonsterData")};
	inline FName Damage{TEXTVIEW("Rem.Mass.Damage")};
	inline FName Respawn{TEXTVIEW("Rem.Mass.Respawn")};
	inline FName Experience{TEXTVIEW("Rem.Mass.Experience")};
	inline FName HUD{TEXTVIEW("Rem.Mass.HUD")};

}
