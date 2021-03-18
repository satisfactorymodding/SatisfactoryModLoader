// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "Resources/FGResourceNodeBase.h"
#include "FGUseableInterface.h"
#include "Resources/FGExtractableResourceInterface.h"
#include "FGResourceNode.generated.h"

class UFGResourceDescriptor;

/** How much resources this node contains, a rich vein will deplete later */
UENUM( BlueprintType )
enum EResourceAmount
{
	RA_Poor UMETA(DisplayName="Poor"),
	RA_Normal UMETA( DisplayName = "Normal" ),
	RA_Rich UMETA( DisplayName = "Rich" ),
	RA_Infinite UMETA( DisplayName = "Infinite"),
	RA_MAX UMETA( Hidden )
};

/** How how fast it is to mine the resource */
UENUM()
enum EResourcePurity
{
	RP_Inpure UMETA( DisplayName = "Impure" ),
	RP_Normal UMETA( DisplayName = "Normal" ),
	RP_Pure UMETA( DisplayName = "Pure" ),
	RP_MAX UMETA( Hidden )
};

USTRUCT( BlueprintType )
struct FACTORYGAME_API FPurityTextPair
{
	GENERATED_BODY()

	FPurityTextPair() :
		Text( FText() ),
		Purity( EResourcePurity::RP_Inpure )
	{
	}

	/** Localizable text */
	UPROPERTY( EditDefaultsOnly, Category = "Resources" )
	FText Text;

	/** Enum to localize */
	UPROPERTY( EditDefaultsOnly, Category = "Resources" )
	TEnumAsByte< EResourcePurity > Purity;
};

/**
 * Use state when inventory of player looking at the node has a full inventory
 */
UCLASS()
class FACTORYGAME_API UFGUseState_NodeFullInventory : public UFGUseState
{
	GENERATED_BODY()

	UFGUseState_NodeFullInventory() : Super() { mIsUsableState = false; }
};

UCLASS( Abstract )
class FACTORYGAME_API AFGResourceNode : public AFGResourceNodeBase
{
	GENERATED_BODY()
public:
	AFGResourceNode();

	// Begin AActor interface
	virtual void BeginPlay() override;
	// End AActor interface

	//~ Begin IFGUseableInterface
	virtual void UpdateUseState_Implementation( class AFGCharacterPlayer* byCharacter, const FVector& atLocation, class UPrimitiveComponent* componentHit, FUseState& out_useState ) const override;
	virtual void OnUse_Implementation( class AFGCharacterPlayer* byCharacter, const FUseState& state ) override;
	virtual void OnUseStop_Implementation( class AFGCharacterPlayer* byCharacter, const FUseState& state ) override;
	virtual bool IsUseable_Implementation() const override { return true; }
	virtual void StartIsLookedAt_Implementation( class AFGCharacterPlayer* byCharacter, const FUseState& state ) override;
	virtual FText GetLookAtDecription_Implementation( class AFGCharacterPlayer* byCharacter, const FUseState& state ) const override;
	virtual void StopIsLookedAt_Implementation( class AFGCharacterPlayer* byCharacter, const FUseState& state ) override;
	virtual void RegisterInteractingPlayer_Implementation( class AFGCharacterPlayer* player ) override {};
	virtual void UnregisterInteractingPlayer_Implementation( class AFGCharacterPlayer* player ) override {};
	//~ End IFGUseableInterface

	// Begin IFGExtractableResourceInterface
	virtual bool HasAnyResources() const override;
	virtual int32 ExtractResource( int32 amount ) override;
	virtual float GetExtractionSpeedMultiplier() const override;
	virtual bool CanPlaceResourceExtractor() const override;
	// End IFGExtractableResourceInterface

	/** Setup the resource so it's usable, sets up amount left */
	UFUNCTION(BlueprintCallable, Category="Resources")
	void InitResource( TSubclassOf<UFGResourceDescriptor> resourceClass, EResourceAmount amount, EResourcePurity purity );

	/** For UI */
	UFUNCTION(BlueprintPure,Category="Resources")
	FText GetResoucesLeftText() const;

	/** For UI */
	UFUNCTION( BlueprintPure, Category = "Resources" )
	FText GetResoucePurityText() const;

	/** For UI, returns the enum */
	UFUNCTION( BlueprintPure, Category = "Resources" )
	FORCEINLINE EResourcePurity GetResoucePurity(){ return mPurity; }

	/** The range of a resource for a amount */
	const FInt32Interval& GetResourceAmount( EResourceAmount amount ) const;

	/** Get a random resource amount */
	int32 GetRandomResourceAmount( EResourceAmount amount ) const;

	/** Opens or closes the picking ui */
	UFUNCTION( BlueprintImplementableEvent, Category = "Resources" )
	void ToggleResourcePickUI( AFGCharacterPlayer* player );
	
	/** Gives one resource to a player */
	UFUNCTION( BlueprintCallable )
	virtual void ExtractResourceAndGiveToPlayer( AFGCharacterPlayer* toPlayer, int32 amount = 1 );

	/**Getter for extract multiplier */
	UFUNCTION( BlueprintPure, Category = "Resources" )
	FORCEINLINE int32 GetExtractMultiplier() const { return mExtractMultiplier; }

	/** Returns the mAmount */
	UFUNCTION( BlueprintCallable )
	FORCEINLINE EResourceAmount GetResourceAmount() const { return mAmount; }

	/** Cleanup function for UI. Placed here so that both nodes and deposits can take the same code path */
	UFUNCTION( BlueprintCallable, BlueprintImplementableEvent, Category = "UI" )
	void ClearWidget();

	int32 GetNumResourcesPerExtract() const;

#if WITH_EDITOR

	/** When this is changed in the editor, propagate the changes to the preview window */
	virtual void PostEditChangeProperty( struct FPropertyChangedEvent& propertyChangedEvent ) override;

#endif

protected:
	/** Setup radiation emitters for radioactive resources. */
	virtual void InitRadioactivity();

	/** Called when a resource is extracted. Never called on infinite resource nodes. */
	virtual void UpdateRadioactivity();

public: // MODDING EDIT: protected -> public
	/** How pure the resource is */
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Resources" ) // MODDING EDIT: BPRW
	TEnumAsByte<EResourcePurity> mPurity;

	/** How pure the resource is */
	UPROPERTY( EditInstanceOnly, BlueprintReadWrite, Category = "Resources" ) // MODDING EDIT: BPRW
	TEnumAsByte<EResourceAmount> mAmount;

	/** How much resources is left in this node */
	UPROPERTY( SaveGame, Replicated, EditInstanceOnly, BlueprintReadOnly, Category="Resources")
	int32 mResourcesLeft;

protected: // MODDING EDIT
	/** Can this resource node be used for placing resource extractors on */
	UPROPERTY( EditDefaultsOnly, Category = "Resources" )
	bool mCanPlaceResourceExtractor;

	/** Multiplier that is applied in the end of extraction calculations. Is used for making deposits extract more than regular nodes */
	UPROPERTY( EditDefaultsOnly, Category = "Resources" )
	int32 mExtractMultiplier;

	/** Text mapped to resource purity */
	UPROPERTY( EditDefaultsOnly, Category = "Resources" )
	TArray< FPurityTextPair > mPurityTextArray;

	/** Last frame we flushed net dormancy */
	uint64 mLastFlushFrame;
public:
	/** Can this resource node be used for placing portable miners on */
	bool mCanPlacePortableMiner;
private:
};
