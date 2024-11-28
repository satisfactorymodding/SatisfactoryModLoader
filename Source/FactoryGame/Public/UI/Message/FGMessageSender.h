// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "Templates/SubclassOf.h"
#include "Internationalization/Text.h"
#include "FGMessageSender.generated.h"

/**
 * 
 */
UCLASS( BlueprintType, Blueprintable )
class FACTORYGAME_API UFGMessageSender : public UObject
{
	GENERATED_BODY()
public:
	/** Gets the default object so we can access stuff like the texture etc */
	UFUNCTION( BlueprintPure, Category = "Sender|Utilities", meta = ( DeterminesOutputType = "inClass" ) )
	static UObject* GetSenderDefaultObject( TSubclassOf< UFGMessageSender > inClass );
public:
	/** Name of the sender */
	UPROPERTY( BlueprintReadOnly, EditDefaultsOnly, Category = "Sender" )
	FText mSenderName;

	/** Jingle to play when receiving a message from this sender. */
	UPROPERTY( BlueprintReadOnly, EditDefaultsOnly, Category = "Sender" )
	class UAkAudioEvent* mMessageJingle;

	/** Music to play when displaying a presentation from this sender. */
	UPROPERTY( BlueprintReadOnly, EditDefaultsOnly, Category = "Sender" )
	class UAkAudioEvent* mPresentationMusic;

	/** Logo material for this sender. */
	UPROPERTY( BlueprintReadOnly, EditDefaultsOnly, Category = "Sender" )
	class UMaterialInterface* mLogoMaterial;

	/** The tag used when importing messages. Case-insensitive. */
	UPROPERTY( BlueprintReadOnly, EditDefaultsOnly, Category = "Import" )
	FName mImportTag;
};
