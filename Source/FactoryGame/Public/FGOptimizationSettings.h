// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "FGOptimizationSettings.generated.h"


UENUM( BlueprintType )
enum class EDistanceCullCategory : uint8
{
	FGDDC_NEVERCULL					UMETA( DisplayName = "Never distance cull",					ToolTip = "Should never distance cull, do not use unless you are sure its needed"),
	FGDDC_Gameplay					UMETA( DisplayName = "Buildings - Gameplay(NEVER CULL)",	ToolTip = "Trading Post, Space elevator etc." ),
	FGDCC_BuildingSmall				UMETA( DisplayName = "Building - Small",					ToolTip = "Power poles, Player storage etc." ),
	FGDCC_BuildingMedium			UMETA( DisplayName = "Building - Medium",					ToolTip = "Constructors, Assemblers." ),
	FGDCC_BuildingBig				UMETA( DisplayName = "Building - Big",						ToolTip = "Nuclear power plant, Coal generators etc." ),
	FGDCC_BuildingSupports			UMETA( DisplayName = "Building Supports",					ToolTip = "Factory legs, feet etc."),
	FGDCC_Infrastructure			UMETA( DisplayName = "infrastructure",						ToolTip = "Foundations, Walls etc." ),
	FGDDC_ProductionIndicators		UMETA( DisplayName = "Production Indicator",				ToolTip = "Production Indicators etc."),
	FGDDC_Decor						UMETA( DisplayName = "Decor",								ToolTip = "Non essentials."),
	FGDDC_MAX						UMETA( Hidden = true)
};

		
USTRUCT( BlueprintType )
struct FCullSettings
{
	GENERATED_BODY()

public:
	UPROPERTY( BlueprintReadWrite, EditAnywhere )
	int32 mMinDistance;

	UPROPERTY( BlueprintReadWrite, EditAnywhere )
	int32 mMaxDistance;

	UPROPERTY( BlueprintReadWrite, EditAnywhere )
	int32 mInstanceDestroyDistance;

	FCullSettings()
	{
		mMinDistance = -1;
		mMaxDistance = -1;
		mInstanceDestroyDistance = -1;
	}

	FCullSettings( int32 MinDistance, int32 MaxDistance, int32 InstanceDestroyDistance )
	{
		mMinDistance =				MinDistance;
		mMaxDistance =				MaxDistance;
		mInstanceDestroyDistance =	InstanceDestroyDistance;
	}

	FVector2D GetMinMax() const { return FVector2D( mMinDistance, mMaxDistance ); }
};


UCLASS( config = Game, defaultconfig, meta = (DisplayName = "Satisfactory Optimization settings") )
class FACTORYGAME_API UFGOptimizationSettings : public UDeveloperSettings
{
	GENERATED_BODY()

#if WITH_EDITOR
	virtual void PostInitProperties() override
	{
		Super::PostInitProperties();

		for ( uint8 i = 0; i < ( uint8 ) EDistanceCullCategory::FGDDC_MAX; i++)
		{
			if ( !mCullDistances.Contains( ( EDistanceCullCategory ) i) )
			{
				mCullDistances.Add( ( EDistanceCullCategory ) i, FCullSettings() );
			}
		}
	};
#endif

public:
	UPROPERTY( EditAnywhere, config )
	TMap< EDistanceCullCategory, FCullSettings > mCullDistances;

public:
	/** Returns associated cull distance.**/
	FVector2D GetCullDistanceByCategory( EDistanceCullCategory Type, float Modifier ) const
	{
		if ( mCullDistances.Contains( Type ) )
		{
			FVector2D Dist = mCullDistances[Type].GetMinMax();
			return Dist * Modifier;
		}

		return FVector2D( -1, -1 );
	};
};
