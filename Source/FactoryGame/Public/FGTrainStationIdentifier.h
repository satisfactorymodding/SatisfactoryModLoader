// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "GameFramework/Info.h"
#include "FGSaveInterface.h"
#include "FGActorRepresentationInterface.h"
#include "FGTrainStationIdentifier.generated.h"

/**
 * Identifier for a train station that is always available on server and clients.
 */
UCLASS()
class FACTORYGAME_API AFGTrainStationIdentifier : public AInfo, public IFGSaveInterface, public IFGActorRepresentationInterface
{
	GENERATED_BODY()
public:
	AFGTrainStationIdentifier();

	// Begin AActor Interface
	virtual void GetLifetimeReplicatedProps( TArray< FLifetimeProperty >& OutLifetimeProps ) const override;
	virtual void BeginPlay() override;
	virtual void EndPlay( const EEndPlayReason::Type endPlayReason ) override;
	// End AActor Interface

	// Begin IFGSaveInterface
	virtual void PreSaveGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void PostSaveGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void PreLoadGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void PostLoadGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void GatherDependencies_Implementation( TArray< UObject* >& out_dependentObjects ) override;
	virtual bool NeedTransform_Implementation() override;
	virtual bool ShouldSave_Implementation() const override;
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

	/** Get the station actor, only valid on server. */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Railroad|StationIdentifier" )
	class AFGBuildableRailroadStation* GetStation() const { return mStation; }

	/** Get the name of this station. */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Railroad|StationIdentifier" )
	FText GetStationName() const { return mStationName; }

	/** Set the name of this station, must be called on server. */
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Railroad|StationIdentifier" )
	void SetStationName( const FText& text );

	/** Get the track graph this station is located in. */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Railroad|StationIdentifier" )
	int32 GetTrackGraphID() const { return mTrackGraphID; }

private:
	UFUNCTION()
	void OnRep_StationName();

	UFUNCTION()
	void OnRep_Station();
public:
	/** The station this info represents. */
	UPROPERTY( SaveGame, ReplicatedUsing = OnRep_Station )
	class AFGBuildableRailroadStation* mStation;

	/** The track this station is on. */
	UPROPERTY( Replicated )
	int32 mTrackGraphID;

	/** Cached here for clients. */
	UPROPERTY( SaveGame, ReplicatedUsing = OnRep_StationName )
	FText mStationName;
	
	UPROPERTY(EditDefaultsOnly)
	UMaterialInterface* mCompassMaterialInstance;
};
