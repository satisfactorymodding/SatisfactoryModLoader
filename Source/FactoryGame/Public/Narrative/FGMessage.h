// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "UI/Message/FGAudioMessage.h"
#include "FGMessage.generated.h"

/**
 * 
 */
UCLASS()
class FACTORYGAME_API UFGMessage : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	void UpdateMessage( const FString& inTitle, const FString& inTrigger, const FString& inMessage, TArray<FString>& out_Results );
#if WITH_EDITOR
	void InitDependency( TSubclassOf<class UFGSchematic> schematicClass );
	void InitDependency( TSubclassOf<class UFGItemDescriptor> itemDescriptorClass );
	void InitDependency( TSubclassOf<class UFGResearchTree> researchTreeClass );
#endif
	
	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = "Message" )
	FText mTitle;

	/** Can this message be played more than once */
	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = "Trigger" )
	bool mCanMessageBeRepeated;
	
	UPROPERTY( EditDefaultsOnly, Instanced, BlueprintReadOnly, Category = "Trigger" )
	class UFGAvailabilityDependency* mTrigger;

	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = "Message" )
	FText mMessage;

	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = "Sender" )
	TSoftClassPtr< class UFGMessageSender > mSenderClass;

	/** The Dialogue, Audio and subtitles, to play and display when this message is played */
	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = "Audio Message" )
	TArray< FMessageDialogue > mDialogueData;

	/** Multiplier for time per character to display */
	UPROPERTY( EditDefaultsOnly, Category = "Audio Message" )
	float mSubtitleTimeMultiplier;

	/** Text that can be displayed instead for (or added to) subtitle text when displaying the message */
	UPROPERTY( EditDefaultsOnly, Category = "Audio Message", meta = (MultiLine = true) )
	FText mOverrideText;

};
