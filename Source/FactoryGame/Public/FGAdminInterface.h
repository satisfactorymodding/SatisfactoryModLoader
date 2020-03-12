#pragma once
#include "Array.h"
#include "UnrealString.h"
#include "GameFramework/Actor.h"
#include "UObject/Class.h"

#include "FGOnlineSessionSettings.h"
#include "FGSaveSystem.h"
#include "FGAdminInterface.generated.h"

DECLARE_DYNAMIC_DELEGATE_TwoParams( FOnAdminEnumerateSaveGamesComplete, bool, success, const TArray<FSaveHeader>&, saveGames );
DECLARE_DYNAMIC_DELEGATE_OneParam( FOnAdminDeleteSaveGameComplete, bool, success );
DECLARE_DYNAMIC_DELEGATE_TwoParams( FOnAdminSaveGameComplete, bool, success, const FText&, errorMessage );

typedef int16 RequestIdType;

UCLASS(notplaceable)
class FACTORYGAME_API AFGAdminInterface : public AInfo
{
	GENERATED_BODY()
public:
	AFGAdminInterface();

	//~Begin AActor interface
	virtual bool IsNetRelevantFor( const AActor* realViewer, const AActor* viewTarget, const FVector& srcLocation ) const override;
	//~End AActor interface

	/** Kick a player from the game */
	UFUNCTION( BlueprintCallable, Server, Reliable, WithValidation )
	void KickPlayer( class APlayerState* playerState );

	/** Set the visibility of the session */
	UFUNCTION( BlueprintCallable, Server, Reliable, WithValidation )
	void SetSessionVisibility( ESessionVisibility visibility );

	/** Save a game on this or host machine */
	UFUNCTION( BlueprintCallable, Category="FactoryGame|Admin" )
	void SaveGame( bool locally, const FString& saveName, FOnAdminSaveGameComplete completeDelegate );

	/** Load a game on this or host machine */
	UFUNCTION( BlueprintCallable, Category="FactoryGame|Admin" )
	void LoadGame( bool locally, const FSaveHeader& save );

	/** Returns the list of saves */
	UFUNCTION( BlueprintCallable, Category="FactoryGame|Admin" )
	void EnumerateSaveGames( bool localSaves, FOnAdminEnumerateSaveGamesComplete completeDelegate );

	/** Delete a entire save session and all contaning saves */
	UFUNCTION( BlueprintCallable, Category="FactoryGame|Admin" )
	void DeleteSaveSession( bool localSaves, const FSessionSaveStruct& session, FOnAdminDeleteSaveGameComplete completeDelegate );

	/** Delete a list of save files */
	UFUNCTION( BlueprintCallable, Category="FactoryGame|Admin" )
	void DeleteSaveFiles( bool localSaves, const TArray<FString>& saveNames, FOnAdminDeleteSaveGameComplete completeDelegate );

	/** Delete a single save file */
	UFUNCTION( BlueprintCallable, Category="FactoryGame|Admin" )
	void DeleteSaveFile( bool localSaves, const FString& saveName, FOnAdminDeleteSaveGameComplete completeDelegate );
protected:
	/** Internal implementation of save enumeration */
	void Internal_EnumerateSaveGames( RequestIdType requestId );

	/** Server call of save enumeration */
	UFUNCTION( Server, Reliable, WithValidation )
	void Server_EnumerateSaveGames( int16 requestId );

	/** Result call of the save enumeration */
	UFUNCTION( Client, Reliable )
	void Client_OnEnumerateSaveGamesCompleted( bool success, int16 requestId, const TArray<FSaveHeader>& saves );

	/** Interal implementation of deleting a save file */
	void Internal_DeleteSaveFiles( const TArray<FString>& saveNames, RequestIdType requestId );

	/** Server call of save deletion */
	UFUNCTION( Server, Reliable, WithValidation )
	void Server_DeleteSaveFiles( const TArray<FString>& saveNames, int16 requestId );

	/** Client call with result of save deletion */
	UFUNCTION( Client, Reliable )
	void Client_DeleteSaveFilesCompleted( bool success, int16 requestId );

	/** Server call of loading a save */
	UFUNCTION( Server, Reliable, WithValidation )
	void Server_LoadGame( const FSaveHeader& header );

	/** Client call with result of save game */
	UFUNCTION( Client, Reliable )
	void Client_OnSaveGameCompleted( bool success, int16 requestId, const FText& errorMessage );

	/** Server call of save game */
	UFUNCTION( Server, Reliable, WithValidation )
	void Server_SaveGame( int16 requestId, const FString& saveGame );

	/** Internal implementation of save game */
	void Internal_SaveGame( RequestIdType requestId, const FString& saveGame );

	/** Counter to create a id of server/client requests to keep track of results */
	static RequestIdType RequestIdCounter;

	/** Map to keep track of what call will trigger what result */
	TMap<int16, FOnAdminEnumerateSaveGamesComplete> mRequestEnumerateSavesDelegate;

	/** Map to keep track of what call will trigger what result */
	TMap<int16, FOnAdminDeleteSaveGameComplete> mRequestDeleteSaveDelegate;

	/** Map to keep track of what call will trigger what result */
	TMap<int16, FOnAdminSaveGameComplete> mRequestSaveGameDelegate;

	/** Helper to get our owning player */
	class AFGPlayerControllerBase* GetOwningPlayer() const;

	/** Helper to get our owning player */
	class UFGLocalPlayer* GetOwningLocalPlayer() const;

	/** Helper to get game session in a cleaner way */
	class AFGGameSession* GetGameSession() const;

	/** @SERVER: Return true if our owner is logged in */
	bool IsOwnerAdmin() const;

public:
	FORCEINLINE ~AFGAdminInterface() = default;
};