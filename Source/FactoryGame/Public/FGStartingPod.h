// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FGDismantleInterface.h"
#include "FGActorRepresentationInterface.h"
#include "FGStartingPod.generated.h"

UCLASS()
class FACTORYGAME_API AFGStartingPod : public AActor, public IFGDismantleInterface, public IFGActorRepresentationInterface
{
	GENERATED_BODY()
	
public:	
	AFGStartingPod();

	/** Decide on what properties to replicate */
	virtual void GetLifetimeReplicatedProps( TArray<FLifetimeProperty>& OutLifetimeProps ) const override;

	//~ Begin IFGDismantleInterface
	virtual FVector GetRefundSpawnLocationAndArea_Implementation( const FVector& aimHitLocation, float& out_radius ) const override;
	virtual bool CanDismantle_Implementation() const override;
	virtual void GetDismantleRefund_Implementation( TArray< FInventoryStack >& out_refund ) const override;
	virtual void PreUpgrade_Implementation() override;
	virtual void Upgrade_Implementation( AActor* newActor ) override;
	virtual void Dismantle_Implementation() override;
	virtual void StartIsLookedAtForDismantle_Implementation(class AFGCharacterPlayer* byCharacter ) override;
	virtual void StopIsLookedAtForDismantle_Implementation( class AFGCharacterPlayer* byCharacter ) override;
	virtual void GetChildDismantleActors_Implementation( TArray< AActor* >& out_ChildDismantleActors ) const override;
	//~ End IFGDismantleInferface

	// Begin IFGActorRepresentationInterface
	virtual bool AddAsRepresentation() override;
	virtual bool UpdateRepresentation() override;
	virtual bool RemoveAsRepresentation() override;
	virtual bool IsActorStatic() override;
	virtual FVector GetRealActorLocation() override;
	virtual FRotator GetRealActorRotation() override;
	virtual class UTexture2D* GetActorRepresentationTexture() override;
	virtual FText GetActorRepresentationText() override;
	virtual void SetActorRepresentationText( const FText& newText ) override;
	virtual FLinearColor GetActorRepresentationColor() override;
	virtual void SetActorRepresentationColor( FLinearColor newColor ) override;
	virtual ERepresentationType GetActorRepresentationType() override;
	virtual bool GetActorShouldShowInCompass() override;
	virtual bool GetActorShouldShowOnMap() override;
	virtual EFogOfWarRevealType GetActorFogOfWarRevealType() override;
	virtual float GetActorFogOfWarRevealRadius() override;
	virtual ECompassViewDistance GetActorCompassViewDistance() override;
	virtual void SetActorCompassViewDistance( ECompassViewDistance compassViewDistance ) override;
	// End IFGActorRepresentationInterface

	/** Getter for player */
	UFUNCTION( BlueprintPure, Category = "Starting Pod" )
	FORCEINLINE AFGCharacterPlayer* GetCachedPlayer() { return mCachedPlayer; }

	/** Start the pod animation */
	UFUNCTION( BlueprintCallable, BlueprintImplementableEvent, Category = "Starting Pod" )
	void StartSequence();

	UFUNCTION( BlueprintCallable, BlueprintImplementableEvent, Category = "Starting Pod" )
	void OnPlayerSkipIntroSequence();

	/** Fetches the color to use for this actors representation */
	UFUNCTION( BlueprintImplementableEvent, Category = "Representation" )
	FLinearColor GetDefaultRepresentationColor();

protected:
	virtual void BeginPlay() override;
public:
	/** Player associated with this pod */
	UPROPERTY( Replicated )
	class AFGCharacterPlayer* mCachedPlayer;
protected:
	/** Array containing how much to get back when dismantling this bad boy */
	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = "Dismantle")
	TArray< FInventoryStack > mDismantleStacks;

	/** Main mesh */
	UPROPERTY( VisibleAnywhere, BlueprintReadOnly, Category = "Starting Pod" )
	class USkeletalMeshComponent* mDropPodMesh;

	/** Flag for whether the actor is being dismantled */
	int32 mIsDismantled : 1;

private:
	UPROPERTY( EditDefaultsOnly, Category = "Representation" )
	class UTexture2D* mActorRepresentationTexture;

	UPROPERTY( Replicated )
	FText mMapText;

};
