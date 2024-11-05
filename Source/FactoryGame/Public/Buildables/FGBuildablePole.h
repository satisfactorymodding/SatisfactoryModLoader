// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FGBuildable.h"
#include "FGBuildablePoleBase.h"
#include "FGBuildablePole.generated.h"


/**
 * An arbitrarily high pole.
 */
UCLASS( Abstract )
class FACTORYGAME_API AFGBuildablePole : public AFGBuildablePoleBase
{
	GENERATED_BODY()
public:
	AFGBuildablePole(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	// Begin AActor interface
	virtual void GetLifetimeReplicatedProps( TArray< FLifetimeProperty >& OutLifetimeProps ) const override;
	virtual void BeginPlay() override;
	// End AActor interface

	
	virtual float GetStackHeight() const override
	{
		float baseOffset = mUseStaticHeight ? 0 : mHeight;
		return baseOffset + mStackHeight;
	}


	/** Set the pole's height. */
	void SetPoleHeight( float height );

	/** Sets the connection component to be at correct height and registers */
	virtual void SetupConnectionComponent();
	
	static const FName PoleMeshName;

	/* We only have to check mCanContainLightweightInstances for poles, the instance data is made dynamically. */
	bool virtual DoesContainLightweightInstances_Native() const override { return mCanContainLightweightInstances; }
	virtual TArray<struct FInstanceData> GetActorLightweightInstanceData_Implementation() override;
	
protected:
	virtual void SetupInstances_Native( bool bSpawnHidden ) override;
	
public:
	/** This poles height. */
	UPROPERTY( SaveGame, Replicated )
	float mHeight;

	/** The component we want to use with the pole */
	UPROPERTY( VisibleAnywhere, BlueprintReadOnly, Category = "Pole" )
	class UFGColoredInstanceMeshProxy* mPoleComponentProxy;

	/** Connection component used */
	UPROPERTY( VisibleAnywhere, Category = "Pole" )
	class UFGFactoryConnectionComponent* mSnapOnly0;

	// TODO Networking do we need to replicate this?
	/** This poles mesh. */
	UPROPERTY( )
	UStaticMesh* mPoleMesh;

	//SaveGame
	UPROPERTY( Replicated, SaveGame )
	int8 mSelectedPoleVersion;
	
	/** Should the stack height only be calculated using the mStackHeight? */
	UPROPERTY( EditDefaultsOnly, Category = "Pole" )
	bool mUseStaticHeight;
	
	// TODO Add height variations to this buildable instead of the descriptor
	// This would allow for better mod~ability & future proofing.
	// and we can just save an ID and replicate an ID instead of a mesh.
};

UCLASS(Abstract)
class FACTORYGAME_API AFGBuildablePoleLightweight : public AFGBuildablePole
{
	GENERATED_BODY()
	AFGBuildablePoleLightweight(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get() );
};
