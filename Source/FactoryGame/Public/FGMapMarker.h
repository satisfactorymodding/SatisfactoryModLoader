// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"
#include "FGActorRepresentation.h"
#include "UI/FGMapWidget.h"
#include "FGSaveInterface.h"
#include "FGMapMarker.generated.h"

USTRUCT( BlueprintType )
struct FACTORYGAME_API FMapMarker
{
	GENERATED_BODY()

	FMapMarker() :
		MarkerID_DEPRECATED( 0 ),
		MarkerGUID( FGuid() ),
		Location( 0,0,0 ),
		Name( TEXT("") ),
		MapMarkerType( ERepresentationType::RT_Default ),
		IconID( 0 ),
		Color( FLinearColor::Black ),
		Scale( 1.0 ),
		CompassViewDistance( ECompassViewDistance::CVD_Off ),
		LastEditedBy( FPlayerInfoHandle() )
	{
	};

	// Legacy Marker ID saved by the old save system
	UPROPERTY(SaveGame) 
	uint8 MarkerID_DEPRECATED;

	// A unique ID of this map marker
	UPROPERTY( SaveGame, BlueprintReadWrite ) 
	FGuid MarkerGUID;
	
	UPROPERTY( SaveGame, BlueprintReadWrite )
	FVector_NetQuantize Location;
	
	UPROPERTY( SaveGame, BlueprintReadWrite )
	FString Name;

	UPROPERTY( SaveGame, BlueprintReadWrite )
	FString CategoryName;

	UPROPERTY( SaveGame, BlueprintReadWrite )
	ERepresentationType MapMarkerType;

	UPROPERTY( SaveGame, BlueprintReadWrite )
	int32 IconID;
	
	UPROPERTY( SaveGame, BlueprintReadWrite )
	FLinearColor Color;
	
	UPROPERTY( SaveGame, BlueprintReadWrite )
	float Scale;

	UPROPERTY( SaveGame, BlueprintReadWrite )
	ECompassViewDistance CompassViewDistance;

	UPROPERTY( SaveGame, BlueprintReadWrite )
	FPlayerInfoHandle LastEditedBy;

	/** ID of the player that created this marker. This is not saved, and is only used to associate created markers with their authors in session */
	UPROPERTY()
	FGuid CreatedByPlayerID;
	// static_assert(false, "check if this is needed or the above is sufficient post merge once in IDE");
	
	bool HasValidID() const { return MarkerGUID.IsValid(); }
	void InvalidateMapMarker() { MarkerGUID.Invalidate(); } 

	bool operator==(const FMapMarker& other) const;
};

// Simple object wrapper for a map marker so we can put it as the interact object for an interact widget
UCLASS( Blueprintable )
class FACTORYGAME_API UFGMapMarkerWrapper : public UObject
{
	GENERATED_BODY()
public:

	UFUNCTION( BlueprintPure, Category = "Map" )
	FMapMarker GetMapMarker() const { return mMapMarker; }

	UFUNCTION( BlueprintPure, Category = "Map" )
	bool GetIsNewMarker() const { return mIsNewMarker; }

	UFUNCTION( BlueprintPure, Category = "Map" )
	AActor* GetHitActor() const { return mHitActor; }

	bool mIsNewMarker;
	FMapMarker mMapMarker;

	UPROPERTY( Transient )
	TObjectPtr<AActor> mHitActor;
};


UCLASS()
class FACTORYGAME_API UFGHighlightedMarker : public UObject, public IFGSaveInterface
{
	GENERATED_BODY()
public:
	UPROPERTY( Transient )
	TObjectPtr<class UFGActorRepresentation> mActorRepresentation;

	UPROPERTY( Transient )
	TObjectPtr<UStaticMeshComponent> mStaticMeshComponent;

	UPROPERTY( Transient )
	TObjectPtr<class UNiagaraComponent> mNiagaraComponent;

	virtual bool ShouldSave_Implementation() const override { return true; }
};

UCLASS()
class FACTORYGAME_API UFGHighlightedMarker_Actor : public UFGHighlightedMarker
{
	GENERATED_BODY()
public:
	UPROPERTY( SaveGame )
	TObjectPtr<UObject> mActor;
};

UCLASS()
class FACTORYGAME_API UFGHighlightedMarker_MapMarker : public UFGHighlightedMarker
{
	GENERATED_BODY()
public:	
	UPROPERTY( SaveGame )
	FMapMarker mMapMarker;
};
