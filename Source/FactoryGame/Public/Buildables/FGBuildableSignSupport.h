// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"
#include "FGBuildablePole.h"
#include "FGBuildableSignSupport.generated.h"

/**
 * Simple pole support class for standalone signs. Very similar to the BuildablePole but excluding the overhead of any snap components
 * Includes ability to change the pole scale on the X/Y for variable thickness poles
 */
UCLASS()
class FACTORYGAME_API AFGBuildableSignSupport : public AFGBuildablePole_NoCustomization
{
	GENERATED_BODY()
public:
	AFGBuildableSignSupport();
	virtual void GetLifetimeReplicatedProps( TArray< FLifetimeProperty >& OutLifetimeProps ) const override;

	/** Sets an optional scale to scale the x/y values of the pole by */
	virtual void SetPoleScale( const FVector2D& poleScale );
	virtual void OnBuildEffectActorFinished() override;

	virtual bool CanBeSampled_Implementation() const override;

	const FVector2D& GetPoleScale() const { return mPoleScale; }

private:
	UFUNCTION()
	void OnRep_PoleScale();
	
private:
	// 2D scale for pole meshes
	UPROPERTY( ReplicatedUsing = OnRep_PoleScale )
	FVector2D mPoleScale;
};
