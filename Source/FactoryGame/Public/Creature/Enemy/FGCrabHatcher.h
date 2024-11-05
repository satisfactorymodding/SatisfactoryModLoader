// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

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

	virtual float TakeDamage( float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser ) override;

	virtual void GetLifetimeReplicatedProps( TArray< FLifetimeProperty >& OutLifetimeProps ) const override;

	UFUNCTION( BlueprintCallable, Category = "FGCrabHatcher" )
	void RegisterHostilePlayer( class AFGCharacterPlayer* player );

	UFUNCTION( BlueprintCallable, Category = "FGCrabHatcher" )
	class AFGFlyingBabyCrab* SpawnBabyCrab();

private:
	UFUNCTION()
	void OnBabyCrabDestroyed( class AActor* babyCrabActor );
	
public:
	UPROPERTY( EditAnywhere, Category = "FGCrabHatcher" )
	TSubclassOf< class AFGFlyingBabyCrab > mBabyClass;
	
	UPROPERTY( EditAnywhere, Category = "FGCrabHatcher" )
	FVector mBabySpawnCenterOffset;

	UPROPERTY( EditAnywhere, Category = "FGCrabHatcher" )
	FVector mBabySpawnExtent;

	UPROPERTY( EditAnywhere, Category = "FGCrabHatcher ")
	FFloatInterval mBabySpawnImpulse;
	
	UPROPERTY(SaveGame, Replicated, BlueprintReadWrite, Category="FGCrabHatcher|Runtime")
	float mCurrentHealth;

protected:
	TArray< class AFGCharacterPlayer* > mHostilePlayers;

private:
	TArray< class AFGFlyingBabyCrab* > mSpawnedBabyCrabs;
	
};
