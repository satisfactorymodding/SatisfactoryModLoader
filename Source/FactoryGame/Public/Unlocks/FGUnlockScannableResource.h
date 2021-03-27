// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

#include "Resources/FGResourceDescriptorGeyser.h"
#include "Resources/FGResourceNode.h"
#include "Unlocks/FGUnlock.h"
#include "FGUnlockScannableResource.generated.h"


USTRUCT( BlueprintType )
struct FScannableResourcePair
{
	GENERATED_BODY()

	FScannableResourcePair() :
		ResourceDescriptor( nullptr )
	{
		ResourceNodeType = EResourceNodeType::Node;
	}

	FScannableResourcePair( TSubclassOf< class UFGResourceDescriptor > resourceDescriptor ) :
    ResourceDescriptor( resourceDescriptor )
	{
		if( resourceDescriptor->IsChildOf( UFGResourceDescriptorGeyser::StaticClass() ) )
		{
			ResourceNodeType = EResourceNodeType::Geyser; // Special case for geyser when loading old saves and migrating to new pair system
		}
		ResourceNodeType = EResourceNodeType::Node;
	}

	FScannableResourcePair( TSubclassOf< class UFGResourceDescriptor > resourceDescriptor, EResourceNodeType resourceNodeType ) :
	ResourceDescriptor( resourceDescriptor ),
	ResourceNodeType( resourceNodeType )
	{}
	
	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly )
	TSubclassOf< class UFGResourceDescriptor > ResourceDescriptor;
	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly )
	EResourceNodeType ResourceNodeType;

	bool operator ==(const FScannableResourcePair& other) const;

	bool operator !=(const FScannableResourcePair& other) const;
};

/**
 * Unlocks scanning of the specified resources
 */
UCLASS( Blueprintable, EditInlineNew, abstract, DefaultToInstanced )
class FACTORYGAME_API UFGUnlockScannableResource : public UFGUnlock
{
	GENERATED_BODY()

public:
	// Begin FGUnlock interface
	virtual void Apply( class AFGUnlockSubsystem* unlockSubssytem ) override;
	// End FGUnlock interface

	// Only for migrate mResourcesToAddToScanner to new system
	virtual void PostLoad() override;

#if WITH_EDITORONLY_DATA
	//void Init( TArray< TSubclassOf< class UFGResourceDescriptor > > resources ) { mResourcesToAddToScanner = resources; }
#endif

	UFUNCTION( BlueprintPure, Category=Unlocks )
	FORCEINLINE TArray< FScannableResourcePair > GetResourcesToAddToScanner() const { return mResourcePairsToAddToScanner; }

protected:
	/**  These are the resources that are scannable after this unlock */
	UPROPERTY() //@todok2 Deprecated remove this when all assets been resaved.
	TArray< TSubclassOf< class UFGResourceDescriptor > > mResourcesToAddToScanner;

	/**  These are the resources that are scannable after this unlock */
	UPROPERTY( EditDefaultsOnly )
	TArray< FScannableResourcePair > mResourcePairsToAddToScanner;

};
