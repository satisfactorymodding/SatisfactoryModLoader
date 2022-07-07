// Copyright 2016-2021 Coffee Stain Studios. All Rights Reserved.

#pragma once

UENUM( BlueprintType )
enum class EWeaponState : uint8
{
	EWS_Unequipped		UMETA( displayName = "Unequipped" ),
	EWS_Standby			UMETA( displayName = "Standby" ),
	EWS_NeedReload		UMETA( displayName = "Need Reload" ),
	EWS_Reloading		UMETA( displayName = "Reloading" ),
	EWS_Firing			UMETA( displayName = "Firing" ),
};