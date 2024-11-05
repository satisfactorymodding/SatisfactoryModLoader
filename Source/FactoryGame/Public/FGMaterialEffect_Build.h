// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "FGMaterialEffectComponent.h"
#include "InstanceData.h"
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
	void SetTransform( const FTransform& transform ) { mTransform = transform; }
	FORCEINLINE void SetUsingInstanceData() { mIsUsingInstanceData = true; }
	
	/** Who build the thing. */
	UFUNCTION( BlueprintPure )
	FORCEINLINE AActor* GetInstigator() const { return mInstigator; }

	/** How much did the thing cost. */
	UFUNCTION( BlueprintCallable, BlueprintPure = false )
	FORCEINLINE TArray< FItemAmount > GetCost() const { return mCost; }

	/** How fast is the thing built. [cm/s] */
	UFUNCTION( BlueprintPure )
	FORCEINLINE float GetSpeed() const { return mSpeed; }

	UFUNCTION( BlueprintPure )
	FORCEINLINE FTransform GetTransform() const { return mTransform; }

	UFUNCTION( BlueprintPure )
	FORCEINLINE bool IsUsingInstanceData() const { return mIsUsingInstanceData; }
	
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

	UPROPERTY()
	bool mIsUsingInstanceData;

	/* Transform, in case we are using a lightweight instance.*/
	UPROPERTY()
	FTransform mTransform;
};
