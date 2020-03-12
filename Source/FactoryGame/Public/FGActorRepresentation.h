// Copyright 2016 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "Array.h"
#include "GameFramework/Actor.h"
#include "UObject/Class.h"

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
	RT_VehicleDockingStation	UMETA( DisplayName = "VehicleDockingStation" )
};

UENUM( BlueprintType )
enum class EFogOfWarRevealType : uint8
{
	FOWRT_None			UMETA( DisplayName = "None" ),
	FOWRT_Static		UMETA( DisplayName = "Static" ),
	FOWRT_Intermittent	UMETA( DisplayName = "Intermittent" ),
	FOWRT_Dynamic		UMETA( DisplayName = "Dynamic" )
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
	/** Mark this class as supported for networking */
	virtual bool IsSupportedForNetworking() const override;
	
	/** Decide on what properties to replicate */
	void GetLifetimeReplicatedProps( TArray<FLifetimeProperty>& OutLifetimeProps ) const override;

	/** Get the Real actor we represent, might not be relevant on client */
	UFUNCTION( BlueprintPure, Category = "Representation" )
	FORCEINLINE AActor* GetRealActor() const { return mRealActor; }

	/** If this actor representation is temporary or not */
	UFUNCTION( BlueprintPure, Category = "Representation" )
	FORCEINLINE bool GetIsTemporary() const { return mIsTemporary; }
	
	/** Is this the represented actor static or not */
	UFUNCTION( BlueprintPure, Category = "Representation" )
	FORCEINLINE bool IsActorStatic() const { return mIsStatic; }

	/** Get the location of the represented actor */
	UFUNCTION( BlueprintPure, Category = "Representation" )
	FVector GetActorLocation() const;

	/** Get the rotation of the represented actor */
	UFUNCTION( BlueprintPure, Category = "Representation" )
	FRotator GetActorRotation() const;

	/** This is the image to render in the compass */
	UFUNCTION( BlueprintPure, Category = "Representation" )
	class UTexture2D* GetRepresentationTexture() const;

	/** This is the text to render in the compass */
	UFUNCTION( BlueprintPure, Category = "Representation" )
	FText GetRepresentationText() const;

	/** This is the color to render in the compass */
	UFUNCTION( BlueprintPure, Category = "Representation" )
	FLinearColor GetRepresentationColor() const;

	UFUNCTION( BlueprintPure, Category = "Representation" )
	ERepresentationType GetRepresentationType() const;

	/** If this should be shown in the compass or not*/
	UFUNCTION( BlueprintPure, Category = "Representation" )
	bool GetShouldShowInCompass() const;

	/** If this should be shown on the map or not*/
	UFUNCTION( BlueprintPure, Category = "Representation" )
	bool GetShouldShowOnMap() const;

	UFUNCTION( BlueprintPure, Category = "Representation" )
	EFogOfWarRevealType GetFogOfWarRevealType() const;

	UFUNCTION( BlueprintPure, Category = "Representation" )
	float GetFogOfWarRevealRadius() const;

	void SetIsOnClient( bool onClient );

	UFUNCTION( BlueprintPure, Category = "Representation" )
	ECompassViewDistance GetCompassViewDistance() const;

	/** Sets the client representations compass view distance directly. It doesn't change the connected actors status so this is only for local updates to avoid waiting for replicated value */
	void SetLocalCompassViewDistance( ECompassViewDistance compassViewDistance );
	
protected:

	/** Returns a cast of outer */
	class AFGActorRepresentationManager* GetActorRepresentationManager();

	/** This updates the location for this actor representation */
	void UpdateLocation();

	/** This updates the rotation for this actor representation */
	void UpdateRotation();

	/** Updates the representation text for this actor */
	void UpdateRepresentationText();

	/** Updates the representation texture for this actor */
	void UpdateRepresentationTexture();

	/** Updates the color of the representation for this actor */
	void UpdateRepresentationColor();

	/** Updates if this should be shown in the compass or not */
	void UpdateShouldShowInCompass();

	/** Updates if this should be shown on the map or not */
	void UpdateShouldShowOnMap();

	/** Updates the fog of war reveal type */
	void UpdateFogOfWarRevealType();

	/** Updates the fog of war reveal radius */
	void UpdateFogOfWarRevealRadius();

	/** Updates the view distance for this actor on the compass */
	void UpdateCompassViewDistance();

	/** Repnotifies */
	UFUNCTION()
	void OnRep_ShouldShowInCompass();

	UFUNCTION()
	void OnRep_ShouldShowOnMap();

	UFUNCTION()
	void OnRep_ActorRepresentationUpdated();

private:
	friend AFGActorRepresentationManager;

	/** This actor representation is just local and should not be shown to other players */
	bool mIsLocal;

	/** This actor representation resides on a client, used to determine if we want the replicated property or get it from the actor itself. 
	This is used on properties that are replicated with notification */
	bool mIsOnClient;

	/** This is the real actor that this representation represents */
	UPROPERTY( Replicated )
	AActor* mRealActor;

	/** This is the actor location */
	UPROPERTY( Replicated )
	FVector_NetQuantize mActorLocation;

	/** This is the actor rotation */
	UPROPERTY( Replicated )
	FRotator mActorRotation;

	/** If the actor is static or can be moved */
	UPROPERTY( Replicated )
	bool mIsStatic;

	/** This is the texture to show for this actor representation */
	UPROPERTY( ReplicatedUsing = OnRep_ActorRepresentationUpdated )
	UTexture2D* mRepresentationTexture;

	/** This is the text to show for this actor representation */
	UPROPERTY( ReplicatedUsing = OnRep_ActorRepresentationUpdated )
	FText mRepresentationText;

	/** This is the color used for the representation of this actor */
	UPROPERTY( ReplicatedUsing = OnRep_ActorRepresentationUpdated )
	FLinearColor mRepresentationColor;	

	/** This helps define how this actor representation should be presented */
	UPROPERTY( Replicated )
	ERepresentationType mRepresentationType;

	UPROPERTY( ReplicatedUsing = OnRep_ActorRepresentationUpdated )
	EFogOfWarRevealType mFogOfWarRevealType;

	UPROPERTY( ReplicatedUsing = OnRep_ActorRepresentationUpdated )
	float mFogOfWarRevealRadius;

	/** If this representation should be removed when lifetime < 0.0f */
	bool mIsTemporary;

	/** How long this representation has to live */
	float mLifeTime;

	/** If this should be shown in the compass or not*/
	UPROPERTY( ReplicatedUsing = OnRep_ShouldShowInCompass )
	bool mShouldShowInCompass;

	/** If this should be shown on the map or not*/
	UPROPERTY( ReplicatedUsing = OnRep_ShouldShowOnMap )
	bool mShouldShowOnMap;

	/** How far away this representation should be shown in the compass */
	UPROPERTY( ReplicatedUsing = OnRep_ActorRepresentationUpdated )
	ECompassViewDistance mCompassViewDistance;

public:
	FORCEINLINE ~UFGActorRepresentation() = default;
};
