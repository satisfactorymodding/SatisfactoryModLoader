// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"
#include "FGSignTypes.h"
#include "FGSettings.h"
#include "FGSignSettings.generated.h"



/**
 * Master settings for Standalone Sign parameters and attributes
 */
UCLASS( abstract )
class FACTORYGAME_API UFGSignSettings : public UFGSettings
{
	GENERATED_BODY()
	
	UFGSignSettings();

public:

	/** Helper to get signs settings without going through UFGGlobalSettings */
	static UFGSignSettings* Get();

	/** Reverse lookup for getting the key name (string) for a sign element type */
	FString GetStringKeyFromAttributeTag( SignTags::AttributeTag tag ) const;

	/** Reverse lookup for getting the key name (string) for a sign element type */
	FString GetStringKeyFromElementClass( TSubclassOf<UWidget> widgetClass ) const;

public:
	/** The size of the grid to use when snapping*/
	UPROPERTY( EditDefaultsOnly, Category = "Sign Data Settings" )
	int32 mGridSize;

	/** Base material to be used for text component material instances */
	UPROPERTY( EditDefaultsOnly, Category = "Sign Data Settings" )
	UMaterial* mTextMaterial;

	/** Base material to be used for icon material instances */
	UPROPERTY( EditDefaultsOnly, Category = "Sign Data Settings" )
	UMaterial* mIconMaterial;

	/** Base material to be used for sign background material instances */
	UPROPERTY( EditDefaultsOnly, Category = "Sign Data Settings" )
	UMaterial* mBackgroundMaterial;

	/** The index in the sign mesh material array pointing to the screen / background material */
	UPROPERTY( EditDefaultsOnly, Category = "Sign Data Settings" )
	int32 mBackgroundMeshMaterialIndex;

	/** Parameter name of color adjustment FVector inside the text material */
	UPROPERTY( EditDefaultsOnly, Category = "Sign Data Settings" )
	FName mTextMaterialColorParam;

	/** Parameter name of color adjustment FVector inside the icon material */
	UPROPERTY( EditDefaultsOnly, Category = "Sign Data Settings" )
	FName mIconMaterialColorParam;

	/** Parameter name of color adjustment FVector inside the background material */
	UPROPERTY( EditDefaultsOnly, Category = "Sign Data Settings" )
	FName mBackgroundMaterialColorParam;

	/** Icon to use in layout editor list */
	UPROPERTY( EditDefaultsOnly, Category = "Sign Data Settings" )
	UTexture2D* mLayerIcon;

	/** Icon to use in layout editor list */
	UPROPERTY( EditDefaultsOnly, Category = "Sign Data Settings" )
	UTexture2D* mTextIcon;

	/** Icon to use in layout editor list */
	UPROPERTY( EditDefaultsOnly, Category = "Sign Data Settings" )
	UTexture2D* mIconIcon;

	/** Icon to use in layout editor list */
	UPROPERTY( EditDefaultsOnly, Category = "Sign Data Settings" )
	UTexture2D* mPanelIcon;


	// String tag to the widget type the string tag represents
	UPROPERTY( EditDefaultsOnly, Category = "Sign Data Settings")
	TMap< FString, TSubclassOf< UWidget > > SignTagToElement;

	// Element size enum to the actual font size it represents for text
	UPROPERTY( EditDefaultsOnly, Category = "Sign Data Settings" )
	TMap< ESignSizeDefinition, int32 > SizeDefinitionToFontSize;

	// Element Size enum to the actual pixel size it represents for icons
	UPROPERTY( EditDefaultsOnly, Category = "Sign Data Settings" )
	TMap< ESignSizeDefinition, int32 > SizeDefinitionToIconSize;


};
