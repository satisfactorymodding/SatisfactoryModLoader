// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"
#include "FGChatManager.h"
#include "Blueprint/UserWidget.h"
#include "Components/RichTextBlockDecorator.h"
#include "FGChatMessageRichTextBlockDecorator.generated.h"

/** Base class for text components on chat messages */
UCLASS(Blueprintable)
class FACTORYGAME_API UFGChatMessageComponentWidget : public UUserWidget {
	GENERATED_BODY()
public:
	/** Chat message this component is a part of */
	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = "Chat Message Component" )
	FChatMessageStruct mChatMessage;

	/** Contents of the string inside this message component */
	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = "Chat Message Component" )
	FText mComponentContent;

	/** Metadata applied to the run this component was created from, can be used for additional formatting */
	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = "Chat Message Component" )
	TMap<FString, FString> mComponentMetadata;
};

DECLARE_DELEGATE_RetVal(TSubclassOf<UFGChatMessageComponentWidget>, FGetChatComponentWidgetClassDelegate);

/** Decorator class applied to the chat message */
UCLASS(NotBlueprintable, BlueprintType)
class FACTORYGAME_API UFGChatMessageRichTextBlockDecorator : public URichTextBlockDecorator
{
	GENERATED_BODY()
public:
	/** Chat message that this decorator has been applied to */
	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = "Chat Message Rich Text Block Decorator", meta = (ExposeOnSpawn) )
	FChatMessageStruct mChatMessage;

	/** Message component for the player name formatting */
	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = "Chat Message Rich Text Block Decorator", meta = (ExposeOnSpawn) )
	TSubclassOf<UFGChatMessageComponentWidget> mPlayerNameComponent;

	/** Extension points that can be used to register custom message components */
	static TMap<FString, FGetChatComponentWidgetClassDelegate> CustomComponentWidgetRegistry;

	virtual TSharedPtr<ITextDecorator> CreateDecorator(URichTextBlock* InOwner) override;
};
