#include "Buildables/FGBuildableMergerPriority.h"
#include "Net/UnrealNetwork.h"

AFGBuildableMergerPriority::AFGBuildableMergerPriority() : Super() {
	this->mFactoryTickFunction.TickGroup = ETickingGroup::TG_PrePhysics;
	this->mFactoryTickFunction.EndTickGroup = ETickingGroup::TG_PrePhysics;
	this->mFactoryTickFunction.bTickEvenWhenPaused = false;
	this->mFactoryTickFunction.bCanEverTick = true;
	this->mFactoryTickFunction.bStartWithTickEnabled = true;
	this->mFactoryTickFunction.bAllowTickOnDedicatedServer = true;
	this->mFactoryTickFunction.TickInterval = 0.0;
}
void AFGBuildableMergerPriority::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const {
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AFGBuildableMergerPriority, mInputPriorities);
}
void AFGBuildableMergerPriority::BeginPlay(){ Super::BeginPlay(); }
void AFGBuildableMergerPriority::Factory_Tick(float deltaTime){ Super::Factory_Tick(deltaTime); }
int32 AFGBuildableMergerPriority::GetPriorityByInputIndex(int32 inputIndex) const{ return 0; }
int32 AFGBuildableMergerPriority::GetPriorityByInputConnection(const UFGFactoryConnectionComponent* inputConnection) const{ return 0; }
void AFGBuildableMergerPriority::SetPriorityByInputIndex(int32 inputIndex, int32 newPriority){ }
void AFGBuildableMergerPriority::SetInputPriorities(TArray<int32> newInputPriorities){ }
void AFGBuildableMergerPriority::SetPriorityByInputConnection(const UFGFactoryConnectionComponent* inputConnection, int32 newPriority){ }
void AFGBuildableMergerPriority::OnRep_InputPriorities(){ }
void AFGBuildableMergerPriority::RebuildPriorityGroupInputIndices(){ }
void AFGBuildableMergerPriority::ApplyInputPrioritiesToMesh_Implementation(){ }