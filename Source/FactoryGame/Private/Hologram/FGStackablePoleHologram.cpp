#include "Hologram/FGStackablePoleHologram.h"

AFGStackablePoleHologram::AFGStackablePoleHologram() : Super() {

}
void AFGStackablePoleHologram::BeginPlay(){ Super::BeginPlay(); }
void AFGStackablePoleHologram::SetHologramLocationAndRotation(const FHitResult& hitResult){ Super::SetHologramLocationAndRotation(hitResult); }
bool AFGStackablePoleHologram::TrySnapToActor(const FHitResult& hitResult){ return Super::TrySnapToActor(hitResult); }
void AFGStackablePoleHologram::SetZoopFromHitresult(const FHitResult& hitResult){  }
void AFGStackablePoleHologram::CreateZoopInstances(){ Super::CreateZoopInstances(); }
FVector AFGStackablePoleHologram::ConvertZoopToWorldLocation(const FIntVector& zoop) const{ return Super::ConvertZoopToWorldLocation(zoop); }