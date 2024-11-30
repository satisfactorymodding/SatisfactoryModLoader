#include "Hologram/FGBuildableSnowCannonHologram.h"

AFGBuildableSnowCannonHologram::AFGBuildableSnowCannonHologram(){ }
void AFGBuildableSnowCannonHologram::BeginPlay(){ Super::BeginPlay(); }
int32 AFGBuildableSnowCannonHologram::GetRotationStep() const{ return int32(); }
void AFGBuildableSnowCannonHologram::ScrollRotate(int32 delta, int32 step){ }
bool AFGBuildableSnowCannonHologram::DoMultiStepPlacement(bool isInputFromARelease){ return bool(); }
bool AFGBuildableSnowCannonHologram::IsValidHitResult(const FHitResult& hitResult) const{ return bool(); }
void AFGBuildableSnowCannonHologram::ConfigureActor(AFGBuildable* inBuildable) const{ }
bool AFGBuildableSnowCannonHologram::TrySnapToActor(const FHitResult& hitResult){ return bool(); }
void AFGBuildableSnowCannonHologram::SetHologramLocationAndRotation(const FHitResult& hitResult){ }
