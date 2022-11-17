// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"
#include "FGHotbarShortcut.h"
#include "FGBlueprintShortcut.generated.h"

/**
 * 
 */
UCLASS()
class FACTORYGAME_API UFGBlueprintShortcut : public UFGHotbarShortcut
{
	GENERATED_BODY()
public:
	/** Decide on what properties to replicate */
	virtual void GetLifetimeReplicatedProps( TArray<FLifetimeProperty>& OutLifetimeProps ) const override;

	/** Get the blueprint name we want to activate when activating this shortcut */
	UFUNCTION( BlueprintPure, Category="Shortcut" )
	FString GetBlueprintName() const { return mBlueprintName; }
	
	/** Get the blueprint descriptor we want to activate when activating this shortcut */
	UFUNCTION( BlueprintPure, Category="Shortcut" )
	class UFGBlueprintDescriptor* GetBlueprintDescriptor() const;

	/** Set the blueprint name of the current shortcut, the name will be saved
	 * @param blueprintName - empty is valid, then we won't have any shortcut show up
	 **/
	UFUNCTION( BlueprintCallable, Category="Shortcut" )
	void SetBlueprintName( const FString& inBlueprintName );

	//~ Begin UFGHotbarShortcut interface
	void Execute_Implementation( class AFGPlayerController* owner ) override;
	bool IsValidShortcut_Implementation( class AFGPlayerController* owner ) const override;
	class UTexture2D* GetDisplayImage_Implementation() const override;
	bool IsActive_Implementation( class AFGPlayerController* owner ) const override;
	//~ End UFGHotbarShortcut interface

protected:
	UFUNCTION()
	void OnRep_BlueprintName() const;

protected:
	UPROPERTY( ReplicatedUsing=OnRep_BlueprintName, SaveGame )
	FString mBlueprintName;
	
};
