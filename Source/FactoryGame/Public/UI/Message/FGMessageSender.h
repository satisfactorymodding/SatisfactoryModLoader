// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
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

	/** Mail adress of the sender */
	UPROPERTY( BlueprintReadOnly, EditDefaultsOnly, Category = "Sender" )
	FText mSenderMail;

	/** Image of the sender */
	UPROPERTY( BlueprintReadOnly, EditDefaultsOnly, Category = "Sender" )
	class UTexture2D* mTexture;
};
