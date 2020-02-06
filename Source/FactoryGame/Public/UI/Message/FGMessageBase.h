// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Array.h"
#include "SubclassOf.h"
#include "UObject/Class.h"

#include "UMG.h"
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
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
 * 
 */
UCLASS( BlueprintType, Blueprintable )
class FACTORYGAME_API UFGMessageBase : public UUserWidget
{
	GENERATED_BODY()
public:
	/** Returns the owning fgpawn by looking at ower and vehicle driver */
	class AFGCharacterPlayer* GetFGCharacter();

	/** Gets the default object of the message class */
	UFUNCTION( BlueprintPure, Category = "Message|Utilities", meta = ( DeterminesOutputType = "inClass" ) )
	static UObject* GetMessageDefaultObject( TSubclassOf< UFGMessageBase > inClass );
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
