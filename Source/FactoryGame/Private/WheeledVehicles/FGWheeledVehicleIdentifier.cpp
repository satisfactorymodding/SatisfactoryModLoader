#include "WheeledVehicles/FGWheeledVehicleIdentifier.h"
#include "Net/UnrealNetwork.h"

AFGWheeledVehicleIdentifier::AFGWheeledVehicleIdentifier() : Super() {
	this->mOwnerVehicleClass = nullptr;
	this->mOwnerVehicle = nullptr;
	this->mVehicleName = INVTEXT("");
	this->mIsAutopilotEnabled = false;
	this->mCurrentAutopilotErrorStatus = EVehicleAutopilotErrorStatus::None;
	this->mCurrentTargetWaypointIndex = -1;
	this->mIsCurrentlyDocking = false;
	this->mFuelTypeDescriptor = nullptr;
	this->bAlwaysRelevant = true;
	this->bReplicates = true;
	this->NetDormancy = ENetDormancy::DORM_DormantAll;
}
void AFGWheeledVehicleIdentifier::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const {
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AFGWheeledVehicleIdentifier, mOwnerVehicleClass);
	DOREPLIFETIME(AFGWheeledVehicleIdentifier, mOwnerVehicle);
	DOREPLIFETIME(AFGWheeledVehicleIdentifier, mVehicleName);
	DOREPLIFETIME(AFGWheeledVehicleIdentifier, mIsAutopilotEnabled);
	DOREPLIFETIME(AFGWheeledVehicleIdentifier, mVehicleRoute);
	DOREPLIFETIME(AFGWheeledVehicleIdentifier, mCurrentFromPathNodeGuid);
	DOREPLIFETIME(AFGWheeledVehicleIdentifier, mCurrentToPathNodeGuid);
	DOREPLIFETIME(AFGWheeledVehicleIdentifier, mLastEditedBy);
	DOREPLIFETIME(AFGWheeledVehicleIdentifier, mCurrentAutopilotErrorStatus);
	DOREPLIFETIME(AFGWheeledVehicleIdentifier, mCurrentTargetWaypointIndex);
	DOREPLIFETIME(AFGWheeledVehicleIdentifier, mIsCurrentlyDocking);
	DOREPLIFETIME(AFGWheeledVehicleIdentifier, mFuelTypeDescriptor);
}
void AFGWheeledVehicleIdentifier::BeginPlay(){ Super::BeginPlay(); }
void AFGWheeledVehicleIdentifier::EndPlay(const EEndPlayReason::Type EndPlayReason){ Super::EndPlay(EndPlayReason); }
bool AFGWheeledVehicleIdentifier::ShouldSave_Implementation() const{ return IFGSaveInterface::ShouldSave_Implementation(); }
void AFGWheeledVehicleIdentifier::PostLoadGame_Implementation(int32 saveVersion, int32 gameVersion){ IFGSaveInterface::PostLoadGame_Implementation(saveVersion, gameVersion); }
bool AFGWheeledVehicleIdentifier::AddAsRepresentation(){ return false; }
bool AFGWheeledVehicleIdentifier::UpdateRepresentation(){ return false; }
bool AFGWheeledVehicleIdentifier::RemoveAsRepresentation(){ return false; }
bool AFGWheeledVehicleIdentifier::IsActorStatic(){ return IFGActorRepresentationInterface::IsActorStatic(); }
FVector AFGWheeledVehicleIdentifier::GetRealActorLocation(){ return FVector(); }
FRotator AFGWheeledVehicleIdentifier::GetRealActorRotation(){ return IFGActorRepresentationInterface::GetRealActorRotation(); }
ERepresentationType AFGWheeledVehicleIdentifier::GetActorRepresentationType(){ return ERepresentationType(); }
bool AFGWheeledVehicleIdentifier::GetActorShouldShowOnMap(){ return false; }
bool AFGWheeledVehicleIdentifier::GetActorShouldShowInCompass(){ return false; }
FText AFGWheeledVehicleIdentifier::GetActorRepresentationText(){ return FText(); }
FPlayerInfoHandle AFGWheeledVehicleIdentifier::GetLastEditedBy() const{ return IFGActorRepresentationInterface::GetLastEditedBy(); }
UTexture2D* AFGWheeledVehicleIdentifier::GetActorRepresentationTexture(){ return nullptr; }
FLinearColor AFGWheeledVehicleIdentifier::GetActorRepresentationColor(){ return FLinearColor(); }
UMaterialInterface* AFGWheeledVehicleIdentifier::GetActorRepresentationCompassMaterial(){ return nullptr; }
void AFGWheeledVehicleIdentifier::SetActorRepresentationText(const FText& newText){ IFGActorRepresentationInterface::SetActorRepresentationText(newText); }
void AFGWheeledVehicleIdentifier::SetActorLastEditedByHandle(const FPlayerInfoHandle& playerInfoHandle){ IFGActorRepresentationInterface::SetActorLastEditedByHandle(playerInfoHandle); }
void AFGWheeledVehicleIdentifier::UpdateRepresentation_Local(){ }
void AFGWheeledVehicleIdentifier::SetVehicleName(const FText& newVehicleName){ }
bool AFGWheeledVehicleIdentifier::CanEnableAutopilot() const{ return false; }
void AFGWheeledVehicleIdentifier::SetAutopilotEnabled(bool newAutopilotEnabled){ }
void AFGWheeledVehicleIdentifier::Internal_SetVehicleName(const FText& newVehicleName){ }
void AFGWheeledVehicleIdentifier::RemoveWaypointAtIndex(int32 waypointIndex){ }
void AFGWheeledVehicleIdentifier::AddWaypoint(const FGuid& waypointGuid){ }
void AFGWheeledVehicleIdentifier::InsertWaypoint(int32 waypointIndex, const FGuid& waypointGuid){ }
void AFGWheeledVehicleIdentifier::SetVehicleRoute(const TArray<FGuid>& newVehicleRoute){ }
void AFGWheeledVehicleIdentifier::SanitizeVehicleRoute(){ }
void AFGWheeledVehicleIdentifier::SetOwnerVehicle(AFGWheeledVehicle* ownerVehicle){ }
void AFGWheeledVehicleIdentifier::SetCurrentVehicleSegment(const FGuid& fromPathNodeGuid, const FGuid& toPathNodeGuid){ }
void AFGWheeledVehicleIdentifier::SetCurrentTargetWaypoint(int32 newTargetWaypointIndex){ }
void AFGWheeledVehicleIdentifier::SetCurrentAutopilotErrorStatus(EVehicleAutopilotErrorStatus newAutopilotErrorStatus){ }
void AFGWheeledVehicleIdentifier::SetIsCurrentlyDocking(bool newIsCurrentlyDocking){ }
void AFGWheeledVehicleIdentifier::SetFuelTypeDescriptor(const TSubclassOf<UFGItemDescriptor>& newFuelDescriptor){ }
void AFGWheeledVehicleIdentifier::OnVehicleSubsystemValid(){ }
void AFGWheeledVehicleIdentifier::OnRep_CurrentAutopilotErrorStatus(){ }
void AFGWheeledVehicleIdentifier::OnRep_IsAutopilotEnabled(){ }
