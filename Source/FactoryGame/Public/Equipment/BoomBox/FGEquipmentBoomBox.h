// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"
#include "FGBoomBoxControlInterface.h"
#include "FGBoomBoxPlayer.h"
#include "DamageTypes/FGPointDamageType.h"
#include "Equipment/FGEquipment.h"
#include "FGEquipmentBoomBox.generated.h"

/**
 * 
 */
UCLASS()
class FACTORYGAME_API AFGEquipmentBoomBox : public AFGEquipment, public IFGBoomBoxControlInterface
{
	GENERATED_BODY()
public:
	AFGEquipmentBoomBox();

	/** Puts the boombox down. Traces a line in the direction the player looks at to determine actual transform */
	UFUNCTION( BlueprintCallable )
	void PutDown();

	UFUNCTION( BlueprintCallable )
	void Inspect();

	UFUNCTION( BlueprintCallable )
	virtual void FireTurboBass() override;
	
	/** Begin IFGBoomBoxControlInterface */
	virtual void ChangeTape( TSubclassOf< class UFGTapeData > newTape ) override;
	virtual void NextSong() override;
	virtual void PreviousSong() override;
	virtual void Play() override;
	virtual void Stop() override;
	virtual void SetVolumeNormalized(float volume) override;
	virtual bool IsCurrentlyPlaying() override;
	virtual TSubclassOf< class UFGTapeData > GetCurrentTape() override;
	virtual void RegisterStateListener( TScriptInterface<class IFGBoomboxListenerInterface> stateListener ) override;
	virtual void UnregisterStateListener( TScriptInterface<class IFGBoomboxListenerInterface > stateListener ) override;
	virtual void PutDownNearPlayer() override;
	/** End IFGBoomBoxControlInterface */

	void SetBoomBoxPlayer( class AFGBoomBoxPlayer* player );
	
protected:
	UFUNCTION( Client, Reliable )
	void Client_PlayPressPlayEffects();

	UFUNCTION( Client, Reliable )
	void Client_PlayPressStopEffects();

	UFUNCTION( Client, Reliable )
	void Client_PlayInspectEffects();

	UFUNCTION( Client, Reliable )
	void Client_PlayLoadTapeEffects();

	UFUNCTION( Client, Reliable )
	void Client_PlaySwitchTapeEffects();

	UFUNCTION( Client, Reliable )
	void Client_PlayPressNextEffects();

	UFUNCTION( Client, Reliable )
	void Client_PlayPressPreviousEffects();

	UFUNCTION( Client, Reliable )
	void Client_PlayTurboBassEffects();

	UFUNCTION( Client, Reliable )
	void Client_PlayFireTurboBassEffects();
	
	UFUNCTION( Server, Reliable )
	void Server_Inspect();
	
	UFUNCTION( Server, Reliable )
	void Server_ChangeTape( TSubclassOf< UFGTapeData > newTape );

	UFUNCTION( Server, Reliable )
	void Server_Play();

	UFUNCTION( Server, Reliable )
	void Server_Stop();

	UFUNCTION( Server, Reliable )
	void Server_FireTurboBass();
	
	UFUNCTION( Server, Reliable )
	void Server_NextSong();

	UFUNCTION( Server, Reliable )
	void Server_PreviousSong();

	UFUNCTION( Server, Reliable )
	void Server_LoadTapeNow();

	UFUNCTION( Server, Reliable )
	void Server_EjectTapeNow();

	UFUNCTION( Server, Reliable )
	void Server_PlayNow();

	UFUNCTION( Server, Reliable )
	void Server_StopNow();

	UFUNCTION( Server, Reliable )
	void Server_TogglePlaybackNow();

	UFUNCTION( Server, Reliable )
	void Server_NextNow();

	UFUNCTION( Server, Reliable )
	void Server_PrevNow();

	UFUNCTION( Server, Reliable )
	void Server_FireTurboBassNow();

	UFUNCTION( Server, Reliable )
	void Server_PutDown( const FTransform& transform );

	UFUNCTION( Server, Reliable )
	void Server_SetVolumeNormalized( float volume );

	UFUNCTION( BlueprintCallable )
	UAkComponent* GetAkComponent();

	/** Called on server to do actual logic when bass is fired */
	UFUNCTION()
	void FireTurboBassLogics();
	
	UFUNCTION( BlueprintImplementableEvent )
	void PlayLoadTapeEffect();

	UFUNCTION( BlueprintImplementableEvent )
	void PlaySwitchTapeEffect();

	UFUNCTION( BlueprintImplementableEvent )
	void PlayPressPlayEffect();

	UFUNCTION( BlueprintImplementableEvent )
	void PlayPressStopEffect();

	UFUNCTION( BlueprintImplementableEvent )
	void PlayPressNextEffect();

	UFUNCTION( BlueprintImplementableEvent )
	void PlayPressPrevEffect();

	UFUNCTION( BlueprintImplementableEvent )
	void PlayStingerEffects();

	UFUNCTION( BlueprintImplementableEvent )
	void PlayEquipEffects();

	UFUNCTION( BlueprintImplementableEvent )
	void PlayInspectEffects();

	UFUNCTION( BlueprintImplementableEvent )
	void PlayTurboBassEffects();

	UFUNCTION( BlueprintImplementableEvent )
	void PlayFireTurboBassEffects();

	UFUNCTION( BlueprintCallable )
	void LoadTapeNow();

	UFUNCTION( BlueprintCallable )
	void EjectTapeNow();

	UFUNCTION( BlueprintCallable )
	void PlayNow();

	UFUNCTION( BlueprintCallable )
	void StopNow();

	UFUNCTION( BlueprintCallable )
	void NextNow();

	UFUNCTION( BlueprintCallable )
	void PrevNow();

	UFUNCTION( BlueprintCallable )
	void FireTurboBassNow();

	UFUNCTION( BlueprintCallable )
	void TogglePlaybackNow();

	void PutDownImpl( const FTransform& transform );
	
	/** Boombox mesh */
	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = "Boombox" )
	USkeletalMeshComponent* mMesh = nullptr;

	/** Separate scene root component, needed to allow the mesh transform to be changed in editor */
	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = "Boombox" )
	USceneComponent* mSceneRoot = nullptr;

	virtual void WasEquipped_Implementation() override;
	virtual void WasUnEquipped_Implementation() override;
	virtual void WasRemovedFromSlot_Implementation() override;
	
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void GetLifetimeReplicatedProps( TArray< FLifetimeProperty >& OutLifetimeProps ) const;
	virtual bool ShouldSaveState() const override;
private:
	
	UPROPERTY()
	TSubclassOf< class UFGTapeData > mLoadingTape = nullptr;

	UPROPERTY( Replicated, SaveGame )
	class AFGBoomBoxPlayer* mBoomBoxPlayer = nullptr;

	UPROPERTY( EditDefaultsOnly, Category = "Boombox" )
	float mImpulseRadius;

	UPROPERTY( EditDefaultsOnly, Category = "Boombox" )
	float mImpulseStrength;

	UPROPERTY( EditDefaultsOnly, Category = "Boombox" )
	TSubclassOf< UFGPointDamageType > mImpulseDamageType;

	UPROPERTY( EditDefaultsOnly, Category = "Boombox" )
	TSubclassOf< class UFGNoise > mTurboBassNoise;

	UPROPERTY( EditDefaultsOnly, Category = "Boombox" )
	float mBoostJumpMultiplier;

	UPROPERTY( EditDefaultsOnly, Category = "Boombox" )
	float mBoostJumpVelocityRange;

	
};
