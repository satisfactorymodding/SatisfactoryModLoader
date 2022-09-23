// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"
#include "FGSaveInterface.h"
#include "Replication/FGStaticReplicatedActor.h"
#include "GameFramework/Actor.h"
#include "FGCrabHatcher.generated.h"

/**
 * TODO: Nativize Char_CrabHatcher
 */
UCLASS()
class FACTORYGAME_API AFGCrabHatcher : public AFGStaticReplicatedActor, public IFGSaveInterface
{
	GENERATED_BODY()
public:
	AFGCrabHatcher();
	
	virtual void PreSaveGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void PostSaveGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void PreLoadGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void PostLoadGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void GatherDependencies_Implementation( TArray<UObject*>& out_dependentObjects ) override;
	virtual bool NeedTransform_Implementation() override;
	virtual bool ShouldSave_Implementation() const override;

	virtual void GetLifetimeReplicatedProps( TArray< FLifetimeProperty >& OutLifetimeProps ) const override;

	UPROPERTY(SaveGame, Replicated, BlueprintReadWrite, Category="FGCrabHatcher|Runtime")
	float mCurrentHealth = 20.f;
	
};
