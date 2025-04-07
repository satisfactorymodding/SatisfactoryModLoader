// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"
#include "FGBuildablePoleBase.h"
#include "FGBuildablePoleStackable.generated.h"

/**
 * 
 */
UCLASS()
class FACTORYGAME_API AFGBuildablePoleStackable : public AFGBuildablePoleBase
{
	GENERATED_BODY()
public:
	AFGBuildablePoleStackable();

	virtual void GetLifetimeReplicatedProps( TArray< FLifetimeProperty >& OutLifetimeProps ) const override;

	UFUNCTION( BlueprintPure, Category = "Stackable Pole" )
	FORCEINLINE float GetStackHeight() const { return mStackHeight; }

private:
	UPROPERTY( EditDefaultsOnly, Category = "Stackable Pole" )
	float mStackHeight;
};
