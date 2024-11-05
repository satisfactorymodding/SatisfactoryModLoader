// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FGSubsystem.h"
#include "FGAudioVolumeSubsystem.generated.h"

#define WITH_AUDIO_DEBUG 1 && !UE_BUILD_SHIPPING

UCLASS(NotPlaceable)
class FACTORYGAME_API AFGAudioVolumeSubsystem : public AFGSubsystem
{
	GENERATED_BODY()
public:
	AFGAudioVolumeSubsystem();

	/** Called every frame, updates the location of all ambient volumes */
	virtual void Tick( float dt ) override;
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

protected:
	/** returns true if we should update the given world */
	bool ShouldUpdateWorld( UWorld* world ) const;

	/** Update the volumes in the specified world */
	void UpdateWorld( UWorld* world );

	/** Get the distance where we assume that we are "close" to the volume */
	float GetCloseDistance( class AFGAmbientVolume* ambientVolume ) const;

private:
#if WITH_AUDIO_DEBUG
	TArray< TWeakObjectPtr< AFGAmbientVolume > > mInsideVolumes;
	TArray< TWeakObjectPtr< AFGAmbientVolume > > mNearbyVolumes;
	bool mDebuggingEnabled = false;
	FDelegateHandle mDebugMessageDelegateHandle;

	void AudioVolumeDebuggingChanged(IConsoleVariable* var);
#endif
};

