#include "Buildables/FGBuildableElevator.h"
#include "Components/SceneComponent.h"
#include "FGPowerConnectionComponent.h"
#include "Net/UnrealNetwork.h"

AFGBuildableElevator::AFGBuildableElevator() : Super() {
	this->mElevatorSparseDataCDO = nullptr;
	this->mElevatorCabin = nullptr;
	this->mSpeed = 100.0;
	this->mHeight = 0.0;
	this->mLockedMovementDirection = EElevatorDirection::EED_Up;
	this->mHeightOfCabin = 0.0;
	this->mSongID = 0;
	this->mCurrentFloorStop = nullptr;
	this->mDurationToOpenDoors = 1.0;
	this->mDurationToWaitAtStop = 3.0;
	this->mDurationToCloseDoors = 1.0;
	this->mDurationPauseBeforeMove = 0.5;
	this->mDurationPausePowerOutage = 2.0;
	this->mDurationPauseBeforeDoorOpen = 0.5;
	this->mPowerConnectionComponent = CreateDefaultSubobject<UFGPowerConnectionComponent>(TEXT("PowerConnection "));
	this->mPowerConnectionComponent->SetMobility(EComponentMobility::Movable);
	this->mElevatorState = EElevatorState::EES_NONE;
	this->mPowerConsumption = 20.0;
	this->mMinimumProducingTime = 0.0;
	this->mPowerConnectionComponent->SetupAttachment(RootComponent);
}
void AFGBuildableElevator::PostLoadGame_Implementation(int32 saveVersion, int32 gameVersion){ Super::PostLoadGame_Implementation(saveVersion, gameVersion); }
void AFGBuildableElevator::BeginPlay(){ Super::BeginPlay(); }
void AFGBuildableElevator::EndPlay(const EEndPlayReason::Type EndPlayReason){ Super::EndPlay(EndPlayReason); }
void AFGBuildableElevator::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const {
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AFGBuildableElevator, mElevatorCabin);
	DOREPLIFETIME(AFGBuildableElevator, mHeight);
	DOREPLIFETIME(AFGBuildableElevator, mLockedMovementDirection);
	DOREPLIFETIME(AFGBuildableElevator, mFloorStopInfos);
	DOREPLIFETIME(AFGBuildableElevator, mQueuedStopIndexes);
	DOREPLIFETIME(AFGBuildableElevator, mHeightOfCabin);
	DOREPLIFETIME(AFGBuildableElevator, mSongID);
	DOREPLIFETIME(AFGBuildableElevator, mElevatorState);
}
int32 AFGBuildableElevator::GetDismantleRefundReturnsMultiplier() const{ return Super::GetDismantleRefundReturnsMultiplier(); }
void AFGBuildableElevator::OnBuildEffectFinished(){ Super::OnBuildEffectFinished(); }
void AFGBuildableElevator::OnBuildEffectActorFinished(){ Super::OnBuildEffectActorFinished(); }
void AFGBuildableElevator::GetDismantleDisqualifiers_Implementation(TArray<TSubclassOf<UFGConstructDisqualifier>>& out_dismantleDisqualifiers, const TArray<AActor*>& allSelectedActors) const{ Super::GetDismantleDisqualifiers_Implementation(out_dismantleDisqualifiers, allSelectedActors); }
void AFGBuildableElevator::GetChildDismantleActors_Implementation(TArray<AActor*>& out_ChildDismantleActors) const{ Super::GetChildDismantleActors_Implementation(out_ChildDismantleActors); }
bool AFGBuildableElevator::CanDismantle_Implementation() const{ return Super::CanDismantle_Implementation(); }
void AFGBuildableElevator::ApplyCustomizationData_Native(const FFactoryCustomizationData& customizationData){ Super::ApplyCustomizationData_Native(customizationData); }
void AFGBuildableElevator::Factory_Tick(float dt){ Super::Factory_Tick(dt); }
bool AFGBuildableElevator::CanProduce_Implementation() const{ return Super::CanProduce_Implementation(); }
void AFGBuildableElevator::Factory_TickProducing(float dt){ Super::Factory_TickProducing(dt); }
void AFGBuildableElevator::Factory_StartProducing(){ Super::Factory_StartProducing(); }
void AFGBuildableElevator::Factory_StopProducing(){ Super::Factory_StopProducing(); }
void AFGBuildableElevator::GetChildClearanceOutlineActors_Implementation(TArray<AActor*>& out_actors) const{ Super::GetChildClearanceOutlineActors_Implementation(out_actors); }
const TArray<AFGCharacterPlayer*>& AFGBuildableElevator::GetOccupyingCharacters(){ return *(new TArray<AFGCharacterPlayer*>()); }
const TArray<APawn*>& AFGBuildableElevator::GetOccupyingPawns(){ return *(new TArray<APawn*>()); }
void AFGBuildableElevator::AddOccupyingPawn(APawn* pawn) {}
void AFGBuildableElevator::RemoveOccupyingPawn(APawn* pawn) {}
int32 AFGBuildableElevator::GetIndexOfFloorStop(AFGBuildableElevatorFloorStop* floorStop) const{ return 0; }
bool AFGBuildableElevator::HasFloorAtHeight(float height) const{ return false; }
bool AFGBuildableElevator::HasFloorAtHeightFromFloorInfos(const TArray<FElevatorFloorStopInfo>& floorInfos, float height){ return false; }
bool AFGBuildableElevator::HasFloorInRange(float minHeight, float maxHeight) const{ return false; }
bool AFGBuildableElevator::HasFloorInRangeFromFloorInfos(const TArray<FElevatorFloorStopInfo>& floorInfos, float minHeight, float maxHeight){ return false; }
void AFGBuildableElevator::GetFloorStopInfos(TArray<FElevatorFloorStopInfo>& out_floorInfos){ }
float AFGBuildableElevator::GetDurationOfCurrentElevatorState(){ return 0; }
const FElevatorFloorStopInfo& AFGBuildableElevator::GetFloorStopInfoNearestHeight(float height, bool mustNotMatch, EElevatorDirection dir){ return *(new FElevatorFloorStopInfo()); }
const FElevatorFloorStopInfo& AFGBuildableElevator::GetFloorStopInfoByIndex(int32 index){ return *(new FElevatorFloorStopInfo()); }
void AFGBuildableElevator::SetNameOfFloorStop(AFGBuildableElevatorFloorStop* floorStop, const FString& floorStopName){ }
void AFGBuildableElevator::SetIconForFloorStop(AFGBuildableElevatorFloorStop* floorStop, int32 iconId){ }
void AFGBuildableElevator::SetIconColorForFloorStop(AFGBuildableElevatorFloorStop* floorStop, FLinearColor color){ }
int32 AFGBuildableElevator::IndexOfFloorStopInArray(const TArray<FElevatorFloorStopInfo>& infoArray, const FElevatorFloorStopInfo& info){ return 0; }
void AFGBuildableElevator::OnRep_FloorStops(){ }
void AFGBuildableElevator::RequestGotoFloorStop(AFGBuildableElevatorFloorStop* floorStop){ }
void AFGBuildableElevator::CabinReachedDestination(AFGBuildableElevatorFloorStop* floorStop){ }
void AFGBuildableElevator::UpdateStopSequence(){ }
void AFGBuildableElevator::SortFloorStopsByHeightAndDirection(TArray<FElevatorFloorStopInfo>& infoArray, EElevatorDirection dir, float testHeight){ }
bool AFGBuildableElevator::SnapLocationToBestNewStopLocation(FVector& location, float stepHeight){ return false; }
void AFGBuildableElevator::OnRep_ElevatorState(){ }
void AFGBuildableElevator::SetQueuedStopIndices(const TArray<int32>& queuedStops){ }
void AFGBuildableElevator::OnRep_QueuedStopIndexes(){ }
void AFGBuildableElevator::RegisterFloorStopWithElevator(AFGBuildableElevatorFloorStop* floorStop){ }
void AFGBuildableElevator::UnregisterFloorStopWithElevator(AFGBuildableElevatorFloorStop* floorStop){ }
void AFGBuildableElevator::ConnectFloorStopPower(AFGBuildableElevatorFloorStop* floorStop){ }
void AFGBuildableElevator::CopyFloorStopInfoFrom(AFGBuildableElevator* from){ }
void AFGBuildableElevator::SetSongID(uint8 songId){ }
void AFGBuildableElevator::OnRep_SongID(){ }
bool AFGBuildableElevator::IsPointInElevatorCabin(const FVector& location) const{ return false; }
void AFGBuildableElevator::BeginMoveToFloorStop(const FElevatorFloorStopInfo& floorInfo){ }
void AFGBuildableElevator::DebugLogQueuedArray(){ }
void AFGBuildableElevator::SetElevatorState(EElevatorState newState){ }
#if WITH_EDITOR
void AFGBuildableElevator::PostEditChangeChainProperty(FPropertyChangedChainEvent& PropertyChangedEvent){ Super::PostEditChangeChainProperty(PropertyChangedEvent); }
#endif
TArray<class AFGBuildableElevatorFloorStop*> AFGBuildableElevator::GetElevatorFloorStops() const{ return TArray<AFGBuildableElevatorFloorStop*>(); }
TArray<struct FInstanceData> AFGBuildableElevator::GetActorLightweightInstanceData_Implementation() const{ return Super::GetActorLightweightInstanceData_Implementation(); }
