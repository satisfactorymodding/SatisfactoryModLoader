// Copyright 2016-2018 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "GameFramework/Actor.h"
#include "UObject/Class.h"

#include "CoreMinimal.h"
#include "FGBuildableStorage.h"
#include "FGCentralStorageContainer.generated.h"

/**
 * Storage container connected to the central storage interface.
 */
UCLASS()
class FACTORYGAME_API AFGCentralStorageContainer : public AFGBuildableStorage
{
	GENERATED_BODY()
public:
	AFGCentralStorageContainer();

	// Begin AActor interface
	virtual void BeginPlay() override;
	virtual void EndPlay( const EEndPlayReason::Type endPlayReason ) override;
	// End AActor interface
private:
	// Recalled if the storage subsystem isn't created
	UFUNCTION()
	void AddToCentralStorageSubsystem();
};
