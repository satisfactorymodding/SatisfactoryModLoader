// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Equipment/FGObjectScanner.h"
#include "FGActorRepresentation.h"
#include "Net/Serialization/FastArraySerializer.h"
#include "FGRadarTowerRepresentation.generated.h"


USTRUCT( BlueprintType )
struct FScanObjectPair : public FFastArraySerializerItem
{
	GENERATED_BODY()
	
	FScanObjectPair( TSubclassOf<class UFGItemDescriptor> itemDescriptor, int32 numActors ) :
		ItemDescriptor( itemDescriptor ),
		NumActorsFound( numActors )
	{}
	
	FScanObjectPair() :
		ItemDescriptor( nullptr ),
		NumActorsFound( 0 )
	{}

	UPROPERTY( BlueprintReadOnly )
	TSubclassOf<class UFGItemDescriptor> ItemDescriptor;
	UPROPERTY( BlueprintReadOnly )
	int32 NumActorsFound;
};

USTRUCT()
struct FScanObjectPairArray : public FFastArraySerializer
{
	GENERATED_BODY()

	UPROPERTY()
	TArray<FScanObjectPair> Items;

	bool NetDeltaSerialize(FNetDeltaSerializeInfo& DeltaParms)
	{
		return FastArrayDeltaSerialize<FScanObjectPair>(Items, DeltaParms, *this);
	}
};

template<>
struct TStructOpsTypeTraits<FScanObjectPairArray>: public TStructOpsTypeTraitsBase2<FScanObjectPairArray>
{
	enum { WithNetDeltaSerializer = true };
};

/**
 * 
 */
UCLASS()
class FACTORYGAME_API UFGRadarTowerRepresentation : public UFGActorRepresentation
{
	GENERATED_BODY()
	
public:
	virtual void SetupActorRepresentation(AActor* realActor, bool isLocal, float lifeSpan) override;

	void GetLifetimeReplicatedProps( TArray<FLifetimeProperty>& OutLifetimeProps ) const override;

	void UpdateScannedActors( const TMap<TSubclassOf<UFGItemDescriptor>, int32>& scannedActors );
	
	UPROPERTY( Replicated )
	FScanObjectPairArray mFoundActors;
	
	UFUNCTION( BlueprintCallable, Category=RadarTower )
	void GetFoundWeakSignals( TArray< FScanObjectPair >& out_FoundWeakSignals ) const;
	UFUNCTION( BlueprintCallable, Category=RadarTower )
	void GetFoundFauna( TArray< class TSubclassOf<UFGItemDescriptor> >& out_FoundFauna ) const;
	UFUNCTION( BlueprintCallable, Category=RadarTower )
	void GetFoundFlora( TArray< class TSubclassOf<UFGItemDescriptor> >& out_FoundFlora ) const;
};
