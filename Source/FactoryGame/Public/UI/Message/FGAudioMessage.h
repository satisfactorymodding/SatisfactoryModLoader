// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AkGameplayTypes.h"
#include "FGMessageBase.h"
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

	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = "Audio Message" )
	int32 SubtitleIndex = 0;

	UPROPERTY( BlueprintReadOnly, Category = "Audio Message" )
	TSubclassOf< class UFGPresentationSlideWidget > PresentationSlideWidget = nullptr;
};

USTRUCT( BlueprintType )
struct FMessageSubtitle
{
	GENERATED_BODY()

	FMessageSubtitle(){}
	
	
	FMessageSubtitle( FText subtitle, TSubclassOf< class UFGMessageSender > senderClass ) :
		Subtitle( subtitle ),
		SenderClass( senderClass )
	{}

	FMessageSubtitle( FText subtitle, TSubclassOf< class UFGMessageSender > senderClass, float timeStamp, TSubclassOf< class UFGPresentationSlideWidget > presentationSlideWidget ) :
		Subtitle( subtitle ),
		SenderClass( senderClass ),
		TimeStamp( timeStamp ),
		PresentationSlideWidget( presentationSlideWidget )
	{}

	/** Subtitle to display */
	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = "Audio Message" )
	FText Subtitle = FText();

	/** Sender for this subtitle */
	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = "Audio Message" )
	TSubclassOf< class UFGMessageSender > SenderClass = nullptr;

	/** When in the audio event should we show this subtitle */
	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = "Audio Message" )
	float TimeStamp = 0.f;

	/** The presentation slide widget for this subtitle */
	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = "Audio Message" )
	TSubclassOf< class UFGPresentationSlideWidget > PresentationSlideWidget = nullptr;

	float TimeOnScreen = 0.f;
	
	int32 SubtitleIndex = 0;
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

	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = "Audio Message" )
	TArray< FMessageSubtitle > MessageSubtitles;

	/** How much should we overlap this dialogue with the next one. Useful when you want to overlap two conversations like one person interrupting another. 0 (default) means it will just play as usual */
	UPROPERTY( EditDefaultsOnly, Category = "Audio Message" )
	float OverlapWithNextDialogue;

	bool HasMoreSubtitlesToShow() const;
	
	/** Return length of this dialogue in seconds */
	float GetLength() const;

	FMessageSubtitle PopNextSubtitle();
};

/**
 * This class is used to display a UFGMessage on screen. The widget is populated with data from the message asset.
 * It could benefit from some cleanup.
 */
UCLASS( BlueprintType, Blueprintable )
class FACTORYGAME_API UFGAudioMessage : public UFGMessageBase
{
	GENERATED_BODY()
public:
	/** ctor */
	UFGAudioMessage( const FObjectInitializer& ObjectInitializer );

	// Begin Userwidget interface
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
	// End Userwidget interface

	// Begin UFGMessageBase interface
	virtual int32 GetMessagePriority() const override;
	// End UFGMessageBase interface
	
	/** Starts playing the first dialogue */
	UFUNCTION( BlueprintCallable, Category = "Audio Message" )
	void StartPlayback();

	UFUNCTION()
	void OnSkipButtonPressed();
	UFUNCTION()
	void OnSkipButtonReleased();
	
	/** Does the setup for playing next part in the dialogue
	 * @param skipToNextTimeStamp if true we jump in the audio file to the next subtitles timestamp.
	 */
	UFUNCTION( BlueprintNativeEvent, Category = "AudioMessage" )
	void PlayNextDialogue( bool skipToNextTimeStamp = false );

	/** Continues playing next dialoge in the mDialogue array  */
	UFUNCTION()
	void ContinuePlayback();
	
	UFUNCTION( BlueprintCallable, Category = "Message|Tools" )
	void SkipToNextSubtitle();

	/** Removes all unplayed dialogues and stops the current one.  */
	UFUNCTION( BlueprintCallable, Category = "Audio Message" )
	void CancelPlayback();

	/** Called when all dialogue waves have finished playing or we canceled the dialogue */
	void FinishPlayback();

	/** Gets current dialogue */
	UFUNCTION( BlueprintPure, Category = "Audio Message" )
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

	void InitMessage( class UFGMessage* message );
	/** Returns the associated message asset for this message  */
	UFUNCTION( BlueprintPure, Category = "Message" )
	class UFGMessage* GetMessage() const { return mMessage; }

#if WITH_EDITOR
	UFUNCTION( BlueprintPure, Category = "Message" )
	float GetCurrentAudioPlayProgress();
	UFUNCTION( BlueprintCallable, Category = "Message|Tools" )
	void PauseMessage();
	UFUNCTION( BlueprintPure, Category = "Message|Tools" )
	bool IsMessagePaused();
	UFUNCTION( BlueprintCallable, Category = "Message|Tools" )
	void ResumeMessage();
	UFUNCTION( BlueprintCallable, Category = "Message|Tools" )
	void StopAndDestroyMessage();
	/** Used if we want to start playing a message from somewhere other that the first subtitle. Only used by tools */
	int32 Tool_StartOnSubtitleIndex = 0;
	float Tool_CurrentAudioPlayProgress = 0.f;
	bool Tool_SkipIncomingAnimation = false;
#endif

protected:
	/** Do we want to skip the dot animation in the incoming message */
	UFUNCTION( BlueprintPure, Category = "Audio Message" )
	bool SkipIncomingAnimation();

	/** Does any subtitle in this message contain a presentation slide */
	UFUNCTION( BlueprintPure, Category = "Audio Message" )
	bool DoesMessageContainPresentation() const;
	
private:
	/** Used to discard any input we want to consume but not use */
	FORCEINLINE UFUNCTION()
	void DiscardInput() { ; }
	
	void SetupAkAudioComponent();
	void TrySkipToSubtitle();
	
public:
	/** The Ak component */
	UPROPERTY()
	class UAkComponent* mAkAudioComponent;

	AkPlayingID mAkPlayingId = AK_INVALID_PLAYING_ID;

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
	
protected:
	/** Mapping context which is applied when opening this audio message */
	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category="Input" )
	TObjectPtr< class UInputMappingContext > mMappingContext;
	
private:

	UPROPERTY( Transient )
	class UInputComponent* mAudioMessageInputComponent;

	/** This is the message data for this audio message. This is not always valid. Old message system used derived audio message classes
	 *	and some of them is still around. In those cases the data is specified directly in the UFGAudioMessage class  */  
	UPROPERTY( Transient )
	class UFGMessage* mMessage;
	
};
