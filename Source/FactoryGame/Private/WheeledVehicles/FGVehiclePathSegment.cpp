#include "WheeledVehicles/FGVehiclePathSegment.h"
#include "Components/SceneComponent.h"
#include "Components/SplineComponent.h"
#include "Net/UnrealNetwork.h"

FString FVehiclePathVisualizationHandle::GetReferencerName() const{ return FString(); }
void FVehiclePathVisualizationHandle::AddReferencedObjects(FReferenceCollector& Collector){ }
void FVehiclePathBlockExclusiveReservation::ReleaseAllSharedReservations_ThreadSafe(){ }
void FVehiclePathBlockExclusiveReservation::ReleaseExclusiveReservation_ThreadSafe(){ }
const struct FVehiclePathBlock* FVehiclePathBlockReference::ResolveConst() const{ return nullptr; }
AFGVehiclePathSegment::AFGVehiclePathSegment() : Super() {
	this->mSplineComponent = CreateDefaultSubobject<USplineComponent>(TEXT("SplineComponent"));
	this->mSplineComponent->SetMobility(EComponentMobility::Static);
	this->mVisualizationMesh = nullptr;
	this->mVisualizationMeshLength = 100.0;
	this->mCollisionExtent = 120.0;
	this->mPathOverlapCheckGranularity = 50.0;
	this->mVisualizationZOffset = 100.0;
	this->mSignificanceRange = 15000.0;
	this->mNetSignificanceRange = 15000.0;
	this->mPathBlockRelativeSize = 2.0;
	this->mPathOverlapVehicleSpacing = 25.0;
	this->mStartNode = nullptr;
	this->mEndNode = nullptr;
	this->mHasOverlappingSegments = false;
	this->mPathValidationDataDirty = false;
	this->mOverlappingPathSegmentsDirty = false;
	this->mIsLegacyPath = false;
	this->mAllowColoring = false;
	this->mAllowPatterning = false;
	this->mSkipBuildEffect = true;
	this->mShouldApplyCustomizationData = false;
	this->mSplineComponent->SetupAttachment(RootComponent);
}
void AFGVehiclePathSegment::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const {
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AFGVehiclePathSegment, mSplinePoints);
	DOREPLIFETIME(AFGVehiclePathSegment, mValidationData);
	DOREPLIFETIME(AFGVehiclePathSegment, mStartNode);
	DOREPLIFETIME(AFGVehiclePathSegment, mEndNode);
	DOREPLIFETIME(AFGVehiclePathSegment, mHasOverlappingSegments);
	DOREPLIFETIME(AFGVehiclePathSegment, mStartPathNodeGuid);
	DOREPLIFETIME(AFGVehiclePathSegment, mVehicles);
	DOREPLIFETIME(AFGVehiclePathSegment, mIsLegacyPath);
}
void AFGVehiclePathSegment::OnConstruction(const FTransform& Transform){ Super::OnConstruction(Transform); }
void AFGVehiclePathSegment::BeginPlay(){ Super::BeginPlay(); }
void AFGVehiclePathSegment::EndPlay(const EEndPlayReason::Type EndPlayReason){ Super::EndPlay(EndPlayReason); }
#if WITH_EDITOR
bool AFGVehiclePathSegment::CanVisualizeBlueprintAsset() const{ return Super::CanVisualizeBlueprintAsset(); }
#endif
void AFGVehiclePathSegment::PostSerializedFromBlueprint(bool isBlueprintWorld){ Super::PostSerializedFromBlueprint(isBlueprintWorld); }
FBox AFGVehiclePathSegment::CalculateBounds() const{ return Super::CalculateBounds(); }
void AFGVehiclePathSegment::PostLoadGame_Implementation(int32 saveVersion, int32 gameVersion){ Super::PostLoadGame_Implementation(saveVersion, gameVersion); }
void AFGVehiclePathSegment::GetDismantleDependencies_Implementation(TArray<AActor*>& out_dismantleDependencies) const{ Super::GetDismantleDependencies_Implementation(out_dismantleDependencies); }
void AFGVehiclePathSegment::TogglePendingDismantleMaterial(bool enabled){ Super::TogglePendingDismantleMaterial(enabled); }
void AFGVehiclePathSegment::GetClearanceData_Implementation(TArray<FFGClearanceData>& out_data) const{ Super::GetClearanceData_Implementation(out_data); }
float AFGVehiclePathSegment::GetSignificanceRange_Implementation() const{ return IFGSignificanceInterface::GetSignificanceRange_Implementation(); }
void AFGVehiclePathSegment::GainedSignificance_Implementation(){ IFGSignificanceInterface::GainedSignificance_Implementation(); }
void AFGVehiclePathSegment::LostSignificance_Implementation(){ IFGSignificanceInterface::LostSignificance_Implementation(); }
float AFGVehiclePathSegment::GetNetSignificanceRange_Implementation() const{ return IFGNetSignificanceInterface::GetNetSignificanceRange_Implementation(); }
void AFGVehiclePathSegment::GainedNetSignificance_Implementation(){ IFGNetSignificanceInterface::GainedNetSignificance_Implementation(); }
void AFGVehiclePathSegment::LostNetSignificance_Implementation(){ IFGNetSignificanceInterface::LostNetSignificance_Implementation(); }
bool AFGVehiclePathSegment::GetValidationDataForPreset(const UFGVehiclePathPreset* pathPreset, FVehiclePathValidationInfo& out_validationInfo) const{ return false; }
bool AFGVehiclePathSegment::IsPathValidForPreset(const UFGVehiclePathPreset* pathPreset) const{ return false; }
FVector AFGVehiclePathSegment::CalculateLargestAllowedVehicleExtents() const{ return FVector(); }
void AFGVehiclePathSegment::ImmediateRebuildPathValidationData(){ }
void AFGVehiclePathSegment::AddVehicle(AFGWheeledVehicle* newVehicle){ }
void AFGVehiclePathSegment::RemoveVehicle(AFGWheeledVehicle* vehicle){ }
int32 AFGVehiclePathSegment::FindVehiclePathBlockIndexAtDistance(float distanceAlongSpline) const{ return int32(); }
float AFGVehiclePathSegment::GetVehiclePathBlockSize() const{ return float(); }
float AFGVehiclePathSegment::GetVehiclePathBlockStartDistance(int32 pathBlockIndex) const{ return float(); }
float AFGVehiclePathSegment::GetVehiclePathBlockEndDistance(int32 pathBlockIndex) const{ return float(); }
bool AFGVehiclePathSegment::CanCreateExclusiveBlockReservation_ThreadSafe(int32 pathBlockIndex) const{ return false; }
TSharedPtr<FVehiclePathBlockExclusiveReservation> AFGVehiclePathSegment::CreateExclusiveReservationUnchecked_ThreadSafe(const AFGWheeledVehicle* ownerVehicle, int32 pathBlockIndex){ return nullptr; }
void AFGVehiclePathSegment::ReleaseExclusiveReservation_ThreadSafe(const TSharedPtr<FVehiclePathBlockExclusiveReservation>& exclusiveReservation){ }
void AFGVehiclePathSegment::ReleaseSharedReservation_ThreadSafe(const TSharedPtr<FVehiclePathBlockSharedReservation>& sharedReservation){ }
void AFGVehiclePathSegment::SetSplinePointsAndValidatePath(const TArray<FSplinePointData>& splinePointData){ }
void AFGVehiclePathSegment::SetNodeConnections(AFGVehiclePathNode* newStartNode, AFGVehiclePathNode* newEndNode){ }
void AFGVehiclePathSegment::SetLegacyConvertedPath(){ }
AFGVehiclePathNode* AFGVehiclePathSegment::Split(float splitAtDistanceAlongSpline){ return nullptr; }
void AFGVehiclePathSegment::SplitAtNode(AFGVehiclePathNode* splitAtPathNode){ }
AFGVehiclePathSegment* AFGVehiclePathSegment::MoveConnectionToNodes(AFGVehiclePathNode* newStartNode, AFGVehiclePathNode* newEndNode){ return nullptr; }
void AFGVehiclePathSegment::CreateSplineMeshComponents(const USplineComponent* splineComponent, const FVehiclePathVisualizationInfo& visualizationInfo, TArray<TObjectPtr<USplineMeshComponent>>& out_splineMeshComponents, const TFunctionRef<USplineMeshComponent*(UStaticMesh* staticMesh)>& componentConstructor) const{ }
void AFGVehiclePathSegment::CreateClearanceData(const USplineComponent* splineComponent, TArray<FFGClearanceData>& out_clearanceData) const{ }
void AFGVehiclePathSegment::SetVisualizationEnabled(const FVehiclePathVisualizationHandle& visualizationHandle){ }
void AFGVehiclePathSegment::SetVisualizationDisabled(){ }
void AFGVehiclePathSegment::SplitInternal(AFGVehiclePathNode* splitPathNode, float splitAtDistanceAlongSpline){ }
void AFGVehiclePathSegment::UnrotateForBlueprintPlaced(){ }
FVehiclePathVisualizationInfo AFGVehiclePathSegment::GetPathVisualizationInfo(const FVehiclePathVisualizationHandle& visualizationHandle) const{ return FVehiclePathVisualizationInfo(); }
void AFGVehiclePathSegment::CleanupOverlappingPathSegments(){ }
void AFGVehiclePathSegment::RecalculateHasOverlappingPathSegments(){ }
void AFGVehiclePathSegment::InitializeOverlappingPathSegments(){ }
void AFGVehiclePathSegment::CreateCollisionComponents(TArray<TObjectPtr<UBoxComponent>>& out_collisionComponents, bool bIsEditorVisualization){ }
void AFGVehiclePathSegment::DestroyCollisionComponents(){ }
void AFGVehiclePathSegment::DestroyVisualizationComponents(){ }
#if WITH_EDITOR
void AFGVehiclePathSegment::CreateEditorVisualization(){ Super::CreateEditorVisualization(); }
#endif
void AFGVehiclePathSegment::OnVehicleSubsystemValid(){ }
