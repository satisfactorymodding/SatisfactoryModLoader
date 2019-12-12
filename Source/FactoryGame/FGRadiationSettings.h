// Copyright 2016-2019 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "Array.h"
#include "SubclassOf.h"
#include "UObject/Class.h"

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "FGRadioactivitySubsystem.h"
#include "Resources/FGResourceNode.h"
#include "FGRadiationSettings.generated.h"

USTRUCT( BlueprintType )
struct FRadiationVisualization
{
	GENERATED_BODY()
public:
	FRadiationVisualization(){}
	FRadiationVisualization( FName Case, int32 ItemAmount, float Decay, int32 UnitMultiplier ) :
		Case( Case ),
		UnitMultiplier( UnitMultiplier ),
		ItemAmount( ItemAmount ),
		Decay( Decay )
	{}
	

	UPROPERTY( BlueprintReadWrite, EditAnywhere )
	FName Case;

	UPROPERTY( BlueprintReadWrite, EditAnywhere )
	int32 ItemAmount;

	UPROPERTY( BlueprintReadWrite, EditAnywhere )
	float Decay;

	UPROPERTY( BlueprintReadWrite, EditAnywhere )
	int32 UnitMultiplier;

	UPROPERTY( BlueprintReadOnly, VisibleAnywhere, meta = ( DisplayName = "Highest Intensity (Normalized Value)" ) )
	float HighestIntensity;

	UPROPERTY( BlueprintReadOnly, VisibleAnywhere )
	float HighestDamageInterval;

	UPROPERTY( BlueprintReadOnly, VisibleAnywhere )
	float DistanceForHighestIntensity;

	UPROPERTY( BlueprintReadOnly, VisibleAnywhere )
	float DistanceForNoticableIntensity;

};

/**
 * 
 */
UCLASS( config = Game, defaultconfig, meta = ( DisplayName = "Radiation") )
class FACTORYGAME_API UFGRadiationSettings : public UDeveloperSettings
{
	GENERATED_BODY()

#if WITH_EDITOR
	virtual void PostEditChangeProperty( FPropertyChangedEvent& PropertyChangedEvent ) override;
	virtual void PostInitProperties() override;
#endif

public: 

	UPROPERTY( EditAnywhere, config, Category = Radiation, meta = ( ToolTip = "The type of damage radiation deals" ) )
	TSubclassOf< class UFGDamageType > mRadiationDamageType;
	
	UPROPERTY( EditAnywhere, config, Category = Radiation, meta = ( ToolTip = "The max accumulated intensity that can be registered from radioactive emitters" ) )
	float mMaxIntensity;

	UPROPERTY( EditAnywhere, config, Category = Radiation, meta = ( ToolTip = "The minimum damage interval ( 0.2 = every 5 second, 10.0 = 10 times per second )",
																	ClampMin = "0.01", ClampMax = "30.0", UIMin = "0.01", UIMax = "30.0" ) )
	float mMinDamageInterval;

	UPROPERTY( EditAnywhere, config, Category = Radiation, meta = ( ToolTip = "The maximum damage interval ( 0.2 = every 5 second, 10.0 = 10 times per second )",
																	ClampMin = "0.01", ClampMax = "30.0", UIMin = "0.01", UIMax = "30.0" ) )
	float mMaxDamageInterval;

	UPROPERTY( EditAnywhere, config, Category = Radiation, meta = ( ToolTip = "How much damage we should apply during each damage event. Once per interval",
																	ClampMin = "0.01", ClampMax = "5.0", UIMin = "0.01", UIMax = "5.0" ) )
	float mDamagePerInterval;

	UPROPERTY( EditAnywhere, config, Category = Radiation, meta = ( ToolTip = "The closest we can get to any radiation source. This can greatly limit the radiation received from items in the players inventory",
																	ClampMin = "0.1", ClampMax = "2", UIMin = "0.1", UIMax = "2" ) )
	float mMinDistanceToSource;

	UPROPERTY( EditAnywhere, config, Category = Radiation, meta = ( ToolTip = "Radiation levels lower than this are ignored. (Legacy value value was 0.0001)",
																	ClampMin = "0.000001", ClampMax = "0.2", UIMin = "0.000001", UIMax = "0.2" ) )
	float mMinRadiationThreshold;
	
	UPROPERTY( EditAnywhere, config, Category = Radiation, meta = ( ToolTip = "How much radiation falls off during distance (0.0 - 0.2). (Legacy value was 0.08)",
																	ClampMin = "0.0", ClampMax = "0.2", UIMin = "0.0", UIMax = "0.2" ) )
	float mRadiationFalloffByDistance;

	UPROPERTY( EditAnywhere, config, Category = Radiation, meta = ( ToolTip = "The amount of items of the nodes resource class that each purity level will radiate equivalent to (e.g. A value of 100 will make an uranium node radiate roughly equivalent to 100 uranium ores)" ) )
	TMap<TEnumAsByte<EResourcePurity>, int32> mNodeRadiationPurityAmounts;

private:

#if WITH_EDITORONLY_DATA
	UPROPERTY( EditAnywhere, Category = "VISUALIZATION ONLY", meta = ( ToolTip = "Check this to calculate values. Will reset itself afterwards" ) )
	bool mCalculateNewValues;

	UPROPERTY( EditAnywhere, Category = "VISUALIZATION ONLY", meta = ( ToolTip = "Examples of emitter values. Doesn't affect gameplay and isn't saved" ) )
	TArray<FRadiationVisualization> mVisualizations;
#endif

};
