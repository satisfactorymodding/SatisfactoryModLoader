#include "Hologram/FGStackableShelfHologram.h"

AFGStackableShelfHologram::AFGStackableShelfHologram() : Super() {

}
void AFGStackableShelfHologram::BeginPlay(){ Super::BeginPlay(); }
bool AFGStackableShelfHologram::TrySnapToActor(const FHitResult& hitResult){ return Super::TrySnapToActor(hitResult); }
void AFGStackableShelfHologram::CreateZoopInstances(const FIntVector& DesiredZoop){ Super::CreateZoopInstances(DesiredZoop); }
FVector AFGStackableShelfHologram::ConvertZoopToWorldLocation(const FIntVector& zoop) const{ return Super::ConvertZoopToWorldLocation(zoop); }
void AFGStackableShelfHologram::SetZoopFromHitResult(const FHitResult& hitResult){  }