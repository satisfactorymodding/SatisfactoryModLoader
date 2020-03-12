#pragma once

#include "AnimNodes/AnimNode_RandomPlayer.h"
#include "FGAnimNodeRandomPlayer.generated.h"

USTRUCT( BlueprintInternalUseOnly )
struct FACTORYGAME_API FFGAnimNode_RandomPlayer : public FAnimNode_RandomPlayer
{
	GENERATED_BODY()
public:
	// Play Rate for the sequence
	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = Runtime, meta = (AlwaysAsPin) )
	float mPlayRate;
public:
	FFGAnimNode_RandomPlayer()
		: FAnimNode_RandomPlayer()
		, mPlayRate( 1.0f )
	{
	}

	// Begin FAnimNode_Base interface
	virtual void Initialize_AnyThread( const FAnimationInitializeContext& Context ) override;
	// End FAnimNode_Base interface

public:
	FORCEINLINE ~FFGAnimNode_RandomPlayer() = default;
};