#include "Fonts/FontMeasure.h"
#include "Widgets/Layout/SScaleBox.h"
#include "Components/RichTextBlockDecorator.h"
#include "Components/RichTextBlockImageDecorator.h"

class SFGRichInlineImage : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS( SFGRichInlineImage )
		: _WidthRatio(1.0f)
	{}
	SLATE_ARGUMENT( float, WidthRatio )
	SLATE_END_ARGS()

public:
	void Construct( const FArguments& InArgs, const FSlateBrush* Brush, const FTextBlockStyle& TextStyle, TOptional< int32 > Width,
					TOptional< int32 > Height, EStretch::Type Stretch)
	{
		check( Brush );

		const TSharedRef< FSlateFontMeasure > FontMeasure = FSlateApplication::Get().GetRenderer()->GetFontMeasureService();
		float IconHeight = (float)FontMeasure->GetMaxCharacterHeight( TextStyle.Font, 1.0f );
		float IconWidth = IconHeight * InArgs._WidthRatio;
		
		ChildSlot[ SNew( SBox )
					   .HeightOverride( IconHeight )
					   .WidthOverride( IconWidth )[ SNew( SScaleBox )
														.Stretch( Stretch )
														.StretchDirection( EStretchDirection::DownOnly )
														.VAlign( VAlign_Center )[ SNew( SImage ).Image( Brush ) ] ] ];
	}
};

class FFGRichInlineImage : public FRichTextDecorator
{
public:
	FFGRichInlineImage( URichTextBlock* InOwner, URichTextBlockImageDecorator* InDecorator ) :
		FRichTextDecorator( InOwner ), Decorator( InDecorator )
	{
	}

	virtual bool Supports( const FTextRunParseResults& RunParseResult, const FString& Text ) const override
	{
		if( RunParseResult.Name == TEXT( "img" ) && RunParseResult.MetaData.Contains( TEXT( "id" ) ) )
		{
			const FTextRange& IdRange = RunParseResult.MetaData[ TEXT( "id" ) ];
			const FString TagId = Text.Mid( IdRange.BeginIndex, IdRange.EndIndex - IdRange.BeginIndex );

			const bool bWarnIfMissing = false;
			return Decorator->FindImageBrush( *TagId, bWarnIfMissing ) != nullptr;
		}

		return false;
	}

protected:
	virtual TSharedPtr< SWidget > CreateDecoratorWidget( const FTextRunInfo& RunInfo, const FTextBlockStyle& TextStyle ) const override
	{
		const bool bWarnIfMissing = true;
		const FSlateBrush* Brush = Decorator->FindImageBrush( *RunInfo.MetaData[ TEXT( "id" ) ], bWarnIfMissing );

		if( ensure( Brush ) )
		{
			// For out use-case we just need to scale to font height, then scale X by the ratio of the original image
			TOptional< int32 > Height;
			TOptional< int32 > Width;
			// Calculate the AspecRatio of the image so that the widget can scale itself according to it's desired ratio in the Slate Element
			// since the slate element will determine it's height from the rendered font in it's own context.
			float WidthRatio = Brush->ImageSize.X/(float)Brush->ImageSize.Y;

			// Constrain the image to the widget without overflows 
			EStretch::Type Stretch = EStretch::ScaleToFit;

			return SNew( SFGRichInlineImage, Brush, TextStyle, Width, Height, Stretch ).WidthRatio(WidthRatio);
		}
		return TSharedPtr< SWidget >();
	}

private:
	URichTextBlockImageDecorator* Decorator;
};