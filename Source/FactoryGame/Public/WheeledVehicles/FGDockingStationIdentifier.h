// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "GameFramework/Info.h"
#include "FGActorRepresentationInterface.h"
#include "FGSaveInterface.h"
#include "FGDockingStationIdentifier.generated.h"

class AFGBuildableDockingStation;

UENUM( BlueprintType )
enum class EDockingStationStatus : uint8
{
	DSS_Operational,
	DSS_FuelTypeWarning,
	DSS_NoPowerWarning,
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FOnDockingStationStatusChangedDelegate, EDockingStationStatus, status );

/**
 * Represents a minimal set of information about a vehicle docking station that needs to be replicated to clients at all times
 */
UCLASS()
class FACTORYGAME_API AFGDockingStationIdentifier : public AInfo, public IFGSaveInterface, public IFGActorRepresentationInterface
{
	GENERATED_BODY()
public:
	AFGDockingStationIdentifier();

	virtual void GetLifetimeReplicatedProps( TArray<FLifetimeProperty>& OutLifetimeProps ) const override;

	// Begin AActor interface
	virtual void BeginPlay() override;
	virtual void EndPlay( const EEndPlayReason::Type EndPlayReason ) override;
	// End AActor interface

	/** Returns the name of this docking station. This is set by the player */
	UFUNCTION( BlueprintPure, Category = "Docking Station" )
	FORCEINLINE FText GetStationName() const { return mStationName; }

	/** Sets the station name to the new value. Does text filtering on consoles */
	UFUNCTION( BlueprintCallable, Category = "Docking Station" )
	void SetStationName( const FText& newStationName );

	/** Returns the docking station building this info belongs to, if it is currently replicated to the client */
	UFUNCTION( BlueprintPure, Category = "Docking Station" )
	AFGBuildableDockingStation* GetStation() const { return mStation; }

	/** Returns the GUID of the path node associated with this docking station. Can be used to resolve the path network */
	UFUNCTION( BlueprintPure, Category = "Docking Station" )
	FGuid GetPathNodeGUID() const { return mPathNodeGUID; }

	/** The current status of this station  */
	UFUNCTION( BlueprintPure, Category = "Docking Station" )
	EDockingStationStatus GetStationStatus() const { return mDockingStationStatus; }

	/** Broadcast when the operation status has changed */
	UPROPERTY( BlueprintAssignable, Category = "Docking Station" )
	FOnDockingStationStatusChangedDelegate StationStatusChangedDelegate;

	/** Sets station name without doing the text filtering */
	void Internal_SetStationName( const FText& newStationName );

	/** Initializes docking station info from the docking station object. Must be called on the server */
	void Internal_SetDockingStation( AFGBuildableDockingStation* station );
	void Internal_UpdateFromDockingStation( const AFGBuildableDockingStation* station );

	/** Updates the status of the docking station */
	void Internal_SetStationStatus( EDockingStationStatus status );

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
	virtual UTexture2D* GetActorRepresentationTexture() override;
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
	virtual UMaterialInterface* GetActorRepresentationCompassMaterial() override;
	virtual FPlayerInfoHandle GetLastEditedBy() const override { return mLastEditedBy; }
	virtual void SetActorLastEditedByHandle(const FPlayerInfoHandle& playerInfoHandle) override;
	// End IFGActorRepresentationInterface
private:
	void OnVehicleSubsystemValid();

	UPROPERTY( SaveGame, Replicated )
	TObjectPtr<AFGBuildableDockingStation> mStation;

	UPROPERTY( Replicated )
	FVector mCachedStationActorLocation{ForceInit};

	/** Name of the docking station given to it by the player */
	UPROPERTY( SaveGame, Replicated )
	FText mStationName;

	UPROPERTY( SaveGame, Replicated )
	FPlayerInfoHandle mLastEditedBy;

	UPROPERTY( SaveGame, Replicated )
	FGuid mPathNodeGUID;

	UPROPERTY( SaveGame, Replicated )
	EDockingStationStatus mDockingStationStatus{EDockingStationStatus::DSS_Operational};

	UPROPERTY()
	FString mBuildingTag;
};
