// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
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
	CMT_AdaMessage,
	CMT_CustomMessage,
};

USTRUCT( BlueprintType )
struct FACTORYGAME_API FChatMessageStruct
{
	GENERATED_BODY()

	/** Contents of the message */
	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = "Chat Message" )
	FText MessageText;
	
	/** Type of this message. Determines the formatting and appearance of the message */
	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = "Chat Message" )
	EFGChatMessageType MessageType{EFGChatMessageType::CMT_SystemMessage};

	/** Sender of the message. System and ADA messages override the sender, but original sender can be accessed in the message text using <PlayerName/> */
	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = "Chat Message" )
	FText MessageSender;

	/** Color of the message sender. System and ADA messages override the sender, but original sender can be accessed in the message text using <PlayerName/> */
	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = "Chat Message" )
	FLinearColor MessageSenderColor{FLinearColor::White};
	
	/** Timestamp of this message from the server. Used for message sorting. Automatically set by the Chat Manager */
	UPROPERTY( BlueprintReadWrite, Category = "Chat Message" )
	float ServerTimeStamp{0.0f};

	/** True if this message has been instigated by a local player. Automatically set by the Chat Manager */
	UPROPERTY( BlueprintReadWrite, NotReplicated, Category = "Chat Message" )
	bool bIsLocalPlayerMessage{false};
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
	static AFGChatManager* Get( UWorld* world );

	/** Get the chat manager from a world context, this should always return something unless you call it really early. */
	UFUNCTION( BlueprintPure, Category = "Schematic", DisplayName = "GetChatManager", Meta = ( DefaultToSelf = "worldContext" ) )
	static AFGChatManager* Get( UObject* worldContext );
	
public:
	AFGChatManager();

	/** Broadcasts a chat message to all connected players */
	void BroadcastChatMessage( const FChatMessageStruct& newMessage, APlayerController* instigatorPlayerController = nullptr );

	/** Helper function to add a chat message to the local received messages */
	void AddChatMessageToReceived( const FChatMessageStruct& inMessage );

	UFUNCTION( BlueprintCallable, BlueprintPure = false, Category = "Chat" )
	void GetReceivedChatMessages( UPARAM( ref ) TArray< FChatMessageStruct >& out_messages ) const;

	UFUNCTION( BlueprintPure, Category = "Chat" )
	int32 GetMaxNumMessagesInHistory() const;

	UFUNCTION( BlueprintPure, Category = "Chat" )
	float GetMessageVisibleDuration() const;
protected:

	/** Broadcast a chat message to all clients */
	UFUNCTION( NetMulticast, Reliable )
	void Multicast_BroadcastChatMessage( const FChatMessageStruct& newMessage, APlayerController* instigatorPlayerController );
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

};
