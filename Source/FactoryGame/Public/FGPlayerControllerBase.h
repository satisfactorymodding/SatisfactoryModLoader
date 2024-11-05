// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FGInputLibrary.h"
#include "PlayerPresenceState.h"
#include "GameFramework/PlayerController.h"
#include "FGPlayerControllerBase.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE( FOnInputChanged );

UCLASS()
class FACTORYGAME_API AFGPlayerControllerBase : public APlayerController
{
	GENERATED_BODY()
public:
	AFGPlayerControllerBase();

	// Begin AActor interface
	virtual void GetLifetimeReplicatedProps( TArray<FLifetimeProperty>& OutLifetimeProps ) const override;
	virtual void BeginPlay() override;
	// End AActor interface

	// Begin APlayerController interface
	virtual void ClientRestart_Implementation( APawn* newPawn ) override;
	virtual void AddCheats( bool force = false ) override;
	// End APlayerController interface

	UFUNCTION( BlueprintPure, Category = "FactoryGame|Input" )
	FORCEINLINE bool GetIsUsingGamepad(){ return mIsUsingGamepad; }

	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Input" )
	void SetIsUsingGamepad( bool newIsUsingGamepad );

	/**
	 * Called on Server and Owning client when the character we controlled died
	 * 
	 * @param character - the character that died
	 **/ 
	virtual void OnControlledCharacterDied( class AFGCharacterBase* character );

	/**
	* Called on Server and Owning client when the character we controlled has been revived
	*
	* @param character - the character that was revived
	**/
	virtual void OnControlledCharacterRevived( class AFGCharacterBase* character );

	/** Called when we rebind any key */
	UPROPERTY( BlueprintAssignable )
	FOnInputChanged OnInputChanged;

	/** Exposing flushPressedKeys to BP */
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Input" )
	void FlushPressedKeys();

	/** Flushes the mouse button keys */
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Input" )
	void FlushMouseKeys();

	/** Triggered when we update the mouse sensitivity option */
	UFUNCTION()
	void OnMouseSensitivityUpdated( FString updatedCvar );

	/** Sets mouse sensitivity */
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Input" )
	void SetMouseSensitivity( float newSense );

	/** Get current sensitivity */
	UE_DEPRECATED(4.21, "Use GetMouseSensitivityX/GetMouseSensitivityY instead")
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Input", meta=(DeprecatedFunction,DeprecationMessage = "Use GetMouseSensitivityX/GetMouseSensitivityY instead") )
	float GetMouseSensitivity();

	/** Get current sensitivity in X axis */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Input" )
	float GetMouseSensitivityX();

	/** Get current sensitivity in X axis*/
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Input" )
	float GetMouseSensitivityY();

	/** Get default value for mouse sensitivity */
	UE_DEPRECATED(4.21, "Use GetDefaultMouseSensitivityX/GetDefaultMouseSensitivityY instead")
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Input", meta=(DeprecatedFunction,DeprecationMessage = "Use GetDefaultMouseSensitivityX/GetDefaultMouseSensitivityY instead") )
	float GetDefaultMouseSensitivity();

	/** Get default value for mouse sensitivity in X axis*/
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Input" )
	float GetDefaultMouseSensitivityX();

	/** Get default value for mouse sensitivity in Y axis*/
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Input" )
	float GetDefaultMouseSensitivityY();

	/** Returns readable name for an action */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Input", meta = ( DeprecatedFunction, DeprecationMessage = "Use FGInpuLibrary::FormatStringWithInputActionNames or FGInpuLibrary::GetInputActionNameAsText" ) )
	FText GetKeyNameForAction( FName inAction, bool getGamepadKey );

	/** Returns the name for the key bound to the "use" action */
	FText GetKeyNameForUseAction();

	UFUNCTION( BlueprintNativeEvent, Category="FactoryGame|Online|Presence") 
	FString GetPresenceString() const;

	virtual bool GetPresenceState(FPlayerPresenceState& outState) const 
	{
		return false;
	};

	/** Set CurrentNetSpeed to the lower of its current value and Cap, can update during the game to the new value if server updates it's bandwith due to options */
	UFUNCTION(Reliable, Client)
	void Client_UpdateCappedBandwidth(int32 cap);

	/** Set CurrentNetSpeed to the lower of its current value and Cap, can update during the game to the new value if client updates it's bandwidth */
	UFUNCTION(Reliable, Server, WithValidation)
	void Server_UpdateCappedBandwidth(int32 cap);

	/** Setup additional things if we have been granted admin access */
	void OnAdminRightsGranted();

	/** Logged out as admin */
	void OnAdminRightsRevoked();

	/** Try to run a command on the server, require admin rights */
	UFUNCTION(exec)
	void Admin( const FString& command );

	UFUNCTION( Server, Reliable )
	void Server_Admin( const FString& command );
	
	/** @return the admin interface if we are logged in as server admin */
	UFUNCTION(BlueprintPure, Category="FactoryGame|Online|Admin")
	FORCEINLINE class AFGAdminInterface* GetAdminInterface() const { return mAdminInterface; }

	// This is valid on both server and client if cheats are allowed
	FORCEINLINE class UFGCheatManager* GetCheatManager() const { return mReplicatedCheatManager; }

	/** Returns the most relevant save manager. This will be the local save manager in the main menu, the server save manager when playing on a server and authenticated as admin, or null when playing on a server without admin privilege */
	UFUNCTION( BlueprintCallable, Category = "Utility")
	TScriptInterface<class IFGSaveManagerInterface> GetMostRelevantSaveManager();

	UFUNCTION( BlueprintCallable, Category = "Utility")
	TScriptInterface<class IFGSaveManagerInterface> GetLocalSaveManager();

protected:
	/** Used to discard any input when we are dead */
	UFUNCTION()
	void DiscardInput();

	virtual void SetPlayer(UPlayer* InPlayer);
	virtual void OnNetCleanup(class UNetConnection* Connection) override;

	// UPROPERTY( BlueprintReadOnly )
	// class UFGServerObject* mCurrentServer = nullptr;
private:
	/** 
	 * Enables or disables the input for all ActionBindings except for the ones specified in mAllowedInputWhenDead.
	 * Does nothing if the state doesn't change
	 *
	 * @note Call on owning client only
	 *
	 * @param enable - if true, then we enable our input, false we disable it
	 */
	void EnablePlayerInput( bool enable );

	void SetCurrentServer( class UFGServerObject* CurrentServer );

	UFUNCTION()
	void OnRep_ReplicatedCheatManager();

	void InitDefaultCheats();

private:
	/** Admin interface if we have one available */
	UPROPERTY(Replicated)
	class AFGAdminInterface* mAdminInterface;

	/** If we are allowed to cheat, then we replicate the cheat manager */
	UPROPERTY(ReplicatedUsing=OnRep_ReplicatedCheatManager)
	class UFGCheatManager* mReplicatedCheatManager;

	/** If true, the our input is enabled */
	uint8 mInputEnabled:1;

	/** Are we using gamepad? */
	bool mIsUsingGamepad;
};
