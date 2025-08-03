#include "Hologram/FGStorageBoxHologram.h"

AFGStorageBoxHologram::AFGStorageBoxHologram() : Super() {
	this->mCanRotateAroundAttachmentPoint = false;
}
void AFGStorageBoxHologram::ScrollRotate(int32 delta, int32 step){ Super::ScrollRotate(delta, step); }
void AFGStorageBoxHologram::CreateAttachmentPointTransform(FTransform& out_transformResult, const FHitResult& HitResult, AFGBuildable* pBuildable, const FFGAttachmentPoint& BuildablePoint, const FFGAttachmentPoint& LocalPoint){ Super::CreateAttachmentPointTransform(out_transformResult, HitResult, pBuildable, BuildablePoint, LocalPoint); }