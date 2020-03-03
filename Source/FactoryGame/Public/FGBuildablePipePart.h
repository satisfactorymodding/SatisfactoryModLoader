// Copyright 2016-2019 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "Engine/StaticMesh.h"
#include "Array.h"
#include "GameFramework/Actor.h"
#include "UObject/Class.h"

#include "CoreMinimal.h"
#include "Buildables/FGBuildableFactory.h"
#include "FGPipeHyperInterface.h"
#include "FGBuildablePipePart.generated.h"

class UFGPipeConnectionComponentBase;
/**
 * Base class for variable length pipe supports
 */
UCLASS()
class FACTORYGAME_API AFGBuildablePipePart : public AFGBuildableFactory
{
	GENERATED_BODY()
public:
	AFGBuildablePipePart();

	// Begin AActor interface
	virtual void GetLifetimeReplicatedProps( TArray< FLifetimeProperty >& OutLifetimeProps ) const override;
	virtual void BeginPlay() override;
	// End AActor interface

	/** Set the pole's height. */
	void SetSupportLength( float length );

	/** Sets the connection component to be at correct height and registers */
	virtual void SetupConnectionComponent();

	static const FName SupportMeshName;



#if WITH_EDITOR
	virtual void OnConstruction( const FTransform& transform ) override;
#endif


public:
	/** This supports length. */
	UPROPERTY( SaveGame, Replicated )
	float mLength;

	/** Can this support stack. */
	UPROPERTY( EditDefaultsOnly, Category = "Pipe Support" )
	bool mCanStack;

	/** Height between two stacked supports excluding the poles height. */
	UPROPERTY( EditDefaultsOnly, Category = "Pipe Support" )
	float mStackHeight;

	/** The component we want to use with the support */
	UPROPERTY( EditAnywhere, Category = "Pipe Support" )
	class UFGColoredInstanceMeshProxy* mSupportComponentDefaultMesh;

	/** Connection component used
	**MOST BE SET FROM CONSTRUCTION SCRIPT OR IT WILL BE NULL!**/
	UPROPERTY( VisibleAnywhere, BlueprintReadWrite, Category = "Pipe Support" )
	UFGPipeConnectionComponentBase* mConnection0;

	/** Static mesh to use when rendering */
	UPROPERTY( Replicated )
	class UStaticMesh* mSupportMesh;

	/** Should the stack height only be calculated using the mStackHeight? */
	UPROPERTY( EditDefaultsOnly, Category = "Pipe Support" )
	bool mUseStaticHeight;


public:
	FORCEINLINE ~AFGBuildablePipePart() = default;
};

UCLASS()
class FACTORYGAME_API AFGBuildablePipeHyperPart : public AFGBuildablePipePart, public IFGPipeHyperInterface
{
	GENERATED_BODY()
	public:
	

	// Begin FGHyperTube Interface
	virtual float GetPipeProgressOfConnection_Implementation( const UFGPipeConnectionComponentBase* connectionEnteredThrough ) override;
	virtual void OnPipeMove_Implementation( UFGCharacterMovementComponent* charMove, float deltaTime ) override;
	virtual bool OnPipeEnter_Implementation( UFGCharacterMovementComponent* charMove, const UFGPipeConnectionComponentBase* connectionEnteredThrough = nullptr, const AActor* fromPipe = nullptr ) override;
	// End FGHyperTube Interface


public:
	FORCEINLINE ~AFGBuildablePipeHyperPart() = default;
};
