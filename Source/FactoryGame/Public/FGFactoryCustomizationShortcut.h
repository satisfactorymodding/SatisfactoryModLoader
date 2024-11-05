// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FGHotbarShortcut.h"
#include "FGFactoryCustomizationShortcut.generated.h"

/**
 * A specific type of hotbar shortcut that is used for factory customization (coloring, patterns, materials)
 */
UCLASS()
class FACTORYGAME_API UFGFactoryCustomizationShortcut : public UFGHotbarShortcut
{
	GENERATED_BODY()
public:
	/** Decide on what properties to replicate */
	virtual void GetLifetimeReplicatedProps( TArray<FLifetimeProperty>& OutLifetimeProps ) const override;

	/** Get the Customization we want to activate when activating this shortcut */
	UFUNCTION( BlueprintPure, Category="Shortcut" )
	TSubclassOf< class UFGCustomizationRecipe > GetCustomizationRecipe() const { return mCustomizationRecipeToActivate; }

	/** Set the class of the customization recipe this shortcut should activate
	 * @param customization - null is valid, then we won't have any shortcut show up
	 * @param silent if true, the "Shortcut Bound" notification will be suppressed
	 **/
	UFUNCTION( BlueprintCallable, Category="Shortcut" )
	void SetCustomizationRecipe( TSubclassOf< class UFGCustomizationRecipe > customization, bool silent = false );

	//~ Begin UFGHotbarShortcut interface
	void Execute_Implementation( class AFGPlayerController* owner ) override;
	bool IsValidShortcut_Implementation( class AFGPlayerController* owner ) const override;
	UTexture2D* GetDisplayImage_Implementation() const override;
	bool IsActive_Implementation( class AFGPlayerController* owner ) const override;
	virtual bool IsSame_Implementation(UFGHotbarShortcut* shortcut) const override;
	virtual FString DescribeShortcut_Implementation() const override;
	//~ End UFGHotbarShortcut interface

protected:
	UFUNCTION()
	void OnRep_Customization();

	virtual void OnClientSubsystemsValid() override;
	virtual void DestroyShortcut_Implementation() override;

	UFUNCTION()
	void OnRecipeUnlocked( TSubclassOf<class UFGRecipe> recipeClass );
protected:
	UPROPERTY( ReplicatedUsing=OnRep_Customization, SaveGame )
	TSubclassOf< class UFGCustomizationRecipe > mCustomizationRecipeToActivate;
};