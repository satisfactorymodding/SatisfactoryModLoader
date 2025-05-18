#include "Online/FGPlatformTelemetryInformer.h"

void UFGPlatformTelemetryInformer::Initialize(FSubsystemCollectionBase& Collection){ Super::Initialize(Collection); }
void UFGPlatformTelemetryInformer::Deinitialize(){ Super::Deinitialize(); }
bool UFGPlatformTelemetryInformer::ShouldCreateSubsystem(UObject* Outer) const{ return Super::ShouldCreateSubsystem(Outer); }
void UFGPlatformTelemetryInformer::SetOnlineFeatureStatus(EOnlineSessionFeatureType sessionFeatureType){ }
