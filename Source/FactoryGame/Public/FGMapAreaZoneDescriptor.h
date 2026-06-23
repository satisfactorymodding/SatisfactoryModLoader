// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "FGMapAreaZoneDescriptor.generated.h"

/**
 * Used by different zones so that different zones can have different audio
 */
UCLASS(abstract, Blueprintable)
class FACTORYGAME_API UFGMapAreaZoneDescriptor : public UObject
{
	GENERATED_BODY()
public:
	UFUNCTION( BlueprintPure, Category = "MapAreaZone" )
	void GetZoneType( FString& out_zoneType ) const{ out_zoneType = mZoneType; }
protected:
	/** WARNING! This is fake and not set properly anywhere. This class should probably be removed. */
	/** Descriptive name of the zone type, this will be sent to music so that it can depend on it */
	UPROPERTY( EditDefaultsOnly, Category = "Description" )
	FString mZoneType;
};
