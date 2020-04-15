// Copyright 2016-2019 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "Array.h"
#include "SubclassOf.h"
#include "UObject/Class.h"

#include "CoreMinimal.h"
#include "AvailabilityDependencies/FGAvailabilityDependency.h"
#include "FGSchematicPurchasedDependency.generated.h"

/**
 * Dependency that's met if we have purchased all the given schematics
 */
UCLASS( Blueprintable, abstract )
class FACTORYGAME_API UFGSchematicPurchasedDependency : public UFGAvailabilityDependency
{
	GENERATED_BODY()
	
public:
	bool AreDependenciesMet( UObject* worldContext ) const override;

	UFUNCTION( BlueprintCallable, BlueprintPure = false, Category = "Dependency" )
	void GetSchematics( TArray< TSubclassOf< class UFGSchematic > >& out_schematics ) const;

#if WITH_EDITOR
	void Init( TArray< TSubclassOf< class UFGSchematic > > schematics, bool requireAllSchematicsToBePurchased );
#endif

protected:
	/** The schematics that should have been purchased for this dependency to be met */
	UPROPERTY( EditDefaultsOnly )
	TArray< TSubclassOf< class UFGSchematic > > mSchematics;

	/** Do we need to have purchased all of the schematics to or is it enough with just one of them */
	UPROPERTY( EditDefaultsOnly )
	bool mRequireAllSchematicsToBePurchased;


public:
	FORCEINLINE ~UFGSchematicPurchasedDependency() = default;
};
