// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "FGActorRepresentationInterface.h"
#include "FGBuildableFactory.h"
#include "ItemAmount.h"
#include "FGBuildableSpaceElevator.generated.h"

UENUM( BlueprintType )
enum ESpaceElevatorState
{
	ESES_Load		= 0 UMETA( DisplayName = "Load" ),
	ESES_Seal		= 1 UMETA( DisplayName = "Seal" ),
	ESES_Send		= 2 UMETA( DisplayName = "Send" )
};

UCLASS()
class FACTORYGAME_API UFGBuildableSpaceElevatorRemoteCallObject : public UFGRemoteCallObject
{
	GENERATED_BODY()
public:
	virtual void GetLifetimeReplicatedProps( TArray< FLifetimeProperty >& OutLifetimeProps ) const override;

	UPROPERTY( Replicated, Meta = ( NoAutoJson ) )
	bool mForceNetField_UFGBuildableSpaceElevatorRemoteCallObject = false;

	static UFGBuildableSpaceElevatorRemoteCallObject* Get( UWorld* world );
	
	UFUNCTION( Server, Reliable )
	void Server_SetSpaceElevatorState( class AFGBuildableSpaceElevator* elevator, ESpaceElevatorState spaceElevatorState, APlayerController* instigatingPlayer );

	UFUNCTION( Server, Reliable )
	void Server_StartSpaceElevatorUpgradeTimer( class AFGBuildableSpaceElevator* elevator, float time );

	UFUNCTION( NetMulticast, Reliable )
	void NetMulticast_StartSpaceElevatorUpgradeTimer( class AFGBuildableSpaceElevator* elevator, float time );

	UFUNCTION( Server, Reliable )
	void Server_StoreProjectAssemblyLaunchSequenceValues( const TArray< FProjectAssemblyLaunchSequenceValue >& PAValues );
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FOnSpaceElevatorStateUpdated, ESpaceElevatorState, spaceElevatorState );

/**
 * 
 */
UCLASS()
class FACTORYGAME_API AFGBuildableSpaceElevator : public AFGBuildableFactory, public IFGActorRepresentationInterface
{
	GENERATED_BODY()

public:	
	AFGBuildableSpaceElevator();
	
	// Begin IFGActorRepresentationInterface
	UFUNCTION()
	virtual bool AddAsRepresentation() override;
	UFUNCTION()
	virtual bool UpdateRepresentation() override;
	UFUNCTION()
	virtual bool RemoveAsRepresentation() override;
	UFUNCTION()
	virtual bool IsActorStatic() override;
	UFUNCTION()
	virtual FVector GetRealActorLocation() override;
	UFUNCTION()
	virtual FRotator GetRealActorRotation() override;
	UFUNCTION()
	virtual class UTexture2D* GetActorRepresentationTexture() override;
	UFUNCTION()
	virtual FText GetActorRepresentationText() override;
	UFUNCTION()
	virtual void SetActorRepresentationText( const FText& newText ) override;
	UFUNCTION()
	virtual FLinearColor GetActorRepresentationColor() override;
	UFUNCTION()
	virtual void SetActorRepresentationColor( FLinearColor newColor ) override;
	UFUNCTION()
	virtual ERepresentationType GetActorRepresentationType() override;
	UFUNCTION()
	virtual bool GetActorShouldShowInCompass() override;
	UFUNCTION()
	virtual bool GetActorShouldShowOnMap() override;
	UFUNCTION()
	virtual EFogOfWarRevealType GetActorFogOfWarRevealType() override;
	UFUNCTION()
	virtual float GetActorFogOfWarRevealRadius() override;
	UFUNCTION()
	virtual ECompassViewDistance GetActorCompassViewDistance() override;
	UFUNCTION()
	virtual void SetActorCompassViewDistance( ECompassViewDistance compassViewDistance ) override;
	UFUNCTION()
	virtual UMaterialInterface* GetActorRepresentationCompassMaterial() override;

	// End IFGActorRepresentationInterface
	
	// Begin AActor interface
	virtual void BeginPlay() override;
	virtual void GetLifetimeReplicatedProps( TArray<FLifetimeProperty>& OutLifetimeProps ) const override;
	// End AActor interface

	//~ Begin IFGDismantleInterface
	virtual void Dismantle_Implementation() override;
	//~ End IFGDismantleInferface

	//~ Begin AFGBuildable interface
	virtual bool CanBeSampled_Implementation() const override { return false; }
	//~ End AFGBuildable interface

	// Begin AFGBuildableFactory interface
	virtual void Factory_CollectInput_Implementation() override;
	virtual void Factory_Tick( float dt ) override;
	// End AFGBuildableFactory interface

	//@returns true when we are fully upgraded.
	UFUNCTION( BlueprintPure, Category = "Space Elevator" )
	bool IsFullyUpgraded();

	/** Returns the cost for the next upgrade */
	UFUNCTION( BlueprintCallable, Category = "Space Elevator" )
	void GetNextPhaseCost( TArray< FItemAmount >& out_cost );

	/** Player has dropped items onto the pay off widget from their inventory*/
	UFUNCTION( BlueprintCallable, Category = "Space Elevator" )
	void PayOffFromInventory( UFGInventoryComponent* inventory, int32 inventorySlotIndex );

	/* *@returns True if we have eaten up all the items needed to upgrade. Returns false if not, but also if there is no current recipe available. */
	UFUNCTION( BlueprintPure, Category = "Space Elevator" )
	bool IsReadyToUpgrade() const;

	/** Get the input inventory from this building.	*/
	UFUNCTION( BlueprintPure, Category = "Space Elevator" )
	FORCEINLINE class UFGInventoryComponent* GetInputInventory() { return mInputInventory; }

	/** Called when the player presses to send more stuff to the tow truck */
	UFUNCTION( BlueprintNativeEvent, BlueprintCallable, Category = "Space Elevator" )
	void UpgradeTowTruck();

	/** Fetches the color to use for this actors representation */
	UFUNCTION( BlueprintImplementableEvent, Category = "Representation" )
	FLinearColor GetDefaultRepresentationColor();

	UFUNCTION( BlueprintPure, Category = "Space Elevator" )
	ESpaceElevatorState GetSpaceElevatorState() { return mSpaceElevatorState; }

	UFUNCTION( BlueprintCallable, Category = "Space Elevator" )
	void SetSpaceElevatorState( ESpaceElevatorState spaceElevatorState, APlayerController* instigatingPlayer );

	UFUNCTION( BlueprintCallable, Category = "Space Elevator" )
	void StoreProjectAssemblyLaunchSequenceValues( const TArray< FProjectAssemblyLaunchSequenceValue >& PAValues );

	/** Starts an timer that will trigger the space elevator upgrade and set the mSpaceElevatorState to ESES_Load when expired.
	 * Can be called on both server and client
	 */
	UFUNCTION( BlueprintCallable, Category = "Space Elevator" )
	void StartSpaceElevatorUpgradeTimer( float time );
	/** Actually starts the timer for StartSpaceElevatorUpgradeTimer */
	void Internal_StartSpaceElevatorUpgradeTimer( float time );
	void SpaceElevatorUpgradeTimerExpired();
	/** Returns the time elapsed on the space elevator upgrade timer. Returns 0 if no timer is active */
	UFUNCTION( BlueprintPure, Category = "Space Elevator" )
	float GetSpaceElevatorUpgradeTimer();

	UPROPERTY( BlueprintAssignable )
	FOnSpaceElevatorStateUpdated mOnSpaceElevatorStateUpdated;

	UPROPERTY(EditDefaultsOnly)
	UMaterialInterface* mCompassMaterialInstance;
protected:

	/** Returns the game phase manager, finds it if it isn't cached */
	class AFGGamePhaseManager* GetGamePhaseManager();

	UFUNCTION()
	void OnRep_SpaceElevatorState( ESpaceElevatorState previousSpaceElevatorState );

private:
	/*
	* Checks and consumes any ingredient in the input inventory if the upgrade recipe requires it.
	*/
	void ConsumeInputIngredientsIfNecessary();
	
protected:
	/** Our input inventory, shared for all input connections. */
	UPROPERTY( SaveGame )
	class UFGInventoryComponent* mInputInventory;

	/** Our input inventory, shared for all input connections. */
	UPROPERTY( SaveGame, ReplicatedUsing=OnRep_SpaceElevatorState )
	TEnumAsByte<ESpaceElevatorState> mSpaceElevatorState;

	FTimerHandle mSpaceElevatorTimerHandle;

	/** A cached version of the game phase manager */
	UPROPERTY()
	AFGGamePhaseManager* mGamePhaseManager;

	/** Cached input connections (No need for UPROPERTY as they are referenced in component array) */
	TArray< class UFGFactoryConnectionComponent* > mInputConnections;


private:
	UPROPERTY( EditDefaultsOnly, Category = "Representation" )
	class UTexture2D* mActorRepresentationTexture;

	UPROPERTY( EditDefaultsOnly, Category = "ProjectAssembly" )
	TSubclassOf<AFGProjectAssembly> mProjectAssemblyClass;
};
