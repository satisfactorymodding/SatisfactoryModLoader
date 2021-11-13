// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once


#include "FactoryGame.h"
#include "UMG.h"
#include "UI/FGSignTextWidget.h"
#include "UI/FGSignElementWidget.h"
#include "FGSignTypes.generated.h"



USTRUCT( BlueprintType, Blueprintable )
struct FSignConstraints
{
	GENERATED_BODY()

	UPROPERTY( EditDefaultsOnly, Category = "Widget Sign" )
	int32 MaxElements;
};

//UENUM( BlueprintType )
//enum class ESignElementType : uint8
//{
//	ESET_Text,
//	ESET_Icon
//};

UENUM( BlueprintType )
enum class ESignSizeDefinition : uint8
{
	ESSD_VERYSMALL,
	ESSD_SMALL,
	ESSD_MEDIUM,
	ESSD_LARGE,
	ESSD_VERYLARGE
};


namespace SignTags
{
	extern const FString OPEN_TAG;
	extern const FString CLOSE_TAG;
	const int32 PROP_LENGTH = 3;

	const FString TEST_STR_CANVAS = "< CLA = CA >< EID = 0 >< POS = 0, 0 >";
	const FString TEST_STR_TEXTBLOCK = "< CLA = TB >< EID = 1 >< POS = 100, 300 >< SIZ = 350, 100 ><TBT = This is the text that will be displayed ><ECD = #66FFDD >< EAD = 1 >< ESD = 1 >";
	const FString TEST_STR_TEXTBLOCK2 = "< CLA = TB >< EID = 2 >< POS = 15, 600 >< SIZ = 350, 100 ><TBT = Here is some new text ><ECD = #66FFDD >< EAD = 0 >< ESD = 1 >";
	const FString TEST_STR_ICON = "< CLA = II >< EID = 2 >< POS = 150, 101 >< IID = 13 >";

	const FString DEFAULT_TEXTBLOCK = "< CLA = TB >< EID = 0 >< POS = 35, 200 >< SIZ = 400, 100 >< TBT = ENTER TEXT >< ECD = #66FFDD >< EAD = 0>< ESD = 1 >";
	const FString DEFAULT_ICON = "< CLA = II >< EID = 0 >< IID=0 >< POS = 35, 35 >< SIZ = 128, 128 >< ECD = #FFFFFF >< ESD = 2 >";

	enum class AttributeTag : uint8
	{
		EAT_NONE,
		EAT_CLA,
		EAT_EID,
		EAT_POS,
		EAT_SIZ,
		EAT_TBT,
		EAT_IID,
		EAT_ESD,
		EAT_ECD,
		EAT_EAD
	};

	static const TMap< FString, AttributeTag > StringToAttributeTag
	{
		{ "CLA", AttributeTag::EAT_CLA },
		{ "EID", AttributeTag::EAT_EID },
		{ "POS", AttributeTag::EAT_POS },
		{ "SIZ", AttributeTag::EAT_SIZ },
		{ "TBT", AttributeTag::EAT_TBT },
		{ "IID", AttributeTag::EAT_IID },
		{ "ESD", AttributeTag::EAT_ESD },
		{ "ECD", AttributeTag::EAT_ECD },
		{ "EAD", AttributeTag::EAT_EAD },

	};

}

USTRUCT( BlueprintType )
struct FACTORYGAME_API FSignStringElement
{
	GENERATED_BODY()

public:
	FSignStringElement() :
		RawString( "" ),
		WidgetClass( nullptr ),
		Position( FVector2D::ZeroVector ),
		Size( FVector2D::ZeroVector ),
		ID( INDEX_NONE ),
		TextString( "" ),
		Color( FColor::White ),
		IconID( -1 ),
		SizeSpecifier( 0 ),
		Alignment( 0 ),
		WasParsed( false )
	{}

	FSignStringElement( const FSignStringElement& other ) :
		RawString( other.RawString ),
		WidgetClass( other.WidgetClass ),
		Position( other.Position ),
		Size( other.Size ),
		ID( other.ID ),
		TextString( other.TextString ),
		Color( other.Color ),
		IconID( other.IconID ),
		SizeSpecifier( other.SizeSpecifier ),
		Alignment( other.Alignment ),
		WasParsed( other.WasParsed )
	{}

	FSignStringElement& operator =( const FSignStringElement& other )
	{
		RawString = other.RawString;
		WidgetClass = other.WidgetClass;
		Position = other.Position;
		Size = other.Size;
		ID = other.ID;
		TextString = other.TextString;
		Color = other.Color;
		IconID = other.IconID;
		SizeSpecifier = other.SizeSpecifier;
		Alignment = other.Alignment;
		WasParsed = other.WasParsed;
		return *this;
	}

	// Invalid / Null element
	static FSignStringElement InvalidStringElement;

	// Debug function for printing out all values of the element
	static void DebugPrintAttributes(const  FSignStringElement& stringElement )
	{
		UE_LOG( LogSigns, Log, TEXT(" -----  Debug Attributes for String Element  -------\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s"),
		SHOWVAR( stringElement.WidgetClass),SHOWVAR( stringElement.Position),SHOWVAR( stringElement.Position ), SHOWVAR( stringElement.ID),
		SHOWVAR( stringElement.TextString),SHOWVAR( stringElement.Color),SHOWVAR( stringElement.IconID),
		SHOWVAR( stringElement.SizeSpecifier),SHOWVAR( stringElement.Alignment),SHOWVAR( stringElement.WasParsed));
	}

	bool IsRootType() const
	{
		if( WasParsed == false )
		{
			return false;
		}

		// At the time of writing, we do not support deep nests. So each panel type should be seen as a root element (just below the main Canvas)
		if( WidgetClass->IsChildOf( UPanelWidget::StaticClass() ) )
		{
			return true;
		}

		return false;
	}

	void SetID( int32 newID )
	{
		if( newID != ID )
		{
			IsDirty = true;
			ID = newID;
		}
	}

	void SetIconID( int32 newIconID )
	{
		if( newIconID != IconID )
		{
			IsDirty = true;
			IconID = newIconID;
		}
	}

	void SetPosition( FVector2D newPosition )
	{
		if( newPosition != Position )
		{
			IsDirty = true;
			Position = newPosition;
		}
	}

	void SetSize( FVector2D newSize )
	{
		if( newSize != Size )
		{
			IsDirty = true;
			Size = newSize;
		}
	}

	void SetSizeSpecifier( ESignSizeDefinition newSizeSpecification )
	{
		if( (int32)newSizeSpecification != SizeSpecifier )
		{
			IsDirty = true;
			SizeSpecifier = (int32)newSizeSpecification;
		}
	}

	void SetAlignment( int32 newAlignment )
	{
		if( newAlignment != Alignment )
		{
			IsDirty = true;
			Alignment = newAlignment;
		}
	}

	void SetText( FString newText )
	{
		if( newText != TextString )
		{
			IsDirty = true;
			TextString = FString( newText );
		}
	}

	void SetColor( FLinearColor newColor )
	{
		if( newColor != Color )
		{
			IsDirty = true;
			Color = newColor;
		}
	}


	// Helpers for deducing type easily (this is a little ugly, atm just used for the list layout elements to determine which icons and naming to use)
	bool IsProbablyImageElement() const { return IconID != INDEX_NONE && TextString.IsEmpty(); }
	bool IsProbablyTextElement() const { return IconID == INDEX_NONE && !TextString.IsEmpty(); }

	// Is this item for realz? Or just an empty representation used as a null check
	bool IsValid() const { return ID != INDEX_NONE && WasParsed; }

	UPROPERTY()
	FString RawString;

	//////////////////////////////////////////////////////////////////////////
	/// Properties that are filled after parsing

	UPROPERTY()
	TSubclassOf< class UFGSignElementWidget > WidgetClass;

	UPROPERTY()
	FVector2D Position;

	UPROPERTY()
	FVector2D Size;

	UPROPERTY()
	int32 ID;

	UPROPERTY()
	FString TextString;

	UPROPERTY()
	FLinearColor Color;

	UPROPERTY()
	int32 IconID = -1;

	UPROPERTY()
	int32 SizeSpecifier = 1;

	// @todo - Come up with a good way to store alignment info
	UPROPERTY()
	int32 Alignment = 0;

	// A validity check of sorts. Will be false if the parsing failed / early outted. If so this element should not be considered valid
	UPROPERTY()
	bool WasParsed = false;

	// If a property has changed but the raw string hasn't been updated then this is out of date. Meaning it is no synchronized with the full sign data
	UPROPERTY()
	bool IsDirty = false;



};


USTRUCT( BlueprintType )
struct FACTORYGAME_API FSignStringData
{
	GENERATED_BODY()

	FSignStringData()
	{}

	FSignStringData( TArray< FString > stringArr ) :
		ElementArray( stringArr )
	{
		ParsedStringElements.Empty();
	}

	static FSignStringData Empty;

	/*
	All elements and layers must have unique IDs. Layers and Elements cannot share an ID as it is just an int32 used to iterate the hierarchy
	If a layer and an element share an ID they wont be differentiable for much of the code and will lead to undefined behaviour

	EID - Specifies the ID of Elements - These must all be unique
	CLA - Class representation for widget. Corresponds to an Unreal Widget Type
			CA = Canvas
			HL = Horizontal List
			VL = Vertical List
			TB = Text Block
			II = Icon Image

			Class Attributes - Properties to define how the element should be laid out / appear
				POS - Relative Position of this element. Only valid if its parent is a free placement panel type (Canvas)
				SIZ = The size of the slot
				TBT = Text Block Text - The string to display in a text block
				IID = Icon ID - Value to use as lookup for Icon to display
				ESD = Element Size Definition - Integer value that corresponds to an elements size
				ECD = Element Color Data - RGB representation of the color of this element
				EAD = Element Alignment Definition - Optional - Alignment


	// Visualized with spaces to make reading easier. Actual files will not have spaces
	< CLA=CA >< EID = 0 >< POS = 0,0 >< /CA >
	< CLA=TB >< EID = 1 >< POS = 102,101 ><TBT = This is the text that will be displayed ><ECD = #66FFDD >< ESD = 1 >< /TB >
	< CLA=II >< EID = 2 >< POS = 150,101 >< IID = 13 >< /II >

	*/
	
	// Call to parse the string elements into SignStringElements
	void ParseStringElements();

	// Call to fill the saved string element array with the updated element data. This should be called when apply data from the widget editor
	void ParseOutStringElements();

	// Adds a new element from a templated string ( so that the object is partially constructed ). A new (valid) ID will be assigned upon adding
	// Returns The ID of the new element that is generated
	int32 AddElement( FString elementStrData );

	// Removes an Element
	bool RemoveElement( int32 elementID );

	// Get unused ID
	int32 GetNewUniqueID();

	// Get a reference to a String Element with an ID
	FSignStringElement& GetStringElementRefFromID( int32 id );

	// Get the String Element for a specified ID
	bool GetStringElementCopyFromID( int32 id, FSignStringElement& out_stringElement ) const;

	// Get a reference to the ElementArray
	FORCEINLINE TArray<FSignStringElement>& GetStringElements() { return ParsedStringElements; }

	// True if the string elements have been parsed out from the raw strings
	FORCEINLINE bool GetIsParsed() const { return IsParsed; }

	// Check will return true if there is not string elements present
	FORCEINLINE bool IsEmpty() const { return ElementArray.Num() <= 0; }

	// Set the string ElementArray and immediately parse out the strings into string elements
	void SetElementArray( const TArray<FString>& elementArray )
	{
		ElementArray.Empty();
		ElementArray.Append( elementArray );
		ParsedStringElements.Empty();
		ParseStringElements();
	}

	// Check to see if a given element ID exists in this data
	bool ElementIDExists( int32 id ) 
	{ 
		if( IsParsed )
		{
			return ParsedStringElements.ContainsByPredicate( [&] ( const FSignStringElement& element ) { return element.ID == id; } );
		}

		return false;
	}

	// Return a copy of a sign string element (useful when pulling a templated copy that we want to fill out with user set info)
	void GetSignStringElementByID( int32 id, FSignStringElement& out_stringElement ) const
	{ 
		out_stringElement = *ParsedStringElements.FindByPredicate( [ & ]( const FSignStringElement& element ) { return element.ID == id; } );
	}


public:

	// FString array of element data. Each index pertains to 1 element. The string will be parsed and its type/properties will be pulled from the string
	UPROPERTY( SaveGame )
	TArray<FString> ElementArray;

	// Array of sign string elements that is constructed when parsing. This is not saved as it is essentially a "processed" version of mElementArray for easier access
	UPROPERTY()
	TArray< FSignStringElement > ParsedStringElements;

private:
	// Has this Data been parsed? If false we will need / want to parse it before utilizing
	UPROPERTY()
	bool IsParsed = false;


};

// Blueprint Data class for holding information that can be shared between multiple FGBuildableWidgetSign classes
UCLASS( Blueprintable, Abstract )
class FACTORYGAME_API UFGSignTypeDescriptor : public UObject
{
	GENERATED_BODY()

public:
	UFGSignTypeDescriptor();

	UFUNCTION( BlueprintPure, Category = "Sign Data" )
	bool IsValidElementName( const FString& elementName ) 
	{
		TArray< FString > keys;
		mTextElementNameMap.GenerateKeyArray( keys );
		if( keys.Contains( elementName ) )
		{
			return true;
		}

		keys.Empty();
		mIconElementNameMap.GenerateKeyArray( keys );
		if( keys.Contains( elementName ) )
		{
			return true;
		}

		return false;
	}

	UFUNCTION( BlueprintPure, Category = "Sign Data" )
	FORCEINLINE FVector2D GetSignCanvasDimensions() { return mSignCanvasDimensions; }

	UFUNCTION( BlueprintPure, Category = "Sign Data" )
	FORCEINLINE FLinearColor GetDefaultForegroundColor() { return mDefaultForegroundColor; }

	UFUNCTION( BlueprintPure, Category = "Sign Data" )
	FORCEINLINE FLinearColor GetDefaultBackgroundColor() { return mDefaultBackgroundColor; }

	UFUNCTION( BlueprintPure, Category = "Sign Data" )
	FORCEINLINE FLinearColor GetDefaultAuxiliaryColor() { return mDefaultAuxiliaryColor; }

	UFUNCTION( BlueprintPure, Category = "Sign Data" )
	TMap< FString, FString >& GetTextElementNameMap() { return mTextElementNameMap; }

	UFUNCTION( BlueprintPure, Category = "Sign Data" )
	TMap< FString, class UObject* >& GetIconElementNameMap() { return mIconElementNameMap; }

	UFUNCTION( BlueprintPure, Category = "Sign Data" )
	TArray< TSubclassOf< UFGSignPrefabWidget > >& GetPrefabArray() { return mPrefabArray; }


public:
	
	UPROPERTY( EditDefaultsOnly, Category = "Sign Data" )
	FVector2D mSignCanvasDimensions;

	UPROPERTY( EditDefaultsOnly, Category = "Sign Data" )
	FLinearColor mDefaultForegroundColor;

	UPROPERTY( EditDefaultsOnly, Category = "Sign Data" )
	FLinearColor mDefaultBackgroundColor;

	UPROPERTY( EditDefaultsOnly, Category = "Sign Data" )
	FLinearColor mDefaultAuxiliaryColor;

	UPROPERTY( EditDefaultsOnly, Category = "Sign Data" )
	TMap< FString, FString > mTextElementNameMap;

	UPROPERTY( EditDefaultsOnly, Category = "Sign Data" )
	TMap< FString, class UObject* > mIconElementNameMap;

	UPROPERTY( EditDefaultsOnly, Category = "Sign Data" )
	TArray< TSubclassOf< class UFGSignPrefabWidget > > mPrefabArray;


};


/**
 *	Stuct for saving out text data that can be converted back into a TMap for ease of use
 */
USTRUCT()
struct FACTORYGAME_API FPrefabTextElementSaveData
{
	GENERATED_BODY()

	UPROPERTY( SaveGame )
	FString ElementName;

	UPROPERTY( SaveGame )
	FString Text;
};

/**
 *	Stuct for saving out icon data that can be converted back into a TMap for ease of use
 */
USTRUCT()
struct FACTORYGAME_API FPrefabIconElementSaveData
{
	GENERATED_BODY()

	UPROPERTY( SaveGame )
	FString ElementName;

	UPROPERTY( SaveGame )
	int32 IconID;
};



/**
 * Structure for passing sign save data to and from blueprint so that it is compiled into one location before delivery
 */
USTRUCT( BlueprintType )
struct FACTORYGAME_API FPrefabSignData
{
	GENERATED_BODY()

	UPROPERTY( BlueprintReadWrite, Category = "Prefab Sign Data" )
	TSubclassOf< UUserWidget > PrefabLayout;

	UPROPERTY( BlueprintReadWrite, Category = "Prefab Sign Data" )
	TMap< FString, FString > TextElementData;

	UPROPERTY( BlueprintReadWrite, Category = "Prefab Sign Data" )
	TMap< FString, int32 > IconElementData;

	UPROPERTY( BlueprintReadWrite, Category = "Prefab Sign Data" )
	FLinearColor ForegroundColor;

	UPROPERTY( BlueprintReadWrite, Category = "Prefab Sign Data" )
	FLinearColor BackgroundColor;

	UPROPERTY( BlueprintReadWrite, Category = "Prefab Sign Data" )
	FLinearColor AuxiliaryColor;

	UPROPERTY( BlueprintReadWrite, Category = "Prefab Sign Data" )
	float Emissive;

	UPROPERTY( BlueprintReadWrite, Category = "Prefab Sign Data" )
	float Glossiness;

	UPROPERTY( BlueprintReadWrite, Category = "Prefab Sign Data" )
	TSubclassOf < UFGSignTypeDescriptor > SignTypeDesc;

	// For clients to know if they should call the server RPC to set the data when they receive new data (if from replication don't trigger the RPC as it came from an RPC)
	bool IsFromReplication;
};


UCLASS( Blueprintable, Abstract )
class FACTORYGAME_API UFGSignPrefabWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION( BlueprintCallable, Category = "Sign Data" )
	void SetNameToTextWidgetMap( TMap<FString, class URichTextBlock*>& textWidgetMap ) 
	{
		mNameToTextWidget.Empty();
		mNameToTextWidget.Append( textWidgetMap );
	}

	UFUNCTION( BlueprintCallable, Category = "Sign Data" )
	void SetNameToIconWidgetMap( TMap< FString, class UImage* >& iconWidgetMap )
	{
		mNameToIconWidget.Empty();
		mNameToIconWidget.Append( iconWidgetMap );
	}

	// Getters
	TMap< FString, class URichTextBlock* > GetNameToTextWidgetMap() { return mNameToTextWidget; }
	TMap< FString, class UImage* > GetNameToIconWidgetMap() { return mNameToIconWidget; }

	// The prefab data for this widget - Changes per instance
	UPROPERTY( EditAnywhere, BlueprintReadWrite, Transient, Category = "Sign Data", meta=( ExposeOnSpawn ) )
	FPrefabSignData mPrefabSignData;

 protected:
	UPROPERTY( BlueprintReadWrite, Category = "Sign Data" )
	TMap< FString, class URichTextBlock* > mNameToTextWidget;

	UPROPERTY( BlueprintReadWrite, Category = "Sign Data" )
	TMap< FString, class UImage* > mNameToIconWidget;

};
