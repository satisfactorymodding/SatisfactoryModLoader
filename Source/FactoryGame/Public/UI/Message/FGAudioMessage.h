// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"
#include "UI/Message/FGMessageBase.h"
#include "FGAudioMessage.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE( FOnAudioMessageFinishedPlaying );

/** What is the priorty for this message. Not the same as message type since one kind of messag ecan have different priorities */
UENUM( BlueprintType )
enum class EMessagePriorityType : uint8
{
	MPT_DirectMessage	= 0			UMETA( DisplayName = "Direct Message" ),
    MPT_PriorityCall	= 1			UMETA( DisplayName = "Priority Call" ),
    MPT_OptionalCall	= 2			UMETA( DisplayName = "Optional Call" )
};

USTRUCT( BlueprintType )
struct FAudioSubtitlePair
{
	GENERATED_BODY()

	FAudioSubtitlePair() : 
		AudioEvent( nullptr ),
		SenderClass( nullptr )
	{}

	/** Audio to play */
	UPROPERTY( EditDefaultsOnly, Category = "Audio Message" )
	class UAkAudioEvent* AudioEvent;

	/** Subtitle to display */
	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = "Audio Message" )
	FText Subtitle;

	/** Sender for this part of message */
	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = "Audio Message" )
	TSubclassOf< class UFGMessageSender > SenderClass;
};

USTRUCT( BlueprintType )
struct FMessageSubtitle
{
	GENERATED_BODY()

	FMessageSubtitle() :
		Subtitle( FText() ),
		SenderClass( nullptr ),
		TimeStamp( 0.0f )
	{}
	
	
	FMessageSubtitle( FText subtitle, TSubclassOf< class UFGMessageSender > senderClass ) :
		Subtitle( subtitle ),
		SenderClass( senderClass ),
		TimeStamp( 0.0f )
	{}

	/** Subtitle to display */
	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = "Audio Message" )
	FText Subtitle;

	/** Sender for this subtitle */
	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = "Audio Message" )
	TSubclassOf< class UFGMessageSender > SenderClass;

	/** When in the audio event should we show this subtitle */
	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = "Audio Message" )
	float TimeStamp;

	float TimeOnScreen;
};

USTRUCT( BlueprintType )
struct FMessageDialogue
{
	GENERATED_BODY()

	FMessageDialogue() : 
		AudioEvent( nullptr ),
		OverlapWithNextDialogue( 0.0f )
	{}

	// For merging purposes from FAudioSubtitlePair to FMessageDialogue
	FMessageDialogue( FAudioSubtitlePair subtitlePair ) : 
		AudioEvent( subtitlePair.AudioEvent ),
		MessageSubtitles( { FMessageSubtitle( subtitlePair.Subtitle, subtitlePair.SenderClass ) } ),
		OverlapWithNextDialogue( 0.0f )
	{}

	/** Audio to play */
	UPROPERTY( EditDefaultsOnly, Category = "Audio Message" )
	class UAkAudioEvent* AudioEvent;

	UPROPERTY( EditDefaultsOnly, Category = "Audio Message" )
	TArray< FMessageSubtitle > MessageSubtitles;

	/** How much should we overlap this dialogue with the next one. Useful when you want to overlap two conversations like one person interrupting another. 0 (default) means it will just play as usual */
	UPROPERTY( EditDefaultsOnly, Category = "Audio Message" )
	float OverlapWithNextDialogue;

	bool HasMoreSubtitlesToShow() const;

	FMessageSubtitle PopNextSubtitle( float subtitleTimeMultiplier );
};

USTRUCT( BlueprintType )
struct FPendingMessage
{
	GENERATED_BODY()

	FPendingMessage() : 
        Message( nullptr ),
        MessagePriorityType( EMessagePriorityType::MPT_DirectMessage ),
        Delay( 0.0f )
	{}

	FPendingMessage( TSubclassOf< class UFGMessageBase > message, EMessagePriorityType messagePriorityType, float delay ) : 
        Message( message ),
        MessagePriorityType( messagePriorityType ),
        Delay( delay )
	{}

	FPendingMessage( TSubclassOf< class UFGMessageBase > message, EMessagePriorityType messagePriorityType ) : 
    Message( message ),
    MessagePriorityType( messagePriorityType )
	{}

	UPROPERTY( BlueprintReadOnly, Category = "Message" )
	TSubclassOf< class UFGMessageBase > Message;

	/** What priority type is this message. Only applicable for audio messages */
	UPROPERTY(  BlueprintReadOnly, Category = "Message" )
	EMessagePriorityType MessagePriorityType;
	
	/** The delay between this message and the previous pending message. Only applicable for messages in the same queue */
	UPROPERTY( BlueprintReadOnly, Category = "Message" )
	float Delay;
};

USTRUCT( BlueprintType )
struct FPendingMessageQueue
{
	GENERATED_BODY()

	FPendingMessageQueue( FPendingMessage pendingMessage ) :
		PendingMessages( {pendingMessage} )
	{}

	FPendingMessageQueue( TArray<FPendingMessage> pendingMessages ) :
		PendingMessages( pendingMessages )
	{}

	FPendingMessageQueue(  TSubclassOf< class UFGMessageBase > message ) :
		PendingMessages( {FPendingMessage( message, EMessagePriorityType::MPT_DirectMessage )} )
	{}

	FPendingMessageQueue(){}

	UPROPERTY( BlueprintReadOnly, Category = "Audio Message" )
	TArray< FPendingMessage > PendingMessages;

	bool HasUnplayedMessages();

	bool ContainsAudioMessages();

	FPendingMessage PopPendingMessage();

};


/**
 * 
 */
UCLASS( BlueprintType, Blueprintable )
class FACTORYGAME_API UFGAudioMessage : public UFGMessageBase
{
	GENERATED_BODY()
public: 
	/** ctor */
	UFGAudioMessage( const FObjectInitializer& ObjectInitializer );

	// Begin UObject interface
	virtual void PostLoad() override;
	// End UObject interface

	// Begin Userwidget interface
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
	// End Userwidget interface
	
	/** Starts playing the first dialogue */
	UFUNCTION( BlueprintCallable, Category = "Audio Message" )
	void StartPlayback();

	UFUNCTION()
	void OnSkipButtonPressed();
	UFUNCTION()
	void OnSkipButtonReleased();
	
	/** Does the setup for playing next part in the dialogue */
	UFUNCTION( BlueprintNativeEvent, Category = "AudioMessage" )
	void PlayNextDialogue();

	/** Continues playing next dialoge in the mDialogue array  */
	UFUNCTION()
	void ContinuePlayback();

	/** Removes all unplayed dialogues and stops the current one.  */
	UFUNCTION( BlueprintCallable, Category = "Audio Message" )
	void CancelPlayback();

	/** Called when all dialogue waves have finished playing or we canceled the dialogue */
	void FinishPlayback();

	/** Gets current dialogue */
	UFUNCTION( BlueprintPure, Category = "Audio Message", meta = ( DeprecatedFunction, DeprecationMessage = "GetCurrentDialogue is deprecated, use GetCurrentSubtitle instead" ) )
	FAudioSubtitlePair GetCurrentDialogue();

	/** Gets current subtitle */
	UFUNCTION( BlueprintPure, Category = "Audio Message" )
	FORCEINLINE FMessageSubtitle GetCurrentSubtitle() const { return mCurrentSubtitle; }

	/** Gets the message text  */
	UFUNCTION( BlueprintPure, BlueprintImplementableEvent, Category = "Audio Message" )
	FText GetMessageText();

	/** Gets the message text  */
	UFUNCTION( BlueprintPure, Category = "Audio Message" )
	FORCEINLINE FText GetOverrideText() { return mOverrideText; }

	/** Do we want to show only the override text or the subtitle also?  */
	UFUNCTION( BlueprintPure, Category = "Audio Message" )
	FORCEINLINE bool ShowOnlyOverrideText() { return mShowOnlyOverrideText; }

	UFUNCTION( BlueprintPure, Category = "Audio Message" )
	static EMessagePriorityType GetMessagePriorityType( TSubclassOf< UFGAudioMessage > message, UObject* worldContext );
private:
	/** Used to discard any input we want to consume but not use */
	FORCEINLINE UFUNCTION()
	void DiscardInput() { ; }

#if WITH_EDITOR
	/** This migrates the old audio events structs to the new message dialogue structs */
	void MigrateDialogueData();
#endif

public:
	/** The Ak component */
	UPROPERTY()
	class UAkComponent* mAkAudioComponent;

	/** The AK audio to play when "showing" this message */
	UE_DEPRECATED(4.26, "Please use mDialogueData instead. It should have all the data from this property migrated")
	UPROPERTY( VisibleDefaultsOnly, Category = "Audio Message - DEPRECATED" )
	TArray< FAudioSubtitlePair > mAudioEvents;

	/** The Dialogue, Audio and subtitles, to play/show when "showing" this message */
	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = "Audio Message" )
	TArray< FMessageDialogue > mDialogueData;

	/** Timer handle for subtitles */
	FTimerHandle mSubtitleTimerHandle;

	/** Timer handle for checking how long we pressed skip button if we should skip to next message or skip the whole message */
	FTimerHandle mSkipButtonTimerHandle;

	/** How long the already showned subtitles have been on screen. Used for calculating the time on screen for last subtitle in a dialogue */
	float mTotalTimeOnScreen;

	/** Current dialogue that is displayed */
	UPROPERTY()
	FMessageDialogue mCurrentDialogue;

	/** Current subtitle that is displayed */
	UPROPERTY()
	FMessageSubtitle mCurrentSubtitle;

	/**Multiplier for time per character to display */
	UPROPERTY( EditDefaultsOnly, Category = "Audio Message" )
	float mSubtitleTimeMultiplier;

	/** Text that can be displayed instead for (or added to) subtitle text when displaying the message */
	UPROPERTY( EditDefaultsOnly, Category = "Audio Message", meta = (MultiLine = true) )
	FText mOverrideText;

	/**Multiplier for time per character to display */
	UPROPERTY( EditDefaultsOnly, Category = "Audio Message" )
	bool mShowOnlyOverrideText;

	UPROPERTY( BlueprintAssignable )
	FOnAudioMessageFinishedPlaying mOnAudioMessageFinishedPlayback;
	
private:

	UPROPERTY()
	class UInputComponent* mAudioMessageInputComponent;
};
