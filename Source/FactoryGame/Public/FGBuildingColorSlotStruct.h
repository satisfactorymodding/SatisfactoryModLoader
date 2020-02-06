#pragma once

#include "NoExportTypes.h"
#include "FGBuildingColorSlotStruct.generated.h"

USTRUCT()
struct FACTORYGAME_API FFGBuildingColorSlotStruct
{
	GENERATED_USTRUCT_BODY()
	
	UPROPERTY()
	FColor primary;

	UPROPERTY()
	FColor secondary;

	inline bool operator==( const FFGBuildingColorSlotStruct& b ) const
	{
		return primary == b.primary && secondary == b.secondary;
	}

	inline const FFGBuildingColorSlotStruct& operator=( const FFGBuildingColorSlotStruct& b )
	{
		primary = b.primary;
		secondary = b.secondary;
		return *this;
	}

	void set( FColor prim, FColor sec )
	{
		primary = prim;
		secondary = sec;
	}
};

