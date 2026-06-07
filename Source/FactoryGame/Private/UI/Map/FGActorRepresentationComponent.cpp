#include "UI/Map/FGActorRepresentationComponent.h"

UFGActorRepresentationComponent::UFGActorRepresentationComponent() : Super() {
	this->mActorRepresentationTexture = nullptr;
	this->mActorRepresentationCompassMaterial = nullptr;
	this->mActorRepresentationText = INVTEXT("");
	this->mActorRepresentationColor = FLinearColor(1.0, 1.0, 1.0, 1.0);
	this->mActorRepresentationType = ERepresentationType::RT_Default;
	this->mShouldShowInCompass = false;
	this->mShouldShowOnMap = true;
	this->mFogOfWarRevealType = EFogOfWarRevealType::FOWRT_None;
	this->mFogOfWarRevealRadius = 0.0;
	this->mCompassViewDistance = ECompassViewDistance::CVD_Off;
}
bool UFGActorRepresentationComponent::AddAsRepresentation(){ return false; }
bool UFGActorRepresentationComponent::UpdateRepresentation(){ return false; }
bool UFGActorRepresentationComponent::RemoveAsRepresentation(){ return false; }
bool UFGActorRepresentationComponent::IsActorStatic(){ return IFGActorRepresentationInterface::IsActorStatic(); }
FVector UFGActorRepresentationComponent::GetRealActorLocation(){ return FVector(); }
FRotator UFGActorRepresentationComponent::GetRealActorRotation(){ return IFGActorRepresentationInterface::GetRealActorRotation(); }
class UTexture2D* UFGActorRepresentationComponent::GetActorRepresentationTexture(){ return nullptr; }
UMaterialInterface* UFGActorRepresentationComponent::GetActorRepresentationCompassMaterial(){ return nullptr; }
FText UFGActorRepresentationComponent::GetActorRepresentationText(){ return FText(); }
void UFGActorRepresentationComponent::SetActorRepresentationText(const FText& newText){ IFGActorRepresentationInterface::SetActorRepresentationText(newText); }
FLinearColor UFGActorRepresentationComponent::GetActorRepresentationColor(){ return FLinearColor(); }
void UFGActorRepresentationComponent::SetActorRepresentationColor(FLinearColor newColor){ IFGActorRepresentationInterface::SetActorRepresentationColor(newColor); }
ERepresentationType UFGActorRepresentationComponent::GetActorRepresentationType(){ return ERepresentationType(); }
bool UFGActorRepresentationComponent::GetActorShouldShowInCompass(){ return false; }
bool UFGActorRepresentationComponent::GetActorShouldShowOnMap(){ return false; }
EFogOfWarRevealType UFGActorRepresentationComponent::GetActorFogOfWarRevealType(){ return IFGActorRepresentationInterface::GetActorFogOfWarRevealType(); }
float UFGActorRepresentationComponent::GetActorFogOfWarRevealRadius(){ return IFGActorRepresentationInterface::GetActorFogOfWarRevealRadius(); }
ECompassViewDistance UFGActorRepresentationComponent::GetActorCompassViewDistance(){ return IFGActorRepresentationInterface::GetActorCompassViewDistance(); }
void UFGActorRepresentationComponent::SetActorCompassViewDistance(ECompassViewDistance compassViewDistance){ IFGActorRepresentationInterface::SetActorCompassViewDistance(compassViewDistance); }
FPlayerInfoHandle UFGActorRepresentationComponent::GetLastEditedBy() const{ return IFGActorRepresentationInterface::GetLastEditedBy(); }
void UFGActorRepresentationComponent::SetActorLastEditedByHandle(const FPlayerInfoHandle& playerInfoHandle){ IFGActorRepresentationInterface::SetActorLastEditedByHandle(playerInfoHandle); }
void UFGActorRepresentationComponent::BeginPlay(){ Super::BeginPlay(); }
void UFGActorRepresentationComponent::EndPlay(const EEndPlayReason::Type EndPlayReason){ Super::EndPlay(EndPlayReason); }
