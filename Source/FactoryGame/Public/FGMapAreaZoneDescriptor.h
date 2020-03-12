#pragma once
#include "UnrealString.h"
#include "UObject/Class.h"

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
	/** Descriptive name of the zone type, this will be sent to music so that it can depend on it */
	UPROPERTY( EditDefaultsOnly, Category = "Description" )
	FString mZoneType;

public:
	FORCEINLINE ~UFGMapAreaZoneDescriptor() = default;
};
