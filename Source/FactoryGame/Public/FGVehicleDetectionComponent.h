// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "Math/GenericOctreePublic.h"
#include "FGVehicleDetectionComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FACTORYGAME_API UFGVehicleDetectionComponent : public UBoxComponent
{
	GENERATED_BODY()
public:
	UFGVehicleDetectionComponent();

	// Begin AActorComponent interface
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	// End AActorComponent interface

	/** Note: this is only computed on server. On client this will always return false */
	FORCEINLINE bool IsOverlappingAnyVehicles() const { return mIsOverlappingAnyVehicles; }

	DECLARE_MULTICAST_DELEGATE_OneParam( FOnOverlappingAnyVehiclesChanged, bool );
	FOnOverlappingAnyVehiclesChanged OnOverlappingAnyVehiclesChanged;

	void Private_SetIsOverlappingAnyVehicles(bool newIsOverlappingAnyVehicles);
	FOctreeElementId2 mPrivateOctreeElementId;
	uint64 mPrivateLastOverlapCheckFrameIndex{0};
protected:
	bool mIsOverlappingAnyVehicles{false};
};
