// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "FGActorRepresentationInterface.h"
#include "Animation/SkeletalMeshActor.h"
#include "FGSaveInterface.h" // MODDING EDIT
#include "WheeledVehicles/FGWheeledVehicle.h" // MODDING EDIT
#include "FGWheeledVehicleInfo.generated.h"

UENUM( BlueprintType )
enum class EVehicleStatus : uint8
{
	VS_Operational,
	VS_OutOfFuel,
	VS_Deadlocked
};

/**
 * Containing wheeled-vehicle data that needs to be on client always
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

	// Begin AActor interface
	virtual void BeginPlay() override;
	virtual void EndPlay( const EEndPlayReason::Type EndPlayReason ) override;
	virtual void Tick( float dt ) override;
	// End AActor interface

	void Init( AFGWheeledVehicle* vehicle );

	void InitCollisionData( class UFGVehicleCollisionBoxComponent* collisionBox );

	// Accessors and change delegates

	class AFGWheeledVehicle* GetVehicle() const;

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FStatusChanged, EVehicleStatus, status );
	UPROPERTY( BlueprintAssignable, Category = "Vehicle", DisplayName = "OnVehicleStatusChanged" )
	FStatusChanged VehicleStatusChangedDelegate;
	
	void SetVehicleStatus( EVehicleStatus status );

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

	class UStaticMeshComponent* GetStaticMeshComponent() const { return mStaticMeshComponent; }

	// End Accessors and change delegates

	FVector GetVehicleLocation() const;

	FRotator GetVehicleRotation() const;

	void UpdateTarget();

	bool ShouldStayAtDock();

	void OnTargetDestroyed( class AFGTargetPoint* target );

	class AFGDrivingTargetList* GetTargetList() const;

	void TryActivatePathSimulation();

	TSubclassOf< class UFGItemDescriptor > GetCurrentFuelClass() const { return mCurrentFuelClass; }

	void SetSimulationVisible( bool isVisible );

	void UpdateCustomizationData( class AFGWheeledVehicle* vehicle );

	void ApplyMeshPrimitiveData( const FFactoryCustomizationData& customizationData );

	void ShowGhostingEffect( bool enabled );

#ifdef DEBUG_SELF_DRIVING
	void DrawDebug( int debugLevel );
#endif

private:
	UFUNCTION()
	void OnRep_Status();

	UFUNCTION()
	void OnRep_IsFollowingPath();
	
	UFUNCTION()
	void OnRep_IsGhosting();

	void OnSimulationTargetReached( AFGTargetPoint* newTarget );

private:
	friend class AFGWheeledVehicle;

	UPROPERTY( SaveGame )
	class AFGWheeledVehicle* mVehicle;

	bool mIsServer = false;

	UPROPERTY( Replicated )
	class AFGWheeledVehicle* mReplicatedVehicle;

	UPROPERTY( ReplicatedUsing = OnRep_Status )
	EVehicleStatus mStatus = EVehicleStatus::VS_Operational;

	UPROPERTY( ReplicatedUsing = OnRep_IsFollowingPath )
	bool mIsFollowingPath = false;

	UPROPERTY( Replicated )
	bool mIsPossessed = false;

	UPROPERTY( Replicated, SaveGame )
	class AFGTargetPoint* mTarget = nullptr;
	
	/** Used for simulated movement along path described by mTargetList */
	UPROPERTY( Replicated )
	class UFGSplinePathMovementComponent* mSimulationMovement;

	/** The station to which this vehicle is currently docked */
	UPROPERTY( Replicated )
	class AFGBuildableDockingStation* mCurrentStation = nullptr;

	UPROPERTY( Replicated )
	bool mIsSimulated = false;

	UPROPERTY( Replicated )
	FVector mAuthoritativeLocation;

	UPROPERTY( Replicated )
	FQuat mAuthoritativeRotation;

	UPROPERTY( Replicated )
	FVector mAuthoritativeLinearVel;

	UPROPERTY( ReplicatedUsing = OnRep_IsGhosting )
	bool mIsGhosting = false;

	bool mIsSimulationVisible = false;

	UPROPERTY( Replicated, SaveGame )
	TSubclassOf< class UFGItemDescriptor > mCurrentFuelClass;

	UPROPERTY( Replicated )
	class UTexture2D* mActorRepresentationTexture;

	UPROPERTY( Replicated )
	FText mMapText;

	UPROPERTY( Replicated )
	FLinearColor mDefaultRepresentationColor;

	UPROPERTY( Replicated )
	FLinearColor mPlayerNametagColor;

	UPROPERTY( Replicated )
	FVector mBoundingBoxExtent;

	UPROPERTY( Replicated )
	FVector mBoundingBoxOffset;

	UPROPERTY( Replicated )
	float mWheelRadius = 0.0f;

	UPROPERTY( Replicated )
	class UStaticMeshComponent* mStaticMeshComponent = nullptr;
};
