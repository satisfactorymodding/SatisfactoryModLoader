#include "Audio/FGVoiceChatAudioMeterSubsystem.h"

AFGVoiceChatAudioMeterSubsystem::AFGVoiceChatAudioMeterSubsystem(){ }
void AFGVoiceChatAudioMeterSubsystem::BeginPlay(){ Super::BeginPlay(); }
void AFGVoiceChatAudioMeterSubsystem::EndPlay(const EEndPlayReason::Type EndPlayReason){ Super::EndPlay(EndPlayReason); }
void AFGVoiceChatAudioMeterSubsystem::Tick(float DeltaTime){ Super::Tick(DeltaTime); }
void AFGVoiceChatAudioMeterSubsystem::ConvertPeakToRTPC(float peak, float DeltaTime){ }
void AFGVoiceChatAudioMeterSubsystem::SetRTPC(float AudioMeterValue){ }
