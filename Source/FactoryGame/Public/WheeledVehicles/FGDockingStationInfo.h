// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "GameFramework/Info.h"
#include "FGActorRepresentationInterface.h"
#include "FGSaveInterface.h"
#include "FGBuildingTagInterface.h"
#include "FGDockingStationInfo.generated.h"

UENUM( BlueprintType )
enum class EDockingStationStatus : uint8
{
	DSS_Operational,
	DSS_FuelTypeWarning,
};

/**
 * Containing wheeled-vehicle data that needs to be on client always
 */
UCLASS()
class FACTORYGAME_API AFGDockingStationInfo : public AInfo, public IFGSaveInterface, public IFGActorRepresentationInterface, public IFGBuildingTagInterface
{
	GENERATED_BODY()
public:
	AFGDockingStationInfo();

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
	
	//~ Begin IFGBuildingTagInterface
	virtual bool HasBuildingTag_Implementation() const override { return true; }
	virtual void SetHasBuildingTag_Implementation( bool hasBuildingTag ) override {}
	virtual FString GetBuildingTag_Implementation() const override { return mBuildingTag; }
	virtual void SetBuildingTag_Implementation( const FString& buildingTag ) override;
	//~ End FGBuildingTagInterface
	
	// Begin AActor interface
	virtual void BeginPlay() override;
	virtual void EndPlay( const EEndPlayReason::Type EndPlayReason ) override;
	// End AActor interface

	void Init( class AFGBuildableDockingStation* station );

	class AFGBuildableDockingStation* GetStation() const { return mStation; }

	void SetStationStatus( EDockingStationStatus status );

	/** The current status of this station  */
	UFUNCTION( BlueprintPure, Category = "DockingStation" )
	EDockingStationStatus GetStationStatus() const { return mStatus; }

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FStationStatusChanged, EDockingStationStatus, status );
	/** Broadcast when the operation status has changed */
	UPROPERTY( BlueprintAssignable, Category = "DockingStation", DisplayName = "OnStationStatusChanged" )
	FStationStatusChanged StationStatusChangedDelegate;

private:
	UFUNCTION()
	void OnRep_Status();

	UFUNCTION()
	void OnRep_BuildingTag();

private:
	bool mIsServer = false;

	UPROPERTY( SaveGame, ReplicatedUsing = OnRep_Status )
	EDockingStationStatus mStatus = EDockingStationStatus::DSS_Operational;

	UPROPERTY( SaveGame )
	class AFGBuildableDockingStation* mStation;

	UPROPERTY( Replicated )
	FVector mLocation;

	UPROPERTY( Replicated )
	class UTexture2D* mActorRepresentationTexture;

	UPROPERTY( Replicated )
	FLinearColor mDefaultRepresentationColor;

	UPROPERTY( SaveGame, ReplicatedUsing = OnRep_BuildingTag )
	FString mBuildingTag;
};
