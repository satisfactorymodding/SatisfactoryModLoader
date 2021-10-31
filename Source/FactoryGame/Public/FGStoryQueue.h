// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"

#include "UObject/NoExportTypes.h"
#include "FGStoryQueue.generated.h"

USTRUCT()
struct FEventTriggeredMessage
{
	GENERATED_BODY()

	UPROPERTY( EditDefaultsOnly, Instanced, Category = "Dependencies" )
	class UFGAvailabilityDependency* TriggerDependency;

	UPROPERTY( EditDefaultsOnly, Category = "Message" )
	TSubclassOf< class UFGMessageBase > Message;
};

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

	static TArray< FEventTriggeredMessage > GetFloatingMessages( TSubclassOf< UFGStoryQueue > inClass );
	
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

	/** Messages that we trigger when the given event is triggered */
	UPROPERTY( EditDefaultsOnly, Category = "Floating Messages" )
	TArray< FEventTriggeredMessage > mFloatingMessages;

	/** What dependencies is needed to be fulfilled before we can start this queue */
	UPROPERTY( EditDefaultsOnly, Instanced, Category = "Dependencies" )
	TArray< class UFGAvailabilityDependency* > mDependencies;

};
