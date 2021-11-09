// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"
#include "FGSettings.h"
#include "FGIconLibrary.generated.h"

UENUM( BlueprintType )
enum class EIconType : uint8
{
	ESIT_Building,
	ESIT_Part,
	ESIT_Equipment,
	ESIT_Monochrome,
	ESIT_Material,
	ESIT_Custom
};

USTRUCT( Blueprintable )
struct FACTORYGAME_API FIconData
{
	GENERATED_BODY()

	FIconData() : ID( INDEX_NONE ), Hidden( false ), SearchOnly( false ), Animated( false ) { Texture = nullptr; }

	// ID's must be unique! They are assign when generating sign data and will never be modified after being used. Do not manually assign
	// this.
	UPROPERTY( VisibleDefaultsOnly, Category = "Icon Data" )
	int32 ID;

	// The actual texture data that will be rendered. WARNING! Only set this for Monochrome elements. All other elements will be gathered
	// automatically.
	UPROPERTY( EditDefaultsOnly, Category = "Icon Data" )
	TSoftObjectPtr< UObject > Texture;

	// The name of this icon, generally pulled from the descriptor this icon resides in. For Monochrome Icons, set the desired name here
	UPROPERTY( EditDefaultsOnly, Category = "Icon Data" )
	FText IconName;

	// Which category this icon belongs to. This is assigned when generating the icon data. Monochrome elements will also automatically
	// assign this
	UPROPERTY( VisibleDefaultsOnly, Category = "Icon Data" )
	EIconType IconType;

	// This is a way for design to manually "remove" the icon from the list of available choices, it will still exist, but not be retrieved
	// when browsing
	UPROPERTY( EditDefaultsOnly, Category = "Icon Data" )
	bool Hidden;

	// This will only appear if searched for directly
	UPROPERTY( EditDefaultsOnly, Category = "Icon Data" )
	bool SearchOnly;

	// Should this Icon Animate?
	UPROPERTY( EditDefaultsOnly, Category = "Icon Data" )
	bool Animated;
};


/**
 * Icon Library = Holds database of all icon data available to players for use on signs (maybe beacons?). As well as helper functions for accessing the data via bp
 */
UCLASS( BlueprintType, Blueprintable, abstract )
class FACTORYGAME_API UFGIconLibrary : public UObject
{
	GENERATED_BODY()
	
public:
	UFGIconLibrary();

	/** Helper to get icon library without going through UFGGlobalSettings */
	static UFGIconLibrary* Get();

	/** Returns the full array of all icons available */
	UFUNCTION( BlueprintPure, Category = "Icon Data Settings" )
	TArray< FIconData >& GetIconData() { return mIconData; }

	/** Attempts to retrieve the index of an icon with the corresponding texture */
	UFUNCTION( BlueprintCallable, Category = "Icon Data Settings" )
	int32 GetIconIDForTexture( class UObject* texture );

	// Get the texture from a IconData element. Will sync load if needed
	UFUNCTION( BlueprintCallable, Category = "IconLibrary|Icon Settings" )
	static UObject* GetTextureFromIconData( UPARAM( ref ) const FIconData& iconData );

	// Get the ID from an IconData element
	UFUNCTION( BlueprintCallable, Category = "IconLibrary|Icon Settings" )
	static int32 GetIDFromIconData( UPARAM( ref ) const FIconData& iconData );

	// Get the ID from an IconData element
	UFUNCTION( BlueprintCallable, Category = "IconLibrary|Icon Settings" )
	static bool GetIsAnimatedFromIconData( UPARAM( ref ) const FIconData& iconData );

	// Get the Text Name from an IconData element
	UFUNCTION( BlueprintCallable, Category = "IconLibrary|Icon Settings" )
	static FText GetIconNameFromIconData( UPARAM( ref ) const FIconData& iconData );

	// Get the Icon Type from an IconData element
	UFUNCTION( BlueprintCallable, Category = "IconLibrary|Icon Settings" )
	static EIconType GetIconTypeFromIconData( UPARAM( ref ) const FIconData& iconData );


	/*	Loop through all schematics and their recipes, add all icons encountered. Adds any manually added elements from the MonochromeData array. 
	*	Icon types are determined from the item descriptor types. ID's are assigned and ensured unique (never manually set an elements ID)
	*	Will not add duplicates. Will not remove any elements that already exist (non-destructive).
	*	If you wish to make an element not exist for the player, use the "Hidden" bool on the element you wish to hide.
	*/
	UFUNCTION( BlueprintCallable, Category = "Icon Data Settings" )
	static FString CompileIconDatabase( TSubclassOf< UFGIconLibrary > iconLibraryClass );

	// This is just for developement and should not be used once the icon data goes live. Hence, a password field to ensure this isn't accidentally called (just to drive home the point of not calling this)
	UFUNCTION( BlueprintCallable, Category = "Icon Data Settings" )
	static FString ClearIconDatabase( TSubclassOf< UFGIconLibrary > iconLibraryClass, FString password );

	/* Get all the icon data from Icon Settings for a given icon type type. If includeHidden is not true, this will filter out those elements */
	UFUNCTION( BlueprintCallable, Category = "Icon Data Settings" )
	static void GetAllIconDataForType( TSubclassOf< UFGIconLibrary > iconLibraryClass, EIconType iconType, bool includeHidden,
									   TArray< FIconData >& out_iconData );

	/** Get the icon data for a specific icon ID */
	UFUNCTION( BlueprintCallable, Category = "Icon Data Settings" )
	static void GetIconDataForIconID( TSubclassOf< UFGIconLibrary > iconLibraryClass, int32 iconID, FIconData& out_iconData );

public:

	/*	List of all Icon Elements and their data to be used as icons (for signs and maybe beacons?).
	*	WARNING! Do not add/remove directly from this list unless you REALLY need to (this is likely not the case, and if it is, then talk to programming for support )
	*	The only property that should ever be manually set in this array is "Hidden"! Do not set the texture directly.
	*/
	UPROPERTY( EditDefaultsOnly, Category = "Icon Data Settings" )
	TArray< FIconData > mIconData;

	/*	Manually add any icons here that should be monochrome type. Then rebuild the icon data.
	*	Removing elements from here will not remove them from the IconData so modifications to this are non-destructive
	*	Do not worry about setting the ID, the id will be manually assigned when compiling the icon data
	*/
	UPROPERTY( EditDefaultsOnly, Category = "Icon Data Settings" )
	TArray< FIconData> mMonochromeIconData;

	/*	Manually add any icons here. Then rebuild the icon data.
	 *	Removing elements from here will not remove them from the IconData so modifications to this are non-destructive
	 *	Do not worry about setting the ID, the id will be manually assigned when compiling the icon data
	 */
	UPROPERTY( EditDefaultsOnly, Category = "Icon Data Settings" )
	TArray< FIconData > mCustomIconData;

	/*	Manually add any animatable materials here
	 */
	UPROPERTY( EditDefaultsOnly, Category = "Icon Data Settings" )
	TArray< FIconData > mMaterialIconData;

};
