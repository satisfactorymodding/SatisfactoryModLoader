// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "FGBuildablePoleBase.h"
#include "FGBuildableSignSupport.generated.h"

/**
 * Simple pole support class for standalone signs. Very similar to the BuildablePole but excluding the overhead of any snap components
 * Includes ability to change the pole scale on the X/Y for variable thickness poles
 */
UCLASS()
class FACTORYGAME_API AFGBuildableSignSupport : public AFGBuildablePoleBase
{
	GENERATED_BODY()
	

public:
	AFGBuildableSignSupport();

	// Begin AActor interface
	virtual void GetLifetimeReplicatedProps( TArray< FLifetimeProperty >& OutLifetimeProps ) const override;
	virtual void BeginPlay() override;
	// End AActor interface


	/** Set the poles height */
	FORCEINLINE void SetPoleHeight( float height ) { mHeight = height; }

	/** Sets an optional scale to scale the x/y values of the pole by */
	virtual void SetPoleScale( FVector2D poleScale );
	virtual void OnBuildEffectActorFinished() override;
	
	/* We only have to check mCanContainLightweightInstances for poles, the instance data is made dynamically. */
	bool virtual DoesContainLightweightInstances_Native() const override { return mCanContainLightweightInstances; }
	virtual TArray<struct FInstanceData> GetActorLightweightInstanceData_Implementation() override;

public:
	static const FName PoleMeshName;

	/** The component we want to use with the pole */
	UPROPERTY( VisibleAnywhere, Category = "Pole" )
	class UFGColoredInstanceMeshProxy* mPoleComponentProxy;

	// Instance data set on begin play read during setup instances.
	FInstanceData InstanceData;
	
	/** This poles height. */
	UPROPERTY( SaveGame, Replicated )
	float mHeight;

	/** This poles mesh. */
	UPROPERTY( Replicated )
	class UStaticMesh* mPoleMesh;

	// 2D scale for pole meshes
	UPROPERTY()
	FVector2D mPoleScale;
};
