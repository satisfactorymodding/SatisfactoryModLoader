// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "InputAction.h"
#include "Engine/DeveloperSettings.h"
#include "Layout/Margin.h"
#include "FGInputSettings.generated.h"

//<FL>[KonradA]
USTRUCT(BlueprintType)
struct FACTORYGAME_API FStringTextureMap
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Id;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* Texture;

};
//</FL>

USTRUCT( BlueprintType )
struct FACTORYGAME_API FInputActionTagBinding
{
	GENERATED_BODY()

	/** Binding Name. Should match the name of the InputAction. */
	UPROPERTY( VisibleAnywhere )
	FName BindingName;

	/** The tag we wish to associate with this input action. */
	UPROPERTY( EditAnywhere, BlueprintReadOnly )
	FGameplayTag GameplayTag;

	/** Soft object path for the input action object. */
	UPROPERTY()
	TSoftObjectPtr<class UInputAction> ObjectPath;

	/** Cached object pointer to the input action. */
	UPROPERTY( Transient )
	TObjectPtr< class UInputAction > CachedInputAction;
};

// <FL> [WuttkeP] Added key/texture bindings for displaying in button hints.
USTRUCT( BlueprintType )
struct FACTORYGAME_API FFGKeyTextureBinding
{
	GENERATED_BODY()

	UPROPERTY( EditAnywhere, BlueprintReadOnly )
	FKey Key;

	UPROPERTY( EditAnywhere, BlueprintReadOnly, meta = ( DisplayName = "Primary Controller Icon" ) )
	class UTexture* TexturePrimary;

	UPROPERTY( EditAnywhere, BlueprintReadOnly, meta = ( DisplayName = "Secondary Controller Icon" ) )
	class UTexture* TextureSecondary;

		UPROPERTY( EditAnywhere, BlueprintReadOnly, meta = ( DisplayName = "Primary Slate Controller Icon" ) )
	class UTexture2D* TexturePrimarySlate;

	UPROPERTY( EditAnywhere, BlueprintReadOnly, meta = ( DisplayName = "Secondary Slate Controller Icon" ) )
	class UTexture2D* TextureSecondarySlate;

	UPROPERTY( EditAnywhere, BlueprintReadOnly )
	FMargin InternalPaddingPrimary;

	UPROPERTY( EditAnywhere, BlueprintReadOnly )
	FMargin InternalPaddingSecondary;
};
// </FL>

// <FL> [VilagosD] for displaying custom button hints that dont match single key
USTRUCT( BlueprintType )
struct FACTORYGAME_API FFGTagTextureBinding
{
	GENERATED_BODY()

	//for displaying custom button hints that dont match single key
	UPROPERTY( EditAnywhere, BlueprintReadOnly )
	FGameplayTag Tag;

	UPROPERTY( EditAnywhere, BlueprintReadOnly, meta = ( DisplayName = "Primary Controller Icon" ) )
	class UTexture* TexturePrimary;

	UPROPERTY( EditAnywhere, BlueprintReadOnly, meta = ( DisplayName = "Secondary Controller Icon" ) )
	class UTexture* TextureSecondary;

	UPROPERTY( EditAnywhere, BlueprintReadOnly )
	FMargin InternalPaddingPrimary;

	UPROPERTY( EditAnywhere, BlueprintReadOnly )
	FMargin InternalPaddingSecondary;
};
// </FL>

/**
 * Input settings for Satisfactory.
 */
UCLASS( config = Input, defaultconfig, meta = ( DisplayName = "Satisfactory Input Settings" ) )
class FACTORYGAME_API UFGInputSettings : public UDeveloperSettings
{
	GENERATED_BODY()
public:
	UFGInputSettings();
	
	static const UFGInputSettings* Get() { return GetDefault< UFGInputSettings >(); };

	virtual FName GetCategoryName() const override;

	/** Returns an InputAction which has been paired to the specified tag. */
	UFUNCTION( BlueprintCallable, Category = "Input" )
	TSoftObjectPtr<UInputAction> GetInputActionForTag( const FGameplayTag& Tag ) const;
	
	// <FL> [WuttkeP] Added key/texture bindings for displaying in button hints.
	UFUNCTION( BlueprintCallable, Category = "Input" )
	bool GetKeyTextureBinding( const FKey& Key, FFGKeyTextureBinding& out_Binding ) const;

	// <FL> [VilagosD] for displaying custom button hints that dont match single key
	UFUNCTION( BlueprintCallable, Category = "Input" )
	bool GetTagTextureBinding( const FGameplayTag& Key, FFGTagTextureBinding& out_Binding ) const;

	const TArray< FFGKeyTextureBinding >& GetKeyTextureBindingArray() const { return mKeyTextureBindings; }

	FMargin GetVariantTexturePadding() const { return mVariantTexturePadding; }
//<FL>[KonradA]
	UTexture2D* GetInlineTextureForId( FString TextureId ) const;
//</FL>
	//<FL>[MartinC]
	float GetLongPressVariantSeconds() const { return mLongPressVariantSeconds; }

	//<FL>[MartinC]
	float GetVeryLongPressVariantSeconds() const { return mVeryLongPressVariantSeconds; }

	// <FL> [WuttkeP]
	float GetMaxTapSeconds() const { return mMaxTapSeconds; }

	// </FL>
#if WITH_EDITOR
	virtual EDataValidationResult IsDataValid( class FDataValidationContext& Context ) const override;
	virtual void PostEditChangeProperty( FPropertyChangedEvent& PropertyChangedEvent ) override;

	UFUNCTION( BlueprintCallable )
	static void CalcKeyImagePaddings( UTexture* VariantTexture );
#endif
	
protected:
	virtual void PostInitProperties() override;

	/** Refreshes the input action binding array, removing invalid bindings and adding new ones, if new InputActions are found. */
	void RefreshInputActionBindingArray();

	/** Callbacks for assets being registered, used to keep track of InputAction assets. */
	void OnAssetAdded( const FAssetData& AssetData );
	void OnAssetRemoved( const FAssetData& AssetData );

private:
	/** Wrapper function for creating an InputAction - GameplayTag binding. */
	void CreateActionTagBinding( const FAssetData& InputActionAssetData );

#if WITH_EDITOR
	/** Runs IsDataValid and prints the result in the message log. */
	void Validate();
#endif

#if WITH_EDITORONLY_DATA
private:
	/** Map used to show what input bindings don't have a valid gameplay tag. Value is their index in the input action array. It won't be possible to reference these input actions by a GameplayTag unless they are assigned. */
	UPROPERTY( VisibleAnywhere )
	TMap< FName, int32 > mInputActionBindingsWithoutValidTag;
#endif

protected:
	// TODO Tobias: Maybe we want to store these on a data asset instead? In that case we can have different setups of bindings but I'm not sure if that's really needed? Maybe for other input configurations?
	/** List of input actions and whatever tag they should be mapped to. */
	UPROPERTY( config, EditAnywhere, meta = (TitleProperty = "BindingName") )
	TArray< FInputActionTagBinding > mInputActionTagBindings;
	// <FL> [WuttkeP] Added key/texture bindings for displaying in button hints.
	UPROPERTY( config, EditAnywhere )
	TArray< FFGKeyTextureBinding > mKeyTextureBindings;
	// <FL> [VilagosD] Added key/texture bindings for displaying in button hints.
	UPROPERTY( config, EditAnywhere )
	TArray< FFGTagTextureBinding > mTagTextureBindings;
	// <FL>[KonradA] Platform Mini-Textures for inline Texts
	UPROPERTY( config, EditAnywhere )
	TArray < FStringTextureMap> PlatformInlineTextDecoratorTextures;
	UPROPERTY( config, EditAnywhere )
	FMargin mVariantTexturePadding;
	// </FL>
	// <FL> [MartinC] Interaction duration for long press on gamepad keybindings
	UPROPERTY( config, EditAnywhere )
	float mLongPressVariantSeconds = 0.5f;
	// <FL> [MartinC] Interaction duration for very long press on gamepad keybindings
	UPROPERTY( config, EditAnywhere )
	float mVeryLongPressVariantSeconds = 1.0f;
	// </FL>
	// <FL> [WuttkeP] Maximum time a gamepad button is pressed for it to be considered a tap.
	UPROPERTY( config, EditAnywhere )
	float mMaxTapSeconds = 0.2f;
	// </FL>
};
