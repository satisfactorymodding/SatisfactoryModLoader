// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"
#include "EnhancedPlayerInput.h"
#include "Framework/Application/IInputProcessor.h"
#include "GameFramework/PlayerInput.h"
#include "FGPlayerInput.generated.h"

USTRUCT()
struct FCachedActionMappingContextPair
{
	GENERATED_BODY()

	FCachedActionMappingContextPair(){};
	FCachedActionMappingContextPair( const FEnhancedActionKeyMapping& inMapping, UInputMappingContext* inOwningContext ) :
		Mapping( inMapping ),
		OwningContext( inOwningContext )
	{};

	UPROPERTY()
	FEnhancedActionKeyMapping Mapping;

	UPROPERTY( Transient )
	UInputMappingContext* OwningContext;
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

	void Native_GetActionMappings( TArray<FEnhancedActionKeyMapping>& out_KeyMappings );

	/* Get overlapping key bindings that is remappable */
	bool GetOverlappingEnhancedKeyMappings( const FName& inActionName, const FKey& newKey, const TArray<FKey>& modifierKeys, TArray<FEnhancedActionKeyMapping>& out_HardConflicts, TArray<FEnhancedActionKeyMapping>& out_SoftConflicts );
	
	/* Returns true if we find a mapped key for the given action. Will first check player mapped keys and then fallback to default mappings.
	 * out_primaryKey can be a FKeys::Invalid if we removed a conflicting binding  */
	bool GetCurrentMappingForAction( const FName& inActionName, FKey& out_primaryKey, TArray<FKey>& out_modifierKeys );

	/** Functions to receive mouse up and down events so we can process them and make sure we don't miss any events */
	void HandleMouseButtonDownEvent( const FPointerEvent& MouseEvent );
	void HandleMouseButtonUpEvent( const FPointerEvent& MouseEvent );

	/* Dumps all states in UPlayerInput::KeyStateMap to the log  */
	void DumpKeyStates();

	/** Flushes the mouse keys. */
	void FlushMouseKeys();

private:
	void TryCacheDefaultKeyMappings();

private:
	/** All default key mappings we use in the game for keyboard and mouse. Cached for faster access since we don't always have a context and want to find keys
	    based on FEnhancedActionKeyMapping::PlayerMappableOptions::Name. This map that name to the relevant FEnhancedActionKeyMapping */
	TMap<FName, FCachedActionMappingContextPair> mCachedDefaultKeyMappings;

	/** An instance of the input processor used to catch and handle specific input events early, before they reach slate. */
	TSharedPtr<UFGPlayerInputPreProcessor> mInputPreprocessor = nullptr;

	/** The released mouse buttons that have not been processed yet. Populated by calls from UFGPlayerInputPreProcessor and then handled in ProcessInputStack */
	TArray<FKey> mReleasedMouseButtons;
};
