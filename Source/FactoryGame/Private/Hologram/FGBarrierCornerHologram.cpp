#include "Hologram/FGBarrierCornerHologram.h"

AFGBarrierCornerHologram::AFGBarrierCornerHologram() : Super() {

}
void AFGBarrierCornerHologram::BeginPlay(){ Super::BeginPlay(); }
void AFGBarrierCornerHologram::SetZoopFromHitresult(const FHitResult& hitResult){ Super::SetZoopFromHitresult(hitResult); }
bool AFGBarrierCornerHologram::TrySnapToActor(const FHitResult& hitResult){ return Super::TrySnapToActor(hitResult); }
void AFGBarrierCornerHologram::CreateZoopInstances(const FIntVector& DesiredZoop){ Super::CreateZoopInstances(DesiredZoop); }
FVector AFGBarrierCornerHologram::ConvertZoopToWorldLocation(const FIntVector& zoop) const{ return Super::ConvertZoopToWorldLocation(zoop); }
