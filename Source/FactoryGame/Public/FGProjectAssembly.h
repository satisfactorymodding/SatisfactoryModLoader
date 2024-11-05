// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "FGSaveInterface.h"
#include "GameFramework/Actor.h"
#include "Net/UnrealNetwork.h"
#include "FGProjectAssembly.generated.h"

class AFGBuildableSpaceElevator;
UCLASS()
class FACTORYGAME_API AFGProjectAssembly : public AActor, public IFGSaveInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFGProjectAssembly();

	// Save interface
	virtual bool ShouldSave_Implementation() const override		{ return true; }
	virtual bool NeedTransform_Implementation() override		{ return true; }

	virtual void GetLifetimeReplicatedProps( TArray<FLifetimeProperty>& OutLifetimeProps ) const override;

	UFUNCTION( BlueprintPure, Category = "Project Assembly" )
	FORCEINLINE bool IsPlayingLaunchSequence() const { return mIsPlayingLaunchSequence; }
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void EndPlay( const EEndPlayReason::Type EndPlayReason ) override;

	UFUNCTION(BlueprintNativeEvent)
	void OnGamePhaseChanged(UFGGamePhase* currentGamePhase);

	UFUNCTION(BlueprintNativeEvent)
	void BeginMoveToTarget();

	UFUNCTION(BlueprintNativeEvent)
	void OnTargetReached();

	UFUNCTION( BlueprintCallable )
	FORCEINLINE void SetIsPlayingLaunchSequence( bool isPlaying ) { mIsPlayingLaunchSequence = isPlaying; }
	
	virtual void Tick(float DeltaSeconds) override;
	
public:
	UFUNCTION(BlueprintNativeEvent)
	void UpdatePosition();

	void SetSpaceElevatorParent(AFGBuildableSpaceElevator* inSpaceElevator) { mSpaceElevator = inSpaceElevator; }

private:
	UFUNCTION()
	void OnRep_IsMovingToTarget();

protected:
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite)
	TObjectPtr<USkeletalMeshComponent> mMainSkeletalMeshComponent;

	UPROPERTY(SaveGame)
	TObjectPtr<AFGBuildableSpaceElevator> mSpaceElevator;
	
	UPROPERTY(EditDefaultsOnly, Category = "ProjectAssembly")
	float mMovementSpeed = 6000.0f;
	
	UPROPERTY(EditDefaultsOnly, Category = "ProjectAssembly")
	float mProjectAssemblyHeight = 2350000.0;
	
	/* from start(0) to end.*/
	UPROPERTY(EditDefaultsOnly, Category = "ProjectAssembly")
	TMap<TSubclassOf<UFGGamePhase>,int32> mGamePhaseMap;

	UPROPERTY( ReplicatedUsing = OnRep_IsMovingToTarget )
	bool mIsMovingToTarget;

	UPROPERTY( Replicated )
	FVector mTargetLocation;

private:	
	bool mIsPlayingLaunchSequence;
};
