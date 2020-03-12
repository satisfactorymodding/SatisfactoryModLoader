#pragma once
#include "UObject/Class.h"

#include "GameFramework/Actor.h"
#include "HologramSplinePathMode.generated.h"

/**
* Enum for the different types of spline placement
*/
UENUM( BlueprintType )
enum class EHologramSplinePathMode : uint8
{
	HSPM_AUTO = 0				UMETA( DisplayName = "Auto" ),
	HSPM_STRAIGHT_HORZ = 1		UMETA( DisplayName = "Straight Horizontal" ),
	HSPM_STRAIGHT_VERT = 2		UMETA( DisplayName = "Straight Vertical" ),
	HSPM_HORZ_TO_VERT = 3		UMETA( DisplayName = "Horizontal to Vertical" ),
	HSPM_VERT_TO_HORZ = 4		UMETA( DisplayName = "Vertical to Horizontal" ),
	HSPM_PATH_FIND = 5			UMETA( DisplayName = "Path Find" ),
	HSPM_AUTO_2D = 6			UMETA( DisplayName = "Auto 2D/Conveyor Mode" ),
	HSPM_NOODLE = 7			UMETA( DisplayName = "Noodle" ),
	HSPM_MAX					UMETA( Hidden )
};


