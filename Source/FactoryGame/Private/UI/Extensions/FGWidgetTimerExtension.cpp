#include "UI/Extensions/FGWidgetTimerExtension.h"

void UFGWidgetTimerExtension::Destruct(){ Super::Destruct(); }
bool UFGWidgetTimerExtension::RequiresTick() const{ return Super::RequiresTick(); }
void UFGWidgetTimerExtension::Tick(const FGeometry& MyGeometry, float InDeltaTime){ Super::Tick(MyGeometry, InDeltaTime); }
void UFGWidgetTimerExtension::StartTickForDuration(FTickDynamicDelegate Delegate, float inDuration){ }
void UFGWidgetTimerExtension::Finish(){ }
