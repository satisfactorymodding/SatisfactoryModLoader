// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "FGSaveInterface.h"
#include "FGSignificanceInterface.h"
#include "GameFramework/Actor.h"
#include "Replication/FGStaticReplicatedActor.h"
#include "FGGasPillarCloud.generated.h"

class UNiagaraComponent;
class UNiagaraSystem;

UCLASS()
class FACTORYGAME_API AFGGasPillarCloud : public AFGStaticReplicatedActor, public IFGSaveInterface, public IFGSignificanceInterface
{
public:
	virtual  void GainedSignificance_Implementation() override;
	virtual  void LostSignificance_Implementation() override;
	virtual float GetSignificanceRange() override { return mSignificanceRange; }
private:
	GENERATED_BODY()

public:
	AFGGasPillarCloud();

	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
	/** Begin Save Interface */
	virtual void GatherDependencies_Implementation( TArray<UObject*>& out_dependentObjects ) override;
	virtual bool NeedTransform_Implementation() override;
	virtual void PostLoadGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void PostSaveGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void PreLoadGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void PreSaveGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual bool ShouldSave_Implementation() const override;
	/** End Save Interface */

	void NotifyGasPillarDestroyed( class AFGGasPillar* gasPillar );

	// Either spawn or destroy systems depending on requirements
	void UpdateNiagaraSystems();

	// When all locations are removed notify BP
	UFUNCTION( BlueprintImplementableEvent, Category="GasPillarCloud" )
	void OnAllLocationsRemoved();

protected:
	UFUNCTION()
	void OnRep_RemovedWorldLocations();
	
	void CalculateRemainingPillarLocations();

#if WITH_EDITOR
public:
	UFUNCTION( CallInEditor )
	void GatherNearbyPillarLocations();

	UFUNCTION()
	void NotifyGasPillarRemovedFromInfluence( class AFGGasPillar* gasPillar );

	UFUNCTION( CallInEditor )
	void DebugDrawCurrentPillarLocations();
#endif
	
protected:

	UPROPERTY( VisibleAnywhere, Category="GasPillarCloud")
	UNiagaraComponent* mNiagaraComponent;

	UPROPERTY( EditDefaultsOnly, Category="GasPillarCloud" )
	UNiagaraSystem* mLongRangeNiagaraSystem;
	
	// Runtime array of valid locations ( set mProximityPillarWorldLocations - set mRemovedWorldLocations )
	UPROPERTY()
	TArray< FVector > mRemainingRelevantWorldLocations;
	
	UPROPERTY( VisibleAnywhere, Category="GasPillarCloud" )
	TArray< FVector > mProximityPillarWorldLocations;

	UPROPERTY( SaveGame, ReplicatedUsing=OnRep_RemovedWorldLocations )
	TArray< FVector > mRemovedWorldLocations;

	UPROPERTY( EditAnywhere, Category="GasPillarCloud")
	float mOverlapRadius = 8000.f;

	// Useful if you want to lower the height of the spawned effects Tex. In a cave setting.
	UPROPERTY( EditAnywhere, Category="GasPillarCloud" )
	float mGlobalEffectZOffset = 0.f;

private:
	UPROPERTY( EditDefaultsOnly, Category = "FactoryGame|Significance" )
	float mSignificanceRange = 8000;
	
	UPROPERTY()
	bool mIsSignificant = false;

	UPROPERTY()
	bool mHasPendingRefreshOfSystems = false;
};
