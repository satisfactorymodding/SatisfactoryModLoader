// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

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
	
	/** Set the blueprint name of the current shortcut, the name will be saved
	 * @param inBlueprintName - empty is valid, then we won't have any shortcut show up
	 * @param silent if true, the "Shortcut Bound" notification will be suppressed
	 **/
	UFUNCTION( BlueprintCallable, Category="Shortcut" )
	void SetBlueprintName( const FString& inBlueprintName, bool silent = false );

	//~ Begin UFGHotbarShortcut interface
	void Execute_Implementation( class AFGPlayerController* owner ) override;
	bool IsValidShortcut_Implementation( class AFGPlayerController* owner ) const override;
	class UTexture2D* GetDisplayImage_Implementation() const override;
	bool IsActive_Implementation( class AFGPlayerController* owner ) const override;
	virtual bool IsSame_Implementation(UFGHotbarShortcut* shortcut) const override;
	virtual FString DescribeShortcut_Implementation() const override;
	//~ End UFGHotbarShortcut interface

	/** Returns the blueprint descriptor for this shortcut, if it has been resolved with the blueprint subsystem already */
	UFUNCTION( BlueprintPure, Category = "Shortcut" )
	FORCEINLINE class UFGBlueprintDescriptor* GetBlueprintDescriptor() const { return mBlueprintDescriptor; }
protected:
	UFUNCTION()
	void OnRep_BlueprintName();

	virtual void OnClientSubsystemsValid() override;
	virtual void DestroyShortcut_Implementation() override;

	UFUNCTION()
	void OnBlueprintDescriptorUpdated( UFGBlueprintDescriptor* blueprintDescriptor );
	
	void UpdateBlueprintDescriptor();
protected:
	
	UPROPERTY( ReplicatedUsing=OnRep_BlueprintName, SaveGame )
	FString mBlueprintName;

	UPROPERTY( Transient )
	UFGBlueprintDescriptor* mBlueprintDescriptor;
};
