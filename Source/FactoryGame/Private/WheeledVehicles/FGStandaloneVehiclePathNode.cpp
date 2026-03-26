#include "WheeledVehicles/FGStandaloneVehiclePathNode.h"
#include "Components/SceneComponent.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"

AFGStandaloneVehiclePathNode::AFGStandaloneVehiclePathNode() : Super() {
	this->mCollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionComponent"));
	this->mCollisionComponent->SetMobility(EComponentMobility::Movable);
	this->mVisualizationMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("VisualizationComponent"));
	this->mVisualizationMeshComponent->SetMobility(EComponentMobility::Movable);
	this->mSignificanceRange = 15000.0;
	this->mCollisionComponent->SetupAttachment(RootComponent);
	this->mVisualizationMeshComponent->SetupAttachment(RootComponent);
}
void AFGStandaloneVehiclePathNode::BeginPlay(){ Super::BeginPlay(); }
void AFGStandaloneVehiclePathNode::EndPlay(const EEndPlayReason::Type EndPlayReason){ Super::EndPlay(EndPlayReason); }
float AFGStandaloneVehiclePathNode::GetSignificanceRange_Implementation() const{ return IFGSignificanceInterface::GetSignificanceRange_Implementation(); }
void AFGStandaloneVehiclePathNode::GainedSignificance_Implementation(){ IFGSignificanceInterface::GainedSignificance_Implementation(); }
void AFGStandaloneVehiclePathNode::LostSignificance_Implementation(){ IFGSignificanceInterface::LostSignificance_Implementation(); }
void AFGStandaloneVehiclePathNode::SetVisualizationEnabled(bool newVisualizationEnabled){ }
void AFGStandaloneVehiclePathNode::OnNodeConnectionsChanged(){ Super::OnNodeConnectionsChanged(); }
void AFGStandaloneVehiclePathNode::UpdateVisualizationOrientation() const{ }
void AFGStandaloneVehiclePathNode::UpdateCollisionResponse() const{ }
