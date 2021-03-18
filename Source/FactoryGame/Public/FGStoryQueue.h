// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

#include "UObject/NoExportTypes.h"
#include "FGStoryQueue.generated.h"

/**
 * 
 */
UCLASS( Blueprintable )
class FACTORYGAME_API UFGStoryQueue : public UObject
{
	GENERATED_BODY()

public:
	static TArray< TSubclassOf< class UFGMessageBase > > GetMessages( TSubclassOf< UFGStoryQueue > inClass );

	static bool IsMessageTriggeredByMilestone( TSubclassOf< UFGStoryQueue > inClass );

	static float GetDelayAfterMilestone( TSubclassOf< UFGStoryQueue > inClass );
	
	static bool IsMessageTriggeredByTimer( TSubclassOf< UFGStoryQueue > inClass );
	
	static float GetTimeUntilMessageIsTriggered( TSubclassOf< UFGStoryQueue > inClass );
	
	static float GetMinimumDelayBetweenMessages( TSubclassOf< UFGStoryQueue > inClass );

	UFUNCTION( BlueprintPure, Category = "Story" )
	static float GetMaximumDelayForCall( TSubclassOf< UFGStoryQueue > inClass );

	static TArray< TSubclassOf< class UFGMessageBase > > GetBarkMessages( TSubclassOf< UFGStoryQueue > inClass );

	static float GetTimeUntilBarkIsTriggered( TSubclassOf< UFGStoryQueue > inClass );
	
    static bool AreDependenciesForQueueMet( TSubclassOf< UFGStoryQueue > inClass, UObject* worldContext );
	
	static void GetStoryQueueDebugData( TSubclassOf< UFGStoryQueue > inClass, TArray<FString>& out_debugData );

protected:
	friend class FStoryQueueDetails;
	
private:
	UPROPERTY( EditDefaultsOnly, Category = "Messages" )
	TArray< TSubclassOf< class UFGMessageBase >  > mMessages;

	/** If a message should be considered to be triggered when a milestone is completed */
	UPROPERTY( EditDefaultsOnly, Category = "Triggers" )
	bool mIsMessageTriggeredByMilestone;

	/** How long should the next message be delayed after a milestone is completed */
	UPROPERTY( EditDefaultsOnly, Category = "Triggers", meta = (EditCondition="mIsMessageTriggeredByMilestone") )
	float mDelayAfterMilestone;

	/** If a message should be considered to be triggered when a timer runs out regardless of a milstone have been finished or not */
	UPROPERTY( EditDefaultsOnly, Category = "Triggers" )
	bool mIsMessageTriggeredByTimer;
	
	/** How long do we wait until we trigger a message by a timer */
	UPROPERTY( EditDefaultsOnly, Category = "Triggers", meta = (EditCondition="mIsMessageTriggeredByTimer") )
	float mTimeUntilMessageIsTriggered;

	/** The minimum time we wait after a message have been triggered until we trigger the next one. Only really useful if messages are triggered by milestones. */
	UPROPERTY( EditDefaultsOnly, Category = "Delay" )
	float mMinimumDelayBetweenMessages;

	/** How long can the player delay a message until it get autoanswered */
	UPROPERTY( EditDefaultsOnly, Category = "Delay" )
	float mMaximumDelayForCall;

	/** What dependencies is needed to be fulfilled before we can start this queue */
	UPROPERTY( EditDefaultsOnly, Instanced, Category = "Dependencies" )
	TArray< class UFGAvailabilityDependency* > mDependencies;

	/** Messages that we trigger when we haven't "regular" messages left to play in this queue */
	UPROPERTY( EditDefaultsOnly, Category = "Bark messages" )
	TArray< TSubclassOf< class UFGMessageBase >  > mBarkMessages;

	/** How long do we wait until we trigger a bark message by a timer */
	UPROPERTY( EditDefaultsOnly, Category = "Bark messages")
	float mTimeUntilBarkIsTriggered;
	
};
