// Copyright 2016-2018 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "Array.h"
#include "GameFramework/Actor.h"
#include "UObject/Class.h"

#include "CoreMinimal.h"
#include "FGMaterialEffectComponent.h"
#include "ItemAmount.h"
#include "FGMaterialEffect_Build.generated.h"


/**
 * Material effect for building.
 */
UCLASS( Abstract )
class FACTORYGAME_API UFGMaterialEffect_Build : public UFGMaterialEffectComponent
{
	GENERATED_BODY()
public:
	UFGMaterialEffect_Build();

	//virtual void GetLifetimeReplicatedProps( TArray< FLifetimeProperty >& OutLifetimeProps ) const override;

	/** Call these before RegisterComponent. If component is registered these have no effect. */
	void SetInstigator( class AActor* instigator );
	void SetCost( TArray< FItemAmount > cost );
	void SetSpeed( float speed );

	/** Who build the thing. */
	UFUNCTION( BlueprintPure )
	FORCEINLINE AActor* GetInstigator() const { return mInstigator; }

	/** How much did the thing cost. */
	UFUNCTION( BlueprintCallable, BlueprintPure = false )
	FORCEINLINE TArray< FItemAmount > GetCost() const { return mCost; }

	/** How fast is the thing built. [cm/s] */
	UFUNCTION( BlueprintPure )
	FORCEINLINE float GetSpeed() const { return mSpeed; }

private:
	/** Who built this */
	UPROPERTY(  )
	class AActor* mInstigator;
	/** How much did this cost */
	UPROPERTY(  )
	TArray< FItemAmount > mCost;
	/** The speed of this effect. */
	UPROPERTY()
	float mSpeed;

public:
	FORCEINLINE ~UFGMaterialEffect_Build() = default;
};
