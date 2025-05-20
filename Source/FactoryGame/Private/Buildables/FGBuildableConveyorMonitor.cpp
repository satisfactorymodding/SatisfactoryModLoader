#include "Buildables/FGBuildableConveyorMonitor.h"
#include "Hologram/FGSplineBuildableSnapHologram.h"
#include "Net/UnrealNetwork.h"

AFGBuildableConveyorMonitor::AFGBuildableConveyorMonitor(): Super() {
	this->mIsSignificant = false;
	this->mChainActor = nullptr;
	this->mConveyorBase = nullptr;
	this->mTimePerAverageSectionFromBeltSpeed = 0.0;
	this->mOffsetAlongConveyor = -1.0;
	this->mCalculatedItemsPerMinute = -1;
	this->mTotalTime = 0.0;
	this->mConfidence = 0.0;
	this->mSignificanceRange = 15000.0;
	this->mHologramClass = AFGSplineBuildableSnapHologram::StaticClass();
	this->mToggleDormancyOnInteraction = true;
	this->NetDormancy = ENetDormancy::DORM_DormantAll;
	this->NetCullDistanceSquared = 400000000.0;
}
void AFGBuildableConveyorMonitor::BeginPlay(){ Super::BeginPlay(); }
void AFGBuildableConveyorMonitor::EndPlay(const EEndPlayReason::Type EndPlayReason){ Super::EndPlay(EndPlayReason); }
void AFGBuildableConveyorMonitor::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const {
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AFGBuildableConveyorMonitor, mPropertyReplicator);
	DOREPLIFETIME(AFGBuildableConveyorMonitor, mReplicatedCoreData);
}
void AFGBuildableConveyorMonitor::RegisterInteractingPlayer_Implementation(class AFGCharacterPlayer* player){ Super::RegisterInteractingPlayer_Implementation(player); }
void AFGBuildableConveyorMonitor::UnregisterInteractingPlayer_Implementation(class AFGCharacterPlayer* player){ Super::UnregisterInteractingPlayer_Implementation(player); }
float AFGBuildableConveyorMonitor::GetSignificanceRange(){ return 0; }
void AFGBuildableConveyorMonitor::GainedSignificance_Implementation(){ }
void AFGBuildableConveyorMonitor::LostSignificance_Implementation(){ }
void AFGBuildableConveyorMonitor::SetSnappedSplineBuildable(AFGBuildable* buildable){ Super::SetSnappedSplineBuildable(buildable); }
void AFGBuildableConveyorMonitor::InitializeOffset(bool forceUpdate){ }
AFGBuildableConveyorBase* AFGBuildableConveyorMonitor::GetConveyorBase(){ return nullptr; }
TArray<FItemMonitorData> AFGBuildableConveyorMonitor::GetAverageDataForUIRepresentation(){ return TArray<FItemMonitorData>(); }
void AFGBuildableConveyorMonitor::SetupMonitorData(){ }
void AFGBuildableConveyorMonitor::CalculateItemsPerMinute(){ }
void AFGBuildableConveyorMonitor::UpdatePassedTimeAndItems(double time, int32 numItems){ }
void AFGBuildableConveyorMonitor::PlayerResetMonitorData(){ }
void AFGBuildableConveyorMonitor::ResetMonitorData(AFGConveyorChainActor* chainActor){ }
void AFGBuildableConveyorMonitor::OnRep_ReplicatedCoreData(){ }
void AFGBuildableConveyorMonitor::OnRep_MonitorData(){ }
void AFGBuildableConveyorMonitor::DebugPrintData() const{ }
void AFGBuildableConveyorMonitor::GetConditionalReplicatedProps(TArray<FFGCondReplicatedProperty>& outProps) const{ }
bool AFGBuildableConveyorMonitor::IsPropertyRelevantForConnection(UNetConnection* netConnection, const FProperty* property) const{ return false; }
