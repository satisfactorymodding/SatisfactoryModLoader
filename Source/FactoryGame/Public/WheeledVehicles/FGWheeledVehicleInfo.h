// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FGActorRepresentationInterface.h"
#include "Animation/SkeletalMeshActor.h"
#include "FGWheeledVehicle.h"
#include "FGWheeledVehicleInfo.generated.h"

UENUM( BlueprintType )
enum class EVehicleStatus : uint8
{
	VS_Operational,
	VS_OutOfFuel,
	VS_Deadlocked
};

/**
 * Containing wheeled-vehicle data that needs to be on client always.
 * Also represents the vehicle visuals in simulated (non-physical) mode.
 */
UCLASS()
class FACTORYGAME_API AFGWheeledVehicleInfo : public ASkeletalMeshActor, public IFGSaveInterface, public IFGActorRepresentationInterface
{
	GENERATED_BODY()
public:
	AFGWheeledVehicleInfo();

	virtual void GetLifetimeReplicatedProps( TArray<FLifetimeProperty>& OutLifetimeProps ) const override;

	// Begin IFGSaveInterface
	virtual void PreSaveGame_Implementation( int32 saveVersion, int32 gameVersion ) override {}
	virtual void PostSaveGame_Implementation( int32 saveVersion, int32 gameVersion ) override {}
	virtual void PreLoadGame_Implementation( int32 saveVersion, int32 gameVersion ) override {}
	virtual void PostLoadGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void GatherDependencies_Implementation( TArray< UObject* >& out_dependentObjects ) override {}
	virtual bool NeedTransform_Implementation() override { return false; }
	virtual bool ShouldSave_Implementation() const override { return true; }
	// End IFSaveInterface

	// Begin IFGActorRepresentationInterface
	UFUNCTION()
	virtual bool AddAsRepresentation() override;
	UFUNCTION()
	virtual bool UpdateRepresentation() override;
	bool UpdateRepresentation_Local();
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
	virtual void EndPlay( const EEndPlayReason::Type EndPlayReason ) override;
	virtual void Tick( float dt ) override;
	// End AActor interface

	/**
	 * Makes this vehicle info ready for use. Called from the vehicle and only on server.
	 */
	void Init( AFGWheeledVehicle* vehicle );

	/**
	 * Initializes a few members that govern vehicle collision detection.
	 */
	void InitCollisionData();

	// Accessors and change delegates

	AFGWheeledVehicle* GetVehicle() const;
	AFGWheeledVehicle* GetVehicleOnClient_MayReturnNull() const;

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FStatusChanged, EVehicleStatus, status );
	UPROPERTY( BlueprintAssignable, Category = "Vehicle", DisplayName = "OnVehicleStatusChanged" )
	FStatusChanged VehicleStatusChangedDelegate;

	UPROPERTY()
	UMaterialInterface* mCompassMaterialInstance;

	/**
	 * Set deadlocked/out-of-fuel status
	 */
	void SetVehicleStatus( EVehicleStatus status );

	/**
	 * Get deadlocked/out-of-fuel status
	 */
	UFUNCTION( BlueprintPure, Category = "Vehicle" )
	EVehicleStatus GetVehicleStatus() const { return mStatus; }

	void SetIsFollowingPath( bool isFollowingPath );

	bool IsFollowingPath() const { return mIsFollowingPath; }
	
	UFUNCTION( BlueprintImplementableEvent, Category = "Vehicle|SelfDriving" )
	void IsFollowingPathChanged( bool isFollowingPath );

	void SetIsPossessed( bool isPossessed );

	bool IsPossessed() const { return mIsPossessed; }

	bool IsAtStation() const { return mCurrentStation != nullptr; }

	class UFGSplinePathMovementComponent* GetSimulationMovement() const { return mSimulationMovement; }

	void SetTarget( class AFGTargetPoint* target );

	class AFGTargetPoint* GetTarget() const { return mTarget; }

	class AFGBuildableDockingStation* GetCurrentStation() const { return mCurrentStation; }
	
	void SetCurrentStation( class AFGBuildableDockingStation* station ) { mCurrentStation = station; }

	void SetIsSimulated( bool isSimulated );

	bool IsSimulated() const { return mIsSimulated; }

	bool IsGhosting() const { return mIsGhosting; }

	void SetIsGhosting( bool isGhosting ) { mIsGhosting = isGhosting; }
	
	FVector GetBoundingBoxExtent() const { return mBoundingBoxExtent; }

	FVector GetBoundingBoxOffset() const { return mBoundingBoxOffset; }

	float GetWheelRadius() const { return mWheelRadius; }

	TArray<class UStaticMeshComponent*> GetStaticMeshComponents() const { return mStaticMeshComponents; }

	// End Accessors and change delegates

	FVector GetVehicleLocation() const;

	FRotator GetVehicleRotation() const;

	void UpdateTarget();

	/**
	 * Is this vehicle supposed to stay at the dock or it is finished?
	 */
	bool ShouldStayAtDock();

	void OnTargetDestroyed( class AFGTargetPoint* target );

	class AFGDrivingTargetList* GetTargetList() const;

	/**
	 * Try to start movement on the spline path
	 */
	void TryStartSplinePathMovement();

	TSubclassOf< class UFGItemDescriptor > GetCurrentFuelClass() const { return mCurrentFuelClass; }

	void SetSimulationVisible( bool isVisible );

	void UpdateCustomizationData( class AFGWheeledVehicle* vehicle );

	void ApplyMeshPrimitiveData( const FFactoryCustomizationData& customizationData );

	/**
	 * Show the cosmetic effect that indicates that the vehicle is temporarily in simulated mode despite being within physical range.
	 */
	void ShowGhostingEffect( bool enabled );

	/**
	 * Is the vehicle on its normal route or is it transitioning there?
	 */
	bool IsOnCanonPath() const;

#if DEBUG_SELF_DRIVING
	void DrawDebug( int debugLevel );
#endif

private:
	virtual void OnRep_ReplicatedMesh() override;

	UFUNCTION()
	void OnRep_StaticMeshComponents();

	UFUNCTION()
	void OnRep_ReplicatedVehicle();
	
	UFUNCTION()
	void OnRep_Status();

	UFUNCTION()
	void OnRep_IsFollowingPath();
	
	UFUNCTION()
	void OnRep_IsGhosting();

	void OnSimulationTargetReached( AFGTargetPoint* newTarget );

	void UpdateComponentVisibility();

private:
	friend class AFGWheeledVehicle;

	/**
	 * The host vehicle. May be nullptr on client if it is net culled.
	 */
	UPROPERTY( SaveGame )
	class AFGWheeledVehicle* mVehicle;

	/**
	 * Same as returned from HasAuthority().
	 */
	bool mIsServer = false;

	/**
	 * The host vehicle replicated. Mainly used to determined if the client is in physical mode but net culled, and therefore should show its simulated vehicle. TODO: seems to be working so-so.
	 */
	UPROPERTY( ReplicatedUsing = OnRep_ReplicatedVehicle )
	class AFGWheeledVehicle* mReplicatedVehicle;

	/**
	 * The deadlocked/out-of-fuel/operational status of this vehicle.
	 */
	UPROPERTY( ReplicatedUsing = OnRep_Status )
	EVehicleStatus mStatus = EVehicleStatus::VS_Operational;

	/**
	 * Is the vehicle currently automated and has a path?
	 */
	UPROPERTY( ReplicatedUsing = OnRep_IsFollowingPath )
	bool mIsFollowingPath = false;

	/**
	 * Is the vehicle possessed by a player?
	 */
	UPROPERTY( Replicated )
	bool mIsPossessed = false;

	/**
	 * The next target that this vehicle is driving towards
	 */
	UPROPERTY( Replicated, SaveGame )
	class AFGTargetPoint* mTarget = nullptr;
	
	/** Used for simulated movement along path described by mTargetList */
	UPROPERTY( Replicated )
	class UFGSplinePathMovementComponent* mSimulationMovement;

	/** The station to which this vehicle is currently docked */
	UPROPERTY( Replicated )
	class AFGBuildableDockingStation* mCurrentStation = nullptr;

	/**
	 * Is this vehicle in physical (false) or simulated (true) mode
	 */
	UPROPERTY( Replicated )
	bool mIsSimulated = false;

	UPROPERTY( Replicated )
	FVector mAuthoritativeLocation;

	UPROPERTY( Replicated )
	FQuat mAuthoritativeRotation;

	UPROPERTY( Replicated )
	FVector mAuthoritativeLinearVel;

	/**
	 * Is vehicle temporarily going into simulated mode (with an extra indicative effect) to cheat its way to the next target (if otherwise unable to progress)?
	 */
	UPROPERTY( ReplicatedUsing = OnRep_IsGhosting )
	bool mIsGhosting = false;

	/**
	 * Is the simulated vehicle visible despite the vehicle being physical (only on client)?
	 */
	bool mIsSimulationVisible = false;

	/**
	 * The type of fuel that is currently loaded into this vehicle.
	 */
	UPROPERTY( Replicated, SaveGame )
	TSubclassOf< class UFGItemDescriptor > mCurrentFuelClass;

	// Actor representation stuff

	UPROPERTY( Replicated )
	class UTexture2D* mActorRepresentationTexture;

	UPROPERTY( Replicated )
	FText mMapText;

	UPROPERTY( Replicated )
	FLinearColor mDefaultRepresentationColor;

	UPROPERTY( Replicated )
	FLinearColor mPlayerNametagColor;

	/**
	 * The extent of the bounding box used for hit testing this vehicle against other objects and terrain.
	 */
	UPROPERTY( Replicated )
	FVector mBoundingBoxExtent;

	/**
	 * The local offset of the bounding box used for hit testing this vehicle against other objects and terrain.
	 */
	UPROPERTY( Replicated )
	FVector mBoundingBoxOffset;

	/**
	 * The wheel radius of this vehicle, used for hit testing this vehicle against other objects and terrain.
	 */
	UPROPERTY( Replicated )
	float mWheelRadius = 0.0f;

	/**
	 * The static mesh representing parts if this vehicle in simulated mode.
	 */
	UPROPERTY( ReplicatedUsing = OnRep_StaticMeshComponents )
	TArray<class UStaticMeshComponent*> mStaticMeshComponents;
};
