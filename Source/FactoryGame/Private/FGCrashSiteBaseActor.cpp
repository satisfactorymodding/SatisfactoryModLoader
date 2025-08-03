#include "FGCrashSiteBaseActor.h"

AFGCrashSiteBaseActor::AFGCrashSiteBaseActor() : Super() {
	this->mDisplayName = INVTEXT("");
	this->mDismantleRefundsIndex = -1;
	this->mDismantleBuildEffect = nullptr;
	this->mDismantleEffectSpeed = 0.0;
	this->mIsDismantled = false;
	this->mActiveDismantleEffect = nullptr;
	this->PrimaryActorTick.TickGroup = ETickingGroup::TG_PrePhysics;
	this->PrimaryActorTick.EndTickGroup = ETickingGroup::TG_PrePhysics;
	this->PrimaryActorTick.bTickEvenWhenPaused = false;
	this->PrimaryActorTick.bCanEverTick = false;
	this->PrimaryActorTick.bStartWithTickEnabled = false;
	this->PrimaryActorTick.bAllowTickOnDedicatedServer = true;
	this->PrimaryActorTick.TickInterval = 0.0;
	this->bReplicates = true;
	this->NetCullDistanceSquared = 2025000000.0;
}
void AFGCrashSiteBaseActor::BeginPlay(){ Super::BeginPlay(); }
void AFGCrashSiteBaseActor::PreSaveGame_Implementation(int32 saveVersion, int32 gameVersion){ IFGSaveInterface::PreSaveGame_Implementation(saveVersion, gameVersion); }
void AFGCrashSiteBaseActor::PostSaveGame_Implementation(int32 saveVersion, int32 gameVersion){ IFGSaveInterface::PostSaveGame_Implementation(saveVersion, gameVersion); }
void AFGCrashSiteBaseActor::PreLoadGame_Implementation(int32 saveVersion, int32 gameVersion){ IFGSaveInterface::PreLoadGame_Implementation(saveVersion, gameVersion); }
void AFGCrashSiteBaseActor::PostLoadGame_Implementation(int32 saveVersion, int32 gameVersion){ IFGSaveInterface::PostLoadGame_Implementation(saveVersion, gameVersion); }
void AFGCrashSiteBaseActor::GatherDependencies_Implementation(TArray<UObject*>& out_dependentObjects){ IFGSaveInterface::GatherDependencies_Implementation(out_dependentObjects); }
bool AFGCrashSiteBaseActor::NeedTransform_Implementation(){ return IFGSaveInterface::NeedTransform_Implementation(); }
bool AFGCrashSiteBaseActor::ShouldSave_Implementation() const{ return IFGSaveInterface::ShouldSave_Implementation(); }
bool AFGCrashSiteBaseActor::CanDismantle_Implementation() const{ return IFGDismantleInterface::CanDismantle_Implementation(); }
void AFGCrashSiteBaseActor::GetDismantleRefund_Implementation(TArray<FInventoryStack>& out_refund, bool noBuildCostEnabled) const{ IFGDismantleInterface::GetDismantleRefund_Implementation(out_refund, noBuildCostEnabled); }
FVector AFGCrashSiteBaseActor::GetRefundSpawnLocationAndArea_Implementation(const FVector& aimHitLocation, float& out_radius) const{ return IFGDismantleInterface::GetRefundSpawnLocationAndArea_Implementation(aimHitLocation, out_radius); }
void AFGCrashSiteBaseActor::Dismantle_Implementation(){ IFGDismantleInterface::Dismantle_Implementation(); }
void AFGCrashSiteBaseActor::StartIsLookedAtForDismantle_Implementation(AFGCharacterPlayer* byCharacter){ IFGDismantleInterface::StartIsLookedAtForDismantle_Implementation(byCharacter); }
void AFGCrashSiteBaseActor::StopIsLookedAtForDismantle_Implementation(AFGCharacterPlayer* byCharacter){ IFGDismantleInterface::StopIsLookedAtForDismantle_Implementation(byCharacter); }
FText AFGCrashSiteBaseActor::GetDismantleDisplayName_Implementation(AFGCharacterPlayer* byCharacter) const{ return IFGDismantleInterface::GetDismantleDisplayName_Implementation(byCharacter); }
void AFGCrashSiteBaseActor::OnDismantleEffectFinished(){  }
void AFGCrashSiteBaseActor::Multicast_Dismantle_Implementation(){  }