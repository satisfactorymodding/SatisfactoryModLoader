// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FGFactoryColoringTypes.h"
#include "FGInventoryComponent.h"
#include "FGMapMarker.h"
#include "FGRecipe.h" 
#include "FGSchematic.h" 
#include "FGUseableInterface.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "UI/FGPopupWidget.h"
#include "FGBlueprintFunctionLibrary.generated.h"

class UDirectionalLightComponent;
class UFXSystemAsset;
UENUM( BlueprintType )
enum class EOutlineColor : uint8
{
	OC_NONE							= 0		UMETA( DisplayName = "None" ),
	OC_INPUTOUTPUT					= 1		UMETA( DisplayName = "InputOutputShape" ),
	OC_HOLOGRAMLINE					= 2		UMETA( DisplayName = "Hologram Line" ),
	OC_SOFTCLEARANCE				= 3		UMETA( DisplayName = "Soft Clearance" ),
	OC_USABLE						= 4		UMETA( DisplayName = "Usable" ),
	OC_HOLOGRAM						= 5		UMETA( DisplayName = "Hologram" ),
	OC_INVALIDHOLOGRAM  			= 6		UMETA( DisplayName = "Invalid Hologram" ),
	OC_RED							= 7		UMETA( DisplayName = "Red" ),
	OC_DISMANTLE					= 8		UMETA( DisplayName = "Dismantle" ),
	OC_SOFTCLEARANCEOVERLAP			= 9		UMETA( DisplayName = "Soft Clearance Overlap" ),
};

// Information about an attachment for a given component
USTRUCT( BlueprintType )
struct FACTORYGAME_API FFGComponentParentAttachmentInfo
{
	GENERATED_BODY()
	
	// Parent component this component attaches to
	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = "Scene Component" )
	USceneComponent* ParentComponent{};

	// Name of the socket this component attaches to
	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = "Scene Component" )
	FName AttachToSocketName{};
};

DECLARE_DYNAMIC_DELEGATE_RetVal( bool, FLatentActionPredicate );

// <FL> [WuttkeP] Interface to allow widgets to influence which child should be focused when using FindWidgetToFocus().
UENUM(BlueprintType)
enum class EFGFocusReason : uint8
{
	Navigation,
	Explicit
};

UINTERFACE( Blueprintable )
class FACTORYGAME_API UFGFocusableWidget : public UInterface
{
	GENERATED_BODY()
};

class FACTORYGAME_API IFGFocusableWidget
{
	GENERATED_BODY()

public:
	UFUNCTION( BlueprintCallable, BlueprintImplementableEvent )
	UWidget* GetWidgetToFocus(EFGFocusReason FocusReason);
};
// </FL>

UCLASS()
class FACTORYGAME_API UFGBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	/** Returns true if the given actor had BeginPlay dispatched */
	UFUNCTION( BlueprintPure, Category = "Actor" )
	static bool HasActorBegunPlay( const AActor* InActor );
	
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
	static void ApplyCustomizationPrimitiveData( class AActor* actor, const FFactoryCustomizationData& customizationData, int32 colorSlotFallback = 0, class UMeshComponent* onlyApplyToComponent = nullptr, bool isLightweightTemporary = false  );

	/** Static Helper to apply default factory color data to actors that use the default factory material */
	UFUNCTION( BlueprintCallable, Category = "Factory|Customization" )
	static void ApplyDefaultColorPrimitiveData( class AActor* actor );

	/** Fills a given array with all mesh components residing on a class. Including any blueprint added components */
	UFUNCTION( BlueprintCallable, Category = "Factory|Customization" )
	static void GetAllMeshComponentsInClass( const TSubclassOf< AActor > inClass, TArray< UMeshComponent* >& out_components );

	/** Fills a given array with all components residing on a class. Including any blueprint added components */
	UFUNCTION( BlueprintCallable, Category = "Factory|Customization" )
	static void GetAllComponentsInClass( const TSubclassOf<AActor> inClass, const TSubclassOf<UActorComponent> inActorComponentClass, TArray<UActorComponent*>& out_components, TMap<USceneComponent*, FFGComponentParentAttachmentInfo>& out_parentComponentMap );

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

	/* Add generic gain / loss significance to the accelerated significance manager.
	**	@Param Object - Actor to add to the system */
	UFUNCTION( BlueprintCallable, Category = "Game", meta = ( WorldContext = "WorldContextObject" ) )
	static void AddStaticSignificance( UObject* WorldContextObject, UObject* Object);

	UFUNCTION( BlueprintCallable, Category = "Game", meta = ( WorldContext = "WorldContextObject" ) )
	static void RemoveStaticSignificance( UObject* WorldContextObject, UObject* Object );
	
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

	UFUNCTION( BlueprintCallable, Category="Game", meta = ( WorldContext = "WorldContextObject" ))
	static void AddToServerSideSignificanceOctTree(UObject* obj);
	
	UFUNCTION( BlueprintCallable, Category="Game", meta = ( WorldContext = "WorldContextObject" ))
	static void RemoveFromServerSideSignificanceOctTree(UObject* obj);
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

	UFUNCTION( BlueprintCallable, Category = "Organization" )
	static void GetVisibleSubCategoriesForSchematicCategory( UObject* worldContext, TSubclassOf< class UFGSchematicCategory > category, ESchematicType schematicType, TArray< TSubclassOf< class UFGSchematicCategory > >& out_subCategories );

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

	// <FL> [WuttkeP] Added utility function to find all child widgets of a class.
	/** Finds all child widgets below the root widget of the specified class (recursively). */
	UFUNCTION( BlueprintCallable, meta = ( DefaultToSelf = "rootWidget", DeterminesOutputType = "widgetClass", DynamicOutputParam = "foundWidgets" ), Category = "Widget" )
	static void GetAllChildWidgetsOfClass( UWidget* rootWidget, TSubclassOf< UWidget > widgetClass, TArray< UWidget* >& foundWidgets );

	/** Finds all visible child widgets below the root widget of the specified class (recursively). */
	UFUNCTION(BlueprintCallable, meta = (DefaultToSelf = "rootWidget", DeterminesOutputType = "widgetClass", DynamicOutputParam = "foundWidgets"), Category = "Widget")
	static void GetVisibleChildWidgetsOfClass( UWidget* rootWidget, TSubclassOf< UWidget > widgetClass, bool bUseIsReallyVisible, TArray< UWidget* >& foundWidgets );

	/** Finds all child widgets below the root widget of any of the specified classes (recursively). */
	UFUNCTION( BlueprintCallable, meta = ( DefaultToSelf = "rootWidget", DeterminesOutputType = "widgetClass", DynamicOutputParam = "foundWidgets" ), Category = "Widget" )
	static void GetAllChildWidgetsOfAnyClass( UWidget* rootWidget, TArray< TSubclassOf< UWidget > > widgetClasses, TArray< UWidget* >& foundWidgets );

	/** Finds the first child widget below the root widget of the specified class (recursively). */
	UFUNCTION( BlueprintCallable, meta = ( DefaultToSelf = "rootWidget", DeterminesOutputType = "widgetClass" ), Category = "Widget" )
	static UWidget* GetFirstChildWidgetOfClass( UWidget* rootWidget, TSubclassOf< UWidget > widgetClass );

	/** Finds the first parent widget of the provided child widget that is of the specified class. */
	UFUNCTION( BlueprintCallable, meta = ( DefaultToSelf = "childWidget", DeterminesOutputType = "widgetClass" ), Category = "Widget" )
	static UWidget* GetFirstParentWidgetOfClass( UWidget* childWidget, TSubclassOf< UWidget > widgetClass );
	// </FL>	

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

	/** Converts legacy short map name to TopLevelAssetPath object containing a full path to the UWorld object representing a map. Returns true if successful, false otherwise */
	static bool TryConvertShortMapNameToTopLevelAssetPath( const FString& mapName, FTopLevelAssetPath& outAssetPath );

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
	static void AddPopupWithCloseDelegate( APlayerController* controller, FText Title, FText Body, const FPopupClosed& CloseDelegate, EPopupId PopupID = PID_OK, TSubclassOf< UUserWidget > popupClass = nullptr, UObject* popupInstigator = nullptr, bool restoreFocusOnClose = false ); // <FL> [WuttkeP] Added restoreFocusOnClose parameter.

	/** Adds a popup to the queue. Allows the caller handle popup content creation. */
	UFUNCTION( BlueprintCallable, Category = "UI", meta = ( AutoCreateRefTerm = "CloseDelegate" ) )
	static void AddPopupWithContent( APlayerController* controller, FText Title, FText Body, const FPopupClosed& CloseDelegate, class UFGPopupWidgetContent* Content, EPopupId PopupID = PID_OK, UObject* popupInstigator = nullptr, bool restoreFocusOnClose = false ); // <FL> [WuttkeP] Added restoreFocusOnClose parameter.

	/** Close the popup that is currently showing. If no popup is showing, don't do anything */	
	UFUNCTION( BlueprintCallable, Category = "UI" )
	static void ClosePopup( APlayerController* controller );

	/** Clear the popup queue of all popups of the given class */
	UFUNCTION( BlueprintCallable, Category = "UI" )
	static void ClearPopupQueueOfClass( APlayerController* controller, TSubclassOf< UUserWidget > widgetClass );

	/** Clear the popup queue of all popups of the given content class. Also removes the currently active popup if of the same content class */
	UFUNCTION( BlueprintCallable, Category = "UI" )
	static void ClearPopupQueueOfContentClass( APlayerController* controller, TSubclassOf< UFGPopupWidgetContent > contentClass);

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

	/** Returns true if the given map markers have the same hidden ID */
	UFUNCTION( BlueprintPure, Category = "Map", meta=(DisplayName = "Equal (Map Marker)", CompactNodeTitle = "==", Keywords = "== equal") )
	static bool EqualEqual_FMapMarkerFMapMarker( const FMapMarker& mapMarkerA, const FMapMarker& mapMarkerB );

	/** Returns given map marker hidden ID used for identifying markers and if it's considered to be a valid marker ID*/
	UFUNCTION( BlueprintPure,  Category = "Map" )
	static int32 GetMapMarkerID( const FMapMarker& mapMarker, UPARAM( DisplayName = "HasValidID" ) bool& out_hasValidID );

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
	static void GetActorsInRadius( UObject* WorldContextObject, FVector inLocation,  float inRadius, TSubclassOf< AActor > inActorClass, TArray< class AActor* >& result );

	UFUNCTION( BlueprintPure, Category = "Widgets" )
	static bool IsWidgetUnderCursor( class ULocalPlayer* localPlayer, class UUserWidget* widget );

	/** Converts an FSessionSaveStruct to a UObject(UFGSessionSaveStructWrapper). Used for list views since they require an object per item */
	UFUNCTION(BlueprintPure, meta=(DisplayName = "ToObject (FSessionSaveStruct)", CompactNodeTitle = "->", BlueprintAutocast), Category="Save Session")
	static UObject* Conv_SessionSaveStructToObject( FSessionSaveStruct inSessionSaveStruct );

	/** Converts an FSaveHeader to a UObject(UFGSaveHeaderWrapper). Used for list views since they require an object per item */
	UFUNCTION(BlueprintPure, meta=(DisplayName = "ToObject (FSaveHeader)", CompactNodeTitle = "->", BlueprintAutocast), Category="Save Header")
	static UObject* Conv_SaveHeaderToObject( FSaveHeader inSaveHeader );

	UFUNCTION( BlueprintCallable, Category="Utilities|FlowControl", meta=( Latent, WorldContext="WorldContextObject", LatentInfo="LatentInfo" ) )
	static void	WaitForValidSubsystems(const UObject* WorldContextObject, struct FLatentActionInfo LatentInfo );

	/** Waits until the player state has been assigned or replicated to the particular player controller */
	UFUNCTION( BlueprintCallable, Category = "Utilities|FlowControl", meta = ( Latent, WorldContext = "WorldContextObject", LatentInfo = "LatentInfo" ) )
	static void WaitForPlayerState(const UObject* WorldContextObject, AFGPlayerController* PlayerController, struct FLatentActionInfo LatentInfo, class AFGPlayerState*& out_playerState );

	/**
	 * Waits for the HUD actor to become available and then executes the connected nodes. Nothing will run on dedicated servers, since HUD is not available there. 
	 */
	UFUNCTION( BlueprintCallable, Category="Utilities|FlowControl", meta=( Latent, WorldContext="WorldContextObject", LatentInfo="LatentInfo" ) )
	static void	WaitForFGHud(const UObject* WorldContextObject, struct FLatentActionInfo LatentInfo, class AFGHUD*& out_HUD );

	/**
	 * Waits for the game UI object to become available and then executes the connected nodes. Nothing will run on dedicated servers, since game UI is not available there. 
	 */
	UFUNCTION( BlueprintCallable, Category="Utilities|FlowControl", meta=( Latent, WorldContext="WorldContextObject", LatentInfo="LatentInfo" ) )
	static void	WaitForGameUI(const UObject* WorldContextObject, struct FLatentActionInfo LatentInfo, class UFGGameUI*& out_GameUI );

	UFUNCTION( BlueprintCallable, Category="Utilities|FlowControl", meta=( Latent, WorldContext="WorldContextObject", LatentInfo="LatentInfo" ) )
	static void WaitForCondition( const UObject* WorldContextObject, struct FLatentActionInfo LatentInfo, const FLatentActionPredicate& Predicate, bool ExecuteOnDedicatedServer = true );

	/** Gets all item descriptors in the game including unlocked ones */
	UFUNCTION(BlueprintCallable, Category = "FactoryGame|Items")
	static void GetAllPickupableItemDescriptors( UObject* WorldContextObject, TArray< TSubclassOf< class UFGItemDescriptor > >& out_itemDescriptors );

	UFUNCTION( BlueprintPure, Category = "UI" )
	static bool ShouldShowUnstableSaveVersionWarning();
	
	UFUNCTION( BlueprintPure, Category = "UI" )
	static bool ShouldShowOfflineSessionWarning();

	UFUNCTION( BlueprintPure, Category = "UI" )
	static bool ShouldShowControllerUI();

	// <FL> [ZimmermannA] Utility function to check if we are using controller
	UFUNCTION( BlueprintPure, Category = "UI" )
	static bool IsUsingController( const UObject* WorldContextObject );
	// </FL>

	/** Get the FGGameInstance */
	UFUNCTION( BlueprintPure, Category="Game", meta=(WorldContext="WorldContextObject") )
	static UFGGameInstance* GetFGGameInstance( const UObject* WorldContextObject );

	// <FL> [WuttkeP] Utility function to find a widget that supports focus.
	UFUNCTION( BlueprintPure, Category = "UI" )
	static UWidget* FindWidgetToFocus( UWidget* Widget, EFGFocusReason FocusReason = EFGFocusReason::Navigation );
	// </FL>	

	// <FL> [WuttkeP] Utility function to check actual widget visibility.
	/** Checks if a widget is really visible by iterating through its parents and checking the visibility of each of them. */
	UFUNCTION( BlueprintPure, Category = "UI" )
	static bool IsReallyVisible( UWidget* Widget );

	UFUNCTION( BlueprintPure, Category = "UI" )
	static bool HasAnyVisibleChildren( UPanelWidget* Parent );
	// </FL>

	// <FL> [WuttkeP] More Utility functions.
	/** Find the previous child of a widget inside a UPanelWidget. */
	UFUNCTION( BlueprintPure, Category = "UI" )
	static UWidget* GetPreviousChild( UWidget* widget );

	/** Find the next child of a widget inside a UPanelWidget. */
	UFUNCTION( BlueprintPure, Category = "UI" )
	static UWidget* GetNextChild( UWidget* widget );

	/** Retrives the geometry of the currently focused widget. */
	UFUNCTION( BlueprintPure, Category = "UI" )
	static const FGeometry& GetFocusedWidgetGeometry();

	UFUNCTION( BlueprintPure, Category = "UI" )
	static UUserWidget* GetFocusedUserWidget();

	/** Finds the first focused (latest in the focus path) widget of the specified class. */
	UFUNCTION( BlueprintPure, meta = ( DeterminesOutputType = "widgetClass" ), Category = "UI" )
	static UUserWidget* GetFirstFocusedUserWidgetOfClass( TSubclassOf< UUserWidget > widgetClass );

	/** Finds the first focused (latest in the focus path) widget of any of the specified classes. */
	UFUNCTION( BlueprintPure, Category = "UI" )
	static UUserWidget* GetFirstFocusedUserWidgetOfAnyClass( TArray< TSubclassOf< UUserWidget > > widgetClasses );

	UFUNCTION( BlueprintPure, Category = "UI" ) // I'd love to use DeterminesOutputType, but Unreal won't let me :/
	static UUserWidget* GetFirstFocusedUserWidgetOfInterface( UClass* widgetInterface );

	/** Computes the shortest distance between two geometries. */
	UFUNCTION( BlueprintPure, Category = "User Interface|Geometry" )
	static FVector2D GetShortestDistance( const FGeometry& fromGeometry, const FGeometry& toGeometry );

	/** Computes the longest distance between two geometries. */
	UFUNCTION( BlueprintPure, Category = "User Interface|Geometry" )
	static FVector2D GetLongestDistance( const FGeometry& fromGeometry, const FGeometry& toGeometry );

	/** Finds the widget closest to a given geometry. */
	UFUNCTION( BlueprintPure, Category = "UI" )
	static UWidget* FindClosestWidget( const FGeometry& geometry, const TArray<UWidget*>& widgets, bool bOnlyVisible = true, bool bOnlyFocusable = false );

	/** Finds the child inside a UPanelWidget that is the closest to a given geometry. */
	UFUNCTION( BlueprintPure, Category = "UI" )
	static UWidget* FindClosestChild( const FGeometry& geometry, UPanelWidget* parentWidget );

	/** Finds the widget furthest in Y direction, then closest in X direction. For wrapping navigation. */
	UFUNCTION( BlueprintPure, Category = "UI" )
	static UWidget* FindOppositeWidgetY( const FGeometry& geometry, const TArray<UWidget*>& widgets, bool bOnlyVisible = true, bool bOnlyFocusable = false );

	/** Simulates a key down event */
	UFUNCTION( BlueprintCallable, Category = "Input" )
	static void SimulateKeyDownEvent( const FKeyEvent& keyEvent );

	/** Simulates a key up event */
	UFUNCTION( BlueprintCallable, Category = "Input" )
	static void SimulateKeyUpEvent( const FKeyEvent& keyEvent );

	UFUNCTION( BlueprintPure, Category = "Input", meta = ( WorldContext = "WorldContextObject" ) )
	static bool GetKeyState(UObject* WorldContextObject, FKey Key);
	// </FL>

	// <FL> [WuttkeP] Added function to notify button hint widgets of key hint changes.
	/** Sends a notification to update button hint widgets when a key hint changed without the focused widget changing. */
	UFUNCTION( BlueprintCallable, Category = "Input", meta = ( WorldContext = "WorldContextObject" ) )
	static void NotifyKeyHintsChanged( UObject* WorldContextObject );
	// </FL>

	/** Returns the underlying source string for this text as it is defined in the editor */
	UFUNCTION( BlueprintPure, Category = "UI" )
	static FString BuildSourceString( const FText& inText );

	/** Sort an array of strings alphabetically */
	UFUNCTION(BlueprintCallable, Category="Utilities|String", meta=(Keywords = "alphabetically, array"))
	static void SortStrings( UPARAM( ref ) TArray< FString >& strings, bool sortAscending = true );
	
	//////////////////////////////////////////////////////////////////////////
	/// Factory Customization

	UFUNCTION( BlueprintCallable, Category = "Buildable Color" )
	static void SetCusomizationColorSlot( FFactoryCustomizationColorSlot& colorData, FLinearColor primaryColor, FLinearColor secondaryColor, TSubclassOf<UFGFactoryCustomizationDescriptor_PaintFinish> PaintFinish )
	{
		colorData.PrimaryColor = primaryColor;
		colorData.SecondaryColor = secondaryColor;
		colorData.PaintFinish = PaintFinish;
	}

	/** Extracts data from a CustomUserColor */
	UFUNCTION( BlueprintPure, Category = "Buildable Color", meta = ( NativeBreakFunc, AdvancedDisplay = "3" ) )
	static void BreakCustomizationColorSlot( const struct FFactoryCustomizationColorSlot& customData, FLinearColor& primaryColor, FLinearColor& secondaryColor, TSubclassOf<UFGFactoryCustomizationDescriptor_PaintFinish>& Finish );

	/** Create CustomUserColorData from params */
	UFUNCTION( BlueprintPure, Category = "Buildable Color", meta = ( NativeMakeFunc, AdvancedDisplay = "2", Normal = "0,0,1", ImpactNormal = "0,0,1" ) )
	static FFactoryCustomizationColorSlot MakeCustomizationColorSlot( FLinearColor primaryColor, FLinearColor secondaryColor, TSubclassOf<UFGFactoryCustomizationDescriptor_PaintFinish> Finish );
	
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
	
	UFUNCTION( BlueprintCallable, Category = "FactoryGame" )
	static UFXSystemAsset* SpawnParticleSystemAtLocationFromFXSystem( UObject* WorldContext, UFXSystemAsset* Asset, FVector Location, FRotator Rotation, FVector Scale = FVector(1));

	UFUNCTION( BlueprintCallable, Category = "FactoryGame" )
	static void SetTraceDistance(UDirectionalLightComponent* DirectionalLight,float Value);
	/////////////////////////////////////////////////////////////////
	// Begin specific functions for cinematic tools.
	
	UFUNCTION(BlueprintPure, Category = "Editor")
	static float GetPrimitiveDataFromIndex(int32 Index, UPrimitiveComponent* Component);

	UFUNCTION(BlueprintPure, Category = "Editor")
	static float GetPrimitiveDefaultDataFromIndex(int32 Index, UPrimitiveComponent* Component);

	UFUNCTION(BlueprintCallable, Category = "Editor")
	static void CSS_SetAnimationAsset(USkeletalMeshComponent* Comp, UAnimationAsset* AnimationAsset);

	// Returns current frame number, Non shipping build only!
	UFUNCTION(BlueprintPure, Category = "Profiling")
	static int64 GetFrameNumber();

	UFUNCTION(BlueprintPure, Category = "Utilities")
	static float FindClosestPlayerSq(AActor* source);

	UFUNCTION(BlueprintCallable, Category = "Water")
	static void SetWaterCollisionSettings(UStaticMeshComponent* Target);

	UFUNCTION(BlueprintCallable)
	static bool SegmentIntersection(const FVector& SegmentBeginA, const FVector& SegmentEndA, const FVector& SegmentBeginB, const FVector& SegmentEndB );

	/*Editor only.*/
	UFUNCTION(BlueprintCallable)
	static FString GetActorGridStringRuntTime(AActor* InActor);
	
	UFUNCTION(BlueprintPure)
	static FVector GetEditorCameraLocation();
	
	UFUNCTION(BlueprintCallable)
	static void ED_SetMinDrawDistance(UStaticMeshComponent* Comp, float Distance);

	UFUNCTION( BlueprintPure, CustomThunk, Category = "Utilities|Dynamic Struct", meta = (NativeMakeFun, CustomStructureParam = "structureValue" ) )
	static FFGDynamicStruct MakeDynamicStruct( const int32& structureValue );

	UFUNCTION( BlueprintPure, CustomThunk, Category = "Utilities|Dynamic Struct", meta = (NativeBreakFunc, CustomStructureParam = "out_structureValue" ) )
	static bool BreakDynamicStruct( const FFGDynamicStruct& inDynamicStruct, int32& out_structureValue );

	DECLARE_FUNCTION(execMakeDynamicStruct);
	DECLARE_FUNCTION(execBreakDynamicStruct);

	/** Blueprint wrapper around AVolume::EncompassesVolume. Returns true if the given point is inside of the volume */
	UFUNCTION( BlueprintPure, Category = "Utilities" )
	static bool VolumeEncompassesPoint( AVolume* volume, const FVector& inPoint, float& outDistanceToPoint, float sphereRadius = 0.0f );

	UFUNCTION(BlueprintCallable,Category="Editor", meta = ( DevelopmentOnly ))
	static void ForceReRunConstructionScript(AActor* Actor);

	/** Attempts to look up an item descriptor associated with the given recipe producer */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Recipe", meta = ( WorldContext = "worldContext" ) )
	static TSubclassOf<UFGItemDescriptor> GetRecipeProducerItemDescriptor( UPARAM( meta = ( MustImplement = "/Script/FactoryGame.FGRecipeProducerInterface" ) ) TSubclassOf<UObject> recipeProducer, UObject* worldContext );

	UFUNCTION( BlueprintPure, BlueprintCallable )
	static TArray< AFGPlayerController* > GetAllPlayerControllersInSession( const UObject* worldContextObject );
	
	UFUNCTION( BlueprintPure, Category = "UI" )
	static bool IsNavigationEvent( UPARAM( ref ) FFocusEvent& inEvent);
};
