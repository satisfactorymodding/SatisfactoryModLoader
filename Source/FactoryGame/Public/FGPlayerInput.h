// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "EnhancedActionKeyMapping.h"
#include "EnhancedPlayerInput.h"
#include "Framework/Application/IInputProcessor.h"
#include "GameFramework/PlayerInput.h"
#include "FGPlayerInput.generated.h"

USTRUCT( BlueprintType )
struct FACTORYGAME_API FFGCachedActionMapping
{
	GENERATED_BODY()

	// Mapping that was deemed default. Used when no player mappable name is available, e.g. the key is not re-mappable or it's a chord.
	UPROPERTY()
	FEnhancedActionKeyMapping DefaultKeyMapping;

	// Mappings of keys for each player re-mappable name
	UPROPERTY()
	TMap<FName, FEnhancedActionKeyMapping> MappingsByPlayerMappableName;

	// Returns the mapping for the given action name, or the default
	FEnhancedActionKeyMapping FindMappingForActionName( FName actionName ) const;
};

USTRUCT()
struct FACTORYGAME_API FFGCachedActionMappingContextMap
{
	GENERATED_BODY()

	// Mappings for each input context
	UPROPERTY()
	TMap<UInputMappingContext*, FFGCachedActionMapping> Mappings;
};

UINTERFACE( Blueprintable )
class FACTORYGAME_API UFGBlueprintInputPreprocessor : public UInterface
{
	GENERATED_BODY()
};

class FACTORYGAME_API IFGBlueprintInputPreprocessor
{
	GENERATED_BODY()

public:
	UFUNCTION( BlueprintCallable, BlueprintImplementableEvent )
	bool HandleKeyDownEvent(const FKeyEvent& InKeyEvent);

	UFUNCTION( BlueprintCallable, BlueprintImplementableEvent )
	bool HandleKeyUpEvent(const FKeyEvent& InKeyEvent);
};

/**
 * UFGPlayerInputPreProcessor is a custom input pre-processor class that intercepts and processes input events
 * before they reach slate. It is designed to resolve a bug where the game receives a pressed
 * event, but the corresponding release event is consumed by a Slate widget, causing the game to miss the release event.
 */

class UFGPlayerInputPreProcessor : public IInputProcessor
{
public:
	UFGPlayerInputPreProcessor( class UFGPlayerInput* playerInput );
	virtual ~UFGPlayerInputPreProcessor() override;
	
	//~ Begin IInputProcessor Interface
	virtual void Tick( const float DeltaTime, FSlateApplication& SlateApp, TSharedRef<ICursor> Cursor ) override;
	virtual bool HandleMouseButtonDownEvent( FSlateApplication& SlateApp, const FPointerEvent& MouseEvent ) override;
	virtual bool HandleMouseButtonUpEvent( FSlateApplication& SlateApp, const FPointerEvent& MouseEvent ) override;
	virtual bool HandleKeyDownEvent( FSlateApplication& SlateApp, const FKeyEvent& InKeyEvent ) override;
	virtual bool HandleKeyUpEvent( FSlateApplication& SlateApp, const FKeyEvent& InKeyEvent ) override;
	virtual bool HandleAnalogInputEvent( FSlateApplication& SlateApp, const FAnalogInputEvent& InAnalogInputEvent ) override; // <FL> [ZimmermannA] Used to disable gamepad on PC
	//~ End IInputProcessor Interface

private:
	UFGPlayerInput* mPlayerInput = nullptr;
};
/**
 * 
 */
UCLASS()
class FACTORYGAME_API UFGPlayerInput : public UEnhancedPlayerInput
{
	GENERATED_BODY()
public:
	//~ Begin UPlayerInput Interface
	virtual void PostInitProperties() override;
	virtual void BeginDestroy() override;
	virtual float SmoothMouse( float aMouse, uint8& SampleCount, int32 Index ) override;
	virtual void ProcessInputStack( const TArray<UInputComponent*>& InputComponentStack, const float DeltaTime, const bool bGamePaused ) override;
	//~ End UPlayerInput Interface
	
	UFUNCTION( BlueprintCallable, Category = "Input", Meta = (DisplayName = "GetEnhancedActionMappings") )
	static void GetActionMappings( APlayerController* playerController, TArray<FEnhancedActionKeyMapping>& out_KeyMappings );
	
	void Native_GetActionMappings( TArray<FEnhancedActionKeyMapping>& out_KeyMappings ) const;

	/* Get overlapping key bindings that is remappable */
	bool GetOverlappingEnhancedKeyMappings( const FName& inActionName, const FKey& newKey, const TArray<FKey>& modifierKeys, TArray<FEnhancedActionKeyMapping>& out_HardConflicts, TArray<FEnhancedActionKeyMapping>& out_SoftConflicts ) const;

	/** Version of the above function that takes input action as an argument instead of relying on action name */
	bool GetOverlappingEnhancedKeyMappings( const UInputAction* inputAction, const FKey& newKey, const TArray<FKey>& modifierKeys, TArray<FEnhancedActionKeyMapping>& out_HardConflicts, TArray<FEnhancedActionKeyMapping>& out_SoftConflicts ) const;

	/** Attempts to find keys mapped to the given primary + modifier key pairs */
	void FindKeysMappedTo( const FKey& newKey, const TArray<FKey>& modifierKeys, TMap<const UInputMappingContext*, TArray<FEnhancedActionKeyMapping>>& out_mappedKeys ) const;
	
	/* Returns true if we find a mapped key for the given action. Will first check player mapped keys and then fallback to default mappings.
	 * out_primaryKey can be a FKeys::Invalid if we removed a conflicting binding  */
	bool GetCurrentMappingForAction( const FName& inActionName, FKey& out_primaryKey, TArray<FKey>& out_modifierKeys ) const;

	/** More convoluted version of the above function */
	bool GetCurrentMappingForInputAction( const UInputAction* inputAction, FKey& out_primaryKey, TArray<FKey>* out_modifierKeys, FName preferredActionName, const UInputMappingContext* preferredContext ) const;

	/** Functions to receive mouse up and down events so we can process them and make sure we don't miss any events */
	void HandleMouseButtonDownEvent( const FPointerEvent& MouseEvent );
	void HandleMouseButtonUpEvent( const FPointerEvent& MouseEvent );
	bool HandleKeyDownEvent( const FKeyEvent& InKeyEvent );
	bool HandleKeyUpEvent( const FKeyEvent& InKeyEvent );

	/* Dumps all states in UPlayerInput::KeyStateMap to the log  */
	void DumpKeyStates();

	/** Flushes the mouse keys. */
	void FlushMouseKeys();

	/** Attempts to resolve action using it's mappable name */
	UFUNCTION( BlueprintPure, Category = "Input" )
	const UInputAction* FindActionByMappableActionName( FName actionName ) const;
	
	UFUNCTION( BlueprintCallable, Category = "Input" )
	static void AddBlueprintInputPreprocessor( APlayerController* playerController, TScriptInterface<UFGBlueprintInputPreprocessor> preprocessor );

	UFUNCTION( BlueprintCallable, Category = "Input" )
	static void RemoveBlueprintInputPreprocessor( APlayerController* playerController, TScriptInterface<UFGBlueprintInputPreprocessor> preprocessor );
	
	/**
	 * Attempts to find a mapping for the provided action in the preferred mapping context, or in any context whatsoever if allowed.
	 * It will prefer the mapping with the specified action name. If no action name is provided, or it is NONE, it will return the default mapping
	 */
	bool FindDefaultKeyMappingForInputAction( const UInputAction* inputAction, FName preferredActionName, const UInputMappingContext* preferredContext, bool allowOtherContexts, FEnhancedActionKeyMapping& out_keyMapping, const UInputMappingContext** out_mappingContext = nullptr ) const;

	/** Returns all contexts in which the given input action is bound */
	bool FindAllMappedContextsForInputAction( const UInputAction* inputAction, TArray<UInputMappingContext*>& out_mappedContexts ) const;
protected:
	void TryCacheDefaultKeyMappings() const;
	void GatherKeyMappingsFromInputContext( UInputMappingContext* mappingContext ) const;
	
private:
	/** A map of all input actions to their bindings in various contexts */
	UPROPERTY()
	mutable TMap<const UInputAction*, FFGCachedActionMappingContextMap> mDefaultKeyMappings;

	/** Maps player re-bindable action names to input actions that correspond to them. Assumes 1-to-1 relationship, e.g. a single mapping can only be used by a single key */
	UPROPERTY()
	mutable TMap<FName, const UInputAction*> mInputActionNameLookupMap;
	
	/** An instance of the input processor used to catch and handle specific input events early, before they reach slate. */
	TSharedPtr<UFGPlayerInputPreProcessor> mInputPreprocessor = nullptr;

	/** The released buttons that have not been processed yet. Populated by calls from UFGPlayerInputPreProcessor and then handled in ProcessInputStack */
	TArray<FKey> ReleasedButtons;

	UPROPERTY()
	TArray<UObject*> mBlueprintPreprocessors;
};
