#include "FGSplineCollisionComponent.h"
UFGSplineCollisionComponent::UFGSplineCollisionComponent(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) { }
void UFGSplineCollisionComponent::AddBox(const FVector& Location, const FVector& Extent, const FRotator& Rotation){ }
void UFGSplineCollisionComponent::AddBoxes(const TArray<FCachedCollisionBoxInfo>& Boxes){ }
void UFGSplineCollisionComponent::CreatePhysics(){ }
void UFGSplineCollisionComponent::DestroyPhysics(){ }
FBoxSphereBounds UFGSplineCollisionComponent::CalcBounds(const FTransform& LocalToWorld) const { return FBoxSphereBounds(); }
UBodySetup* UFGSplineCollisionComponent::GetBodySetup(){ return nullptr; }
FPrimitiveSceneProxy* UFGSplineCollisionComponent::CreateSceneProxy(){ return nullptr; }
bool UFGSplineCollisionComponent::ShouldCreateRenderState() const {	return false; }
bool UFGSplineCollisionComponent::DoCustomNavigableGeometryExport(FNavigableGeometryExport& GeomExport) const {	return false; }
void UFGSplineCollisionComponent::GetNavigationData(FNavigationRelevantData& Data) const { }
bool UFGSplineCollisionComponent::IsNavigationRelevant() const { return false; }
