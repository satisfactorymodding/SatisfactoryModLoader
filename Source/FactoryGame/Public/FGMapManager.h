// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "FGSubsystem.h"
#include "FGSaveInterface.h"
#include "FGMinimapCaptureActor.h"
#include "FGMapMarker.h"
#include "Async/AsyncWork.h"
#include "FGMapManager.generated.h"

DECLARE_STATS_GROUP( TEXT( "MapManager" ), STATGROUP_MapManager, STATCAT_Advanced );

FACTORYGAME_API DECLARE_LOG_CATEGORY_EXTERN( LogMapManager, Log, All );

class UFGMapMarkerRepresentation;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FOnMapMarkerAdded, FGuid, markerGuid );
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FOnMapMarkerRemoved, FGuid, markerGuid );
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams( FOnMarkerHighlightUpdated, UFGActorRepresentation*, actorRepresentation, bool, highlighted, class AFGPlayerState*, playerState );

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
	AFGMapManager();

	// Begin AActor interface
	virtual void GetLifetimeReplicatedProps( TArray< FLifetimeProperty >& OutLifetimeProps ) const override;
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

	/** Get the map manager, this should always return something unless you call it really early. */
	static AFGMapManager* Get(UWorld* world);

	/** Get the map manager from a world context, this should always return something unless you call it really early. */
	UFUNCTION(BlueprintPure, Category = "Map", DisplayName = "GetMapManager", Meta = (DefaultToSelf = "worldContext"))
	static AFGMapManager* Get(UObject* worldContext);

	/* *Returns the texture used for Fog Of War */
	UFUNCTION( BlueprintPure, Category = "Fog of War" )
	FORCEINLINE UTexture2D* GetFogOfWarTexture() const { return mFogOfWarTexture; }
	
	/** Returns the maximum number of map markers that can be created */
	UFUNCTION( BlueprintPure, Category = "Map" )
	FORCEINLINE int32 GetMaxNumMapMarkers() const { return mMaxNumMapMarkers; }

	/** Returns the number of map markers that are currently visible */
	UFUNCTION( BlueprintPure, Category = "Map" )
	FORCEINLINE int32 GetNumMapMarkers() const { return mMapMarkers.Num(); }

	/** Returns the ID of the local player */
	FORCEINLINE FGuid GetLocalPlayerID() const { return mLocalPlayerID; }

	/** Returns all map markers that are currently present */
	UFUNCTION( BlueprintCallable, Category = "Map" )
	void GetMapMarkers( TArray<FMapMarker>& out_mapMarkers );

	/** Returns true if new map markers can be added, and false otherwise */
	UFUNCTION( BlueprintPure, Category = "Map" )
	bool CanAddNewMapMarker() const;

	/** Creates a new map marker with the data provided in the existing marker. Will return the ID for the created marker and true if the marker was created */
	UFUNCTION( BlueprintCallable, Category = "Map" )
	bool AddNewMapMarker( const FMapMarker& mapMarker, FMapMarker& out_NewMapMarker  );

	/** Updates existing map marker on the map. Can be called on the client, in which case the request will be proxied to the server */
	UFUNCTION( BlueprintCallable, Category = "Map" )
	void UpdateMapMarker( const FMapMarker& mapMarker, bool localUpdateOnly = false );
	
	/** Removes map marker from the map. Can be called on the client, in which case the request will be proxied to the server */
	UFUNCTION( BlueprintCallable, Category = "Map" )
	void RemoveMapMarker( const FMapMarker& mapMarker );

	/** Updates the visibility of the map markers in the world */
	UFUNCTION( BlueprintCallable, Category = "Map" )
	void SetMapMarkerComponentsVisible( bool visible );

	/** Creates the map marker, or updates it if it already exists. MarkerGUID must already be set on the marker */
	UFUNCTION( BlueprintCallable, BlueprintAuthorityOnly, Category = "Map" )
	void Authority_UpdateMapMarker( const FMapMarker& mapMarker );
	
	/** Removes Map Marker by it's ID. Should only be called on the Server */
	UFUNCTION( BlueprintCallable, BlueprintAuthorityOnly, Category = "Map" )
	void Authority_RemoveMapMarkerByID( const FGuid& markerGuid );

	/** Attempts to resolve which map marker was hit from the hit result. Returns true if marker was found and populated */
	UFUNCTION( BlueprintCallable, Category = "Map" )
	bool FindMapMarkerFromHitResult( const FHitResult& hitResult, FMapMarker& out_mapMarker );

	/** Attempts to retrieve the representation for the map marker by it's GUID */
	UFUNCTION( BlueprintPure, Category = "Map" )
	UFGMapMarkerRepresentation* FindMapMarkerRepresentation( const FMapMarker& mapMarker );

	/** Attempts to retrieve the representation for the map marker by it's GUID */
	UFGMapMarkerRepresentation* FindMapMarkerRepresentation( const FGuid mapMarkerGUID ); 

	UFUNCTION( BlueprintPure, Category=MapMarker )
	UPARAM(DisplayName = "HighlightColor") FLinearColor IsMarkerHighlighted( const FMapMarker& mapMarker, UPARAM(DisplayName = "IsHighlighted") bool& out_IsHighlighted, UPARAM(DisplayName = "HighlightedByLocalPlayer") bool& out_HighlightedByLocalPlayer );
	UFUNCTION( BlueprintCallable, Category=MapMarker )
	void SetMarkerHighlighted( const FMapMarker& mapMarker, bool highlighted );
	void SetHighLightMarker( class AFGPlayerState* fgPlayerState, UFGActorRepresentation* actorRepresentation );
	void OnMarkerHighlightUpdated( class AFGPlayerState* fgPlayerState, UFGActorRepresentation* actorRepresentation, bool highlighted );
	void HighlightMapMarkerInstance( class UHierarchicalInstancedStaticMeshComponent* component, int32 instanceIndex, bool highlighted, FLinearColor color );
	void OnSetHighLightMarker( class AFGPlayerState* fgPlayerState, UFGActorRepresentation* actorRepresentation );
	void OnSetHighLightMarker( class AFGPlayerState* fgPlayerState, FGuid markerGUID );
	UStaticMeshComponent* SpawnHighLightMarkerMeshComp();
	UNiagaraComponent* SpawnHighLightMarkerNiagaraComponent( const FVector& location );
	void SyncSetHighLightMarker( class AFGPlayerState* fgPlayerState, UFGActorRepresentation* actorRepresentation );

	UFGHighlightedMarker* GetHighlightedActorRepresentation( const class AFGPlayerState* fgPlayerState ) const;
	bool IsActorRepresentationHighlighted( const UFGActorRepresentation* actorRepresentation, FLinearColor& out_HighlightColor, bool& out_HighlightByLocalPlayer ) const;

	void UpdateHoveredMapMarker( const FHitResult& hitResult );
	void SetMapMarkerHovered( TPair< class UHierarchicalInstancedStaticMeshComponent*, int32> instancedMeshPair, bool enabled );
	void ClearHoveredMapMarker();
	void MapToHighlightedMarker( UFGActorRepresentation* actorRepresentation );

	/** Returns a reference to the raw FOW data array */
	FORCEINLINE const TArray<uint8>& GetFogOfWarRawData() const { return mFogOfWarRawData; }
	
	void UpdateFogOfWarRawData( const TArray<uint8>& newFogOfWarRawData );

	/** Overwrites all of the fog of war data with the provided value. 0 means hidden, 0xFF means fully revealed */
	void ReplaceFogOfWarData(uint8 newFogOfWarData);
public:
	/** Broadcast when map marker is added locally */
	UPROPERTY( BlueprintAssignable, Category = "Map" )
	FOnMapMarkerAdded mOnMapMarkerAdded;

	/** Broadcast when map marker is updated locally. Not called when the marker is added*/
	UPROPERTY( BlueprintAssignable, Category = "Map" )
	FOnMapMarkerAdded mOnMapMarkerUpdated;

	/** Broadcast when map marker is removed locally */
	UPROPERTY( BlueprintAssignable, Category = "Map" )
	FOnMapMarkerRemoved mOnMapMarkerRemoved;

	/** Broadcast when the highlight status is changed for a specific marker */
	UPROPERTY( BlueprintAssignable, Category = "Map" )
	FOnMarkerHighlightUpdated mOnMarkerHighlightUpdated;
private:
	void SpawnMapMarkerObjectOfType( const FMapMarker& mapMarker );
	void RemoveMapMarkerObjectOfType( const FMapMarker& mapMarker );
	void CreateOrUpdateMarkerRepresentation( const FMapMarker& mapMarker );
	
	void UpdateMarkerComponentVisibility();

	/** Setups the fog of war texture */
	void SetupFogOfWarTexture();
	void SetupRepresentationManager();
	void BindActorRepresentationManager( class AFGActorRepresentationManager* representationManager );

	/** Local updates of the fog of war*/
	void UpdateFogOfWar( UFGActorRepresentation* actor );
	FVector2D GetMapPositionFromWorldLocation( FVector worldLocation );
	float GetMapDistanceFromWorldDistance( float worldDistance );
	void DrawCircle( FVector2D centerPoint, float radius, float gradientHeightModifier, bool useGradientFalloff );

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

	void Local_CreateOrUpdateMarkerRepresentation(const FMapMarker& mapMarker);
	void Local_RemoveMarkerRepresentationById(const FGuid& markerGuid);

	/** Broadcast to create or update the provided map marker */
	UFUNCTION(NetMulticast, Reliable)
	void Multicast_CreateUpdateMapMarker(const FMapMarker& mapMarker);

	/** Broadcast to remove the map marker by it's ID */
	UFUNCTION(NetMulticast, Reliable)
	void Multicast_RemoveMapMarker(const FGuid& mapMarkerGUID);

	/** Make sure map markers for the initial creation are initialized once all of the relevant data is available */
	UFUNCTION()
	void CreateMapMarkersForInitialReplication();
private:
	/** The raw pixel data for the fog of war texture. Each element represents a channel for a pixel */
	UPROPERTY( SaveGame )
	TArray<uint8> mFogOfWarRawData;

	/** Map markers that are currently saved. Replicated only once on join, upcoming replications are handled by multicasts */
	UPROPERTY( SaveGame, Replicated )
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

	/** ID of the local player used to tell markers created by this player apart from other players */
	FGuid mLocalPlayerID;
	/** True if we have already create map markers for initial replication */
	bool bCreatedInitialMapMarkers{false};

	/** Fog of war config values used for debugging */
	float mLowestWorldLocation;
	float mHighestWorldLocation;
	float mFogOfWarUpperRangeMin;
	float mFogOfWarUpperRangeMax;
	float mFogOfWarGradientExpandValue;
	bool mEnableFogOfWarRevealCalculations;
	bool mEnableFogOfWarTextureUpdates;


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
	
	UPROPERTY()
	TMap<UFGActorRepresentation*,FVector> mActorMapToLocation;
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
