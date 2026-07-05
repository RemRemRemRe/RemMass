// Copyright RemRemRemRe, All Rights Reserved.

#pragma once

#include "Containers/StringView.h"
#include "UObject/NameTypes.h"

namespace Rem::Mass::ProcessorGroup::Name
{

inline FName Initializer{ANSITEXTVIEW("Rem.Mass.Initializer")};

inline FName Player{ANSITEXTVIEW("Rem.Mass.Player")};
inline FName SpawnProjectile{ANSITEXTVIEW("Rem.Mass.Spawn.Projectile")};
inline FName Movement{ANSITEXTVIEW("Rem.Mass.Movement")};
inline FName NearbyMonsterData{ANSITEXTVIEW("Rem.Mass.NearbyMonsterData")};
inline FName Damage{ANSITEXTVIEW("Rem.Mass.Damage")};
inline FName Respawn{ANSITEXTVIEW("Rem.Mass.Respawn")};
inline FName Experience{ANSITEXTVIEW("Rem.Mass.Experience")};
inline FName HUD{TEXTVIEW("Rem.Mass.HUD")};

}
