// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Templates/SubclassOf.h"
#include "FGCreatureFamily.generated.h"

UENUM( BlueprintType )
enum class ECreatureFamilyHostility : uint8
{
	CFH_Neutral		UMETA( displayName = "Neutral" ),
	CFH_Friendly	UMETA( displayName = "Friendly" ),
	CFH_Hostile		UMETA( displayName = "Hostile" )
};

/**
 * Class used in order to establish relationships between different families / species of creatures.
 */
UCLASS( BlueprintType, Blueprintable )
class FACTORYGAME_API UFGCreatureFamily : public UObject
{
	GENERATED_BODY()
public:
	UFGCreatureFamily();
	
	/** What sort of relationship this family has with the specified one. */
	UFUNCTION( BlueprintPure, Category = "Creature Family" )
	ECreatureFamilyHostility GetHostilityTowards( TSubclassOf< UFGCreatureFamily > otherFamily ) const;

protected:
	/** Relationship with other families. */
	UPROPERTY( EditDefaultsOnly, Category = "Creature Family" )
	TMap< TSubclassOf< UFGCreatureFamily >, ECreatureFamilyHostility > mFamilyHostility;

	/** Default response to other creature families, unless otherwise specified. */
	UPROPERTY( EditDefaultsOnly, Category = "Creature Family" )
	ECreatureFamilyHostility mDefaultResponse;
};
