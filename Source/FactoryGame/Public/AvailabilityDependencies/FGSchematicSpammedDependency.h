// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AvailabilityDependencies/FGAvailabilityDependency.h"
#include "FGSchematic.h"
#include "FGSchematicSpammedDependency.generated.h"

/**
 * 
 */
UCLASS( Blueprintable, abstract )
class FACTORYGAME_API UFGSchematicSpammedDependency : public UFGAvailabilityDependency
{
	GENERATED_BODY()

public:
#if WITH_EDITOR
	virtual FString ToString() const override;
	virtual void FromString( const FString& inString ) override;
#endif

	/**
	 * Checks if we've purchased enough of a certain type of schematic in a time interval (mTimeInterval) 
	 * Returns true if we hit or exceed the mRequiredPurchaseCount in that timeframe
	 */
	bool DoesPurchaseHistoryMatchDependency( const double currentWorldTime, const TMap<ESchematicType, TArray<double>>& schematicTypePurchaseHistory ) const;
	
protected:
	UPROPERTY( EditDefaultsOnly, Category="Dependency" )
	ESchematicType mSchematicType;

	UPROPERTY( EditDefaultsOnly, Category="Dependency", meta = ( ToolTip = "Defined in seconds" ) )
	float mTimeInterval;
	
	UPROPERTY( EditDefaultsOnly, Category="Dependency" )
	int32 mRequiredPurchaseCount;
};
