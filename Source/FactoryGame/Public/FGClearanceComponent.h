// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "FGClearanceComponent.generated.h"

/**
 * Generic box clearance component. Used for snapping and simple overlap checks.
 */
UCLASS( ClassGroup = ( Custom ), meta = ( BlueprintSpawnableComponent ) )
class FACTORYGAME_API UFGClearanceComponent : public UBoxComponent
{
	GENERATED_BODY()
public:
	UFGClearanceComponent();

	FORCEINLINE bool GetIsSoftClearance() const { return mIsSoftClearance; }
	FORCEINLINE void SetIsSoftClearance( bool isSoft ) { mIsSoftClearance = isSoft; } 

protected:
	// Whether or not this clearance box is soft, which means it will not block building, just warn the player that there might be risk of clipping.
	UPROPERTY( EditDefaultsOnly, Category = "Clearance")
	bool mIsSoftClearance;
};

/**
* Complex clearance component. Used for overlap checks.
*/
UCLASS( ClassGroup = ( Custom ), meta = ( BlueprintSpawnableComponent ) )
class FACTORYGAME_API UFGComplexClearanceComponent : public UStaticMeshComponent
{
	GENERATED_BODY()
public:
	UFGComplexClearanceComponent();
};
