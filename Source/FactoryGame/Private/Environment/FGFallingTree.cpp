#include "Environment/FGFallingTree.h"
#include "Components/CapsuleComponent.h"
#include "Components/DynamicMeshComponent.h"
#include "Components/SceneComponent.h"

AFGFallingTree::AFGFallingTree() : Super() {
	this->RootMesh = CreateDefaultSubobject<UDynamicMeshComponent>(TEXT("RootMesh"));
	this->RootMesh->SetMobility(EComponentMobility::Movable);
	this->TrunkMesh = CreateDefaultSubobject<UDynamicMeshComponent>(TEXT("TrunkMesh"));
	this->TrunkMesh->SetMobility(EComponentMobility::Movable);
	this->RootCapsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("RootCollisionCapsule"));
	this->RootCapsule->SetMobility(EComponentMobility::Movable);
	this->TrunkCapsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("TrunkCollisionCapsule"));
	this->TrunkCapsule->SetMobility(EComponentMobility::Movable);
	this->TreeMesh = nullptr;
	this->SliceLocation = FVector::ZeroVector;
	this->TrunkRadius = 0.0;
	this->LeafSplashParameterIndexName = TEXT("None");
	this->LeafSplashSocketName = TEXT("None");
	this->LeafSplashVFXSystem = nullptr;
	this->TrunkSplashVFXSystem = nullptr;
	this->TrunkSplashVFXIndexName = TEXT("None");
	this->mFoliageLeafSplatterAKEvent = nullptr;
	this->mTreeFallCrumbleAKEvent = nullptr;
	this->mTreeFallHitAKEvent = nullptr;
	this->mCapOverride = nullptr;
	this->MaxWedgeAngle = 15.0;
	this->RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	this->RootComponent->SetMobility(EComponentMobility::Movable);
	this->RootMesh->SetupAttachment(RootComponent);
	this->TrunkMesh->SetupAttachment(RootComponent);
	this->RootCapsule->SetupAttachment(RootComponent);
	this->TrunkCapsule->SetupAttachment(RootComponent);
}
void AFGFallingTree::SpawnFallingTree(UObject* WorldContext, TSubclassOf<AFGFallingTree> Class, UStaticMesh* StaticMesh, const TArray<UMaterialInterface*>& OverridenMaterials, const FTransform& MeshTransform, UFGFoliageDestructionData* Data){ }
void AFGFallingTree::BeginPlay(){ Super::BeginPlay(); }
void AFGFallingTree::SetupAsync(UStaticMesh* StaticMesh, const TArray<UMaterialInterface*>& OverridenMaterials){ }
bool AFGFallingTree::SetTrunkRadius(UStaticMesh* InMesh, float InRadius, FVector InPivot, FBoxSphereBounds InBounds, float InMaxWedge){ return false; }
void AFGFallingTree::GetMeshData(UStaticMesh* InMesh, float& OutRadius, FVector& OutPivot, FBoxSphereBounds& OutBounds, float& OutMaxWedge){ }
void AFGFallingTree::PostSetup_Implementation(){ }
void AFGFallingTree::SetupTree_Implementation(UStaticMesh* StaticMesh, const TArray<UMaterialInterface*>& OverridenMaterials){ }
void AFGFallingTree::PreSetup_Implementation(UStaticMesh* StaticMesh, const TArray<UMaterialInterface*>& OverridenMaterials){ }
