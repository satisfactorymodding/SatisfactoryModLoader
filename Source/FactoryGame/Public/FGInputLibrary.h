// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "EnhancedActionKeyMapping.h"
#include "GameFramework/PlayerInput.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "FGInputLibrary.generated.h"


USTRUCT( BlueprintType )
struct FFGKeyMapping
{
	GENERATED_BODY()

	FFGKeyMapping() : 
		IsAxisMapping( false )
	{
	}
	
	UPROPERTY( BlueprintReadOnly, Category = "Input" )
	FInputActionKeyMapping ActionKeyMapping;
	
	UPROPERTY( BlueprintReadOnly, Category = "Input" )
	FInputAxisKeyMapping AxisKeyMapping;

	UPROPERTY( BlueprintReadOnly, Category = "Input" )
	bool IsAxisMapping;

};

USTRUCT( BlueprintType )
struct FFGCustomInputActionMapping
{
	GENERATED_BODY()

	FFGCustomInputActionMapping( const FName& inActionName, const FKey& inPrimaryKey, const TArray<FKey>& inModifierKeys ) :
		ActionName( inActionName ),
		PrimaryKey( inPrimaryKey ),
		ModifierKeys( inModifierKeys )
	{}
	FFGCustomInputActionMapping(){}

	UPROPERTY(BlueprintReadWrite, Category = "Input" )
	FName ActionName = FName();

	UPROPERTY(BlueprintReadWrite, Category = "Input" )
	FKey PrimaryKey = FKey();

	UPROPERTY()
	TArray<FKey> ModifierKeys;
};

/**
 * 
 */
UCLASS()
class FACTORYGAME_API UFGInputLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	/** Returns the action key mapping for the action we specify */
	UFUNCTION( BlueprintPure, Category = "Input", meta=(DeprecatedFunction,DeprecationMessage = "DEPRECATED PART OF OLD INPUT SYSTEM") )
	static FInputActionKeyMapping GetKeyMappingForAction( APlayerController* playerController, FName inAction, bool getGamepadKey );

	/** Returns a shortened name for a key */
	UFUNCTION( BlueprintPure, Category = "Input" )
	static FText GetAbbreviatedKeyName( FKey key );

// ENHANCED INPUT SUPPORT 
	
	/** Replaces input action names in the provided text with the corresponding key e.g. ("{PrimaryFire} is for shooting and {PlayerActions_Use} is for using" returns "LMB is for shooting and E is for using" */
	UFUNCTION( BlueprintPure, Category = "Input" )
	static FText FormatStringWithInputActionNames( APlayerController* playerController, FText textToFormat, bool abbreviateKeyNames = true );

	/** Returns the mapped keys to the input action name as a text. "PrimaryFire" returns LMB
	 */
	UFUNCTION( BlueprintPure, Category = "Input" )
	static FText GetInputActionNameAsText( APlayerController* playerController, const FName& inActionName, bool abbreviateKeyNames = true );

	/** Returns all mapping contexts that have at least one rebindable mapping. Sorted by UFGInputMappingContext::mMenuPriority */
	UFUNCTION( BlueprintCallable, Category = "Input" )
	static void GetPlayerRebindableMappingContexts(TArray<class UFGInputMappingContext*>& out_MappingContexts);
	
	/** Returns a global mapping of a parent mapping context to a list of child ones */
	static void FindAllChildMappingContexts(TMultiMap<TSoftObjectPtr<UFGInputMappingContext>, TSoftObjectPtr<UFGInputMappingContext>>& out_ParentToChildContexts);

	/** Returns an input action associated with the specified gameplay tag, if one can be found. */
	UFUNCTION( BlueprintPure, Category = "Input" )
	static TSoftObjectPtr< class UInputAction > FindInputActionByTag( const FGameplayTag& tag );

	/** Returns an input action based on a mapping name. It needs to exist as a binding on the player input by applying a mapping context with the specified action beforehand. */
	UFUNCTION( BlueprintPure, Category = "Input" )
	static TSoftObjectPtr< class UInputAction > FindInputActionByMappingName( APlayerController* playerController, const FName& mappingName );
	
	/** Returns if we have any conflicting mappings with the same exact keys. Hard conflicts are mappings in the same context and soft conflicts are mappings in other contexts */ 
	UFUNCTION( BlueprintCallable, Category = "Input" )
	static bool GetOverlappingEnhancedKeyMappings( APlayerController* playerController, const FName& inActionName, const FKey& primaryKey, const TArray<FKey>& modifierKeys, TArray<FEnhancedActionKeyMapping>& out_HardConflicts, TArray<FEnhancedActionKeyMapping>& out_SoftConflicts );

	/** Rebind a mapping with the given action name. If there is a hard conflict, Binding with the same exact keys in the same context, the conflicting key will be overwritten with None (FKeys:Invalid)   */
	UFUNCTION( BlueprintCallable, Category = "Input" )
	static void RebindEnhancedKeyMapping( APlayerController* playerController, const FName& inActionName, const FKey& primaryKey, const TArray<FKey>& modifierKeys );

	/** Remove all keybindings that the player have mapped */
	UFUNCTION( BlueprintCallable, Category = "Input" )
	static void ResetAllEnhancedKeyBindings( APlayerController* playerController );

	/* Returns true if we find a mapped key for the given action. Will first check player mapped keys and then fallback to default mappings.
	 * out_primaryKey can be a FKeys::Invalid if we removed a conflicting binding  */
	UFUNCTION( BlueprintCallable, Category = "Input" )
	static bool GetCurrentMappingForAction( APlayerController* playerController, const FName& inActionName, FKey& out_primaryKey, TArray<FKey>& out_modifierKeys );

	/** Clears any inut callback delegates from the given user widget
	 *	Exposes UInputComponent::ClearBindingsForObject for a widget
	 */
	UFUNCTION( BlueprintCallable, Category = "Input" )
	static void ClearBindingsForWidget( UUserWidget* widget );

	// <FL> [WuttkeP] Added function to retrieve the corresponding texture for a controller button.
	UFUNCTION( BlueprintCallable, Category = "UI" )
	static UTexture* GetTextureFromKey( const FKey& key );

	UFUNCTION( BlueprintCallable, Category = "UI" )
	static UTexture* GetTextureFromTag( const FGameplayTag& tag );

	UFUNCTION( BlueprintCallable, Category = "UI" )
	static bool GetTexturePaddingFromKey( const FKey& key, FMargin& out_Padding );

	UFUNCTION( BlueprintPure, Category = "UI" )
	static FMargin GetReferenceKeyTexturePadding();

	UFUNCTION( BlueprintPure, Category = "UI" )
	static FMargin GetKeyVariantTexturePadding();

	UFUNCTION( BlueprintCallable, Category = "UI" )
	static bool GetKeyTextureBinding( const FKey& key, struct FFGKeyTextureBinding& out_Binding );
	// </FL>
private:
	static const TArray<FString> IRRELEVANT_PREFIXES;
};
