// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "FGAvailabilityDependency.h"
#include "FGSchematicPurchasedDependency.generated.h"

/**
 * Dependency that's met if we have purchased the given schematics
 */
UCLASS( Blueprintable, abstract )
class FACTORYGAME_API UFGSchematicPurchasedDependency : public UFGAvailabilityDependency
{
	GENERATED_BODY()
	
public:
	virtual bool AreDependenciesMet( UObject* worldContext ) const override;

	UFUNCTION( BlueprintCallable, BlueprintPure = false, Category = "Dependency" )
	void GetSchematics( TArray< TSubclassOf< class UFGSchematic > >& out_schematics ) const;

#if WITH_EDITOR
	void Init( TArray< TSubclassOf< class UFGSchematic > > schematics, bool requireAllSchematicsToBePurchased );
	virtual FString ToString() const override;
	virtual void FromString( const FString& inString ) override;
#endif
	

protected:
	/** The schematics that is required for this dependency to be met */
	UPROPERTY( EditDefaultsOnly, Category="Dependency" )
	TArray< TSubclassOf< class UFGSchematic > > mSchematics;

	/**
	 * Specifies whether all schematics in the list is required to meet the dependency condition.
	 * Misleading name but it was added before UFGSchematicNotPurchasedDependency was added but it made sense then.
	 * In the context of UFGSchematicPurchasedDependency, it denotes that all given schematics should be purchased.
	 * In the context of UFGSchematicNotPurchasedDependency, it denotes that all given schematics should not be purchased.
	 */
	UPROPERTY( EditDefaultsOnly, Category="Dependency", meta = (DisplayName = "RequireAllSchematics") )
	bool mRequireAllSchematicsToBePurchased;

};

/**
 * Inverted version of UFGSchematicPurchasedDependency
 */
UCLASS( Blueprintable, abstract )
class FACTORYGAME_API UFGSchematicNotPurchasedDependency : public UFGSchematicPurchasedDependency
{
	GENERATED_BODY()
	
public:
	virtual bool AreDependenciesMet( UObject* worldContext ) const override;

};
