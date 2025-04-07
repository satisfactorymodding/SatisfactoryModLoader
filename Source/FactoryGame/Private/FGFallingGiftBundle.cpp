#include "FGFallingGiftBundle.h"
#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Net/UnrealNetwork.h"

AFGFallingGiftBundle::AFGFallingGiftBundle() : Super() {
	this->mMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	this->mMeshComponent->SetMobility(EComponentMobility::Movable);
	this->mGiftBundleName = INVTEXT("");
	this->mPickupAudioEvent = nullptr;
	this->mFallingSpeed = 0.0;
	this->mFallingRotationSpeed = 0.0;
	this->mIsFalling = false;
	this->mCachedExpectedLandingZ = 1.17549e-38;
	this->mSignificanceRange = 5000.0;
	this->mGiftSpawner = nullptr;
	this->mSelectedRandomRewardIndex = -1;
	this->mWasPickedUp = false;
	this->mFlipRotationDirection = false;
	this->mHasLanded = false;
	this->PrimaryActorTick.TickGroup = ETickingGroup::TG_PrePhysics;
	this->PrimaryActorTick.EndTickGroup = ETickingGroup::TG_PrePhysics;
	this->PrimaryActorTick.bTickEvenWhenPaused = false;
	this->PrimaryActorTick.bCanEverTick = true;
	this->PrimaryActorTick.bStartWithTickEnabled = false;
	this->PrimaryActorTick.bAllowTickOnDedicatedServer = true;
	this->PrimaryActorTick.TickInterval = 0.0;
	this->SetReplicatingMovement(true);
	this->bEnableAutoLODGeneration = false;
	this->bReplicates = true;
	this->RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	this->RootComponent->SetMobility(EComponentMobility::Movable);
	this->mMeshComponent->SetupAttachment(RootComponent);
}
void AFGFallingGiftBundle::BeginPlay(){ Super::BeginPlay(); }
void AFGFallingGiftBundle::Tick(float DeltaSeconds){ Super::Tick(DeltaSeconds); }
void AFGFallingGiftBundle::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const {
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AFGFallingGiftBundle, mIsFalling);
	DOREPLIFETIME(AFGFallingGiftBundle, mCachedExpectedLandingZ);
	DOREPLIFETIME(AFGFallingGiftBundle, mSelectedRandomRewardIndex);
	DOREPLIFETIME(AFGFallingGiftBundle, mWasPickedUp);
	DOREPLIFETIME(AFGFallingGiftBundle, mFlipRotationDirection);
	DOREPLIFETIME(AFGFallingGiftBundle, mHasLanded);
}
void AFGFallingGiftBundle::PostNetReceiveLocationAndRotation(){ Super::PostNetReceiveLocationAndRotation(); }
void AFGFallingGiftBundle::PreSaveGame_Implementation(int32 saveVersion, int32 gameVersion){ }
void AFGFallingGiftBundle::PostSaveGame_Implementation(int32 saveVersion, int32 gameVersion){ }
void AFGFallingGiftBundle::PreLoadGame_Implementation(int32 saveVersion, int32 gameVersion){ }
void AFGFallingGiftBundle::PostLoadGame_Implementation(int32 saveVersion, int32 gameVersion){ }
void AFGFallingGiftBundle::GatherDependencies_Implementation(TArray<UObject*>& out_dependentObjects){ }
bool AFGFallingGiftBundle::NeedTransform_Implementation(){ return bool(); }
bool AFGFallingGiftBundle::ShouldSave_Implementation() const{ return bool(); }
void AFGFallingGiftBundle::GainedSignificance_Implementation(){ }
void AFGFallingGiftBundle::LostSignificance_Implementation(){ }
void AFGFallingGiftBundle::UpdateUseState_Implementation(class AFGCharacterPlayer* byCharacter, const FVector& atLocation, class UPrimitiveComponent* componentHit, FUseState& out_useState){ }
void AFGFallingGiftBundle::OnUse_Implementation(class AFGCharacterPlayer* byCharacter, const FUseState& state){ }
void AFGFallingGiftBundle::OnUseStop_Implementation(class AFGCharacterPlayer* byCharacter, const FUseState& state){ }
bool AFGFallingGiftBundle::IsUseable_Implementation() const{ return bool(); }
void AFGFallingGiftBundle::StartIsLookedAt_Implementation(class AFGCharacterPlayer* byCharacter, const FUseState& state){ }
FText AFGFallingGiftBundle::GetLookAtDecription_Implementation(class AFGCharacterPlayer* byCharacter, const FUseState& state) const{ return FText(); }
void AFGFallingGiftBundle::StopIsLookedAt_Implementation(class AFGCharacterPlayer* byCharacter, const FUseState& state){ }
float AFGFallingGiftBundle::GetFallingSpeed() const{ return float(); }
void AFGFallingGiftBundle::SetIsFalling(bool isFalling){ }
bool AFGFallingGiftBundle::CanBePickedUp(class AFGCharacterPlayer* byCharacter) const{ return bool(); }
void AFGFallingGiftBundle::SelectNewRandomReward(){ }
void AFGFallingGiftBundle::HandleLanding(const FHitResult& sweepResult){ }
void AFGFallingGiftBundle::OnRep_IsFalling(){ }
void AFGFallingGiftBundle::OnRep_SelectedRandomRewardIndex(){ }
void AFGFallingGiftBundle::OnRep_WasPickedUp(){ }
void AFGFallingGiftBundle::OnRep_HasLanded(){ }
void AFGFallingGiftBundle::PickupByPlayer(class AFGCharacterPlayer* player){ }
void AFGFallingGiftBundle::CacheExpectedLandingZ(){ }
void AFGFallingGiftBundle::Multicast_PickedUpByPlayer_Implementation(class AFGCharacterPlayer* player){ }
void AFGFallingGiftBundle::OnLostSignificance_Implementation(){ }
void AFGFallingGiftBundle::OnGainedSignificance_Implementation(){ }
void AFGFallingGiftBundle::OnPickup_Implementation(AFGCharacterPlayer* player){ }
void AFGFallingGiftBundle::OnLanded_Implementation(){ }
void AFGFallingGiftBundle::OnStopFalling_Implementation(){ }
void AFGFallingGiftBundle::OnBeginFalling_Implementation(){ }
