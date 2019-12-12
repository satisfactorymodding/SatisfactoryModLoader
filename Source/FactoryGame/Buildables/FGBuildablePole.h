// Copyright 2016 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "Engine/StaticMesh.h"
#include "Array.h"
#include "GameFramework/Actor.h"
#include "UObject/Class.h"

#include "FGBuildable.h"
#include "FGBuildablePole.generated.h"


/**
 * An arbitrarily high pole.
 */
UCLASS( Abstract )
class FACTORYGAME_API AFGBuildablePole : public AFGBuildable
{
	GENERATED_BODY()
public:
	AFGBuildablePole();

	// Begin AActor interface
	virtual void GetLifetimeReplicatedProps( TArray< FLifetimeProperty >& OutLifetimeProps ) const override;
	virtual void BeginPlay() override;
	// End AActor interface


	/** Set the pole's height. */
	void SetPoleHeight( float height );

	/** Sets the connection component to be at correct height and registers */
	virtual void SetupConnectionComponent();

	virtual void PostLoad() override;

	static const FName PoleMeshName;
public:
	/** This poles height. */
	UPROPERTY( SaveGame, Replicated )
	float mHeight;

	/** Can this pole stack. */
	UPROPERTY( EditDefaultsOnly, Category = "Pole" )
	bool mCanStack;

	/** Height between two stacked poles excluding the poles height. */
	UPROPERTY( EditDefaultsOnly, Category = "Pole" )
	float mStackHeight;

	/** The component we want to use with the pole */
	UPROPERTY( VisibleAnywhere, Category = "Pole" )
	class UFGColoredInstanceMeshProxy* mPoleComponentProxy;

	/** Connection component used */
	UPROPERTY( VisibleAnywhere, Category = "Pole" )
	class UFGFactoryConnectionComponent* mSnapOnly0;

	/** This poles mesh. @save 2018-10-24, this is here so old poles < alpha 2 path will still have a correct mesh, resaving an old save */
	UPROPERTY( SaveGame, Replicated )
	class UStaticMesh* mPoleMesh;
	
	/** Should the stack height only be calculated using the mStackHeight? */
	UPROPERTY( EditDefaultsOnly, Category = "Pole" )
	bool mUseStaticHeight;
protected:
	//virtual void TogglePendingDismantleMaterial( bool enabled ) override;
	//virtual void OnBuildEffectFinished() override;
};
