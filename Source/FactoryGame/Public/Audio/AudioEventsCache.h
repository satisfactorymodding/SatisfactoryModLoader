// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"
#include "AkAudioEvent.h"
#include "UObject/Object.h"
#include "AudioEventsCache.generated.h"

/**
 * 
 */
USTRUCT( BlueprintType )
struct FACTORYGAME_API FAudioEventsCache
{
	GENERATED_BODY()
public:

	void AddSoftAudioEvent( TSoftObjectPtr< UAkAudioEvent > audioEvent );

	void AddSoftAudioEvents( const TArray< TSoftObjectPtr< UAkAudioEvent > >& audioEvents );

	void CacheAudioEvents();
	
	void ResetCache();
	
	void ResetSoftReferences();
	
	void HandleAllAudioEventsLoaded();

protected:
	//Soft refs that were requested
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio")
	TArray< TSoftObjectPtr< UAkAudioEvent > > mSoftAudioEvents;

private:
	//Actual cache with hard refs
	UPROPERTY()
	TArray< TObjectPtr< UAkAudioEvent > > mAudioEventsCache;
};