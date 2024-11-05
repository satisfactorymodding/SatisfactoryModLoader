// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FGSubsystem.h"
#include "FGSaveInterface.h"
#include "FGActorRepresentationInterface.h"
#include "FGMinimapCaptureActor.h"
#include "FGMapMarker.h"
#include "Async/AsyncWork.h"
#include "FGMapManager.generated.h"

DECLARE_STATS_GROUP( TEXT( "MapManager" ), STATGROUP_MapManager, STATCAT_Advanced );
FACTORYGAME_API DECLARE_LOG_CATEGORY_EXTERN( LogMapManager, Log, All );
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FOnMapMarkerAdded, int32, markerIndex );
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FOnMapMarkerRemoved, int32, markerIndex  );
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams( FOnMarkerHighlightUpdated, UFGActorRepresentation*, actorRepresentation, bool, highlighted, class AFGPlayerState*, playerState );

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

USTRUCT()
struct FMapMarkerQueuePair
{
	GENERATED_BODY()

	FMapMarkerQueuePair() :
		PlayerController( nullptr ),
		CurrentProgressIndex( 0 )
	{
		MapMarkers.Reset();
	}

	UPROPERTY()
	class AFGPlayerController* PlayerController;

	// The index of the progress through the map marker data for this transfer
	int32 CurrentProgressIndex;
	// Array to hold the map marker data per transfer
	TArray<FMapMarker> MapMarkers;

};

USTRUCT()
struct FHighlightedMarkerPair
{
	GENERATED_BODY()

	FHighlightedMarkerPair() :
		PlayerState( nullptr ),
		HighlightedMarker( nullptr )
	{}

	FHighlightedMarkerPair( class AFGPlayerState* playerState, class UFGHighlightedMarker* highlightedMarker ) :
		PlayerState( playerState ),
		HighlightedMarker( highlightedMarker )
	{}

	UPROPERTY( SaveGame )
	class AFGPlayerState* PlayerState;
	UPROPERTY( SaveGame )
	class UFGHighlightedMarker* HighlightedMarker;

	
};

USTRUCT()
struct FFOWData
{
	GENERATED_BODY()

	FFOWData(){}

	FFOWData( FVector2D centerPoint, float radius, float gradientHeightModifier, bool useGradientFalloff ) :
		CenterPoint( centerPoint ),
		Radius( radius ),
		GradientHeightModifier( gradientHeightModifier ),
		UseGradientFalloff( useGradientFalloff )
	{}

	FVector2D CenterPoint = FVector2D::ZeroVector;
	float Radius = 0.f;
	float GradientHeightModifier = 0.f;
	bool UseGradientFalloff = false;
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
	virtual void BeginPlay() override;
	virtual void EndPlay( const EEndPlayReason::Type endPlayReason ) override;
	virtual void Tick( float dt ) override;
	virtual void DisplayDebug( class UCanvas* canvas, const class FDebugDisplayInfo& debugDisplay, float& YL, float& YPos ) override;
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
	/** Transfers map marker data via player controller  */
	void TransferMapMarkerData();

	/** Receive fog of war data via player controller  */
	void SyncFogOfWarChanges( const TArray<uint8>& fogOfWarRawData, int32 finalIndex );
	/** Receive map marker data via player controller  */
	void SyncMapMarkerChanges( const TArray<FMapMarker>& mapMarkers );

	// Cheats
	void RevealMap();
	void HideMap();

	/** Return true if we could add a map marker. False if we have reached marker limit */
	UFUNCTION( BlueprintCallable, Category=Map )
	UPARAM( DisplayName = "Success" ) bool AddNewMapMarker( const FMapMarker& mapMarker, FMapMarker& out_NewMapMarker  );

	/** Adds a new marker to the system. This function is NEVER meant to trigger remote calls that adds markers.
	 *	Just a local add and whatever local changes we want to trigger after that */ 
	void AddIndexedMapMarker( const FMapMarker& mapMarker );

	void SyncMapMarkerAdded( const FMapMarker& mapMarker );

	UFUNCTION( BlueprintCallable, Category=Map )
	void UpdateMapMarker( const FMapMarker& mapMarker, bool localUpdateOnly = false );

	UFUNCTION( BlueprintCallable, Category=Map )
	void GetMapMarkers( TArray<FMapMarker>& out_mapMarkers );
	UFUNCTION( BlueprintPure, Category=Map )
	int32 GetMaxNumMapMarkers() const { return mMaxNumMapMarkers; }
	
	UFUNCTION( BlueprintPure, Category=Map )
	int32 GetNumMapMarkers() const;
	UFUNCTION( BlueprintPure, Category=Map )
	bool CanAddNewMapMarker() const;

	UFUNCTION( BlueprintCallable, Category=Map )
	void RemoveMapMarker( const FMapMarker& mapMarker );
	void RemoveMapMarkerOnIndex( int32 index );

	void SetMapMarkerComponentsVisible( bool visible );
	void SpawnMapMarkerObjectOfType( const FMapMarker& mapMarker );
	void RemoveMapMarkerObjectOfType( const FMapMarker& mapMarker );

	bool FindMapMarkerFromHitResult( const FHitResult& hitResult, FMapMarker& out_mapMarker );
	class UFGMapMarkerRepresentation* FindMapMarkerRepresentation( const FMapMarker& mapMarker ); 
	class UFGMapMarkerRepresentation* FindMapMarkerRepresentation( const int32 mapMarkerID ); 

	UFUNCTION( BlueprintPure, Category=MapMarker )
	UPARAM(DisplayName = "HighlightColor") FLinearColor IsMarkerHighlighted( const FMapMarker& mapMarker, UPARAM(DisplayName = "IsHighlighted") bool& out_IsHighlighted, UPARAM(DisplayName = "HighlightedByLocalPlayer") bool& out_HighlightedByLocalPlayer );
	UFUNCTION( BlueprintCallable, Category=MapMarker )
	void SetMarkerHighlighted( const FMapMarker& mapMarker, bool highlighted );
	void SetHighLightMarker( class AFGPlayerState* fgPlayerState, UFGActorRepresentation* actorRepresentation );
	void OnMarkerHighlightUpdated( class AFGPlayerState* fgPlayerState, UFGActorRepresentation* actorRepresentation, bool highlighted );
	void HighlightMapMarkerInstance( class UHierarchicalInstancedStaticMeshComponent* component, int32 instanceIndex, bool highlighted, FLinearColor color );
	void OnSetHighLightMarker( class AFGPlayerState* fgPlayerState, UFGActorRepresentation* actorRepresentation );
	void OnSetHighLightMarker( class AFGPlayerState* fgPlayerState, int32 markerID );
	UStaticMeshComponent* SpawnHighLightMarkerMeshComp();
	UNiagaraComponent* SpawnHighLightMarkerNiagaraComponent( const FVector& location );
	void SyncSetHighLightMarker( class AFGPlayerState* fgPlayerState, UFGActorRepresentation* actorRepresentation );

	UFGHighlightedMarker* GetHighlightedActorRepresentation( const class AFGPlayerState* fgPlayerState ) const;
	bool IsActorRepresentationHighlighted( const UFGActorRepresentation* actorRepresentation, FLinearColor& out_HighlightColor, bool& out_HighlightByLocalPlayer ) const;

	void UpdateHoveredMapMarker( const FHitResult& hitResult );
	void SetMapMarkerHovered( TPair< class UHierarchicalInstancedStaticMeshComponent*, int32> instancedMeshPair, bool enabled );
	void ClearHoveredMapMarker();

	void MapToHighlightedMarker( UFGActorRepresentation* actorRepresentation );
	void RequestMapMarkerData( class AFGPlayerController* playerController );

	UPROPERTY( BlueprintAssignable )
	FOnMapMarkerAdded mOnMapMarkerAdded;
	UPROPERTY( BlueprintAssignable )
	FOnMapMarkerRemoved mOnMapMarkerRemoved;
	UPROPERTY()
	FOnMarkerHighlightUpdated mOnMarkerHighlightUpdated;

private:
	void UpdateMarkerComponentVisiblity();
	void SetMarkerComponentVisiblity( float opacity );
	
	/** Setups the fog of war texture */
	void SetupFogOfWarTexture();
	void InitialFogOfWarRequest();
	void SetupRepresentationManager();
	void BindActorRepresentationManager( class AFGActorRepresentationManager* representationManager );

	/** Local updates of the fog of war*/
	void UpdateFogOfWar( UFGActorRepresentation* actor );
	FVector2D GetMapPositionFromWorldLocation( FVector worldLocation );
	float GetMapDistanceFromWorldDistance( float worldDistance );
	void DrawCircle( FVector2D centerPoint, float radius, float gradientHeightModifier, bool useGradientFalloff );
	
	void InitialMapMarkerRequest();

	UFUNCTION()
	void OnActorRepresentationAdded( class UFGActorRepresentation* actorRepresentation );

	UFUNCTION()
	void OnActorRepresentationUpdated( class UFGActorRepresentation* actorRepresentation );
	
	void OnActorRepresentationFOWUpdated( class UFGActorRepresentation* actorRepresentation );

	UFUNCTION()
	void OnActorRepresentationRemoved( class UFGActorRepresentation* actorRepresentation );

	UFUNCTION()
	void OnPlayerStateSlotDataUpdated( class AFGPlayerState* playerState );

	void RecreateSavedMarkers();

	void RefreshHighlightedMarkers();

private:
	
	/** The raw pixel data for the fog of war texture. Each element represents a channel for a pixel */
	UPROPERTY( SaveGame )
	TArray<uint8> mFogOfWarRawData;
	UPROPERTY()
	TArray<uint8> mClientFogOfWarBuffer;

	UPROPERTY( SaveGame )
	TArray<FMapMarker> mMapMarkers;

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

	/** Queue to handle clients waiting for fog of war transfer */
	UPROPERTY()
	TArray<FFogOfWarQueuePair> mFogOfWarTransferQueue;
	/** Queue to handle clients waiting for map marker transfer */
	UPROPERTY()
	TArray<FMapMarkerQueuePair> mMapMarkerTransferQueue;

	/** Actor representation manager to get representations updates to calculate fog of war data  */
	UPROPERTY( Transient )
	class AFGActorRepresentationManager* mActorRepresentationManager;

	/** The currently active dynamic actor representations that reveal fog of war */
	UPROPERTY()
	TArray<UFGActorRepresentation*> mDynamicFogOfWarRevealActors;

	/** The current index for the tick update loop for fog of war from dynamic actor representations */
	int32 mDynamicActorsArrayIndex;

	/** The maximum amount of map markers. Not exposed as EditDefaults since it might require some changes with how map marker structs are IDed */
	int32 mMaxNumMapMarkers = 250;

	UPROPERTY()
	TMap< int32, class UHierarchicalInstancedStaticMeshComponent* > mMapMarkerComponents;

	/** Highlighted marker can be almost anything that is an actor representation on the map. The underlying saved data could be an FMapMarker or a actor. */ 
	UPROPERTY( SaveGame )
	TArray< FHighlightedMarkerPair > mHighlightedMarkers;

	/** Not a UPROPERTY but should be fine since the object that is the key is always referenced by mMapMarkerComponents */
	TPair< class UHierarchicalInstancedStaticMeshComponent*, int32 > mHoveredInstancedMeshComponent;

	/** Used to show/hide map marker component. */
	float mMarkerComponentCurrentVisibilityOpacity;
	float mMarkerComponentTargetVisibilityOpacity;
	/* We use a timer instead of tick since tick is set to an TickInterval of 0.1 and that doesn't look nice and I don't want to lower that for this small lerp  */
	FTimerHandle mMarkerComponentVisibilityTimer;
	
	FAsyncTask<class FFogOfWarTask>* mFOWAsyncTask;

	TArray<FFOWData> mFOWDrawQueue;
	
};

struct FFogOfWarWorker
{
	TArray<uint8> FogOfWarRawData;
	int32 FogOfWarResolution = 0;
	float FogOfWarUpperRangeMin = 0.f;
	float FogOfWarUpperRangeMax = 0.f;
	float FogOfWarGradientExpandValue = 0.f;
	bool ForceSingleThreadedCalculations = false;

	TArray<FFOWData> DrawQueue;
	
	void DoWork();
};

class FFogOfWarTask : public FNonAbandonableTask
{
public:
	FFogOfWarTask( FFogOfWarWorker* InWorker )
	{
		Worker = InWorker;
	}
	
	FFogOfWarWorker* Worker;
	
	void DoWork();

	FORCEINLINE TStatId GetStatId() const
	{
		RETURN_QUICK_DECLARE_CYCLE_STAT( FFogOfWarTask, STATGROUP_ThreadPoolAsyncTasks )		
	}
	~FFogOfWarTask();
};
