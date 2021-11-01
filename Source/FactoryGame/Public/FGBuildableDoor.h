// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"

#include "FGSignificanceInterface.h"
#include "Buildables/FGBuildableWall.h"
#include "Kismet/KismetMathLibrary.h"

#include "FGBuildableDoor.generated.h"


UENUM(BlueprintType)
enum class EDoorConfiguration : uint8
{
	DC_Auto,
	DC_Closed,
	DC_Open
};

// Replication state.
UENUM(BlueprintType)
enum class EDoorState : uint8
{
	DS_Closed,
	DS_Closing,
	DS_Open,
	DS_Opening
};

/**
 * 
 */
class UFGColoredInstanceMeshProxy;

UCLASS()
class FACTORYGAME_API AFGBuildableDoor : public AFGBuildableWall, public IFGSignificanceInterface
{
	GENERATED_BODY()

	AFGBuildableDoor();

public:
	// Begin AActor interface
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	
	virtual void GetLifetimeReplicatedProps( TArray<FLifetimeProperty>& OutLifetimeProps ) const override;
	// End AActor interface
	
	// Begin AFGBuildable interface
	virtual void ConfigureDynamicDecoratorComponent( USceneComponent* newComponent ) override;
	// End AFGBuildable interface

	// Begin interaction interface
	virtual bool IsUseable_Implementation() const override;
	virtual void OnUse_Implementation(AFGCharacterPlayer* byCharacter, const FUseState& state) override;
	// End interaction interface
	
	/* Returns instanced door component */
	UFUNCTION( BlueprintPure, Category = "Doors")
	FORCEINLINE UFGColoredInstanceMeshProxy* GetDoorComponent() const
	{
		return mMeshComponentProxy;
	}

protected:
	// Begin IFGSignificanceInterface
	virtual void GainedSignificance_Implementation() override;
	virtual	void LostSignificance_Implementation() override;	
	virtual float GetSignificanceRange() override { return 5000.f; }
	// End IFGSignificanceInterface
	
	UFUNCTION(BlueprintCallable)
	void OnOverlapBegin( UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult );

	UFUNCTION(BlueprintCallable)
	void OnEndOverlap( UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex );

	UFUNCTION()
	void OnRep_DoorState();

	UFUNCTION()
	void OnRep_DoorConfiguration();

	UFUNCTION( BlueprintImplementableEvent, BlueprintCosmetic, Category = "Doors" )
	void OnFinishedOpening();

	UFUNCTION( BlueprintImplementableEvent,BlueprintCosmetic, Category = "Doors" )
	void OnBeginOpening();
	
	UFUNCTION( BlueprintImplementableEvent,BlueprintCosmetic, Category = "Doors" )
	void OnFinishedClosing();

	UFUNCTION( BlueprintImplementableEvent,BlueprintCosmetic, Category = "Doors" )
	void OnBeginClosing();
	
	UFUNCTION( BlueprintImplementableEvent, Category = "Doors" )
	void OnMovementStateChanged( EDoorState oldState, EDoorState newState, float percentage );

	UFUNCTION( BlueprintImplementableEvent, Category = "Doors" )
	void OnDoorConfigurationChanged( EDoorConfiguration newState );

	void SetDoorLightFeedbackState(EDoorConfiguration Config);

	UFUNCTION(BlueprintPure, Category = "Doors")
	EDoorConfiguration GetCurrentDoorConfiguration() const { return mDoorConfiguration; }

	UFUNCTION(BlueprintPure, Category = "Doors")
	bool CanBeLocked() const { return mCanBeLocked; }

	UFUNCTION(BlueprintNativeEvent)
	bool CanClose();
	
private:
	UFUNCTION()
	void Update();
	
	void BeginOpening();
	void BeginClosing();
	void FinishedMoving( bool shouldBlock );

private:
	UPROPERTY( VisibleAnywhere, SaveGame, ReplicatedUsing = OnRep_DoorState, meta = ( NoAutoJson = true ) )
	EDoorState mDoorState;

	UPROPERTY( VisibleAnywhere, SaveGame, ReplicatedUsing = OnRep_DoorConfiguration, meta = ( NoAutoJson = true ) )
	EDoorConfiguration mDoorConfiguration;
	
	/* List of controllers that are active. */
	UPROPERTY( Transient )
	TArray<APawn*> mActiveOverlaps;

	bool mIsOpening;

	float mAnimationPercentage;

	FTimerHandle mTimerHandle;

	UPROPERTY( EditDefaultsOnly, Category = "Doors")
	bool mCanBeLocked;

	/*animation interval update. 1/60 means 60 fps */
	UPROPERTY( EditDefaultsOnly, Category = "VTX Animation")
	float mAnimationRate;

	UPROPERTY( EditDefaultsOnly, Category = "VTX Animation")
	float mMovementRate;

	// Animation
	UPROPERTY( EditDefaultsOnly, Category = "VTX Animation")
	TEnumAsByte<EEasingFunc::Type> EasingFunction;

	UPROPERTY( EditDefaultsOnly, Category = "VTX Animation")
	float BlendExp = 2;

	UPROPERTY( EditDefaultsOnly, Category = "VTX Animation")
	int32 Steps = 2;
};
