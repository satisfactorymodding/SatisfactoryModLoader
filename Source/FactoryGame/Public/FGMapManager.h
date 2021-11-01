// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "FGSubsystem.h"
#include "FGSaveInterface.h"
#include "FGActorRepresentationInterface.h"
#include "FGMinimapCaptureActor.h"
#include "FGMapManager.generated.h"

DECLARE_STATS_GROUP( TEXT( "MapManager" ), STATGROUP_MapManager, STATCAT_Advanced );
DECLARE_LOG_CATEGORY_EXTERN( LogMapManager, Log, All );

USTRUCT()
struct FFogOfWarQueuePair
{
	GENERATED_BODY()

	FFogOfWarQueuePair() :
		PlayerController( nullptr ),
		CurrentProgressIndex( 0 )
	{
		CompressedFogOfWar.Reset();
	}

	UPROPERTY()
	class AFGPlayerController* PlayerController;

	// The index of the progress through the compressed data for this transfer
	int32 CurrentProgressIndex;
	// Array to hold the compressed data per transfer
	TArray<uint8> CompressedFogOfWar;

};

/**
* This class manages the map.
*/
UCLASS()
class FACTORYGAME_API AFGMapManager : public AFGSubsystem, public IFGSaveInterface
{
	GENERATED_BODY()
public:
	/** Get the map manager, this should always return something unless you call it really early. */
	static AFGMapManager* Get(UWorld* world);

	/** Get the map manager from a world context, this should always return something unless you call it really early. */
	UFUNCTION(BlueprintPure, Category = "Map", DisplayName = "GetMapManager", Meta = (DefaultToSelf = "worldContext"))
	static AFGMapManager* Get(UObject* worldContext);

public:
	AFGMapManager();

	// Begin AActor interface
	void GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const override;
	virtual void BeginPlay() override;
	virtual void Tick( float dt ) override;
	// End AActor interface

	// Begin IFGSaveInterface
	virtual void PreSaveGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void PostSaveGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void PreLoadGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void PostLoadGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void GatherDependencies_Implementation( TArray< UObject* >& out_dependentObjects ) override;
	virtual bool NeedTransform_Implementation() override;
	virtual bool ShouldSave_Implementation() const override;
	// End IFSaveInterface

	UFUNCTION( BlueprintPure, Category = "Fog of War" )
	FORCEINLINE class UTexture2D* GetFogOfWarTexture() const { return mFogOfWarTexture; }

	/** Puts a player controller in the transfer queue awaiting fog of war transfer  */
	void RequestFogOfWarData( class AFGPlayerController* playerController );

	/** Transfers fog of war data via player controller  */
	void TransferFogOfWarData();

	/** Receive fog of war data via player controller  */
	void SyncFogOfWarChanges( const TArray<uint8>& fogOfWarRawData, int32 finalIndex );

	// Cheats
	void RevealMap();
	void HideMap();

private:
	
	/** Setups the fog of war texture TODO: Move the texture parts to separate class */
	void SetupFogOfWarTexture();
	void InitialFogOfWarRequest();
	void SetupRepresentationManager();
	void BindActorRepresentationManager( class AFGActorRepresentationManager* representationManager );

	/** Local updates of the fog of war*/
	void UpdateFogOfWar( UFGActorRepresentation* actor );
	FVector2D GetMapPositionFromWorldLocation( FVector worldLocation );
	float GetMapDistanceFromWorldDistance( float worldDistance );
	void DrawCircle( FVector2D centerPoint, float radius, float gradientHeightModifier );

	UFUNCTION()
	void OnActorRepresentationAdded( class UFGActorRepresentation* actorRepresentation );

	UFUNCTION()
	void OnActorRepresentationUpdated( class UFGActorRepresentation* actorRepresentation );

	UFUNCTION()
	void OnActorRepresentationRemoved( class UFGActorRepresentation* actorRepresentation );
private:
	
	/** The raw pixel data for the fog of war texture. Each element represents a channel for a pixel */
	UPROPERTY( SaveGame )
	TArray<uint8> mFogOfWarRawData;
	UPROPERTY()
	TArray<uint8> mClientFogOfWarBuffer;


	/** The size of the raw pixel data array */
	int32 mFogOfWarDataSize;
	/** The resolution for the fog of war texture */
	int32 mFogOfWarResolution;
	/** Size (in bytes) we will allow for a single fog of war packet */
	int32 mFogOfWarNetPacketSize;
	/** The fog of war texture that is used for the map */
	UPROPERTY()
	UTexture2D* mFogOfWarTexture;
	/** The fog of war texture region used for updating the texture */
	FUpdateTextureRegion2D mFogOfWarUpdateTextureRegion;
	/** Capture actor used for translate world locations to map locations  */
	UPROPERTY()
	AFGMinimapCaptureActor* mCachedMinimapCaptureActor;

	/** Fog of war config values used for debugging */
	float mLowestWorldLocation;
	float mHighestWorldLocation;
	float mFogOfWarUpperRangeMin;
	float mFogOfWarUpperRangeMax;
	float mFogOfWarGradientExpandValue;
	bool mEnableFogOfWarRevealCalculations;
	bool mEnableFogOfWarTextureUpdates;
	bool mForceSingleThreadedCalculations;

	/** Queue to handle clients waiting for fog of war transfer */
	UPROPERTY()
	TArray<FFogOfWarQueuePair> mFogOfWarTransferQueue;

	/** Actor representation manager to get representations updates to calculate fog of war data  */
	UPROPERTY( Transient )
	class AFGActorRepresentationManager* mActorRepresentationManager;

	/** The currently active dynamic actor representations that reveal fog of war */
	UPROPERTY()
	TArray<UFGActorRepresentation*> mDynamicFogOfWarRevealActors;

	/** The current index for the tick update loop for fog of war from dynamic actor representations */
	int32 mDynamicActorsArrayIndex;

	/** The pixel data array contains 4 uint8 per pixel. We only need to change 1 during runtime and the red channel is used in the material.
	So we stick with an offset of 2 for now. */
	const static int32 PIXEL_OFFSET;
};
