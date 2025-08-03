// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"
#include "Components/RichTextBlockImageDecorator.h"
#include "Misc/DefaultValueHelper.h"
#include "FGRichTextBlockImageDecorator.generated.h"

USTRUCT(Blueprintable, BlueprintType)
struct FFGRichImageRow : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere, Category = Appearance)
	FSlateBrush Brush_XSX;

	UPROPERTY(EditAnywhere, Category = Appearance)
	FSlateBrush Brush_PS5;
};

UCLASS()
class FACTORYGAME_API UFGRichTextBlockImageDecorator : public URichTextBlockImageDecorator
{
	GENERATED_BODY()
	
public:
	virtual TSharedPtr< ITextDecorator > CreateDecorator( URichTextBlock* InOwner ) override;

	virtual const FSlateBrush* FindImageBrush( FName TagOrId, bool bWarnIfMissing ) override;
};
