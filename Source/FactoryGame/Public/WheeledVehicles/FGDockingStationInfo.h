// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

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

	UPROPERTY(EditDefaultsOnly)
	UMaterialInterface* mCompassMaterialInstance;

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
