#include "WheeledVehicles/FGDockingStationIdentifier.h"
#include "Net/UnrealNetwork.h"

AFGDockingStationIdentifier::AFGDockingStationIdentifier() : Super() {
	this->mStation = nullptr;
	this->mCachedStationActorLocation = FVector::ZeroVector;
	this->mStationName = INVTEXT("");
	this->mDockingStationStatus = EDockingStationStatus::DSS_Operational;
	this->mBuildingTag = TEXT("");
	this->bAlwaysRelevant = true;
	this->bReplicates = true;
}
void AFGDockingStationIdentifier::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const {
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AFGDockingStationIdentifier, mStation);
	DOREPLIFETIME(AFGDockingStationIdentifier, mCachedStationActorLocation);
	DOREPLIFETIME(AFGDockingStationIdentifier, mStationName);
	DOREPLIFETIME(AFGDockingStationIdentifier, mLastEditedBy);
	DOREPLIFETIME(AFGDockingStationIdentifier, mPathNodeGUID);
	DOREPLIFETIME(AFGDockingStationIdentifier, mDockingStationStatus);
}
void AFGDockingStationIdentifier::BeginPlay(){ Super::BeginPlay(); }
void AFGDockingStationIdentifier::EndPlay(const EEndPlayReason::Type EndPlayReason){ Super::EndPlay(EndPlayReason); }
void AFGDockingStationIdentifier::SetStationName(const FText& newStationName){ }
void AFGDockingStationIdentifier::Internal_SetStationName(const FText& newStationName){ }
void AFGDockingStationIdentifier::Internal_SetDockingStation(AFGBuildableDockingStation* station){ }
void AFGDockingStationIdentifier::Internal_UpdateFromDockingStation(const AFGBuildableDockingStation* station){ }
void AFGDockingStationIdentifier::Internal_SetStationStatus(EDockingStationStatus status){ }
void AFGDockingStationIdentifier::PostLoadGame_Implementation(int32 saveVersion, int32 gameVersion){ IFGSaveInterface::PostLoadGame_Implementation(saveVersion, gameVersion); }
bool AFGDockingStationIdentifier::AddAsRepresentation(){ return false; }
bool AFGDockingStationIdentifier::UpdateRepresentation(){ return false; }
bool AFGDockingStationIdentifier::RemoveAsRepresentation(){ return false; }
bool AFGDockingStationIdentifier::IsActorStatic(){ return IFGActorRepresentationInterface::IsActorStatic(); }
FVector AFGDockingStationIdentifier::GetRealActorLocation(){ return FVector(); }
FRotator AFGDockingStationIdentifier::GetRealActorRotation(){ return IFGActorRepresentationInterface::GetRealActorRotation(); }
UTexture2D* AFGDockingStationIdentifier::GetActorRepresentationTexture(){ return nullptr; }
FText AFGDockingStationIdentifier::GetActorRepresentationText(){ return FText(); }
void AFGDockingStationIdentifier::SetActorRepresentationText(const FText& newText){ IFGActorRepresentationInterface::SetActorRepresentationText(newText); }
FLinearColor AFGDockingStationIdentifier::GetActorRepresentationColor(){ return FLinearColor(); }
void AFGDockingStationIdentifier::SetActorRepresentationColor(FLinearColor newColor){ IFGActorRepresentationInterface::SetActorRepresentationColor(newColor); }
ERepresentationType AFGDockingStationIdentifier::GetActorRepresentationType(){ return ERepresentationType(); }
bool AFGDockingStationIdentifier::GetActorShouldShowInCompass(){ return false; }
bool AFGDockingStationIdentifier::GetActorShouldShowOnMap(){ return false; }
EFogOfWarRevealType AFGDockingStationIdentifier::GetActorFogOfWarRevealType(){ return IFGActorRepresentationInterface::GetActorFogOfWarRevealType(); }
float AFGDockingStationIdentifier::GetActorFogOfWarRevealRadius(){ return IFGActorRepresentationInterface::GetActorFogOfWarRevealRadius(); }
ECompassViewDistance AFGDockingStationIdentifier::GetActorCompassViewDistance(){ return IFGActorRepresentationInterface::GetActorCompassViewDistance(); }
void AFGDockingStationIdentifier::SetActorCompassViewDistance(ECompassViewDistance compassViewDistance){ IFGActorRepresentationInterface::SetActorCompassViewDistance(compassViewDistance); }
UMaterialInterface* AFGDockingStationIdentifier::GetActorRepresentationCompassMaterial(){ return nullptr; }
void AFGDockingStationIdentifier::SetActorLastEditedByHandle(const FPlayerInfoHandle& playerInfoHandle){ IFGActorRepresentationInterface::SetActorLastEditedByHandle(playerInfoHandle); }
void AFGDockingStationIdentifier::OnVehicleSubsystemValid(){ }
