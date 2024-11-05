// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

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
		MarkerID( 255 ),
		Location( 0,0,0 ),
		Name( "" ),
		MapMarkerType( ERepresentationType::RT_Default ),
		IconID( 0 ),
		Color( FLinearColor::Black ),
		Scale( 1.0 ),
		CompassViewDistance( ECompassViewDistance::CVD_Off ),
		CreatedByLocalPlayer( false )
	{
	};

	// 255 means empty/available
	UPROPERTY( SaveGame ) 
	uint8 MarkerID;
	
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

	// Used to know if this map marker was created locally. Useful for map representation.
	// Will only be true for the local session where the marker was created.
	TOptional<bool> CreatedByLocalPlayer;

	bool HasValidID() const { return MarkerID != 255; }
	void InvalidateMapMarker() { MarkerID = 255; } 

	bool operator==(const FMapMarker& other) const;

	bool operator!=(const FMapMarker& other) const;
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
	AActor* mHitActor;
};


UCLASS()
class FACTORYGAME_API UFGHighlightedMarker : public UObject, public IFGSaveInterface
{
	GENERATED_BODY()
public:
	UPROPERTY( Transient )
	class UFGActorRepresentation* mActorRepresentation;

	UPROPERTY( Transient )
	UStaticMeshComponent* mStaticMeshComponent;

	UPROPERTY( Transient )
	class UNiagaraComponent* mNiagaraComponent;

	virtual bool ShouldSave_Implementation() const override { return true; }
};

UCLASS()
class FACTORYGAME_API UFGHighlightedMarker_Actor : public UFGHighlightedMarker
{
	GENERATED_BODY()
public:
	UPROPERTY( SaveGame )
	UObject* mActor;
};

UCLASS()
class FACTORYGAME_API UFGHighlightedMarker_MapMarker : public UFGHighlightedMarker
{
	GENERATED_BODY()
public:	
	UPROPERTY( SaveGame )
	FMapMarker mMapMarker;
};

