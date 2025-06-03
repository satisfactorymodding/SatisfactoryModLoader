// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "FGUseableInterface.h"
#include "Buildables/FGBuildableElevator.h"
#include "GameFramework/Actor.h"

#include "FGElevatorCabin.generated.h"

class UFGElevatorMovementComponent;
class AFGBuildableElevator;
class UBoxComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FOnSongIdChanged, int32, newSongId );

UENUM( BlueprintType )
enum class EElevatorConsoleLocation : uint8
{
	ECL_None,
	ECL_QuickStopButtons,
	ECL_ButtonArray,
	ECL_WidgetEntry
};

UCLASS()
class FACTORYGAME_API UFGUseState_ElevatorMustSelectButton : public UFGUseState
{
	GENERATED_BODY()

	UFGUseState_ElevatorMustSelectButton() : Super() { mIsUsableState = false; }
};

UCLASS()
class FACTORYGAME_API UFGUseState_ElevatorConsoleInteract : public UFGUseState
{
	GENERATED_BODY()
public:
	UFGUseState_ElevatorConsoleInteract() : Super() { mIsUsableState = true; mWantAdditonalData = true; mInteractingPlayer = nullptr; }
	
	EElevatorConsoleLocation mConsoleUseType = EElevatorConsoleLocation::ECL_None;
	FVector mOffsetUseLocation = FVector::ZeroVector;
	int32 mFloorStopIndex = INDEX_NONE;
	float mUpdateTime = 0.f;
	
	UPROPERTY()
	APlayerController* mInteractingPlayer;
};


UCLASS( Abstract )
class FACTORYGAME_API AFGElevatorCabin : public AActor, public IFGSaveInterface, public IFGUseableInterface, public IFGSignificanceInterface
{
	GENERATED_BODY()

public:
	AFGElevatorCabin();
	
	// Begin AActor Interface
	virtual void BeginPlay() override;
	virtual void EndPlay( EEndPlayReason::Type reason ) override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	virtual bool CanBeBaseForCharacter(APawn* Pawn) const override;
	// End AActor Interface

	// Begin Useable Interface
	virtual bool IsUseable_Implementation() const override;
	virtual void UpdateUseState_Implementation(AFGCharacterPlayer* byCharacter, const FVector& atLocation, UPrimitiveComponent* componentHit, FUseState& out_useState) override;
	virtual void OnUse_Implementation(AFGCharacterPlayer* byCharacter, const FUseState& state) override;
	virtual void StartIsLookedAt_Implementation(AFGCharacterPlayer* byCharacter, const FUseState& state) override;
	virtual void StopIsLookedAt_Implementation(AFGCharacterPlayer* byCharacter, const FUseState& state) override;
	virtual FText GetLookAtDecription_Implementation(AFGCharacterPlayer* byCharacter, const FUseState& state) const override;
	// End Useable Interface

	// Begin IFGSignificanceInterface
	virtual void GainedSignificance_Implementation() override;
	virtual void LostSignificance_Implementation() override;
	virtual float GetSignificanceRange() override;
	// End IFGSignificanceInterface

	virtual bool ShouldSave_Implementation() const override { return true; }
	
	TArray< APawn* > GetOccupyingPawns() { return mOwningElevator ? mOwningElevator->GetOccupyingPawns() : TArray<APawn*>() ; }

	UFUNCTION( BlueprintCallable, Category="ElevatorCabin" )
	void OnPawnEnterCabin( APawn* pawn, const FVector& lastLocation );
	
	UFUNCTION( BlueprintCallable, Category="ElevatorCabin" )
	void OnPawnExitCabin( APawn* pawn );
	
	// Called by the owning Elevator to update the cabins state (this is driven by the elevator rather than the cabin to keep all behaviour logic centered in the BuildableElevator itself)
	void NotifyElevatorStateChanged( EElevatorState newState );
	
	UFUNCTION( BlueprintImplementableEvent )
	void OnElevatorStateChanged( EElevatorState newState );
	
	UFUNCTION( BlueprintImplementableEvent, BlueprintCosmetic )
	void OnPlayerUseFloorStopButton( bool isSelected );
	
	UFUNCTION( BlueprintCallable, Category="Elevator Cabin" )
	void SetTargetFloorStop( const FElevatorFloorStopInfo& stopInfo, bool teleport = false );

	UFUNCTION()
	void AddForceControlPoint( const FVector& worldLocation );
	
	UFUNCTION()
	void ClearControlPoints();
	
	// Functions for converting use location to a button press
	EElevatorConsoleLocation GetConsoleTypeUseLocation( const FVector& useLocation );
	int32 GetFloorStopIndexForUseLocation( const FVector& useLocation, const FUseState& state );
	
	UFUNCTION(BlueprintCallable, Category="Elevator Cabin" )
	void TeleportToFloorStop( const FElevatorFloorStopInfo& floorStop );


	UFUNCTION(Blueprintable, Category="Elevator Cabin")
	void SetOwningElevator( AFGBuildableElevator* elevator, float height);

	UFUNCTION(BlueprintPure, Category="Elevator Cabin")
	class AFGBuildableElevator* GetOwningElevator( ) const { return mOwningElevator; };

	UFUNCTION( BlueprintPure, Category="Elevator Cabin" )
	FORCEINLINE float GetCurrentHeightOfCabin() const { return GetActorLocation().Z - mOwningElevator->GetActorLocation().Z; };

	UFUNCTION( BlueprintPure, Category="Elevator Cabin" )
	FORCEINLINE FElevatorFloorStopInfo GetCurrentFloorStopInfo() const { return mCurrentFloorStopInfo.IsValid( HasAuthority() ) ? mCurrentFloorStopInfo : FElevatorFloorStopInfo::EmptyFloor; };

	UFUNCTION( BlueprintPure, Category="Elevator Cabin" )
	float GetTimeToDestination() const;

	/** Get the widget used for naming / quick search input **/
	UFUNCTION( BlueprintPure, Category = "Elevator Cabin|Interaction" )
	FORCEINLINE class TSubclassOf< class UFGInteractWidget > GetInteractWidgetClass() const { return mInteractWidgetClass; }
	
	UFUNCTION()
	void OnMovementStopped();
	
	UFUNCTION()
	void OnRep_CurrentFloorStopInfo( FElevatorFloorStopInfo& lastFloorStopInfo );
	
	void UpdateFloorStops();
	
	void UpdateCabinVisibility();

	void SetQueuedFloors(  const TArray< int32 >& queuedFloorIndexes );
	void UpdateQueuedFloorVisuals();
	UFUNCTION( BlueprintImplementableEvent, Category="Elevator Cabin" )
	void OnQueuedFloorsUpdated();

	UFUNCTION( BlueprintPure, Category="Elevator Cabin" )
	TArray< int32 > GetQueuedFloors() { return mCachedQueuedFloorStops; }
	
	UFUNCTION(BlueprintCallable, Category="Elevator Cabin" )
	void SetCabinHidden( bool newHidden );

	UFUNCTION()
	void OnRep_OwningElevator();
	
	UFUNCTION()
	void RebuildButtonMeshComponents( bool iconsOnly = false );

	UFUNCTION()
	void RemoveButtonMeshComponents();

	UFUNCTION()
	void ClientWaitForIconSubsystem();

	// Called by the owning elevator to notify of power status changes
	UFUNCTION()
	void NotifyPowerStatusChanged( bool hasPower );
	
	UFUNCTION(BlueprintImplementableEvent, Category="FactoryGame|Buildable|ElevatorFloorStop" )
	void OnPowerStatusChanged( bool hasPower );

	UFUNCTION(BlueprintNativeEvent, Category="FactoryGame|Buildable|ElevatorFloorStop" )
	UBoxComponent* GetOccupyingBoxCollisionComp() const;
	
	FTransform GetConsoleToWorldForConsoleSection( EElevatorConsoleLocation consoleType ) const
	{
		switch(consoleType) {
			case EElevatorConsoleLocation::ECL_None:
				break;
			case EElevatorConsoleLocation::ECL_QuickStopButtons:
				return FTransform::Identity; // Unused
			case EElevatorConsoleLocation::ECL_ButtonArray:
				return mFloorStopButtonsTransform * mConsoleMeshComponent->GetRelativeTransform() * GetActorTransform();
			case EElevatorConsoleLocation::ECL_WidgetEntry:
				return mWidgetInteractTransform * mConsoleMeshComponent->GetRelativeTransform() * GetActorTransform();
		}

		return FTransform::Identity;
	}

	// Gets the currently set songID from the owning elevator. If no elevator is present MAX_uint8.
	UFUNCTION( BlueprintPure, Category="Elevator Cabin" )
	uint8 GetSongID() const
	{
		if( mOwningElevator )
		{
			return mOwningElevator->GetSongID();
		}

		return MAX_uint8;
	}

	// Sets the current song ID. This should only be called on authority.
	UFUNCTION( BlueprintCallable, Category="Elevator Cabin" )
	void SetSongID( uint8 songId )
	{
		ensure( HasAuthority() );
		if( mOwningElevator)
		{
			mOwningElevator->SetSongID( songId );
		}
	}

	// Called from owning elevator to notify of change to song ID (which in turn triggers a blueprint event)
	void NotifySongIdChanged( uint8 newSongId ) { SongIDChangedBroadcast.Broadcast( newSongId ); OnSongIDChanged( newSongId ); }
	
	UFUNCTION(BlueprintImplementableEvent, Category="Elevator Cabin" )
	void OnSongIDChanged( uint8 newSongId );
	
	void ApplyCustomizatinDataFromElevator();
	
	UStaticMeshComponent* GetMeshComponent() const { return mMeshComponent; }

public:
	UPROPERTY( BlueprintReadWrite, BlueprintAssignable, Category = "Elevator Cabin" )
	FOnSongIdChanged SongIDChangedBroadcast;
	
protected:
#if WITH_EDITOR
	virtual void PostCDOCompiled(const FPostCDOCompiledContext& Context) override;
#endif
	
protected:
	UPROPERTY( EditDefaultsOnly, Category="Elevator Cabin")
	TSubclassOf< class UFGInteractWidget > mInteractWidgetClass;
	
	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category="Elevator Cabin" )
	TObjectPtr< UFGElevatorMovementComponent > mMovementComponent;

	UPROPERTY( EditAnywhere,BlueprintReadOnly, Category="Elevator Cabin" )
	TObjectPtr< UBoxComponent > mCollisionComponent;

#if WITH_EDITORONLY_DATA
	UPROPERTY( EditAnywhere, Category="Elevator Cabin" )
	TObjectPtr< UBoxComponent > mFloorButtonContainer;

	UPROPERTY( EditAnywhere, Category="Elevator Cabin" )
	TObjectPtr< UBoxComponent > mQuickStopButtonContainer;
	
	UPROPERTY( EditAnywhere, Category="Elevator Cabin" )
	TObjectPtr< UBoxComponent > mWidgetInteractContainer;
#endif

	UPROPERTY( VisibleAnywhere, Category="Elevator Cabin")
	TArray< UStaticMeshComponent* > mButtonMeshComponents;

	UPROPERTY( BlueprintReadWrite, VisibleAnywhere, Category="Elevator Cabin" )
	TObjectPtr< USceneComponent > mButtonArraySceneParent;

	UPROPERTY( EditDefaultsOnly, Category="Elevator Cabin")
	TObjectPtr<UStaticMesh> mButtonMesh;
	
	UPROPERTY( EditDefaultsOnly, Category="Elevator Cabin")
	TSoftObjectPtr< UMaterial > mButtonBackgroundMaterialBase;

	UPROPERTY( EditDefaultsOnly, Category="Elevator Cabin")
	TSoftObjectPtr< UMaterial > mButtonIconMaterialBase;
	
	UPROPERTY()
	TArray< FTransform > mButtonMeshLocalTransforms;
	
	UPROPERTY()
	TArray< FTransform > mButtonMeshWorldTransforms;
	
	UPROPERTY( EditAnywhere, Category="Elevator Cabin" )
	TObjectPtr< UStaticMeshComponent > mMeshComponent;

	UPROPERTY( EditAnywhere, Category="Elevator Cabin" )
	TObjectPtr< UStaticMeshComponent > mConsoleMeshComponent;

	UPROPERTY( EditDefaultsOnly, Category="Elevator Cabin" )
	float mButtonRadius = 5.f;

	UPROPERTY( VisibleDefaultsOnly, Category="Elevator Cabin" )
	FTransform mFloorStopButtonsTransform;
	UPROPERTY( VisibleDefaultsOnly, Category="Elevator Cabin" )
	FVector mFloorStopButtonsExtents;
	UPROPERTY( VisibleDefaultsOnly, Category="Elevator Cabin" )
	FTransform mWidgetInteractTransform;
	UPROPERTY( VisibleDefaultsOnly, Category="Elevator Cabin" )
	FVector mWidgetInteractExtents;

private:

	UPROPERTY()
	EElevatorState mCachedElevatorState;
	
	// Copy of the floor stops from the elevator. Used for building the button array (resolving floors on use)
	UPROPERTY()
	TArray< FElevatorFloorStopInfo > mFloorStops;
	
	UPROPERTY( ReplicatedUsing=OnRep_OwningElevator )
	TObjectPtr< AFGBuildableElevator > mOwningElevator;

	UPROPERTY( ReplicatedUsing=OnRep_CurrentFloorStopInfo )
	FElevatorFloorStopInfo mCurrentFloorStopInfo;

	UPROPERTY( )
	TArray< int32 > mCachedQueuedFloorStops;
	
	// Tracks if this cabin is significant
	bool mIsSignificant;
	// Tracks if we're displaying an outline for the local player
	bool mIsOutlined;
	bool mLastUseStateHasPower;
	
};
