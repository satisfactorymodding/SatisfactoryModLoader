#include "Buildables/FGBuildableElevatorFloorStop.h"
#include "Components/SceneComponent.h"
#include "FGColoredInstanceMeshProxy.h"
#include "Net/UnrealNetwork.h"

AFGBuildableElevatorFloorStop::AFGBuildableElevatorFloorStop(): Super() {
	this->mMesh = CreateDefaultSubobject<UFGColoredInstanceMeshProxy>(TEXT("Mesh"));
	this->mMesh->SetMobility(EComponentMobility::Movable);
	this->mButtonMesh = CreateDefaultSubobject<UFGColoredInstanceMeshProxy>(TEXT("ButtonMesh"));
	this->mButtonMesh->SetMobility(EComponentMobility::Movable);
	this->mSignificanceRange = 12000.0;
	this->mFloorRelevantElevatorState = EElevatorState::EES_NONE;
	this->mElevator = nullptr;
	this->mCachedQueuedStatus = EElevatorFloorStopQueuedStatus::EEFSQS_None;
	this->mCachedFloorStopInfo.FloorStop = nullptr;
	this->mCachedFloorStopInfo.FloorName = TEXT("");
	this->mCachedFloorStopInfo.IconId = -1;
	this->mCachedFloorStopInfo.IconColor = FLinearColor(1.0, 1.0, 1.0, 1.0);
	this->mCachedFloorStopInfo.Height = -1;
	this->mCachedFloorStopInfo.CachedIconTexture = nullptr;
	this->mMesh->SetupAttachment(RootComponent);
	this->mButtonMesh->SetupAttachment(RootComponent);
}
void AFGBuildableElevatorFloorStop::BeginPlay(){ Super::BeginPlay(); }
void AFGBuildableElevatorFloorStop::EndPlay(const EEndPlayReason::Type EndPlayReason){ Super::EndPlay(EndPlayReason); }
void AFGBuildableElevatorFloorStop::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const {
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AFGBuildableElevatorFloorStop, mFloorRelevantElevatorState);
	DOREPLIFETIME(AFGBuildableElevatorFloorStop, mElevator);
}
void AFGBuildableElevatorFloorStop::SetBuildableHiddenInGame(bool hide, bool disableCollisionOnHide){ Super::SetBuildableHiddenInGame(hide, disableCollisionOnHide); }
bool AFGBuildableElevatorFloorStop::CanDismantle_Implementation() const{ return Super::CanDismantle_Implementation(); }
void AFGBuildableElevatorFloorStop::GetDismantleDisqualifiers_Implementation(TArray<TSubclassOf<UFGConstructDisqualifier>>& out_dismantleDisqualifiers, const TArray<AActor*>& allSelectedActors) const{ Super::GetDismantleDisqualifiers_Implementation(out_dismantleDisqualifiers, allSelectedActors); }
void AFGBuildableElevatorFloorStop::GetChildDismantleActors_Implementation(TArray<AActor*>& out_ChildDismantleActors) const{ Super::GetChildDismantleActors_Implementation(out_ChildDismantleActors); }
bool AFGBuildableElevatorFloorStop::IsUseable_Implementation() const{ return Super::IsUseable_Implementation(); }
void AFGBuildableElevatorFloorStop::UpdateUseState_Implementation(AFGCharacterPlayer* byCharacter, const FVector& atLocation, UPrimitiveComponent* componentHit, FUseState& out_useState){ Super::UpdateUseState_Implementation(byCharacter, atLocation, componentHit, out_useState); }
void AFGBuildableElevatorFloorStop::OnUse_Implementation(AFGCharacterPlayer* byCharacter, const FUseState& state){ Super::OnUse_Implementation(byCharacter, state); }
void AFGBuildableElevatorFloorStop::StartIsLookedAt_Implementation(AFGCharacterPlayer* byCharacter, const FUseState& state){ Super::StartIsLookedAt_Implementation(byCharacter, state); }
void AFGBuildableElevatorFloorStop::StopIsLookedAt_Implementation(AFGCharacterPlayer* byCharacter, const FUseState& state){ Super::StopIsLookedAt_Implementation(byCharacter, state); }
FText AFGBuildableElevatorFloorStop::GetLookAtDecription_Implementation(AFGCharacterPlayer* byCharacter, const FUseState& state) const{ return Super::GetLookAtDecription_Implementation(byCharacter, state); }
void AFGBuildableElevatorFloorStop::SetOwningElevator(class AFGBuildableElevator* elevator){ }
void AFGBuildableElevatorFloorStop::ElevatorUpdateStateAtThisStop(EElevatorState newState){ }
void AFGBuildableElevatorFloorStop::OnRep_FloorRelevantElevatorState(){ }
void AFGBuildableElevatorFloorStop::OnRep_Elevator(){ }
void AFGBuildableElevatorFloorStop::NotifyFloorStopInfoHasChanged(const FElevatorFloorStopInfo& floorStopInfo){ }
void AFGBuildableElevatorFloorStop::NotifyPowerStatusChanged(bool hasPower){ }
void AFGBuildableElevatorFloorStop::NotifyQueuedStatus(EElevatorFloorStopQueuedStatus status){ }
void AFGBuildableElevatorFloorStop::UpdateButton(EElevatorFloorStopQueuedStatus status){ }