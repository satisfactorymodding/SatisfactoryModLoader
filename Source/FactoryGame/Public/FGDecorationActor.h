// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "FGInteractActor.h"
#include "FGSaveInterface.h"
#include "FGDecorationActor.generated.h"

/**
 * 
 */
UCLASS()
class FACTORYGAME_API AFGDecorationActor : public AFGInteractActor, public IFGSaveInterface
{
	GENERATED_BODY()
public:

	AFGDecorationActor();

	/** Decide on what properties to replicate */
	virtual void GetLifetimeReplicatedProps( TArray<FLifetimeProperty>& OutLifetimeProps ) const override;

	// Begin IFGSaveInterface
	virtual void PreSaveGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void PostSaveGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void PreLoadGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void PostLoadGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void GatherDependencies_Implementation( TArray< UObject* >& out_dependentObjects ) override;
	virtual bool NeedTransform_Implementation() override;
	virtual bool ShouldSave_Implementation() const override;
	// End IFSaveInterface
public:
	/** The descriptor of this decoration */
	UPROPERTY( SaveGame, Replicated, BlueprintReadWrite, Meta = (ExposeOnSpawn) )
	TSubclassOf< class UFGDecorationDescriptor > mDecorationDescriptor;
};
