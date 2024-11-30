#include "FGFallingGiftBundle.h"

AFGFallingGiftBundle::AFGFallingGiftBundle(){ }
void AFGFallingGiftBundle::BeginPlay(){ Super::BeginPlay(); }
void AFGFallingGiftBundle::Tick(float DeltaSeconds){ Super::Tick(DeltaSeconds); }
void AFGFallingGiftBundle::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const{ Super::GetLifetimeReplicatedProps(OutLifetimeProps); }
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
