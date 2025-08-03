#include "FGElevatorCabin.h"
#include "Components/BoxComponent.h"
#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"
#include "FGElevatorMovementComponent.h"
#include "Net/UnrealNetwork.h"

AFGElevatorCabin::AFGElevatorCabin() : Super() {
	this->mInteractWidgetClass = nullptr;
	this->mMovementComponent = CreateDefaultSubobject<UFGElevatorMovementComponent>(TEXT("ElevatorMovementComponent"));
	this->mCollisionComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionComp"));
	this->mCollisionComponent->SetMobility(EComponentMobility::Movable);
	this->mButtonArraySceneParent = CreateDefaultSubobject<USceneComponent>(TEXT("ButtonArraySceneParent"));
	this->mButtonArraySceneParent->SetMobility(EComponentMobility::Movable);
	this->mButtonMesh = nullptr;
	this->mButtonBackgroundMaterialBase = nullptr;
	this->mButtonIconMaterialBase = nullptr;
	this->mMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	this->mMeshComponent->SetupAttachment(mCollisionComponent);
	this->mMeshComponent->SetMobility(EComponentMobility::Movable);
	this->mConsoleMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ConsoleMeshComp"));
	this->mConsoleMeshComponent->SetupAttachment(mCollisionComponent);
	this->mConsoleMeshComponent->SetMobility(EComponentMobility::Movable);
	this->mButtonArraySceneParent->SetupAttachment(mConsoleMeshComponent);
	this->mButtonRadius = 5.0;
	this->mFloorStopButtonsTransform = FTransform(FQuat::Identity, FVector::ZeroVector, FVector::OneVector);
	this->mFloorStopButtonsExtents = FVector::ZeroVector;
	this->mWidgetInteractTransform = FTransform(FQuat::Identity, FVector::ZeroVector, FVector::OneVector);
	this->mWidgetInteractExtents = FVector::ZeroVector;
	this->mCachedElevatorState = EElevatorState::EES_NONE;
	this->mOwningElevator = nullptr;
	this->mCurrentFloorStopInfo.FloorStop = nullptr;
	this->mCurrentFloorStopInfo.FloorName = TEXT("");
	this->mCurrentFloorStopInfo.IconId = -1;
	this->mCurrentFloorStopInfo.IconColor = FLinearColor(1.0, 1.0, 1.0, 1.0);
	this->mCurrentFloorStopInfo.Height = -1;
	this->mCurrentFloorStopInfo.CachedIconTexture = nullptr;
	this->bReplicates = true;
	this->RootComponent = mCollisionComponent;
}
void AFGElevatorCabin::BeginPlay(){ Super::BeginPlay(); }
void AFGElevatorCabin::EndPlay(EEndPlayReason::Type reason){ Super::EndPlay(reason); }
void AFGElevatorCabin::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const {
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AFGElevatorCabin, mOwningElevator);
	DOREPLIFETIME(AFGElevatorCabin, mCurrentFloorStopInfo);
}
bool AFGElevatorCabin::CanBeBaseForCharacter(APawn* Pawn) const{ return Super::CanBeBaseForCharacter(Pawn); }
bool AFGElevatorCabin::IsUseable_Implementation() const{ return IFGUseableInterface::IsUseable_Implementation(); }
void AFGElevatorCabin::UpdateUseState_Implementation(AFGCharacterPlayer* byCharacter, const FVector& atLocation, UPrimitiveComponent* componentHit, FUseState& out_useState){ IFGUseableInterface::UpdateUseState_Implementation(byCharacter, atLocation, componentHit, out_useState); }
void AFGElevatorCabin::OnUse_Implementation(AFGCharacterPlayer* byCharacter, const FUseState& state){ IFGUseableInterface::OnUse_Implementation(byCharacter, state); }
void AFGElevatorCabin::StartIsLookedAt_Implementation(AFGCharacterPlayer* byCharacter, const FUseState& state){ IFGUseableInterface::StartIsLookedAt_Implementation(byCharacter, state); }
void AFGElevatorCabin::StopIsLookedAt_Implementation(AFGCharacterPlayer* byCharacter, const FUseState& state){ IFGUseableInterface::StopIsLookedAt_Implementation(byCharacter, state); }
FText AFGElevatorCabin::GetLookAtDecription_Implementation(AFGCharacterPlayer* byCharacter, const FUseState& state) const{ return IFGUseableInterface::GetLookAtDecription_Implementation(byCharacter, state); }
void AFGElevatorCabin::GainedSignificance_Implementation(){ IFGSignificanceInterface::GainedSignificance_Implementation(); }
void AFGElevatorCabin::LostSignificance_Implementation(){ IFGSignificanceInterface::LostSignificance_Implementation(); }
float AFGElevatorCabin::GetSignificanceRange(){ return IFGSignificanceInterface::GetSignificanceRange(); }
void AFGElevatorCabin::OnPawnEnterCabin(APawn* pawn, const FVector& lastLocation){  }
void AFGElevatorCabin::OnPawnExitCabin(APawn* pawn){  }
void AFGElevatorCabin::NotifyElevatorStateChanged(EElevatorState newState){  }
void AFGElevatorCabin::SetTargetFloorStop(const FElevatorFloorStopInfo& stopInfo, bool teleport){  }
void AFGElevatorCabin::AddForceControlPoint(const FVector& worldLocation){  }
void AFGElevatorCabin::ClearControlPoints(){  }
EElevatorConsoleLocation AFGElevatorCabin::GetConsoleTypeUseLocation(const FVector& useLocation){ return EElevatorConsoleLocation(); }
int32 AFGElevatorCabin::GetFloorStopIndexForUseLocation(const FVector& useLocation, const FUseState& state){ return int32(); }
void AFGElevatorCabin::TeleportToFloorStop(const FElevatorFloorStopInfo& floorStop){  }
void AFGElevatorCabin::SetOwningElevator(AFGBuildableElevator* elevator, float height){  }
float AFGElevatorCabin::GetTimeToDestination() const{ return float(); }
void AFGElevatorCabin::OnMovementStopped(){  }
void AFGElevatorCabin::OnRep_CurrentFloorStopInfo(FElevatorFloorStopInfo& lastFloorStopInfo){  }
void AFGElevatorCabin::UpdateFloorStops(){  }
void AFGElevatorCabin::UpdateCabinVisibility(){  }
void AFGElevatorCabin::SetQueuedFloors(const TArray<int32>& queuedFloorIndexes){  }
void AFGElevatorCabin::UpdateQueuedFloorVisuals(){  }
void AFGElevatorCabin::SetCabinHidden(bool newHidden){  }
void AFGElevatorCabin::OnRep_OwningElevator(){  }
void AFGElevatorCabin::RebuildButtonMeshComponents(bool iconsOnly){  }
void AFGElevatorCabin::RemoveButtonMeshComponents(){  }
void AFGElevatorCabin::ClientWaitForIconSubsystem(){  }
void AFGElevatorCabin::NotifyPowerStatusChanged(bool hasPower){  }
UBoxComponent* AFGElevatorCabin::GetOccupyingBoxCollisionComp_Implementation() const{ return nullptr; }
void AFGElevatorCabin::ApplyCustomizatinDataFromElevator(){  }
#if WITH_EDITOR
void AFGElevatorCabin::PostCDOCompiled(const FPostCDOCompiledContext& Context){ Super::PostCDOCompiled(Context); }
#endif
