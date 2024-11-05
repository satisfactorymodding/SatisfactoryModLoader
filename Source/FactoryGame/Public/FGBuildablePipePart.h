// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "Buildables/FGBuildableFactory.h"
#include "Buildables/FGPipeHyperAttachmentSnapTargetInterface.h"
#include "CoreMinimal.h"
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

};

UCLASS()
class FACTORYGAME_API AFGBuildablePipeHyperPart : public AFGBuildablePipePart, public IFGPipeHyperAttachmentSnapTargetInterface
{
	GENERATED_BODY()
};
