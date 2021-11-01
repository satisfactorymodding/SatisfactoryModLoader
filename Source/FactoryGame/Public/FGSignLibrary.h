// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "FGInventoryComponent.h"
#include "FGSignInterface.h"
#include "FGSignTypes.h"
#include "FGSignLibrary.generated.h"


/**
 * Function library to provide support for Signs
 */
UCLASS()
class FACTORYGAME_API UFGSignLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:

	// Takes a raw (markup version) of a sign element and parses it into a SignStringElement structure
	static void ParseStringDataIntoElement( const FString& rawString, FSignStringElement& out_Element );

	// Parse a string pair [attr, value] into a stringElement. Will attempt to parse the value based on the attr type
	static bool ParseAttributeValuePair( const FString& attr, const FString& value, FSignStringElement& out_Element );

	// PArse out sign elements into string format
	static bool ParseOutStringData( const TArray< FSignStringElement >& stringElements, TArray< FString >& out_ElementArray );

	// Takes a Canvas Root. Will 
	UFUNCTION( BlueprintCallable, Category="SignLibrary" )
	static void ConvertCanvasPrefabToStringArray( class UCanvasPanel* canvasRoot, TArray<FString>& out_elementStrings );

	// Combines a template type with user defined data
	static void CombineSignTemplateAndUserElement( const FSignStringElement& templateElement, const FSignStringElement& userElement, FSignStringElement& out_combinedElement  );


	//////////////////////////////////////////////////////////////////////////
	/// Sign Type Descriptor Getters for UI to access from Class Type
	
	// From a SignTypeDescriptor class get the canvas dimensions
	UFUNCTION( BlueprintPure, Category = "SignLibrary|Sign Data" )
	static void GetCanvasDimensionsFromSignDescriptor( const TSubclassOf< class UFGSignTypeDescriptor > signTypeClass, FVector2D& signDimensions );

	// From a SignTypeDescriptor class get the background and foreground color
	UFUNCTION( BlueprintPure, Category = "SignLibrary|Sign Data" )
	static void GetDefaultColorsFromSignDescriptor( const TSubclassOf< class UFGSignTypeDescriptor > signTypeClass, FLinearColor& foregroundColor, FLinearColor& backgroundColor, FLinearColor& auxiliaryColor );

	// From a SignTypeDescriptor class get the map of all text element names to their default FString data
	UFUNCTION( BlueprintPure, Category = "SignLibrary|Sign Data" )
	static void GetTextElementNameMapFromSignDescriptor( const TSubclassOf< class UFGSignTypeDescriptor > signTypeClass, TMap< FString, FString >& textElementMap );

	// From a SignTypeDescriptor class get the map of all icon element names to their default Texture2D data
	UFUNCTION( BlueprintPure, Category = "SignLibrary|Sign Data" )
	static void GetIconElementNameMapFromSignDescriptor( const TSubclassOf< class UFGSignTypeDescriptor > signTypeClass, TMap< FString, class UObject* >& iconElementMap );

	// From a SignTypeDescriptor class get array of all prefab layout classes
	UFUNCTION( BlueprintPure, Category = "SignLibrary|Sign Data" )
	static void GetPrefabLayoutsFromSignDescriptor( const TSubclassOf< class UFGSignTypeDescriptor > signTypeClass, TArray< TSubclassOf< UFGSignPrefabWidget > >& prefabArray );


};