// Copyright 2016-2018 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "Array.h"
#include "UObject/Class.h"

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FGSaveInterface.h"
#include "FGTargetPoint.generated.h"

UCLASS()
class FACTORYGAME_API AFGTargetPoint : public AActor, public IFGSaveInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFGTargetPoint();

	/** Decide on what properties to replicate. */
	virtual void GetLifetimeReplicatedProps( TArray<FLifetimeProperty>& OutLifetimeProps ) const override;

	// Begin IFGSaveInterface
	virtual void PreSaveGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void PostSaveGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void PreLoadGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void PostLoadGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void GatherDependencies_Implementation( TArray< UObject* >& out_dependentObjects ) override;
	virtual bool NeedTransform_Implementation() override;
	virtual bool ShouldSave_Implementation() const override;
	// End IFSaveInterface

	/** Set which vehicle this belongs to */
	UFUNCTION( BlueprintCallable, Category = "Target Point" ) 
	void SetOwningVehicle( class AFGWheeledVehicle* newVehicle );

	/** Gets owning vehicle */
	UFUNCTION( BlueprintPure, Category = "Target Point" )
	class AFGWheeledVehicle* GetOwningVehicle();

	/** Sets visibility for this point */
	UFUNCTION( BlueprintCallable, Category = "TargetPoint" )
	void SetVisibility( bool inVisible );

	/** Returns current wait time */
	UFUNCTION( BlueprintPure, Category = "Target Point" ) 
	FORCEINLINE float GetWaitTime() { return mWaitTime; }

	/** Increase wait time
	 * @param addedWaitTime - if not specified we add the default wait time */
	UFUNCTION( BlueprintCallable, Category = "Target Point" ) 
	void IncreaseWaitTime( float addedWaitTime = -1.0f ); 

	/** Sets the wait time
	* @param newWaitTime - time to wait ( seconds ) */
	UFUNCTION( BlueprintCallable, Category = "Target Point" )
	void SetWaitTime( float newWaitTime );

	/** Getter for target speed */
	UFUNCTION( BlueprintPure, Category = "Target Point" )
	FORCEINLINE int32 GetTargetSpeed() { return mTargetSpeed; }

	/** Is target speed low enough to count as still */
	UFUNCTION( BlueprintPure, Category = "Target Point" ) 
	bool IsTargetSpeedStill();

	/** Sets new target speed */
	UFUNCTION( BlueprintCallable, Category = "Target Point" )
	void SetTargetSpeed( int32 newSpeed );
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/** Onrep for visibility */
	UFUNCTION()
	void OnRep_Visibility();
public:
	/** Reference to the next target point ( used in linked list ) */
	UPROPERTY( SaveGame )
	AFGTargetPoint* mNext;

	/** Vehicle that created this node */
	UPROPERTY( SaveGame, Replicated )
	class AFGWheeledVehicle* mOwningVehicle;

	/** Update visibility */
	UPROPERTY( SaveGame, ReplicatedUsing = OnRep_Visibility )
	bool mIsVisible;
private:
	/** Accumulated wait time for this node */ 
	UPROPERTY( SaveGame, Replicated )
	float mWaitTime; 

	/** Default wait time if this target point has no target speed */
	UPROPERTY( EditDefaultsOnly, Category = "Target Point" ) 
	float mDefaultWaitTime;
public:
	/** Target speed at this node */ 
	UPROPERTY( BlueprintReadOnly, SaveGame, Meta = ( ExposeOnSpawn = "true" ), Category = "Target Point" )
	int32 mTargetSpeed;
};
