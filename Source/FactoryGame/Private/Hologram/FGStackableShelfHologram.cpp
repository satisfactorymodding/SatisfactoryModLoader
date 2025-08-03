#include "Hologram/FGStackableShelfHologram.h"

AFGStackableShelfHologram::AFGStackableShelfHologram() : Super() {

}
void AFGStackableShelfHologram::BeginPlay(){ Super::BeginPlay(); }
void AFGStackableShelfHologram::SetHologramLocationAndRotation(const FHitResult& hitResult){ Super::SetHologramLocationAndRotation(hitResult); }
bool AFGStackableShelfHologram::TrySnapToActor(const FHitResult& hitResult){ return Super::TrySnapToActor(hitResult); }
void AFGStackableShelfHologram::CreateZoopInstances(){ Super::CreateZoopInstances(); }
FVector AFGStackableShelfHologram::ConvertZoopToWorldLocation(const FIntVector& zoop) const{ return Super::ConvertZoopToWorldLocation(zoop); }
void AFGStackableShelfHologram::SetZoopFromHitResult(const FHitResult& hitResult){  }