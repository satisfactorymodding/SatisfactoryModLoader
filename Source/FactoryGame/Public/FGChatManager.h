// Copyright 2016-2018 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "Engine/World.h"
#include "Array.h"
#include "UnrealString.h"
#include "UObject/Class.h"

#include "CoreMinimal.h"
#include "FGSubsystem.h"
#include "FGChatManager.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE( FChatMessageAdded );

/**
 * This is the struct for the messages that are displayed in the chat
 */

UENUM( BlueprintType )
enum class EFGChatMessageType : uint8
{
	CMT_PlayerMessage = 0,
	CMT_SystemMessage,
	CMT_AdaMessage
};

USTRUCT( BlueprintType )
struct FACTORYGAME_API FChatMessageStruct
{
	GENERATED_BODY()
public:

	FChatMessageStruct();
	FChatMessageStruct( FString messageString, class AFGPlayerState* sender, float serverTimeStamp );

	/** The message that was sent */
	UPROPERTY( BlueprintReadWrite )
	FString MessageString;
	
	/** Synchronized time stamp of when the message was sent */
	UPROPERTY( BlueprintReadWrite )
	float ServerTimeStamp;

	/** The player who sent the message */
	UPROPERTY( BlueprintReadWrite ) // MODDING EDIT: BPRW
	class AFGPlayerState* Sender;

	/** The name of the player */
	FString CachedPlayerName;

	/** Caching the color */
	FLinearColor CachedColor;

	

	UPROPERTY()
	EFGChatMessageType MessageType = EFGChatMessageType::CMT_PlayerMessage;

public:
	FORCEINLINE ~FChatMessageStruct() = default;
};

/**
 * Manages the chat in the game.
 */
UCLASS( Blueprintable, abstract )
class FACTORYGAME_API AFGChatManager : public AFGSubsystem
{
	GENERATED_BODY()
public:
	/** Called when you get a new local message */
	UPROPERTY( BlueprintAssignable, Category = "Chat" )
	FChatMessageAdded OnChatMessageAdded;

public:
	/** Get the chat manager, this should always return something unless you call it really early. */
	//MODDING EDIT: doesn't exist in executable, so forceinline to use version below
	FORCEINLINE static AFGChatManager* Get(UWorld* world) { return Get(static_cast<UObject*>(world)); }

	/** Get the chat manager from a world context, this should always return something unless you call it really early. */
	UFUNCTION( BlueprintPure, Category = "Schematic", DisplayName = "GetChatManager", Meta = ( DefaultToSelf = "worldContext" ) )
	static AFGChatManager* Get( UObject* worldContext );
	
public:
	AFGChatManager();

	UFUNCTION( BlueprintPure, Category = "Chat" )
	static FString GetChatMessageName( const FChatMessageStruct& inMessage );

	UFUNCTION( BlueprintPure, Category = "Chat" )
	static FLinearColor GetChatMessageColor( const FChatMessageStruct& inMessage );

	/** Broadcast a chat message to all clients */
	UFUNCTION( NetMulticast, Reliable )
	void Multicast_BroadcastChatMessage( const FChatMessageStruct& newMessage );

	/** Helper function to add a chat message to the local array */
	void AddChatMessageToReceived( const FChatMessageStruct& inMessage );

	UFUNCTION( BlueprintCallable, BlueprintPure = false, Category = "Chat" )
	void GetReceivedChatMessages( UPARAM( ref ) TArray< FChatMessageStruct >& out_messages ) const;

	UFUNCTION( BlueprintPure, Category = "Chat" )
	int32 GetMaxNumMessagesInHistory() const;

	UFUNCTION( BlueprintPure, Category = "Chat" )
	float GetMessageVisibleDuration() const;

private:
	/** How many messages will we save in the chat history */
	UPROPERTY( EditDefaultsOnly, Category = "Chat" )
	int32 mMaxNumMessagesInHistory;

	/** How long a message will stay fresh and visible without opening the chat */
	UPROPERTY( EditDefaultsOnly, Category = "Chat" )
	float mMessageVisibleDuration;

	/** An array of all the messages that the local player have received. */
	UPROPERTY()
	TArray< FChatMessageStruct > mReceivedMessages;


public:
	FORCEINLINE ~AFGChatManager() = default;
};
