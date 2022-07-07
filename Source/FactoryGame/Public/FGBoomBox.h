// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"
#include "FGBoomBoxControlInterface.h"
#include "FGBoomboxListenerInterface.h"
#include "FGBoomBoxPlayer.h"
#include "GameFramework/Actor.h"
#include "FGSaveInterface.h"
#include "FGUseableInterface.h"
#include "FGRemoteCallObject.h"

#include "FGBoomBox.generated.h"

UCLASS()
class FACTORYGAME_API UFGBoomBoxRemoteCallObject: public UFGRemoteCallObject
{
	GENERATED_BODY()
public:
	virtual void GetLifetimeReplicatedProps( TArray< FLifetimeProperty >& OutLifetimeProps ) const override;
	
	UFUNCTION( Server, Reliable )
	void Server_Play( class AFGBoomBox* boomBox );

	UFUNCTION( Server, Reliable )
	void Server_Stop( class AFGBoomBox* boomBox );

	UFUNCTION( Server, Reliable )
	void Server_ChangeTape( class AFGBoomBox* boomBox, TSubclassOf< class UFGTapeData > newTape );
	
	UFUNCTION( Server, Reliable )
	void Server_NextSong( class AFGBoomBox* boomBox );

	UFUNCTION( Server, Reliable )
	void Server_PreviousSong( class AFGBoomBox* boomBox );
	
	UFUNCTION( Server, Reliable )
	void Server_SetVolumeNormalized( class AFGBoomBox* boomBox, float volume );

	void SyncPlayerStateReqest( class AFGBoomBoxPlayer* player );
protected:
	UFUNCTION( Server, Reliable )
	void Server_SyncPlayerStateRequest( class AFGBoomBoxPlayer* player, float clientTimestamp );

	UFUNCTION( Client, Reliable )
	void Client_SyncPlayerState( class AFGBoomBoxPlayer* player, FBoomBoxPlayerState state, float timestamp );
private:
	UPROPERTY( Replicated, Meta = ( NoAutoJson ) )
	bool mForceNetField_UFGBoomBoxRemoteCallObject = false;
};

UCLASS( BlueprintType, Abstract )
class FACTORYGAME_API AFGBoomBox : public AActor, public IFGSaveInterface, public IFGUseableInterface, public IFGBoomBoxControlInterface
{
	GENERATED_BODY()
	
public:	
	// Begin IFGSaveInterface
	virtual bool NeedTransform_Implementation() override;
	virtual bool ShouldSave_Implementation() const override;
	// End IFSaveInterface

	// Begin IFGBoomBoxControlInterface
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
	virtual EBoomBoxPickupButtonState GetPickupButtonState( AFGCharacterPlayer* player ) override;
	virtual void PickUp(AFGCharacterPlayer* toPlayer) override;
	// End IFGBoomBoxControlInterface

	// Begin AActor interface
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	virtual void BeginPlay() override;
	// End AActor interface
	
	void SetBoomBoxPlayer( class AFGBoomBoxPlayer* player );
	class AFGBoomBoxPlayer* GetBoomBoxPlayer() const;
protected:
	UFUNCTION( BlueprintCallable )
	bool CanBePickedUp( AFGCharacterPlayer* byCharacter ) const;

	UPROPERTY( VisibleAnywhere, BlueprintReadOnly, Replicated, SaveGame )
	class AFGBoomBoxPlayer* mBoomBoxPlayer = nullptr;

private:
	UFGBoomBoxRemoteCallObject* GetRCO();
};
