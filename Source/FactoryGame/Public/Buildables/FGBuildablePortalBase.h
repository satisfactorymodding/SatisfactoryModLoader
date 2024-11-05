// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "FGActorRepresentationInterface.h"
#include "FGBuildableFactory.h"
#include "UObject/Object.h"
#include "FGBuildablePortalBase.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FOnLinkedPortalChanged, class AFGBuildablePortalBase*, newLinkedPortal );
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FOnPortalTraversableChanged, bool, isNowTraversable );
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FOnPortalHeatUpStateChanged, bool, isNowHeatedUp );

USTRUCT()
struct FACTORYGAME_API FFGPortalCachedFactoryTickData
{
	GENERATED_BODY()
	
	/** Cached GetTargetPowerConsumption() of this building. Updated on Factory_Tick while holding the lock */
	UPROPERTY( SaveGame )
	float mCachedPowerConsumption;
	
	/** Cached mIsProducing of this building. Updated on Factory_Tick while holding the lock */
	UPROPERTY( SaveGame )
	bool mCachedIsProducing;
	
	/** Cached mHasPower of this building. Updated on Factory_Tick while holding the lock */
	UPROPERTY( SaveGame )
	bool mCachedHasPower;

	/** For main nodes, value of mHeatUpComplete */
	UPROPERTY( SaveGame )
	bool mCachedHeatUpComplete;
	
	/** For main nodes, value of mCurrentHeatUpProgress */
	UPROPERTY( SaveGame )
	float mCachedCurrentHeatUpProgress;

	FFGPortalCachedFactoryTickData();
};

UENUM( BlueprintType )
enum class EFGPortalLinkCandidateState : uint8
{
	Invalid UMETA( DisplayName = "Invalid" ),
	Available UMETA( DisplayName = "Available" ),
	AlreadyLinked UMETA( DisplayName = "Already Linked" ),
	NotMasterPortal UMETA( DisplayName = "Not Master Portal" ),
	NotSatellitePortal UMETA( DisplayName = "Not Satellite Portal" ),
	HasNoPower UMETA( DisplayName = "Has No Power" ),
	ThisPortal UMETA( DisplayName = "This Portal (Self)" )
};

USTRUCT( BlueprintType )
struct FACTORYGAME_API FFGPortalLinkCandidate
{
	GENERATED_BODY()

	UPROPERTY( BlueprintReadOnly, Category = "Portal" )
	class AFGBuildablePortalBase* Portal;

	UPROPERTY( BlueprintReadOnly, Category = "Portal" )
	EFGPortalLinkCandidateState State;

	FFGPortalLinkCandidate();
};

/**
 * Base class for portals and portal satellite nodes
 */
UCLASS( Abstract )
class FACTORYGAME_API AFGBuildablePortalBase : public AFGBuildableFactory, public IFGActorRepresentationInterface
{
	GENERATED_BODY()
public:
	AFGBuildablePortalBase();
	
	// Begin AActor interface
	virtual void GetLifetimeReplicatedProps( TArray< FLifetimeProperty >& OutLifetimeProps ) const override;
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	// End AActor interface

	// Begin AFGBuildableFactory interface
	virtual float GetProducingPowerConsumptionBase() const final override;
	virtual void Factory_Tick(float dt) override;
	// End AFGBuildableFactory interface

	// Begin IFGDismantleInterface
	virtual void Dismantle_Implementation() override;
	// End IFGDismantleInterface

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
	// End IFGActorRepresentationInterface
	
	/**
	 * Makes a link between this portal and the other one, making them have a shared inventory
	 */
	UFUNCTION( BlueprintCallable, BlueprintAuthorityOnly, Category = "Portal" )
	void MakeLinkToPortal( AFGBuildablePortalBase* otherPortal );
	
	/**
	 * Disconnects this portal from the other one, clearing the mConnectedPortal on both portals
	 */
	UFUNCTION( BlueprintCallable, BlueprintAuthorityOnly, Category = "Portal" )
	void DisconnectLinkedPortal();

	/**
	 * Gathers a list of all portal buildings that do not have a portal linked to them yet but
	 * satisfy the power and idle power consumption requirements
	 */
	UFUNCTION( BlueprintCallable, Category = "Portal" )
	void PopulatePortalLinkCandidates( TArray<FFGPortalLinkCandidate>& out_linkCandidates ) const;
	
	/**
	 * Returns the portal this portal is connected to.
	 * The delegate mOnLinkedPortalChange will be triggered if it changes.
	 **/
	UFUNCTION( BlueprintPure, Category = "Portal" )
	FORCEINLINE AFGBuildablePortalBase* GetLinkedPortal() const { return mLinkedPortal; }
	
	/**
	 * Returns the transform of the portal plane in the world space
	 * Used for momentum conservation when going through portals
	 */
	UFUNCTION( BlueprintNativeEvent, BlueprintPure, Category = "Portal" )
	void GetPortalSurfaceTransform( FTransform& out_portalTransform ) const;
	
	/**
	 * Called when the player has started the teleportation from one portal to another
	 * Only called on server side!!!
	 */
	UFUNCTION( BlueprintNativeEvent, Category = "Portal" )
	void OnPlayerTeleportBegin( AFGCharacterPlayer* player, AFGBuildablePortalBase* toPortal, float totalTravelDistance );
	
	/**
	 * Called when player teleportation has been complete from a source portal to this portal
	 * Only called on the server side!!!
	 */
	UFUNCTION( BlueprintNativeEvent, Category = "Portal" )
	void OnPlayerTeleportComplete( AFGCharacterPlayer* player, AFGBuildablePortalBase* fromPortal, float totalTravelDistance );

	/**
	 * Returns the current name of the portal
	 * Will only return valid values on the client when the UI is open
	 */
	UFUNCTION( BlueprintPure, Category = "Portal" )
	FORCEINLINE FText GetPortalName() const { return mPortalName; }

	/** Updates the current portal name */
	UFUNCTION( BlueprintCallable, BlueprintAuthorityOnly, Category = "Portal" )
	void SetPortalName( const FText& inPortalName );

	/** Returns true if we are traversable, e.g. have heated up and have  */
	UFUNCTION( BlueprintPure, Category = "Portal" )
	FORCEINLINE bool IsPortalTraversable() const { return mIsPortalTraversable; }

	/**
	 * Returns the estimated power consumption over 1 second for when the player
	 * teleports from or to this portal.
	 */
	UFUNCTION( BlueprintPure, Category = "Portal" )
	float GetEstimatedPowerConsumptionForTeleport() const;

	/**
	 * Calculates power consumption per teleportation from this portal
	 * to another portal away from this one at the specified distance
	 */
	UFUNCTION( BlueprintPure, Category = "Portal" )
	float CalculatePowerConsumptionForDistance( float distance ) const;

	/** Returns the cached data safe to use during Factory_Tick of other buildables */
	FFGPortalCachedFactoryTickData GetCachedFactoryTickData_ThreadSafe();

	/** Called by the logic on both portals when our heat up sequence has been completed */
	UFUNCTION( BlueprintImplementableEvent, Category = "Portal", meta = (DisplayName = "OnHeatUpComplete") )
	void ReceiveHeatUpComplete();
public:
	/**
	 * Called when the portal currently linked with this one changes
	 * That means the currently active shared inventory pointer will change as well
	 * The provided new portal value is the same value that GetLinkedPortal returns
	 */
	UPROPERTY( BlueprintAssignable, Category = "Portal" )
	FOnLinkedPortalChanged mOnLinkedPortalChanged;

	/**
	 * Called when the portal has become traversable and is open for transfer with the other portal
	 * At this point the portals will share the power grid and be able to use each other's inventories
	 */
	UPROPERTY( BlueprintAssignable, Category = "Portal" )
	FOnPortalTraversableChanged mOnPortalTraversableChanged;

	/**
	 * Called when the buildable has completed or reset the heat up stage
	 * After the buildable has fully completed the heat up, it's inventory will be shared with the other portal,
	 * and their power grids will be connected as well
	 */
	UPROPERTY( BlueprintAssignable, Category = "Portal" )
	FOnPortalHeatUpStateChanged mOnHeatUpStateChanged;

	UPROPERTY(EditDefaultsOnly)
	UMaterialInterface* mCompassMaterialInstance;

protected:

	void Factory_UpdatePowerConsumption() const;
	void Factory_UpdateMaxPowerConsumption() const;
	virtual float GetMaximumPowerConsumption() const;
	virtual void FillCachedFactoryTickData( FFGPortalCachedFactoryTickData& out_cachedData ) const;

	virtual float GetProducingPowerConsumptionBase_ForPortal() const;
	virtual EFGPortalLinkCandidateState CanLinkToPortal( AFGBuildablePortalBase* otherPortal ) const;

	void OnPlayerTeleportOverDistance( float distance );
	void MakePortalTraversable();
	void ResetPortalTraversable();

	virtual void SetPortalTraversableInternal( bool isNowTraversable );
	virtual void OnLinkedPortalDisconnected();
	virtual void OnMadeLinkToPortal( AFGBuildablePortalBase* otherPortal );
	
	UFUNCTION()
	virtual void OnRep_LinkedPortal();
	UFUNCTION()
	virtual void OnRep_PortalTraversable();
public:
	// [ZolotukhinN:08/06/2023] Moved these from FGCharacterPlayer to the buildable, because they keep getting overwritten by the merges to Char_Player
	
	/** Portal travel time based on the distance travelled (in kms) */
	UPROPERTY( EditDefaultsOnly, Category = "Portal" )
	UCurveFloat* mPortalTravelTimeOverDistance;

	UPROPERTY( EditDefaultsOnly, Category = "Portal" )
	float mMaxPortalTravelTime;
private:
	/** The portal we are currently linked to */
	UPROPERTY( SaveGame, ReplicatedUsing=OnRep_LinkedPortal, EditInstanceOnly, Category = "Portal" )
	AFGBuildablePortalBase* mLinkedPortal;

	/** True if we have opened the connection after 2 portals have heated up and are hosting a shared inventory now */
	UPROPERTY( SaveGame, ReplicatedUsing=OnRep_PortalTraversable, VisibleInstanceOnly, Category = "Portal" )
	bool mIsPortalTraversable;

	/** Power consumption the portal will have over the span of 1 second after player teleports, based on the distance travelled in kms */
	UPROPERTY( EditDefaultsOnly, Category = "Portal", meta = ( ClampMin = "0.0" ) )
	UCurveFloat* mPowerConsumptionPerTeleportOverDistance;
	
	/** Texture used for the portal representation on the map */
	UPROPERTY( EditDefaultsOnly, Category = "Representation" )
	class UTexture2D* mActorRepresentationTexture;

	/** Color used for the portal representation on the map */
	UPROPERTY( EditDefaultsOnly, Category = "Representation" )
	FLinearColor mActorRepresentationColor;

	UPROPERTY( EditDefaultsOnly, Category = "Representation" )
	ECompassViewDistance mActorRepresentationViewDistance;

	UPROPERTY( EditDefaultsOnly, Category = "Representation" )
	float mActorRepresentationFogOfWarRevealRadius;

	/** Name that this portal has, editable by the user, but you can set the default value here */
	UPROPERTY( EditDefaultsOnly, SaveGame, Replicated, Category = "Representation" )
	FText mPortalName;

	/** True if we teleported the player last frame and need to spike the energy consumption */
	UPROPERTY( SaveGame )
	float mTeleportPowerConsumptionTimeLeft;

	/** Power consumption that we are currently having after the player teleport */
	UPROPERTY( SaveGame )
	float mTeleportPowerConsumption;

	/** Critical section guarding mCachedProductionData */
	FCriticalSection mCachedFactoryTickDataCriticalSection;

	/** Cached production data of this building. Updated on Factory_Tick while holding the lock */
	UPROPERTY( SaveGame )
	FFGPortalCachedFactoryTickData mCachedFactoryTickData;
};
