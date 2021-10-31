// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
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

public:
	/** The station this info represents. */
	UPROPERTY( SaveGame, Replicated )
	class AFGBuildableRailroadStation* mStation;

	/** The track this station is on. */
	UPROPERTY( Replicated )
	int32 mTrackGraphID;

	/** Cached here for clients. */
	UPROPERTY( SaveGame, ReplicatedUsing = OnRep_StationName )
	FText mStationName;
};
