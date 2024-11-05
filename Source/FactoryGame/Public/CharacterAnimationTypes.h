// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "CharacterAnimationTypes.generated.h"

UENUM( BlueprintType )
enum class EArmEquipment : uint8
{
	AE_None,
	AE_ChainSaw,
	AE_RebarGun,
	AE_BuildGun,
	AE_Nobelisk,
	AE_ResourceScanner,
	AE_Rifle,
	AE_ColorGun,
	AE_OneHandEquipment,
	AE_Consumables,
	AE_ObjectScanner,
	AE_PortableMiner,
	AE_StunSpear,
	AE_ShockShank,
	AE_ResourceCollector,
	AE_Generic1Hand,
	AE_Generic2Hand,
	AE_BoomBox
};


UENUM( BlueprintType )
enum class EBackEquipment : uint8
{
	BE_None,
	BE_Jetpack
};