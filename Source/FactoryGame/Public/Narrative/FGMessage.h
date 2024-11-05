// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "UI/Message/FGAudioMessage.h"
#include "FGMessage.generated.h"

DECLARE_LOG_CATEGORY_EXTERN( LogNarrative, Log, All );

UENUM( BlueprintType )
enum class EMessageSharing : uint8
{
	EMS_AlwaysShare				UMETA( DisplayName = "Always Share" ),
	EMS_NeverShare				UMETA( DisplayName = "Never Share" ),
	EMS_ShareOnProximity		UMETA( DisplayName = "Share on Proximity" )
};

/**
 * Holds information about a message the player can receive.
 * 
 * Each message knows its own triggers and conditions based on UFGAvailabilityDependency. There's no external system pointing to and triggering these messages.
 * This setup was chosen to facilitate the tweaking of individual messages and the expansion of their triggers.
 * It also simplifies tool development, as adjustments only need to be made to message properties instead of navigating through different systems for specific messages.
 * This approach is also more mod-friendly for those wanting to add new messages.
 *
 * We've decided on only one trigger per message because they're checked in real-time and not retroactively.
 * There's still a chance we might create a trigger that doesn't fire due to needing dual inputs (some dependencies are array-based),
 * but that's something we catch in testing. The design team has outlined their trigger requirements, and the current setup meets these needs.
 *
 * Conditions, on the other hand, are more like standard dependencies. We can have multiple conditions, and they're checked retroactively.
 *
 * The key difference is that triggers are what initiate the message being played once their criteria are met,
 * whereas conditions are additional checks that determine if a message can be played but do not initiate message playback themselves.
 */
UCLASS( AutoCollapseCategories=("Legacy") )
class FACTORYGAME_API UFGMessage : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
#if WITH_EDITOR // Editor/Tool Section
	UFUNCTION( BlueprintCallable, Category = "Message|Tools" )
	void MarkMessageAssetDirty();
	UFUNCTION( BlueprintCallable, Category = "Message|Tools" )
	void SaveAsset();
	UFUNCTION(BlueprintCallable, Category = "Message|Tools")
	void SetSubtitles( const TArray<FMessageSubtitle>& subtitles );
	UFUNCTION(BlueprintCallable, Category = "Message|Tools")
	void SetMessage( FText message );
	UFUNCTION( BlueprintCallable, Category = "Message|Tools" )
	UFGAudioMessage* GetTestAudioWidget( UUserWidget* owningWidget, int32 startOnSubtitleIndex = 0, bool skipIncomingAnimation = true );
	UFUNCTION( BlueprintCallable, Category = "Message|Tools" )
	static void GetAllMessageAssetsData( TArray<FAssetData>& out_messageAssets, bool FilterLegacyMessages );
	UFUNCTION( BlueprintCallable, Category = "Message|Tools" )
	bool GenerateSubtitlesForTool( const FString& locaNamespace, const FString& locaKeyRoot );
	UFUNCTION( BlueprintCallable, Category = "Message|Tools" )
	bool FindAudioEventForMessage();
	UFUNCTION( BlueprintCallable, Category = "Message|Tools" )
	void SetTrigger( class UFGAvailabilityDependency* inTrigger ) { mTrigger = inTrigger; }
	TArray<FString> mEditorGeneratedErrorMessages;
	TArray<FString> mEditorGeneratedWarningMessages;
#endif

	/** Returns all message assets in the game. Ignores legacy messages */
	static TArray<UFGMessage*> GetAllMessageAssets();

	bool operator<(const UFGMessage& otherMessage) const;
	
	UFUNCTION( BlueprintCallable, Category = "Message" )
	TArray<FMessageSubtitle> GetSubtitles();

	/** Does any subtitle in this message contain a presentation slide */
	UFUNCTION( BlueprintPure, Category = "Message" )
	bool DoesMessageContainPresentation() const;

	/** Returns how far away other players will hear this message. Used for local messages that is marked for sharing */
	float GetSharingDistance() const;
	
	/** 
	 * Determines whether a message is classified as important. Important messages are intended to be accessible in the codex to all players
	 * even if they missed them, provided at least one player has played them.
	 */
	bool IsMessageConsideredImportant() const;

	/** Checks if all conditions within the message are met for a given world. */
	bool AreConditionsMet( UWorld* world ) const;
	/** Checks if all player specific conditions within the message are met for a given world. */
	bool ArePlayerSpecificConditionssMet( class AFGPlayerState* playerState ) const;
	/** Checks if all local conditions within the message are met for a given world. */
	bool AreLocalConditionsMet( UWorld* world ) const;
	
	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = "Message" )
	FText mTitle;
	
	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = "Message", meta = (MultiLine = "true") )
	FText mMessage;

	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = "VO" )
	TSoftObjectPtr< class UAkAudioEvent > mAudioEvent;

	/** These are the subtitle for this message generated from mMessage and tweaked in narrative sync tool. */
	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = "Message" )
	TArray< FMessageSubtitle > mSubtitles;
	
    UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = "Message" )
	class UFGOnboardingStep* mOnboardingStep;

	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = "UI" )
    TSubclassOf<class UFGPhasePresentationWidget> mPhasePresentation;

	/** Specifies who will hear this message except for the player triggering it */
	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = "Sharing" )
	EMessageSharing mMessageSharing;
	
	/** How far away will other players hear this message. If set to 0 default value from FGNarrativeSettings will be used. Only relevant if mMessageSharing is set to EMessageSharing::EMS_ShareOnProximity */
	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = "Sharing", meta=(EditCondition="mMessageSharing==EMessageSharing::EMS_ShareOnProximity", EditConditionHides) )
	float mMessageSharingDistanceOverride;

	/** When this dependency is met we try to play the message */
	UPROPERTY( EditDefaultsOnly, Instanced, BlueprintReadOnly, Category = "Trigger" )
	class UFGAvailabilityDependency* mTrigger;

	/** Delay duration before the message is played after being triggered. Accounts for the time spent in queue if another message is playing.
	 * This is useful when we want to make sure a message isn't played to soon after the trigger is triggered. Keep in mind if we trigger
	 * a message with a long trigger delay it might sit at the top of the queue for a long time until the delay is is over.  */
	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = "Trigger" )
	float mTriggerDelay;

	/** This message can only be played if these conditions are met. The conditions never trigger messages */
	UPROPERTY( EditDefaultsOnly, Instanced, BlueprintReadOnly, Category = "Trigger" )
	TArray<class UFGAvailabilityDependency*> mConditions;

	/** Can this message be queued if another message is already playing */
	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = "Trigger" )
	bool mCanBeQueued;

	/** Can this message be played more than once */
	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = "Trigger" )
	bool mCanBeRepeated;

	/** Can this message interrupt another already playing message */
	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = "Trigger" )
	bool mCanInterrupt;

	/** Whether or not this message will trigger interrupt messages when interrupting another message. */
	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = "Trigger" )
	bool mPlayInterruptMessage = true;

	/** If this message is triggered while the message cooldown is active this message will not play */
	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = "Trigger" )
	bool mBlockedByCooldown;

	/** If a message with higher priority than what is currently in the queue it will clear out the queue and play directly */
	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = "Trigger" )
	float mPriority;

	/** The unlocks you get when playing this message. Only really tested for UFGUnlockSAMIntensity at the moment but should work for all unlocks */
	UPROPERTY( EditDefaultsOnly, Instanced, Category = "Unlocks" )
	TArray< class UFGUnlock* > mUnlocks;

	// Begin legacy properties. Only left for old message support
	UPROPERTY( VisibleDefaultsOnly, BlueprintReadOnly, Category = "Legacy" )
	TSoftClassPtr< class UFGMessageSender > mSenderClass;

	/** The Dialogue, Audio and subtitles, to play and display when this message is played */
	UPROPERTY( VisibleDefaultsOnly, BlueprintReadOnly, Category = "Legacy" )
	TArray< FMessageDialogue > mDialogueData;

	/** Multiplier for time per character to display */
	UPROPERTY( VisibleDefaultsOnly, Category = "Legacy" )
	float mSubtitleTimeMultiplier;

	/** Text that can be displayed instead for (or added to) subtitle text when displaying the message */
	UPROPERTY( VisibleDefaultsOnly, Category = "Legacy", meta = (MultiLine = true) )
	FText mOverrideText;
	
	UPROPERTY( VisibleDefaultsOnly, BlueprintReadOnly, Category = "Legacy" )
	bool mIsLegacyMessage;

};
