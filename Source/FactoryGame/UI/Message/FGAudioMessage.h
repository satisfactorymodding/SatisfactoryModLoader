// Copyright 2016-2018 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "Array.h"
#include "SubclassOf.h"
#include "UObject/Class.h"

#include "CoreMinimal.h"
#include "FGMessageBase.h"
#include "FGAudioMessage.generated.h"

DECLARE_DYNAMIC_DELEGATE( FAudioMessageConcludedDelegate );

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

	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

	/** Starts playing the first dialogue */
	UFUNCTION( BlueprintCallable, Category = "Audio Message" )
	void StartPlayback();

	/** Continues playing next dialoge in the mDialogue array  */
	UFUNCTION()
	void ContinuePlayback();

	/** Removes all unplayed dialogues and stops the current one.  */
	UFUNCTION( BlueprintCallable, Category = "Audio Message" )
	void CancelPlayback();

	/** Called when all dialogue waves have finished playing or we canceled the dialogue */
	void FinishPlayback();

	/** Gets current dialogue */
	UFUNCTION( BlueprintPure, Category = "Audio Message" )
	FORCEINLINE FAudioSubtitlePair GetCurrentDialogue(){ return mCurrentDialogue; }

	/** Does the setup for playing next part in the dialogue */
	UFUNCTION( BlueprintNativeEvent, Category = "AudioMessage" )
	void PlayNextDialogue();

	UFUNCTION( BlueprintCallable, Category = "AudioMessage" )
	void AssignOnConcludedDelegate( FAudioMessageConcludedDelegate concludedDelegate ) { mAudioMessageConcluded = concludedDelegate; }

private:
	/** Used to discard any input we want to consume but not use */
	FORCEINLINE UFUNCTION()
	void DiscardInput() { ; }

public:
	/** The Ak component */
	UPROPERTY()
	class UAkComponent* mAkAudioComponent;

	/** The AK audio to play when "showing" this message */
	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = "Audio Message" )
	TArray< FAudioSubtitlePair > mAudioEvents;

	/** Timer handle for subtitles */
	FTimerHandle mSubtitleTimerHandle;

	/** Current dialogue that is displayed */
	UPROPERTY()
	FAudioSubtitlePair mCurrentDialogue;

	/**Multiplier for time per character to display */
	UPROPERTY( EditDefaultsOnly, Category = "Audio Message" )
	float mSubtitleTimeMultiplier;



private:
	UPROPERTY( )
	FAudioMessageConcludedDelegate mAudioMessageConcluded;

	UPROPERTY()
	class UInputComponent* mAudioMessageInputComponent;
};
