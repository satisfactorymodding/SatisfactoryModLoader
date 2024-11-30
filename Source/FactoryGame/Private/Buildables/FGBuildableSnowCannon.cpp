#include "Buildables/FGBuildableSnowCannon.h"

AFGBuildableSnowCannon::AFGBuildableSnowCannon(){ }
void AFGBuildableSnowCannon::BeginPlay(){ Super::BeginPlay(); }
void AFGBuildableSnowCannon::EndPlay(const EEndPlayReason::Type EndPlayReason){ Super::EndPlay(EndPlayReason); }
void AFGBuildableSnowCannon::GainedSignificance_Implementation(){ }
void AFGBuildableSnowCannon::LostSignificance_Implementation(){ }
void AFGBuildableSnowCannon::SetCannonAngle(int32 angle){ }
void AFGBuildableSnowCannon::UpdateCannonMesh(){ }
