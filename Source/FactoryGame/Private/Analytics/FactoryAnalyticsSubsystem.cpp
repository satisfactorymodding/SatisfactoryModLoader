#include "Analytics/FactoryAnalyticsSubsystem.h"

void UFactoryAnalyticsSubsystem::Initialize(FSubsystemCollectionBase& Collection){  }
bool UFactoryAnalyticsSubsystem::ShouldCreateSubsystem(UObject* Outer) const{ return Super::ShouldCreateSubsystem(Outer); }
void UFactoryAnalyticsSubsystem::ConfigureTags(class USentrySubsystem* Sentry){ }
