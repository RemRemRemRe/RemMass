// Copyright RemRemRemRe, All Rights Reserved.

#pragma once

#include "RemMassInventoryItemState.generated.h"

/**
 * Item State
 */
UENUM(BlueprintType)
enum class ERemMassInventoryItemState : uint8
{
	/** A "idle" state, ready to be pick up, same semantics as in stock */
	Grounded,
    
	/** The state after you request to pick it up, and before it enter your inventory. eg "it flying to you" */
	Picking,
    
	/** It's picked up and lied in the inventory */
	Picked,
    
	/** Swapping two items inside an inventory */
	Swapping,
    
	/** Performing a use operation on this item or been equipped */
	Using,
    
	/** This item has been used */
	Used,
    
	/** The state after you request to drop it, and before it's down on the ground. eg "it flying to the ground" */
	Dropping,
    
	//Dropped, // Dropped item would on the ground
    
	/** It's dealing with operation canceling */
	Canceling,
};
