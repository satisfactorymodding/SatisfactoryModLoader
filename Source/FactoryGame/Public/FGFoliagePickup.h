// Copyright 2016 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "Engine/StaticMesh.h"
#include "UObject/Class.h"

#include "FGUseableInterface.h"
#include "GameFramework/Actor.h"
#include "FGFoliagePickup.generated.h"

UCLASS(abstract,notplaceable,transient)
class FACTORYGAME_API AFGFoliagePickup : public AActor, public IFGUseableInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFGFoliagePickup();

	//~ Begin IFGUseableInterface
	virtual void UpdateUseState_Implementation( class AFGCharacterPlayer* byCharacter, const FVector& atLocation, class UPrimitiveComponent* componentHit, FUseState& out_useState ) const override;
	virtual void OnUse_Implementation( class AFGCharacterPlayer* byCharacter, const FUseState& state ) override;
	virtual void OnUseStop_Implementation( class AFGCharacterPlayer* byCharacter, const FUseState& state ) override;
	virtual bool IsUseable_Implementation() const override;
	virtual void StartIsLookedAt_Implementation( class AFGCharacterPlayer* byCharacter, const FUseState& state  ) override;
	virtual FText GetLookAtDecription_Implementation( class AFGCharacterPlayer* byCharacter, const FUseState& state ) const override;
	virtual void StopIsLookedAt_Implementation( class AFGCharacterPlayer* byCharacter, const FUseState& state ) override;
	virtual void RegisterInteractingPlayer_Implementation( class AFGCharacterPlayer* player ) override {};
	virtual void UnregisterInteractingPlayer_Implementation( class AFGCharacterPlayer* player ) override {};
	//~ End IFGUseableInterface

	UFUNCTION(NetMulticast,Unreliable)
	void BroadcastPickup( class UStaticMesh* fromStaticMesh, FVector atLocation );

	UFUNCTION(BlueprintCosmetic,BlueprintImplementableEvent)
	void PlayPickupEffect( class UFGFoliageResourceUserData* foliageUserData, FVector atLocation );

	/** Set the mesh and it's translation */
	void SetPickupData( class UHierarchicalInstancedStaticMeshComponent* component, int32 instanceIndex, AFGCharacterPlayer* byCharacter );

	/** gets the pickup component, duhh */
	TWeakObjectPtr< class UHierarchicalInstancedStaticMeshComponent > GetPickupComponent() { return mPickupComponent; }

	/** gets the pickup component's instance, duhh */
	int32 GetPickupInstance() { return mInstanceIndex; }

protected:
	/** Sends to the server that something should be removed up at a specific location */
	UFUNCTION(Server, reliable, WithValidation)
	void Server_PickupWithTransform( class AFGCharacterPlayer* byCharacter, AFGFoliageRemoval* foliageRemoval, FTransform withTransform );

	/** Add the item to the player inventory */
	bool AddToPlayerInventory( class AFGCharacterPlayer* character, class UHierarchicalInstancedStaticMeshComponent* meshComponent );

	/** Returns true if the player has space for the items in the component */
	bool HasPlayerSpaceFor( class AFGCharacterPlayer* character, class UHierarchicalInstancedStaticMeshComponent* meshComponent );
protected:
	/** The mesh that should be outlining */
	UPROPERTY()
	class UStaticMesh* mPickupMesh;

	/** Index of instance we want to pickup */
	int32 mInstanceIndex;

	/** The component we want to pickup from */
	TWeakObjectPtr< class UHierarchicalInstancedStaticMeshComponent > mPickupComponent;

public:
	FORCEINLINE ~AFGFoliagePickup() = default;
};
