// Copyright Coffee Stain Studios. All Rights Reserved.
#pragma once

#include "CoreMinimal.h"
#include "FGSubsystem.h"

#include "Audio/AudioMeter/IAudioMeterImpl.h"

#include "FGVoiceChatAudioMeterSubsystem.generated.h"


/*
 * This code defines a subsystem `AFGVoiceChatAudioMeterSubsystem`, which is responsible for monitoring and metering voice chat audio levels in our WWise project
 * 
 * - The system interfaces with platform-specific audio metering implementations (e.g., Windows) to capture real-time audio peaks from active voice chat sessions.
 * - The `ConvertPeakToRTPC` method maps the audio peak value (ranging from 0 to 1) to the Wwise RTPC (Real-Time Parameter Control) range of [-100, 0], representing voice activity intensity.
 * - This subsystem updates two RTPCs: `mAudioMeterPeakRtpc` (for the current audio peak) and `mAudioMeterRtpc` (interpolated value). These RTPC values allow Wwise to control audio behavior dynamically, depending on the voice chat volume.
 * 
 * The audio metering runs asynchronously, offloading calculations to a background thread, and debug information can be rendered in-game to visualize the metering values.
 * The class also handles initialization and cleanup of the audio meter during the subsystem’s lifecycle.
 */

UCLASS( config = Game, Blueprintable, defaultconfig, meta = ( DisplayName = "Voice Chat Audio Meter Subsystem" ) )
class FACTORYGAME_API AFGVoiceChatAudioMeterSubsystem : public AFGSubsystem
{
	GENERATED_BODY()

public:
	AFGVoiceChatAudioMeterSubsystem();

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay( const EEndPlayReason::Type EndPlayReason ) override;

public:
	virtual void Tick( float DeltaTime ) override;

	//RPTC for voice chat metering which ranges from -100 to 0 with default being to -100 (when no once is talking). The data is coming from the audio metering system (windows audio peaks)
	UPROPERTY( EditDefaultsOnly, Category = Audio )
	class UAkRtpc* mAudioMeterPeakRtpc = nullptr;
	//RPTC for voice chat metering which ranges from -100 to 0 with default being to -100 (when no once is talking). This is either -100 to 0, and is interpolating inside wwise
	UPROPERTY( EditDefaultsOnly, Category = Audio )
	class UAkRtpc* mAudioMeterRtpc = nullptr;

private:
	void ConvertPeakToRTPC( float peak, float DeltaTime );
	void SetRTPC( float AudioMeterValue );

	float mPreviousRTPCValue{ -100.0f };
	float mPreviousAudioPeak{ 0.0f };

	bool mReadyToMonitor{ true };

	TUniquePtr< IAudioMeterImpl > mAudioMeterImpl;
};