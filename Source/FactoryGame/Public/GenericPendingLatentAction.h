#pragma once
#include "LatentActions.h"
#include "Engine/LatentActionManager.h"

DECLARE_DELEGATE_TwoParams( FPendingLatentActionPredicate, class FGenericPendingLatentAction& LatentAction, FLatentResponse& Response );

class FGenericPendingLatentAction : public FPendingLatentAction
{
public:
	FName ExecutionFunction;
	int32 OutputLink;
	FWeakObjectPtr CallbackTarget;
	FPendingLatentActionPredicate Predicate;
#if WITH_EDITORONLY_DATA
	FString Description;
#endif
	
	FGenericPendingLatentAction( FString description, const FLatentActionInfo& LatentInfo )
		: ExecutionFunction(LatentInfo.ExecutionFunction)
		, OutputLink(LatentInfo.Linkage)
		, CallbackTarget(LatentInfo.CallbackTarget)
#if WITH_EDITORONLY_DATA
		, Description(description)
#endif
	{
	}

	virtual void UpdateOperation(FLatentResponse& Response) override;

#if WITH_EDITOR
	// Returns a human readable description of the latent operation's current state
	virtual FString GetDescription() const override
	{
		return FString::Printf( TEXT("Waiting for %s"), *Description );
	}
#endif
};
