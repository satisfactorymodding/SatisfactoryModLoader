// Copyright 2016 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "Engine/World.h"
#include "Array.h"
#include "UnrealString.h"
#include "GameFramework/Actor.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "SubclassOf.h"
#include "UObject/Class.h"

#include "FGUseableInterface.h"
#include "FGInventoryComponent.h"
#include "UI/FGPopupWidget.h"
#include "FGOnlineSessionSettings.h"
#include "FGRecipe.h"
#include "FGBlueprintFunctionLibrary.generated.h"

UENUM( BlueprintType )
enum class EOutlineColor : uint8
{
	OC_NONE			= 0		UMETA( DisplayName = "None" ),
	OC_USABLE		= 252	UMETA( DisplayName = "Usable" ),
	OC_HOLOGRAM		= 253	UMETA( DisplayName = "Hologram" ),
	OC_RED			= 254	UMETA( DisplayName = "Disabled" )
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

	/** Gives you all categories that can be unlocked in this game */
	UFUNCTION( BlueprintCallable, Category = "Build Category" )
	static void GetAllBuildCategories( UObject* worldContext, UPARAM( ref ) TArray< TSubclassOf< class UFGBuildCategory > >& out_buildCategories );

	/** Returns all recipes with product of a certain category */
	UFUNCTION( BlueprintCallable, Category = "Build Category" )
	static void GetAvailableRecipesInCategory( UObject* worldContext, TSubclassOf< UFGBuildCategory > buildCategory, UPARAM( ref ) TArray< TSubclassOf< class UFGRecipe > >& out_recipes );

	/** Returns all recipes with product of a certain sub category of a certain build category */
	UFUNCTION( BlueprintCallable, Category = "Build Category" )
	static void GetAvailableRecipesInSubCategory( UObject* worldContext, TSubclassOf< UFGBuildCategory > buildCategory, TSubclassOf< UFGBuildSubCategory > subCategory, UPARAM( ref ) TArray< TSubclassOf< class UFGRecipe > >& out_recipes );

	/** Returns all sub categories with product of a certain category */
	UFUNCTION( BlueprintCallable, Category = "Build Category" )
	static void GetAvailableSubCategoriesForCategory( UObject* worldContext, TSubclassOf< UFGBuildCategory > buildCategory, UPARAM( ref ) TArray< TSubclassOf< class UFGBuildSubCategory > >& out_subCategories );

	/** Returns all sub categories for a schematic category */
	UFUNCTION( BlueprintCallable, Category = "Build Category" )
	static void GetSubCategoriesForSchematicCategory( UObject* worldContext, TSubclassOf< UFGSchematicCategory > buildCategory, UPARAM( ref ) TArray< TSubclassOf< class UFGSchematicCategory > >& out_subCategories );

	/** Finds a widget of a certain class in the hierarchy of the passed widget. Does a breadth-first search of the tree.*/
	UFUNCTION( BlueprintCallable, meta = ( DefaultToSelf = "hierarchyContext", DeterminesOutputType = "widgetClass", DynamicOutputParam = "foundWidgets" ), Category = "Widget" )
	static void GetAllWidgetsOfClassInHierarchy( UWidget* hierarchyContext, TSubclassOf< UWidget > widgetClass, TArray< UWidget* >& foundWidgets );
	
	/** Returns all items in a item category */
	UFUNCTION( BlueprintCallable, Category = "Item Category" )
	static TArray< TSubclassOf< class UFGItemDescriptor > > GetAllItemsInCategory( UObject* worldContext, TSubclassOf< UFGItemCategory > itemCategory);

	/** Returns all categories that have available recipes in them */
	UFUNCTION( BlueprintCallable, Category = "Item Category" )
	static TArray< TSubclassOf< class UFGItemCategory > > GetCategoriesWithAffordableRecipes( AFGCharacterPlayer* playerPawn, TSubclassOf< UObject > forProducer );

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

	/** Adds a popup to the queue */
	UE_DEPRECATED(4.21, "Please use AddPopupWithCloseDelegate instead")
	UFUNCTION( BlueprintCallable, Category = "UI", meta = ( AutoCreateRefTerm = "ConfirmClickDelegate", DeprecatedFunction, DeprecationMessage="Please use AddPopupWithCloseDelegate instead" ) )
	static void AddPopup( APlayerController* controller, FText Title, FText Body, const FPopupConfirmClicked& ConfirmClickDelegate, EPopupId PopupID = PID_OK, TSubclassOf< UUserWidget > popupClass = nullptr, UObject* popupInstigator = nullptr );

	/** Adds a popup to the queue */
	UFUNCTION( BlueprintCallable, Category = "UI", meta = ( AutoCreateRefTerm = "CloseDelegate" ) )
	static void AddPopupWithCloseDelegate( APlayerController* controller, FText Title, FText Body, const FPopupClosed& CloseDelegate, EPopupId PopupID = PID_OK, TSubclassOf< UUserWidget > popupClass = nullptr, UObject* popupInstigator = nullptr );

	/** Close the popup that is currently showing. If no popup is showing, don't do anything */	
	UFUNCTION( BlueprintCallable, Category = "UI" )
	static void ClosePopup( APlayerController* controller );

	/** Copies the given text to the users clipboard */
	UFUNCTION( BlueprintCallable, Category = "UI" )
	static void CopyTextToClipboard( FText textToCopy );

	/** Return the text from the users clipboard */
	UFUNCTION( BlueprintCallable, Category = "UI" )
	static FText CopyTextFromClipboard();

	// Find and return a local player
	static class AFGPlayerController* GetLocalPlayerController( const UObject* worldContext );

	/** 
	*	Evaluates a math expression. Can handle white spaces between characters.
	*	@return true if expression could be evaluated.
	**/
	UFUNCTION( BlueprintCallable, Category = "Math" )
	static bool EvaluateMathExpression( const FString& expression, UPARAM( DisplayName = "Result" ) FText& out_Result );

	/** Does the same thing as UEditorAssetLibrary::SetMetadataTag but exposed to gameplay code since we have tools that are technically running as gameplay. Content of function is wrapped with editor only */
	UFUNCTION( BlueprintCallable, Category = "Editor Scripting | Metadata", meta = ( DevelopmentOnly ) )
	static void SetMetadataTag( UObject* object, FName tag, const FString& value );

	/** Does the same thing as UEditorAssetLibrary::GetMetadataTag but exposed to gameplay code since we have tools that are technically running as gameplay. Content of function is wrapped with editor only */
	UFUNCTION( BlueprintCallable, Category = "Editor Scripting | Metadata", meta = ( DevelopmentOnly ) )
	static FString GetMetadataTag( UObject* object, FName tag );


public:
	FORCEINLINE ~UFGBlueprintFunctionLibrary() = default;
};