#include "Hologram/FGBarrierCornerHologram.h"

AFGBarrierCornerHologram::AFGBarrierCornerHologram() : Super() {

}
void AFGBarrierCornerHologram::BeginPlay(){ Super::BeginPlay(); }
void AFGBarrierCornerHologram::SetHologramLocationAndRotation(const FHitResult& hitResult){ Super::SetHologramLocationAndRotation(hitResult); }
bool AFGBarrierCornerHologram::TrySnapToActor(const FHitResult& hitResult){ return Super::TrySnapToActor(hitResult); }
void AFGBarrierCornerHologram::CreateZoopInstances(){ Super::CreateZoopInstances(); }
FVector AFGBarrierCornerHologram::ConvertZoopToWorldLocation(const FIntVector& zoop) const{ return Super::ConvertZoopToWorldLocation(zoop); }
