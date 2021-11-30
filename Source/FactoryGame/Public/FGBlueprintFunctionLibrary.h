// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "FGUseableInterface.h"
#include "FGInventoryComponent.h"
#include "UI/FGPopupWidget.h"
#include "FGOnlineSessionSettings.h"
#include "FGRecipe.h"
#include "FGFactoryColoringTypes.h"
#include "FGBlueprintFunctionLibrary.generated.h"

UENUM( BlueprintType )
enum class EOutlineColor : uint8
{
	OC_NONE				= 0		UMETA( DisplayName = "None" ),
	OC_HOLOGRAMLINE		= 248	UMETA( DisplayName = "Hologram Line" ),
	OC_SOFTCLEARANCE	= 249	UMETA( DisplayName = "Soft Clearance" ),
	OC_DISMANTLE		= 250	UMETA( DisplayName = "Dismantle" ),
	OC_USABLE			= 251	UMETA( DisplayName = "Usable" ),
	OC_HOLOGRAM			= 252	UMETA( DisplayName = "Hologram" ),
	OC_INVALIDHOLOGRAM  = 253	UMETA( DisplayName = "Invalid Hologram" ),
	OC_RED				= 254	UMETA( DisplayName = "Disabled" )
};

UCLASS()
class FACTORYGAME_API UFGBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	/** Helper function to try to fetch the owning actor of a object */
	UFUNCTION( BlueprintPure, Category="Object")
	static AActor* GetOuterActor( const UObject* obj );

	/** Show a outline for the following primitive component */
	UFUNCTION( BlueprintCallable, Category = "Useable" )
	static void ShowOutline( class UPrimitiveComponent* comp, EOutlineColor color );

	/** Let a component occlude the outline */
	UFUNCTION( BlueprintCallable, Category = "Useable" )
	static void OccludeOutlineByComponent( class UPrimitiveComponent* comp, bool occlude );

	/** Let a actor occlude the outline */
	UFUNCTION( BlueprintCallable, Category = "Useable" )
	static void OccludeOutlineByActor( class AActor* actor, bool occlude );

	/** hide the outline for the following primitive component */
	UFUNCTION( BlueprintCallable, Category = "Useable" )
	static void HideOutline( class UPrimitiveComponent* comp );

	UFUNCTION( BlueprintCallable, Category = "Use" )
	static void UpdateUseState( UPARAM( ref ) FUseState& state, TSubclassOf< UFGUseState > newState );

	/** Get all the item descriptors in the game */
	UFUNCTION( BlueprintCallable, Category = "Descriptors" )
	static void Cheat_GetAllDescriptors( TArray< TSubclassOf< class UFGItemDescriptor > >& out_descriptors );

	/** Static Helper to apply common customization data to mesh primitives ( does not work for Instances ) */
	UFUNCTION( BlueprintCallable, Category = "Factory|Customization" )
	static void ApplyCustomizationPrimitiveData( class AActor* actor, const FFactoryCustomizationData& customizationData, int32 colorSlotFallback = 0, class UMeshComponent* onlyApplyToComponent = nullptr  );

	/** Static Helper to apply default factory color data to actors that use the default factory material */
	UFUNCTION( BlueprintCallable, Category = "Factory|Customization" )
	static void ApplyDefaultColorPrimitiveData( class AActor* actor );

	/** Fills a given array with all mesh components residing on a class. Including any blueprint added components */
	UFUNCTION( BlueprintCallable, Category = "Factory|Customization" )
	static void GetAllMeshComponentsInClass( const TSubclassOf< AActor > inClass, TArray< UMeshComponent* >& out_components );

	/**
	 * Does what Cheat_GetAllDescriptors does, but tries to do in in a more reliable way,
	 * and not only hoping for the descriptor to be loaded in memory. This is probably slow!
	 */
	UFUNCTION( BlueprintCallable, Category = "Descriptors", meta = ( DefaultToSelf = "worldContext" ) )
	static void GetAllDescriptorsSorted( UObject* worldContext, UPARAM( ref ) TArray< TSubclassOf< UFGItemDescriptor > >& out_descriptors );

	/* Change Localization at Runtime. */
	UFUNCTION( BlueprintCallable, meta = ( DisplayName = "Change Language"), Category = "Localization" )
	static void ChangeLanguage( FString target );

	/* Return current language code */
	UFUNCTION( BlueprintCallable, meta = (DisplayName = "Get Language"), Category = "Localization" )
	static FString GetLanguage();

	/** Determine if the world is a editor world, will return false if the worldContext isn't in any world */
	UFUNCTION( BlueprintPure, Category="Editor")
	static bool IsEditorWorld( class UObject* worldContext );

	/** Determine if the world is a game world, will return false if the worldContext isn't in any world */
	UFUNCTION( BlueprintPure, Category = "Game" )
	static bool IsGameWorld( class UObject* worldContext );

	/** I wanted to use non natural logarithm in blueprints. */
	UFUNCTION( BlueprintPure, Category = "Math" )
	static float LogX( float base, float value );

	/** Returns a rounded float with a maximum of fractional digits */
	UFUNCTION( BlueprintPure, Category = "Math" )
	static float RoundFloatWithPrecision( float value, int32 MaximumFractionalDigits );

	/** */
	UFUNCTION( BlueprintPure, Category = "Component Flags" )
	static FName GetComponentFlagSoftLanding( );

	/* Returns km/h value based on the input cm/s. */
	UFUNCTION( BlueprintPure, meta = ( DisplayName = "cm/s to km/h", CompactNodeTitle = "CmS2KmH" ), Category = "Math" )
	static float CmS2KmH( float CmS ) { return CmS * 3600.f / 100000.f; }

	/** Returns true if the actor resides in a level that is always loaded, returns false if actor is null */
	UFUNCTION( BlueprintPure, Category="Level")
	static bool IsInAlwaysLoadedLevel( AActor* actor );

	/** Gets the Significance manager */
	static class UFGSignificanceManager* GetSignificanceManager( UWorld* InWorld );

	/** Adds a generic tickable object to be handled by significance manager */
	UFUNCTION( BlueprintCallable, Category = "Game", meta = ( WorldContext = "WorldContextObject" ) )
	static void AddGenericTickObjectToSignificanceManager( UObject* WorldContextObject, UObject* obj );

	/** removes a generic tickable object to be handled by significance manager */
	UFUNCTION( BlueprintCallable, Category = "Game", meta = ( WorldContext = "WorldContextObject" ) )
	static void RemoveGenericTickObjectFromSignificanceManager( UObject* WorldContextObject, UObject* obj );

	/** Adds a factory object to be handled by significance manager */
	UFUNCTION( BlueprintCallable, Category = "Game", meta = ( WorldContext = "WorldContextObject" ) )
	static void AddFactoryObjectToSignificanceManager( UObject* WorldContextObject, UObject* obj );

	/** removes a factory object to be handled by significance manager */
	UFUNCTION( BlueprintCallable, Category = "Game", meta = ( WorldContext = "WorldContextObject" ) )
	static void RemoveFactoryObjectFromSignificanceManager( UObject* WorldContextObject, UObject* obj );

	/** Adds conveyor belt be handled by significance manager */
	UFUNCTION( BlueprintCallable, Category = "Game", meta = ( WorldContext = "WorldContextObject" ) )
	static void AddConveyorBeltToSignificanceManager( UObject* WorldContextObject, UObject* obj );

	/** Removes conveyor belt be handled by significance manager */
	UFUNCTION( BlueprintCallable, Category = "Game", meta = (WorldContext = "WorldContextObject") )
	static void RemoveConveyorBeltFromSignificanceManager( UObject* WorldContextObject, UObject* obj );

	/** Adds pipeline to be handled by significance manager */
	UFUNCTION( BlueprintCallable, Category = "Game", meta = (WorldContext = "WorldContextObject") )
	static void AddPipelineToSignificanceManager( UObject* WorldContextObject, UObject* obj );

	/** Generic removal function for objects in significance manager. Use this if you don't need to do any special operations when removing from significance manager */
	UFUNCTION( BlueprintCallable, Category = "Game", meta = (WorldContext = "WorldContextObject") )
	static void RemoveFromSignificanceManagerGeneric( UObject* WorldContextObject, UObject* obj );

	/** Adds an object that should gain/lose significance on distance */
	UFUNCTION( BlueprintCallable, Category = "Game", meta = ( WorldContext = "WorldContextObject" ) )
	static void AddGainSignificanceObjectToSignificanceManager( UObject* WorldContextObject, UObject* obj, float desiredGainDistance );

	/** Removes an object that should gain/lose significance on distance */
	UFUNCTION( BlueprintCallable, Category = "Game", meta = ( WorldContext = "WorldContextObject" ) )
	static void RemoveGainSignificanceObjectFromSignificanceManager( UObject* WorldContextObject, UObject* obj );

	/** Adds an audio volume that should gain/lose significance on distance */
	UFUNCTION( BlueprintCallable, Category = "Game", meta = ( WorldContext = "WorldContextObject" ) )
	static void AddAudioVolumeToSignificanceManager( UObject* WorldContextObject, UObject* obj );

	/** Removes an audio volume that should gain/lose significance on distance */
	UFUNCTION( BlueprintCallable, Category = "Game", meta = ( WorldContext = "WorldContextObject" ) )
	static void RemoveAudioVolumeFromSignificanceManager( UObject* WorldContextObject, UObject* obj );

	/** Adds an AmbientSoundSpline that should gain/lose significance on distance */
	UFUNCTION( BlueprintCallable, Category = "Game", meta = ( WorldContext = "WorldContextObject" ) )
	static void AddAmbientSoundSplineToSignificanceManager( UObject* WorldContextObject, UObject* obj );

	/** Removes an AmbientSoundSpline that should gain/lose significance on distance */
	UFUNCTION( BlueprintCallable, Category = "Game", meta = ( WorldContext = "WorldContextObject" ) )
	static void RemoveAmbientSoundSplineFromSignificanceManager( UObject* WorldContextObject, UObject* obj );

	/** Adds a train to be handled by significance manager */
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Trains|Optimization", meta = ( WorldContext = "WorldContextObject" ) )
	static void AddTrainToSignificanceManager( UObject* WorldContextObject, UObject* obj );

	/** removes a train from being handled by significance manager */
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Trains|Optimization", meta = ( WorldContext = "WorldContextObject" ) )
	static void RemoveTrainFromSignificanceManager( UObject* WorldContextObject, UObject* obj );

	/**
	 * Checks if a impact effect is relevant for any local player
	 *
	 * @param instigator - the actor making the sound (human instigators of effects are more prone to be relevant)
	 * @param spawnLocation - the location where we want to spawn the effect
	 * @param visibleCullDistance - when outside this distance, then we shouldn't spawn the effect
	 * @param alwaysSuccessDistance - if the effect is spawned within this distance, then we should always spawn the effect (even if it's not visible)
	 * @param skipLOSCheck - if true, then we don't check if the effect is visible with traces
	 *
	 * @return true if the impact effect is relevant
	 **/
	UFUNCTION( BlueprintCallable, Category = "Effect", meta=(DefaultToSelf="worldContext") )
	static bool ImpactEffectIsRelevant( UObject* worldContext, APawn* instigator, FVector spawnLocation, float visibleCullDistance = 5000.0f, float alwaysSuccessDistance = 350.0f, bool skipLOSCheck = true );

	/**
	* Checks if a impact effect is within a certain distance from a local player
	*
	* @param instigator - the actor making the sound (human instigators of effects are more prone to be relevant)
	* @param spawnLocation - the location where we want to spawn the effect
	* @param visibleCullDistance - when outside this distance, then we shouldn't spawn the effect
	*
	* @return true if the impact effect is relevant
	**/
	UFUNCTION( BlueprintCallable, Category = "Effect", meta = ( DefaultToSelf = "worldContext" ) )
	static bool ImpactEffectIsWithinDistance( UObject* worldContext, APawn* instigator, FVector spawnLocation, float visibleCullDistance = 5000.0f );

	/**
	 * Checks if a pawn is controlled by a human on the current computer
	 *
	 * @param pawn - the pawn we want to check if it's controlled by a human on the current computer
	 * @return false if pawn is null, else true if locally human controlled
	 */
	UFUNCTION( BlueprintPure, Category = "Control" )
	static bool IsLocallyHumanControlled( APawn* pawn );

	/**
	 * Get a version string to show to the user
	 */
	UE_DEPRECATED(4.20, "Use GetVersionString from FGVersionBlueprintLibrary instead")
	UFUNCTION( BlueprintPure, Category = "Version", meta=(DeprecatedFunction,DeprecationMessage = "Use GetVersionString from FGVersionBlueprintLibrary instead") )
	static FString GetVersionString();
	
	/**
	* Returns true if this build is alpha. If Shipping, then Alpha. :)
	*/
	UE_DEPRECATED(4.20, "Use IsPublicBuild from FGVersionBlueprintLibrary instead")
	UFUNCTION( BlueprintPure, Category = "Version", meta=(DeprecatedFunction,DeprecationMessage = "Use IsPublicBuild from FGVersionBlueprintLibrary instead") )
	static bool IsAlphaBuild();

	/** Returns true if the passed descriptor can be on a conveyor belt. */
	UFUNCTION( BlueprintPure, Category = "Resource" )
	static bool CanBeOnConveyor( TSubclassOf< UFGItemDescriptor > inClass );

	/** Returns all recipes with product of a certain category */
	static void GetAvailableRecipesInCategory( UObject* worldContext, TSubclassOf< class UFGCategory > category, TArray< TSubclassOf< class UFGRecipe > >& out_recipes );

	/** Returns all recipes with product of a certain sub category of a certain category */
	UFUNCTION( BlueprintCallable, Category = "Organization" )
	static void GetAvailableRecipesInSubCategory( UObject* worldContext, TSubclassOf< class UFGCategory > category, TSubclassOf< class UFGCategory > subCategory, TArray< TSubclassOf< class UFGRecipe > >& out_recipes );

	UFUNCTION( BlueprintCallable, Category = "Organization" )
	static void GetAvailableRecipesWithDefaultMaterialInSubCategory( APlayerController* playerController, TSubclassOf< class UFGCategory > category, TSubclassOf< class UFGCategory > subCategory,
																	 TArray< TSubclassOf< class UFGRecipe > >& out_recipes );
	
	/** Will return all available recipes in a subcategory for a given material descriptor */
	UFUNCTION( BlueprintCallable, Category = "Organization" )
	static void GetAvailableRecipesForMaterialDescriptorInSubCategory( APlayerController* playerController, TSubclassOf< class UFGCategory > category, TSubclassOf< class UFGCategory > subCategory, 
																	 TSubclassOf< class UFGFactoryCustomizationDescriptor_Material > materialDesc,
																	 TArray< TSubclassOf< class UFGRecipe > >& out_recipes );

	/** Returns all sub categories with product of a certain category */
	UFUNCTION( BlueprintCallable, Category = "Organization", meta = (DeterminesOutputType = "outputSubCategoryClass")  )
	static TArray< TSubclassOf< class UFGCategory > > GetAvailableSubCategoriesForCategory( UObject* worldContext, TSubclassOf< UFGCategory > category, TSubclassOf< class UFGCategory > outputSubCategoryClass );

	/** Returns all sub categories for a schematic category */
	UFUNCTION( BlueprintCallable, Category = "Organization" )
	static void GetSubCategoriesForSchematicCategory( UObject* worldContext, TSubclassOf< class UFGSchematicCategory > category, UPARAM( ref ) TArray< TSubclassOf< class UFGSchematicCategory > >& out_subCategories );

	/** Returns all categories from the given recipes*/
	UFUNCTION( BlueprintCallable, Category = "Recipes", meta = (DeterminesOutputType = "outputCategoryClass") )
	static TArray< TSubclassOf< UFGCategory > > GetAllCategoriesFromRecipes( TArray< TSubclassOf< class UFGRecipe > > recipes, TSubclassOf< class UFGCategory > outputCategoryClass );

	/** Returns the first found quick switch group for a descriptor in the given recipe  */
	UFUNCTION( BlueprintCallable, Category = "Organization" )
	static TSubclassOf< class UFGQuickSwitchGroup > GetQuickSwitchGroupFromRecipe( TSubclassOf< class UFGRecipe > recipe );

	/** Returns all recipes in the given recipe array that match the quick switch group of the given recipe. Recipes with no quick switch group will match with other recipes that also has no quick switch group. */
	UFUNCTION( BlueprintCallable, Category = "Organization" )
	static void GetMatchingQuickSwitchGroupRecipes( TSubclassOf< class UFGRecipe > recipe, TArray < TSubclassOf< class UFGRecipe > > recipesToMatchAgainst, TArray< TSubclassOf< class UFGRecipe > >& out_recipes );

	/** Finds a widget of a certain class in the hierarchy of the passed widget. Does a breadth-first search of the tree.*/
	UFUNCTION( BlueprintCallable, meta = ( DefaultToSelf = "hierarchyContext", DeterminesOutputType = "widgetClass", DynamicOutputParam = "foundWidgets" ), Category = "Widget" )
	static void GetAllWidgetsOfClassInHierarchy( UWidget* hierarchyContext, TSubclassOf< UWidget > widgetClass, TArray< UWidget* >& foundWidgets );
	
	/** Returns all items in a item category */
	UFUNCTION( BlueprintCallable, Category = "Item Category" )
	static TArray< TSubclassOf< class UFGItemDescriptor > > GetAllItemsInCategory( UObject* worldContext, TSubclassOf< UFGItemCategory > itemCategory);

	/** Returns all categories that have available recipes in them */
	UFUNCTION( BlueprintCallable, Category = "Item Category" )
	static TArray< TSubclassOf< class UFGItemCategory > > GetCategoriesWithAffordableRecipes( AFGCharacterPlayer* playerPawn, TSubclassOf< UObject > forProducer );
	
	/** Gets all available Customization Descriptors
	 * @param customizationClass - Filter the returned list to only include the specified class (swatch, pattern, material)
	 */
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Customization" )
	static void GetAllAvailableCustomizations( UObject* worldContext, TArray< TSubclassOf< class UFGFactoryCustomizationDescriptor > >& out_customizations, TSubclassOf< class UFGFactoryCustomizationDescriptor > customizationClass );

	/**
	 * Gets all material descriptors that contain a recipe which exists in the given subcategory
	 * Tex. Pass in "Wall" buildable category, this function will return all material descriptors which map to recipes in this subcategory
	 */
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Customization" )
	static void GetValidMaterialRecipesSubCategory( UObject* worldContext, TSubclassOf< class UFGCategory > category, TSubclassOf< class UFGCategory > subCategory, TArray< TSubclassOf< class UFGCustomizationRecipe > >& out_matRecipes );

	/** 
	 * Gets the default material desc for a given buildable sub-category.
	 * @param Category - The Main category, this is not used for saving/retrival but if not saved default is found this category is needed to queary all available
	 * @param SubCategory - This is the category that is saved or used to find the saved reference
	 */
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Customization" )
	static TSubclassOf< class UFGFactoryCustomizationDescriptor_Material > GetDefaultMatDescForBuildableCategory( APlayerController* playerController, TSubclassOf< class UFGCategory> category, TSubclassOf< class UFGCategory > subCategory );

	/** Set the default material desc for a given buildable category */
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Customization" )
	static void SetDefaultMatDescForBuildableCategory( APlayerController* playerController, TSubclassOf< class UFGCategory > category, TSubclassOf< class UFGFactoryCustomizationDescriptor_Material > materialDesc );

	/** Gets the Global Default Material Descriptor set for a given Material Desc subCategory */
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Customization" )
	static TSubclassOf< class UFGFactoryCustomizationDescriptor_Material > GetGlobalDefaultMatDescForMaterialCategory( APlayerController* playerController, TSubclassOf< class UFGCategory > category );

	/** Sets the Global default material. This should be called from the Customizer Tab on a material desc */
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Customization" )
	static void SetGlobalDefaultMaterialDescriptor( APlayerController* playerController, TSubclassOf< class UFGFactoryCustomizationDescriptor_Material > materialDesc, bool updateHotbarShortcuts = false );

	/** Gets the Material Descriptor that corresponds to a given build descriptor. Calls GetMaterialDescriptorForBuildableClass. */
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Customization" )
	static TSubclassOf< class UFGFactoryCustomizationDescriptor_Material > GetMaterialDescriptorForBuildingDescriptor( UObject* worldContext, TSubclassOf< class UFGBuildDescriptor > buildingDesc );

	/** Gets the Material Descriptor that corresponds to a given buildable.
	 * @note: For this to work consistently, the assets must be set up correctly meaning only one asset references this buildable. If its referenced in multiple 
	 * material descriptors the first one found will be returned.
	 */
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Customization" )
	static TSubclassOf< class UFGFactoryCustomizationDescriptor_Material > GetMaterialDescriptorForBuildableClass( UObject* worldContext, TSubclassOf< class AFGBuildable > buildable );

	/** Updates a players hotbars based on a passed in material descriptor */
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Customization" )
	static void UpdateHotbarShortcutsForSpecifiedMaterialDescriptor( APlayerController* playerController, TSubclassOf< class UFGFactoryCustomizationDescriptor_Material > materialDesc );

	/**
	 * Checks if a location is close to a base
	 * @param worldContext - if null or invalid, function will return false
	 * @param inLocation - the location we want to check
	 * @param closeDistance - the distance we considers as close, if < 0, then we will use the default value specified in buildable susbystem
	 *
	 * @return if we consider the location as close to a factory
	 **/
	UFUNCTION( BlueprintPure, Category = "Factory" )
	static bool IsLocationNearABase( const UObject* worldContext, FVector inLocation, float closeDistance = -1);


	static bool IsLocationNearABaseFromResult( const UObject* worldContext, FVector inLocation, float closeDistance, const TArray< FOverlapResult >& Results );

	/** Helper function that takes care of creating a session and travel to the map */
	UFUNCTION( BlueprintCallable, Category="Online" )
	static void CreateSessionAndTravelToMap( APlayerController* player, const FString& mapName, const FString& options, const FString& sessionName, TEnumAsByte<ESessionVisibility> sessionVisibility );

	UFUNCTION( BlueprintCallable, Category="Online" )
	static void CreateSessionAndTravelToMapWithStartingLocation( APlayerController* player, const FString& mapName, const FString& startingLocation, const FString& sessionName, TEnumAsByte<ESessionVisibility> sessionVisibility );

	/** Travel gracefully to main menu, kicking clients if host, and tearing down the game session */
	UFUNCTION( BlueprintCallable, Category="Utils", meta=(DefaultToSelf="worldContext") )
	static void TravelToMainMenu( APlayerController* playerController );

	/** Send the local player to main menu */
	static void SendLocalPlayerToMainMenu( UWorld* world );

	/**
	 * Get a FLinearColor and returns a hex string like "FF00AA88".
	 */
	UFUNCTION( BlueprintPure, Category = "Factory" )
	static FString LinearColorToHex( FLinearColor inColor );

	/**
	 * Takes a hex string like "FF00AA88" and returns a FLinearColor.
	 */
	UFUNCTION( BlueprintCallable, Category = "Factory" )
	static FLinearColor HexToLinearColor( const FString& inHex );

	/** Adds a popup to the queue */
	UE_DEPRECATED(4.21, "Please use AddPopupWithCloseDelegate instead")
	UFUNCTION( BlueprintCallable, Category = "UI", meta = ( AutoCreateRefTerm = "ConfirmClickDelegate", DeprecatedFunction, DeprecationMessage="Please use AddPopupWithCloseDelegate instead" ) )
	static void AddPopup( APlayerController* controller, FText Title, FText Body, const FPopupConfirmClicked& ConfirmClickDelegate, EPopupId PopupID = PID_OK, TSubclassOf< UUserWidget > popupClass = nullptr, UObject* popupInstigator = nullptr );

	/** Adds a popup to the queue */
	UFUNCTION( BlueprintCallable, Category = "UI", meta = ( AutoCreateRefTerm = "CloseDelegate" ) )
	static void AddPopupWithCloseDelegate( APlayerController* controller, FText Title, FText Body, const FPopupClosed& CloseDelegate, EPopupId PopupID = PID_OK, TSubclassOf< UUserWidget > popupClass = nullptr, UObject* popupInstigator = nullptr );

	/** Adds a popup to the queue. Allows the caller handle popup content creation. */
	UFUNCTION( BlueprintCallable, Category = "UI", meta = ( AutoCreateRefTerm = "CloseDelegate" ) )
	static void AddPopupWithContent( APlayerController* controller, FText Title, FText Body, const FPopupClosed& CloseDelegate, class UFGPopupWidgetContent* Content, EPopupId PopupID = PID_OK, UObject* popupInstigator = nullptr );

	/** Close the popup that is currently showing. If no popup is showing, don't do anything */	
	UFUNCTION( BlueprintCallable, Category = "UI" )
	static void ClosePopup( APlayerController* controller );

	/** Clear the popup queue of all popups of the given class */
	UFUNCTION( BlueprintCallable, Category = "UI" )
	static void ClearPopupQueueOfClass( APlayerController* controller, TSubclassOf< UUserWidget > widgetClass );

	/** Copies the given text to the users clipboard */
	UFUNCTION( BlueprintCallable, Category = "UI" )
	static void CopyTextToClipboard( FText textToCopy );

	/** Return the text from the users clipboard */
	UFUNCTION( BlueprintCallable, Category = "UI" )
	static FText CopyTextFromClipboard();

	/** Removes all childs from this panel and releases them from the widget pool in the given FGHUD */
	UFUNCTION( BlueprintCallable, Category = "UI" )
	static void RemoveAndReleaseAllChildsFromPanel( class AFGHUD* hud, UPanelWidget* panelWidget);

	/** Removes the child at the given index from this panel and releases them from the widget pool in the given FGHUD */
	UFUNCTION( BlueprintCallable, Category = "UI" )
	static void RemoveAndReleaseChildFromPanel( class AFGHUD* hud, UPanelWidget* panelWidget, int32 index );

	// Find and return a local player
	static class AFGPlayerController* GetLocalPlayerController( const UObject* worldContext );
 
	UFUNCTION( BlueprintPure, Category = "Math|Conversions", meta=(DisplayName = "Equal (FrameTime)", CompactNodeTitle = "==", Keywords = "== equal") )
	static bool EqualEqual_FrameTimeFrameTime( FFrameTime frameTimeA, FFrameTime frameTimeB ); 
	UFUNCTION( BlueprintPure, Category = "Math|Conversions", meta=(DisplayName = "Not Equal (FrameTime)", CompactNodeTitle = "!=", Keywords = "!= not equal") )
	static bool NotEqual_FrameTimeFrameTime( FFrameTime frameTimeA, FFrameTime frameTimeB );
	UFUNCTION(BlueprintPure, Category="Math|Conversions", meta=(DisplayName = "ToFrameTime (integer)", CompactNodeTitle = "->", Keywords="cast convert", BlueprintAutocast) )
	static FFrameTime Conv_IntToFrameTime( int32 frameCount );
	UFUNCTION(BlueprintPure, Category="Math|Conversions", meta=(DisplayName = "ToInt (frametime)", CompactNodeTitle = "->", Keywords="cast convert", BlueprintAutocast) )
	static int32 Conv_FrameTimeToInt( FFrameTime frameTime );

	/** 
	*	Evaluates a math expression. Can handle white spaces between characters.
	*	@return true if expression could be evaluated.
	**/
	UFUNCTION( BlueprintCallable, Category = "Math" )
	static bool EvaluateMathExpression( const FString& expression, UPARAM( DisplayName = "Result" ) FText& out_Result );

	/** Convert a number of seconds into hour:minutes:seconds format string (including leading zeroes) */
	UFUNCTION(BlueprintPure,  Category = "Utilities|String")
    static FString SecondsToTimeString( float inSeconds );

	/** Converts an 64-bit integer value to a string */
	UFUNCTION(BlueprintPure, meta=(DisplayName = "ToString (integer64)", CompactNodeTitle = "->", BlueprintAutocast), Category="Utilities|String")
    static FString Conv_IntToString(int64 InInt);

	/* Return the value of GIsEditor. This is only true when we are in the actual editor */
	UFUNCTION( BlueprintPure, Category = "Editor" )
	static bool GetGIsEditor();

	/* Calls the scroll to end function after two ticks, This is a special case and shouldn't be used unless necessary */
	UFUNCTION( BlueprintCallable, Category = "Widget" )
	static void ScrollToEndAfterTwoTicks( UScrollBox* scrollBox );

	/** Does the same thing as UEditorAssetLibrary::SetMetadataTag but exposed to gameplay code since we have tools that are technically running as gameplay. Content of function is wrapped with editor only */
	UFUNCTION( BlueprintCallable, Category = "Editor Scripting | Metadata", meta = ( DevelopmentOnly ) )
	static void SetMetadataTag( UObject* object, FName tag, const FString& value );

	/** Does the same thing as UEditorAssetLibrary::GetMetadataTag but exposed to gameplay code since we have tools that are technically running as gameplay. Content of function is wrapped with editor only */
	UFUNCTION( BlueprintCallable, Category = "Editor Scripting | Metadata", meta = ( DevelopmentOnly ) )
	static FString GetMetadataTag( UObject* object, FName tag );

	/* Loads a file from drive via absolute path.*/
	UFUNCTION(BlueprintPure, Category = "Editor Scripting", meta = (DevelopmentOnly))
	static bool FileLoadString(FString AbsoluteFilePath, FString& String);

	/** 
	* Finds the last whole character index before the specified position in pixels along the string horizontally
	* 
	* @param text				The text to measure
	* @param InFontInfo			Information about the font used to draw the string
	* @param HorizontalOffset	Offset horizontally into the string, in pixels
	* @param suffix				[OPTIONAL] suffix to append and fit in the horizontal offset
	*
	* @return The text after it been cut off at the horizontal offset if needed.
	*/
	UFUNCTION( BlueprintPure, Category = "Text" )
    static FText CutTextByPixelOffset( const FText& text, const FSlateFontInfo& inFontInfo, const int32 horizontalOffset, const FString& suffix );

	/**
	 * Returns all actors within desired radius
	 **/
	UFUNCTION( BlueprintCallable, Category = "Fun" )
	static TArray< class AActor* > GetActorsInRadius( UObject* WorldContextObject, FVector inLocation,  float inRadius, TSubclassOf< AActor > inActorClass );

	UFUNCTION( BlueprintPure, Category = "Widgets" )
	static bool IsWidgetUnderCursor( class ULocalPlayer* localPlayer, class UUserWidget* widget );

	UFUNCTION( BlueprintCallable, Category = "Buildable Color" )
	static void SetCusomizationColorSlot( FFactoryCustomizationColorSlot& colorData, FLinearColor primaryColor, FLinearColor secondaryColor, float metallic = 1.f, float roughness = 1.f )
	{
		colorData.PrimaryColor = primaryColor;
		colorData.SecondaryColor = secondaryColor;
		colorData.Metallic = metallic;
		colorData.Roughness = roughness;
	}

	/** Extracts data from a CustomUserColor */
	UFUNCTION( BlueprintPure, Category = "Buildable Color", meta = ( NativeBreakFunc, AdvancedDisplay = "3" ) )
	static void BreakCustomizationColorSlot( const struct FFactoryCustomizationColorSlot& customData, FLinearColor& primaryColor, FLinearColor& secondaryColor, float& metallic, float& roughness );

	/** Create CustomUserColorData from params */
	UFUNCTION( BlueprintPure, Category = "Buildable Color", meta = ( NativeMakeFunc, AdvancedDisplay = "2", Normal = "0,0,1", ImpactNormal = "0,0,1" ) )
	static FFactoryCustomizationColorSlot MakeCustomizationColorSlot( FLinearColor primaryColor, FLinearColor secondaryColor, float metallic, float roughness );


	//////////////////////////////////////////////////////////////////////////
	/// Factory Customization

	/** Gets the icon for a customization class*/
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Customization" )
	static UTexture2D* GetIconForCustomizationDesc( const TSubclassOf< class UFGFactoryCustomizationDescriptor > customizationDesc );

	/** Gets the description for a customization class */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Customization" )
	static void GetDescriptionForCustomizationDesc( const TSubclassOf< class UFGFactoryCustomizationDescriptor > customizationDesc, FText& out_description );

	/** Get the array of buildables this customization can be applied to */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Customization" )
	static void GetValidBuildablsForCustomization( TSubclassOf< class UFGFactoryCustomizationDescriptor > customizationDesc, TArray< TSubclassOf< class AFGBuildable > >& out_buildables );

	/** Returns the ID value for a customization Class*/
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Customization" )
	static int32 GetIDForCustomizationDesc( const TSubclassOf< class UFGFactoryCustomizationDescriptor > customizationDesc );

	/** Returns the buildable map which indicates which buildable to use for a give material descriptor */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Customization" )
	static void GetMaterialCustomizationBuildableMap( TSubclassOf< class UFGFactoryCustomizationDescriptor > materialCustomization,
													  TMap< TSubclassOf< class AFGBuildable >, TSubclassOf< class UFGRecipe > >& out_buildableMap ); 

	/** Returns an array of Customizations from a customization collection */
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Customization" )
	static void GetCustomizationsFromCollectionClass( TSubclassOf< class UFGFactoryCustomizationCollection > collectionClass, TArray< TSubclassOf< class UFGFactoryCustomizationDescriptor > >& out_customizaitons );

	/** Gets the Slot Data (color, metallic, roughness) for a given Swatch Descriptor */
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|BuildGunPaint" )
	static void GetSlotDataForSwatchDesc( TSubclassOf< class UFGFactoryCustomizationDescriptor_Swatch > swatchDesc, class AActor* worldContext, FFactoryCustomizationColorSlot& out_SlotData );

	UFUNCTION( BlueprintPure, Category = "FactoryGame|Customization" )
	static bool GetIsCategoryDefaultForMaterialDesc( TSubclassOf< class UFGFactoryCustomizationDescriptor_Material > materialDesc );

	/** Sort an array dependent on the menu priority of the customization descs in the given customization recipes */
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Recipe" )
	static void SortCustomizationRecipes( UPARAM( ref ) TArray< TSubclassOf< class UFGCustomizationRecipe > >& recipes );

	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Customization" )
	static void ApplySkinDataToMeshArray( TArray< UMeshComponent* >& compArr, FFactorySkinComponentGroup& groupData );

	/////////////////////////////////////////////////////////////////
	// Begin specific functions for cinematic tools.
	
	UFUNCTION(BlueprintPure, Category = "Editor")
	static float GetPrimitiveDataFromIndex(int32 Index, UPrimitiveComponent* Component);

	UFUNCTION(BlueprintPure, Category = "Editor")
	static float GetPrimitiveDefaultDataFromIndex(int32 Index, UPrimitiveComponent* Component);

	UFUNCTION(BlueprintCallable, Category = "Editor")
	static void CSS_SetAnimationAsset(USkeletalMeshComponent* Comp, UAnimationAsset* AnimationAsset);
};
