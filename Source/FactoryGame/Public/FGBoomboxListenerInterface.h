// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"
#include "Resources/FGTapeData.h"
#include "UObject/Interface.h"
#include "FGBoomboxListenerInterface.generated.h"

UENUM( BlueprintType )
enum class EBoomboxPlaybackState: uint8
{
	EPlaying,
	EStopped
};

/**
 * 
 */
UINTERFACE( Blueprintable )
class FACTORYGAME_API UFGBoomboxListenerInterface : public UInterface
{
	GENERATED_BODY()
};

class FACTORYGAME_API IFGBoomboxListenerInterface
{
	GENERATED_BODY()

public:
	UFUNCTION( BlueprintImplementableEvent )
	void PlaybackStateChanged( EBoomboxPlaybackState newState );

	UFUNCTION( BlueprintImplementableEvent )
	void CurrentSongChanged( const FSongData& currentSong, int32 index );

	UFUNCTION( BlueprintImplementableEvent )
	void PlaybackPositionUpdate( float currentPosition, float totalDuration );

	UFUNCTION( BlueprintImplementableEvent )
	void CurrentTapeChanged( TSubclassOf<UFGTapeData> currentTape );

	UFUNCTION( BlueprintImplementableEvent )
	void AudioVolumeChanged( float volume );
};
