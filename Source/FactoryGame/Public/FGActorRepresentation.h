// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FGConveyorItemRenderTargetWriter.h"
#include "UObject/NoExportTypes.h"
#include "FGActorRepresentation.generated.h"

UENUM( BlueprintType )
enum class ERepresentationType : uint8
{
	RT_Default					UMETA( DisplayName = "Default" ),
	RT_Beacon					UMETA( DisplayName = "Beacon" ),
	RT_Crate					UMETA( DisplayName = "Crate" ),
	RT_Hub						UMETA( DisplayName = "Hub" ),
	RT_Ping						UMETA( DisplayName = "Ping" ),
	RT_Player					UMETA( DisplayName = "Player" ),
	RT_RadarTower				UMETA( DisplayName = "RadarTower" ),
	RT_Resource					UMETA( DisplayName = "Resource" ),
	RT_SpaceElevator			UMETA( DisplayName = "SpaceElevator" ),
	RT_StartingPod				UMETA( DisplayName = "StartingPod" ),
	RT_Train					UMETA( DisplayName = "Train" ),
	RT_TrainStation				UMETA( DisplayName = "TrainStation" ),
	RT_Vehicle					UMETA( DisplayName = "Vehicle" ),
	RT_VehicleDockingStation	UMETA( DisplayName = "VehicleDockingStation" ),
	RT_DronePort				UMETA( DisplayName = "DronePort" ),
	RT_Drone					UMETA( DisplayName = "Drone" ),
	RT_MapMarker				UMETA( DisplayName = "MapMarker" ),
	RT_Stamp					UMETA( DisplayName = "Stamp" ),
	RT_Portal					UMETA( DisplayName = "Portal" ),
	RT_DeathCrate				UMETA( DisplayName = "Death Crate" ),
	RT_DismantleCrate			UMETA( DisplayName = "Dismantle Crate" ),
};

UENUM( BlueprintType )
enum class EFogOfWarRevealType : uint8
{
	FOWRT_None					UMETA( DisplayName = "None" ),
	FOWRT_Static				UMETA( DisplayName = "Static" ),
	FOWRT_StaticNoGradient		UMETA( DisplayName = "Static No Gradient" ),
	FOWRT_Dynamic				UMETA( DisplayName = "Dynamic" )
};

UENUM( BlueprintType )
enum class ECompassViewDistance : uint8
{
	CVD_Off				UMETA( DisplayName = "Off" ),
	CVD_Near			UMETA( DisplayName = "Near" ),
	CVD_Mid				UMETA( DisplayName = "Mid" ),
	CVD_Far				UMETA( DisplayName = "Far" ),
	CVD_Always			UMETA( DisplayName = "Always" )
};

/**
 * This object represents an actor in the world. Used in the compass and the minimap.
 */
UCLASS( Blueprintable )
class FACTORYGAME_API UFGActorRepresentation : public UObject
{
	GENERATED_BODY()
	
public:
	UFGActorRepresentation();
	
	/** Mark this class as supported for networking */
	virtual bool IsSupportedForNetworking() const override;
	
	/** Decide on what properties to replicate */
	void GetLifetimeReplicatedProps( TArray<FLifetimeProperty>& OutLifetimeProps ) const override;

	virtual void SetupActorRepresentation( AActor* realActor, bool isLocal, float lifeSpan = 0.0f );

	virtual void TrySetupDestroyTimer( float lifeSpan );
	
	virtual void RemoveActorRepresentation();

	/** Get the Real actor we represent, might not be relevant on client */
	UFUNCTION( BlueprintPure, Category = "Representation" )
	AActor* GetRealActor() const;

	/** Checks if the real actor is the same. On the client, it will also check the Network GUID. This is considerably faster than comparing GetRealActor with actor pointer */
	bool IsSameRealActor( const AActor* realActor, const FNetworkGUID& realActorNetworkId) const;
	
	/** Is this the represented actor static or not */
	UFUNCTION( BlueprintPure, Category = "Representation" )
	FORCEINLINE bool IsActorStatic() const { return mIsStatic; }

	/** Get the location of the represented actor */
	UFUNCTION( BlueprintPure, Category = "Representation" )
	virtual FVector GetActorLocation() const;

	/** Get the rotation of the represented actor */
	UFUNCTION( BlueprintPure, Category = "Representation" )
	virtual FRotator GetActorRotation() const;

	/** This is the image to render in the compass */
	UFUNCTION( BlueprintPure, Category = "Representation" )
	virtual class UTexture2D* GetRepresentationTexture() const;

	/** Returns the material that should be used to create the compass material instance for this representation */
	UFUNCTION( BlueprintPure, Category = "Representation" )
	virtual class UMaterialInterface* GetRepresentationCompassMaterial() const;

	/** Called to update the compass material instance for this representation */
	UFUNCTION( BlueprintCallable, Category = "Representation")
	virtual void UpdateRepresentationCompassMaterial( class UMaterialInstanceDynamic* compassMaterialInstance, APlayerController* ownerPlayerController ) const;

	/** Returns the compass height alignment for this representation. 0 means exactly below the compass line, -0.5 means centered on the line, and -1 means above the line */
	UFUNCTION( BlueprintPure, Category = "Representation" )
	virtual float GetCompassHeightAlignment() const;

	/** Returns true if this representation has dynamic scaling rules for the compass. If this returns true, CalculateCompassRepresentationScale will be called each tick to update the scaling */
	UFUNCTION( BlueprintPure, Category = "Representation" )
	virtual bool NeedsDynamicCompassRepresentationScale() const { return false; }

	/** Calculates the icon scale for this compass representation given the distance from the player and owning player controller */
	UFUNCTION( BlueprintCallable, Category = "Representation" )
	virtual float CalculateCompassRepresentationScale( APlayerController* ownerPlayerController, float distanceToPlayer ) const { return 1.0f; }

	/** This is the text to render in the compass */
	UFUNCTION( BlueprintPure, Category = "Representation" )
	virtual FText GetRepresentationText() const;

	/** Returns true if this representation needs it's name to be dynamically calculated on update instead of being statically cached once. This costs performance. */
	UFUNCTION( BlueprintPure, Category = "Representation" )
	virtual bool NeedsDynamicCompassRepresentationText() const { return false; }

	/** Returns true if this representation is considered "important" in compass. Important representations in compass are always visible, even when outside of view direction */
	UFUNCTION( BlueprintPure, Category = "Representation" )
	virtual bool IsImportantCompassRepresentation() const { return false; }

	/** Called if NeedsDynamicCompassRepresentationText to override the return value of GetRepresentationText for compass names */
	UFUNCTION( BlueprintCallable, Category = "Representation" )
	virtual FText GetDynamicCompassRepresentationText( APlayerController* ownerPlayerController, float distanceToPlayer ) const;

	/** This is the color to render in the compass */
	UFUNCTION( BlueprintPure, Category = "Representation" )
	virtual FLinearColor GetRepresentationColor() const;

	UFUNCTION( BlueprintPure, Category = "Representation" )
	virtual ERepresentationType GetRepresentationType() const;

	/** If this should be shown in the compass or not*/
	UFUNCTION( BlueprintPure, Category = "Representation" )
	virtual bool GetShouldShowInCompass() const;

	/** If this should be shown on the map or not*/
	UFUNCTION( BlueprintPure, Category = "Representation" )
	virtual bool GetShouldShowOnMap() const;

	UFUNCTION( BlueprintPure, Category = "Representation" )
	virtual EFogOfWarRevealType GetFogOfWarRevealType() const;

	UFUNCTION( BlueprintPure, Category = "Representation" )
	virtual float GetFogOfWarRevealRadius() const;

	void SetIsOnClient( bool onClient );
	void SetRepresentationID( const FGuid& NewRepresentationID );

	UFUNCTION( BlueprintPure, Category = "Representation" )
	virtual ECompassViewDistance GetCompassViewDistance() const;

	UFUNCTION( BlueprintPure, Category = "Representation" )
	virtual bool GetScaleWithMap() const;

	UFUNCTION( BlueprintPure, Category = "Representation" )
	virtual float GetScaleOnMap() const;

	/** Sets the client representations compass view distance directly. It doesn't change the connected actors status so this is only for local updates to avoid waiting for replicated value */
	void SetLocalCompassViewDistance( ECompassViewDistance compassViewDistance );
	
	virtual bool CanBeHighlighted() const;
	
	virtual void SetHighlighted( bool highlighted );

	virtual bool IsHighlighted() const;
	virtual bool IsHighlighted( FLinearColor& out_highlightColor, bool& out_HighlightByLocalPlayer ) const;

	virtual class UFGHighlightedMarker* CreateHighlightedMarker( UObject* owner );

	/** Returns the material to use to play the compass visual effect animation for this representation. Nullptr means no visual effect */
	UFUNCTION(BlueprintCallable, Category = "Representation")
	virtual UMaterialInterface* GetRepresentationCompassEffectMaterial() const { return nullptr; }

	/** Returns the size of the compass effect in screen space units */
	UFUNCTION(BlueprintCallable, Category = "Representation")
	virtual FVector2f GetRepresentationCompassEffectSize() const;
	
	/**
	 * Called each tick to update the visual effect material for this representation on the compass, if visual effect material is set for this representation
	 * Return true to allow the special effect to be visible, return false to hide it until next tick
	 */
	UFUNCTION(BlueprintCallable, Category = "Representation")
	virtual bool UpdateRepresentationCompassEffectMaterial( class UMaterialInstanceDynamic* compassMaterialInstance, APlayerController* ownerPlayerController, float distanceToPlayer, float totalTime ) { return true; }

	UFUNCTION( BlueprintPure, Category = "Representation" )
	bool IsHidden() const { return mIsHidden; }
	void SetHidden( bool isHidden );

	FORCEINLINE FGuid GetRepresentationID() const { return mRepresentationID; }
	FORCEINLINE uint64 GetRepresentationChangelist() const { return mRepresentationChangelist; }

	/** Returns a cast of outer */
	class AFGActorRepresentationManager* GetActorRepresentationManager() const;
protected:

	/** Called before the representation properties are updated by the representation manager replication pass */
	virtual void PreRepresentationReplication();
	/** Called to notify the representation that one of it's object properties failed to deserialize because the referenced object has not been replicated to the client yet. */
	virtual void NotifyRepresentationUnmappedObjectReference( const TDoubleLinkedList<FProperty*>& PropertyChain, const FNetworkGUID& ObjectGUID );
	/** Called after the representation properties are updated by the representation manager replication pass */
	virtual void PostRepresentationReplication();
	
	/** Updates properties of this actor representation by polling the real actor properties. Should only be called on server */
	virtual void UpdateActorRepresentationFromInterface( class IFGActorRepresentationInterface* representation, bool bFireDelegates );
	/** Called when any of the properties relevant to this representation are updated, or when the update is explicitly requested by calling UFGActorRepresentationManager::UpdateRepresentationOfActor */
	virtual void UpdateActorRepresentation();
	/** Updates representation's actor location and rotation from the actor */
	virtual void UpdateActorLocationAndRotation();
	/** Called to update the location from the replication data */
	virtual void UpdateActorLocationAndRotationFromReplication( const FVector& newActorLocation, const FRotator& newActorRotation );
	
	friend AFGActorRepresentationManager;
	friend struct FFGActorRepresentationReplicator;

	/** This actor representation is locally created */
	bool mIsLocal;

	/** This actor representation resides on a client, used to determine if we want the replicated property or get it from the actor itself. 
	This is used on properties that are replicated with notification */
	bool mIsOnClient;

	/** This is the real actor that this representation represents */
	UPROPERTY( Replicated )
	AActor* mRealActor;

	/** This is the actor location */
	UPROPERTY( Replicated )
	FVector mActorLocation;

	/** This is the actor location for local representations which uses a regular FVector to get the Z value as well. Used for resource nodes. For Local Use Only */
	FVector mLocalActorLocation;

	/** This is the actor rotation */
	UPROPERTY( Replicated )
	FRotator mActorRotation;

	/** If the actor is static or can be moved */
	UPROPERTY( Replicated )
	bool mIsStatic;

	/** This is the texture to show for this actor representation */
	UPROPERTY( Replicated )
	UTexture2D* mRepresentationTexture;

	/** This is the texture to show for this actor representation */
	UPROPERTY( Replicated )
	UMaterialInterface* mRepresentationCompassMaterial;
	
	/** This is the text to show for this actor representation */
	UPROPERTY( Replicated )
	FText mRepresentationText;

	/** This is the color used for the representation of this actor */
	UPROPERTY( Replicated )
	FLinearColor mRepresentationColor;	

	/** This helps define how this actor representation should be presented */
	UPROPERTY( Replicated )
	ERepresentationType mRepresentationType;

	UPROPERTY( Replicated )
	EFogOfWarRevealType mFogOfWarRevealType;

	UPROPERTY( Replicated )
	float mFogOfWarRevealRadius;
	
	/** If this should be shown in the compass or not*/
	UPROPERTY( Replicated )
	bool mShouldShowInCompass;

	/** If this should be shown on the map or not*/
	UPROPERTY( Replicated )
	bool mShouldShowOnMap;

	/** If this should be hidden in the map and compass. Still showned in object list in map. Used for pawns that are in a vehicle/train */
	UPROPERTY( Replicated )
	bool mIsHidden;

	/** How far away this representation should be shown in the compass */
	UPROPERTY( Replicated )
	ECompassViewDistance mCompassViewDistance;

	/** True if background color is considered to be primary color, false if it should be secondary color */
	UPROPERTY( EditDefaultsOnly, Category = "Representation" )
	bool mBackgroundIsPrimaryColor{true};

	/** True if GetRealActorLocation is allowed to be called on the client when mRealActor is available. In some cases even if the real actor is available, it's location information might not be available on the client */
	UPROPERTY( EditDefaultsOnly, Category = "Representation" )
	bool mAllowRealActorLocationOnClient{true};
	
	bool mIsLocallyControlledPawn;

	/** Unique ID of this representation. Assigned when the representation is replicated on the server, and when it is created from replicated data on the client. */
	FGuid mRepresentationID{};
	/** Current version of this representation. Incremented each time representation changes. Only relevant on server. */
	uint64 mRepresentationChangelist{0};

	FNetworkGUID mRealActorNetworkGUID;
	bool mCachedShouldShowInCompass;
	bool mCachedShouldShowOnMap;

	/** Last time we updated world location/rotation. Used for smoothing location updates on the client */
	float mLastLocationRotationUpdateWorldTime{0.0f};
	FVector mLastActorLocation;
};
