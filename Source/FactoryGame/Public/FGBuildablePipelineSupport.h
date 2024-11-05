// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "Buildables/FGBuildable.h"
#include "Buildables/FGBuildablePoleBase.h"
#include "CoreMinimal.h"
#include "FGBuildablePipelineSupport.generated.h"

class UFGPipeConnectionComponentBase;
/**
 * Base class for variable length pipe supports
 */
UCLASS()
class FACTORYGAME_API AFGBuildablePipelineSupport : public AFGBuildablePoleBase
{
	GENERATED_BODY()
public:
	AFGBuildablePipelineSupport();

	// Begin AActor interface
	virtual void GetLifetimeReplicatedProps( TArray< FLifetimeProperty >& OutLifetimeProps ) const override;
	virtual void BeginPlay() override;
	// End AActor interface

	/* We only have to check mCanContainLightweightInstances for poles, the instance data is made dynamically. */
	bool virtual DoesContainLightweightInstances_Native() const override { return mCanContainLightweightInstances; }
	virtual TArray<struct FInstanceData> GetActorLightweightInstanceData_Implementation() override;

	virtual float GetStackHeight() const override
	{
		float baseOffset = mUseStaticHeight ? 0 : mLength;
		return baseOffset + mStackHeight;
	}

	/** Set the pole's height. */
	void SetSupportLength( float length );

	/** Set the pole's height. */
	void SetVerticalAngle( float angle );

	/** Sets the connection component to be at correct height and registers */
	virtual void SetupConnectionComponent();

	static const FName SupportMeshName;

	/** GetConnectionType
	 * Get the UClass for the connection type for this pipe. All pipe types should have their own function here, or their connection can snap to the wrong type of pipes
	   [DavalliusA:Tue/22-10-2019] this is a virtual function, so we don't have to store a variable in all the instances of this class
	 *
	 * @return	TSubclassOf<UFGPipeConnectionComponentBase> -
	 */
	UFUNCTION( BlueprintNativeEvent, Category = "Pipes" )
	TSubclassOf<UFGPipeConnectionComponentBase> GetConnectionType();

#if WITH_EDITOR
	virtual void OnConstruction( const FTransform& transform ) override;
#endif


public:
	/** This supports length. */
	UPROPERTY( SaveGame, Replicated )
	float mLength;

	/** This supports length. */
	UPROPERTY( SaveGame, Replicated )
	float mVerticalAngle = 0.0f;


	/** The component we want to use with the support */
	UPROPERTY( EditAnywhere, Category = "Pipe Support" )
	class UFGColoredInstanceMeshProxy* mSupportComponentDefaultMesh;

	/** Connection component used
	**MOST BE SET FROM CONSTRUCTION SCRIPT OR IT WILL BE NULL!**/
	UPROPERTY( VisibleAnywhere, BlueprintReadWrite, Category = "Pipe Support" )
	UFGPipeConnectionComponentBase* mSnapOnly0;

	// Instance data set on begin play read during setup instances.
	FInstanceData InstanceData;
	
	/** The scene component for adjusting the length of the support. */
	UPROPERTY()
	class USceneComponent* mSupportLengthComponent;

	/**Used to store the initial offset of the support length component, so we can compensate for it during placement*/
	float mSupportLengthOffset;

	/** Static mesh to use when rendering */
	UPROPERTY( Replicated )
	class UStaticMesh* mSupportMesh;

	/** Should the stack height only be calculated using the mStackHeight? */
	UPROPERTY( EditDefaultsOnly, Category = "Pipe Support" )
	bool mUseStaticHeight;

};
