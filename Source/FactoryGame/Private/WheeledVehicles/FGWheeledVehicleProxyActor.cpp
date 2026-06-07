#include "WheeledVehicles/FGWheeledVehicleProxyActor.h"
#include "Net/UnrealNetwork.h"

AFGWheeledVehicleProxyActor::AFGWheeledVehicleProxyActor() : Super() {
	this->mOwnerVehicle = nullptr;
	this->mAuthoritativeLocation = FVector::ZeroVector;
	this->mAuthoritativeRotation.X = 0.0;
	this->mAuthoritativeRotation.Y = 0.0;
	this->mAuthoritativeRotation.Z = 0.0;
	this->mAuthoritativeRotation.W = 1.0;
	this->mAuthoritativeLinearVelocity = FVector::ZeroVector;
	this->mHasAuthoritativeMovementData = false;
	this->PrimaryActorTick.TickGroup = ETickingGroup::TG_PrePhysics;
	this->PrimaryActorTick.EndTickGroup = ETickingGroup::TG_PrePhysics;
	this->PrimaryActorTick.bTickEvenWhenPaused = false;
	this->PrimaryActorTick.bCanEverTick = true;
	this->PrimaryActorTick.bStartWithTickEnabled = true;
	this->PrimaryActorTick.bAllowTickOnDedicatedServer = true;
	this->PrimaryActorTick.TickInterval = 0.0;
	this->bReplicates = true;
	this->bCanBeInCluster = false;
}
void AFGWheeledVehicleProxyActor::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const {
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AFGWheeledVehicleProxyActor, mOwnerVehicle);
	DOREPLIFETIME(AFGWheeledVehicleProxyActor, mVehicleCustomizationData);
	DOREPLIFETIME(AFGWheeledVehicleProxyActor, mAuthoritativeLocation);
	DOREPLIFETIME(AFGWheeledVehicleProxyActor, mAuthoritativeRotation);
	DOREPLIFETIME(AFGWheeledVehicleProxyActor, mAuthoritativeLinearVelocity);
	DOREPLIFETIME(AFGWheeledVehicleProxyActor, mHasAuthoritativeMovementData);
}
void AFGWheeledVehicleProxyActor::BeginPlay(){ Super::BeginPlay(); }
void AFGWheeledVehicleProxyActor::Tick(float DeltaSeconds){ Super::Tick(DeltaSeconds); }
void AFGWheeledVehicleProxyActor::OnRep_ReplicatedMovement(){ Super::OnRep_ReplicatedMovement(); }
void AFGWheeledVehicleProxyActor::ApplyCustomizationData(){ }
void AFGWheeledVehicleProxyActor::OnRep_VehicleCustomizationData(){ }
