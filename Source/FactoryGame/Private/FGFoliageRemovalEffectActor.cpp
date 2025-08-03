#include "FGFoliageRemovalEffectActor.h"
#include "Components/SceneComponent.h"
#include "Net/UnrealNetwork.h"

AFGFoliageRemovalEffectActor::AFGFoliageRemovalEffectActor() : Super() {
	this->bReplicates = true;
	this->NetCullDistanceSquared = 400000000.0;
	this->RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	this->RootComponent->SetMobility(EComponentMobility::Movable);
}
void AFGFoliageRemovalEffectActor::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const {
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AFGFoliageRemovalEffectActor, Transforms);
	DOREPLIFETIME(AFGFoliageRemovalEffectActor, Meshes);
}
void AFGFoliageRemovalEffectActor::BeginPlay(){ Super::BeginPlay(); }