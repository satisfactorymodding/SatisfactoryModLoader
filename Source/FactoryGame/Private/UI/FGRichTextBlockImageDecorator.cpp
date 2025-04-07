#include "UI/FGRichTextBlockImageDecorator.h"

TSharedPtr<ITextDecorator> UFGRichTextBlockImageDecorator::CreateDecorator(URichTextBlock* InOwner){ return Super::CreateDecorator(InOwner); }
const FSlateBrush* UFGRichTextBlockImageDecorator::FindImageBrush(FName TagOrId, bool bWarnIfMissing){ return Super::FindImageBrush(TagOrId, bWarnIfMissing); }