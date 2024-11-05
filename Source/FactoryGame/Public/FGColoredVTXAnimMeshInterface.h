// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "FGColoredInstanceMeshProxy.h"
#include "Buildables/FGBuildable.h"
#include "FGColoredVTXAnimMeshInterface.generated.h"

enum class EProductionStatus : uint8;
enum class EVTXAnimState : uint8
{
	AS_Producing,		// Shader index 0
	AS_WindingUp,		// Shader index 1
	AS_WindingDown, 	// Shader index 2
	AS_Idle,			// Shader index 3
};

/**
 * 
 */
UCLASS(Blueprintable, ClassGroup = ( FactoryGame ), meta = ( BlueprintSpawnableComponent ))
class FACTORYGAME_API UFGColoredVTXAnimMeshInterface : public UFGColoredInstanceMeshProxy
{
public:
	GENERATED_BODY()

	UFGColoredVTXAnimMeshInterface();

	virtual void BeginPlay() override; 
	//virtual void EndPlay( const EEndPlayReason::Type EndPlayReason );

protected:
	virtual void SetupDelegates(bool bShouldDoInitialCall = true);
	virtual void SetupDefaultPrimitiveValues();

	virtual bool ShouldPlayStartAnimation(EProductionStatus NewState, EProductionStatus OldState);
	virtual bool ShouldPlayEndAnimation(EProductionStatus NewState, EProductionStatus OldState);
	virtual bool ShouldIdle(EProductionStatus NewState, EProductionStatus OldState);
	
	/* Called when production state changed to producing when @bHasStartupAnimation is true*/
	virtual void BeginStartAnimation(float WorldTime);
	
	/* Called when production state changed to Stopped when @bHasEndAnimation is true*/
	virtual void BeginStopAnimation(float WorldTime);

	/* Called when production state changed to producing when @bHasStartupAnimation is false
	 * or when BeginStartAnimation finished. */
	virtual void StartProductionAnimation(float WorldTime);

	virtual void StopAnimation(float WorldTime);

	/* Delegate on that should be bound to its owning actor to determine what state it should enter.*/
	void OnProductionStateChanged(EProductionStatus NewState);
	void OnCurrentPotentialChanged( float Value );

	virtual void UpdateState(EProductionStatus NewState);

	/*Updates time offset to ensure the VTX animation starts from Zero position.*/
	void UpdateTimeOffset(float WorldTime, float StateTime);
	void UpdateAnimationState(EVTXAnimState State);
	
	void SetStartAnimationDuration(float SpeedMultiplier = 1);
	void SetStopAnimationDuration(float SpeedMultiplier = 1);
	void SetProductionAnimationDuration(float SpeedMultiplier = 1);
	
	UPROPERTY(EditDefaultsOnly, Category= "VertexAnimation")
	bool bHasStartupAnimation;

	UPROPERTY(EditDefaultsOnly, Category= "VertexAnimation")
	bool bHasEndAnimation;
	
	UPROPERTY(EditDefaultsOnly, Category= "VertexAnimation")
	float mDefaultProductionAnimDuration = 1;
	
	UPROPERTY(EditDefaultsOnly, Category= "VertexAnimation")
	float mDefaultStartupAnimDuration;
	
	UPROPERTY(EditDefaultsOnly, Category= "VertexAnimation")
	float mDefaultStopAnimDuration;

	UPROPERTY(EditDefaultsOnly, Category= "VertexAnimation|Binds")
	int32 mTimeOffsetPrimitiveID;

	UPROPERTY(EditDefaultsOnly, Category= "VertexAnimation|Binds")
	int32 mProductionStateID;

	UPROPERTY(EditDefaultsOnly, Category= "VertexAnimation|Binds")
	int32 mCurrentPotentialID;

	UPROPERTY(EditDefaultsOnly, Category= "VertexAnimation|Binds")
	int32 mProductionAnimationDurationID;
	
	UPROPERTY(EditDefaultsOnly, Category= "VertexAnimation|Binds")
	int32 mStartAnimationDurationID;

	UPROPERTY(EditDefaultsOnly, Category= "VertexAnimation|Binds")
	int32 mStopAnimationDurationID;

	EVTXAnimState mVTXAnimState;

	
private:

#if WITH_EDITOR
	/* Test function to ensure the component has the right settings.
	 * Called on begin play, can crash the game when settings are invalid */
	virtual void ValidateSettings() const;
#else
	FORCEINLINE void ValidateSettings() const {};
#endif

	/* Cached state. */
	EProductionStatus mCurrentState = EProductionStatus::IS_NONE;
	
	/* Last world time when the animation state switched, used as a threshold */
	float WorldTimeLastStateSwitch = 0;
};
