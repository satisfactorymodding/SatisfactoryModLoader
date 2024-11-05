// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "FGMessageBase.generated.h"

UENUM( BlueprintType )
enum class EMessageType : uint8
{
	MT_PIMARY = 0			UMETA( DisplayName = "Inbox" ),
	MT_TUTORIAL = 1			UMETA( DisplayName = "Tutorial" ),
	MT_SPAM = 2				UMETA( DisplayName = "Spam" ),
	MT_UNDEFINED = 3		UMETA( DisplayName = "All" )
};

/**
 * An old legacy class from when we had both pure text messages and audio messages. Now, we only have audio messages, and text messages have
 * been replaced with notifications. The relevant parts of this class could be moved to UFGAudioMessage, after which this class could be deleted.
 */
UCLASS( BlueprintType, Blueprintable )
class FACTORYGAME_API UFGMessageBase : public UUserWidget
{
	GENERATED_BODY()
public:
	/** Gets the default object of the message class */
	UFUNCTION( BlueprintPure, Category = "Message|Utilities", meta = ( DeterminesOutputType = "inClass" ) )
	static UObject* GetMessageDefaultObject( TSubclassOf< UFGMessageBase > inClass );

	virtual int32 GetMessagePriority() const { return 0; }

public:
	/** I think this may be the title */
	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = "Message" )
	FText mTitle;

	/** Preview text when a message is added */
	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = "Message" )
	FText mPreviewText;

	/** Should the message be displayed in a popup? */
	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = "Message" )
	bool mIsPopup;

	/** Who sent the message */
	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = "Message" )
	TSubclassOf< class UFGMessageSender > mSenderClass;

	/** What type is it */
	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = "Message" )
	EMessageType mType;

	/** Images to display in the codex */
	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = "Message" )
	TArray< class UTexture2D* > mImages;
};
