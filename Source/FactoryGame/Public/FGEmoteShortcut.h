// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "FGHotbarShortcut.h"
#include "Templates/SubclassOf.h"
#include "FGEmoteShortcut.generated.h"

/**
 * 
 */
UCLASS()
class FACTORYGAME_API UFGEmoteShortcut : public UFGHotbarShortcut
{
	GENERATED_BODY()
	
public:
	/** Decide on what properties to replicate */
	virtual void GetLifetimeReplicatedProps( TArray<FLifetimeProperty>& OutLifetimeProps ) const override;

	/** Get the recipe we want to activate when activating this shortcut */
	UFUNCTION( BlueprintPure, Category="Shortcut" )
	TSubclassOf< class UFGEmote > GetEmote() const { return mEmoteToActivate; }

	/** Set the emote of the current shortcut, the emote will be saved
	 * @param emote - null is valid, then we won't have any shortcut show up
	 * @param silent if true, the "Shortcut Bound" notification will be suppressed
	 **/
	UFUNCTION( BlueprintCallable, Category="Shortcut" )
	void SetEmote( TSubclassOf< class UFGEmote > emote, bool silent = false );

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
	void OnRep_Emote();
	
	UPROPERTY( ReplicatedUsing=OnRep_Emote, SaveGame )
	TSubclassOf< class UFGEmote > mEmoteToActivate;
};
