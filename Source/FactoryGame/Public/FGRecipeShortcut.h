#pragma once
#include "Array.h"
#include "SubclassOf.h"
#include "UObject/Class.h"

#include "FGHotbarShortcut.h"
#include "FGRecipeShortcut.generated.h"

UCLASS()
class FACTORYGAME_API UFGRecipeShortcut : public UFGHotbarShortcut
{
	GENERATED_BODY()
public:
	/** Decide on what properties to replicate */
	virtual void GetLifetimeReplicatedProps( TArray<FLifetimeProperty>& OutLifetimeProps ) const override;

	/** Get the recipe we want to activate when activating this shortcut */
	UFUNCTION( BlueprintPure, Category="Shortcut" )
	TSubclassOf< class UFGRecipe > GetRecipe() const{ return mRecipeToActivate; }

	/** Set the recipe of the current shortcut, the recipe will be saved
	 * @param recipe - null is valid, then we won't have any shortcut show up
	 **/
	UFUNCTION( BlueprintCallable, Category="Shortcut" )
	void SetRecipe( TSubclassOf< class UFGRecipe > recipe );

	//~ Begin UFGHotbarShortcut interface
	void Execute_Implementation( class AFGPlayerController* owner ) override;
	bool IsValidShortcut_Implementation( class AFGPlayerController* owner ) const override;
	UTexture2D* GetDisplayImage_Implementation() const override;
	bool IsActive_Implementation( class AFGPlayerController* owner ) const override;
	//~ End UFGHotbarShortcut interface
protected:
	UFUNCTION()
	void OnRep_Recipe();
protected:
	UPROPERTY( ReplicatedUsing=OnRep_Recipe, SaveGame )
	TSubclassOf< class UFGRecipe > mRecipeToActivate;

public:
	FORCEINLINE ~UFGRecipeShortcut() = default;
};