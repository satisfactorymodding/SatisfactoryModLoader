// Copyright Coffee Stain Studios. All Rights Reserved.

#include "FGWorldScannableData.h"
#include "EngineUtils.h"
#include "Buildables/FGBuildableFrackingActivator.h"
#include "FGScannableSubsystem.h"
#include "FGItemPickup.h"
#include "FGDropPod.h"
#include "Creature/FGCreatureSpawner.h"
#include "WorldPartition/WorldPartition.h"
#if WITH_EDITOR
#include "WorldPartition/WorldPartitionActorDesc.h"
#endif

#if WITH_EDITOR

FWorldScannableData::FWorldScannableData(const AActor* actor)
{
	if (actor) {
		Actor = TSoftObjectPtr<AActor>(actor);
		ActorGuid = actor->GetActorGuid();
		ActorClass = actor->GetClass();
		ActorLocation = actor->GetStreamingBounds().GetCenter();
	}
}

FWorldScannableData::FWorldScannableData(const FWorldPartitionActorDesc* ActorDesc, int32 PIEInstanceIndex)
{
	check(ActorDesc);
	Actor = ActorDesc->GetActorSoftPath();
	ActorGuid = ActorDesc->GetGuid();

	// If we have a base class path, e.g. class is not native, load it
	const FTopLevelAssetPath BaseClassPath = ActorDesc->GetBaseClass();
	if (!BaseClassPath.IsNull()) {
		ActorClass = LoadClass<AActor>(nullptr, *ActorDesc->GetBaseClass().ToString());
	} else {
		ActorClass = ActorDesc->GetActorNativeClass();
	}
	// Should always have either a native class or a blueprint loaded class at this point
	check(ActorClass);

	ActorLocation = ActorDesc->GetRuntimeBounds().GetCenter();

	// We need to remap the actor soft path to the correct PIE instance, since actor desc will most certainly come from the original, non-duplicated world package
	if (PIEInstanceIndex != INDEX_NONE) {
		FSoftObjectPath SoftActorPath = Actor.ToSoftObjectPath();
		SoftActorPath.FixupForPIE(PIEInstanceIndex);
		Actor = SoftActorPath;
	}
}

FCreatureSpawnerWorldScannableData::FCreatureSpawnerWorldScannableData(const AFGCreatureSpawner* actor) : FWorldScannableData(actor)
{
	if (actor) {
		CreatureClass = actor->GetCreatureToSpawn();
	}
}

FCreatureSpawnerWorldScannableData::FCreatureSpawnerWorldScannableData(const FWorldPartitionActorDesc* ActorDesc, int32 PIEInstanceIndex) : FWorldScannableData(ActorDesc, PIEInstanceIndex)
{
	if (AFGCreatureSpawner* actor = Cast<AFGCreatureSpawner>(Actor.Get())) {
		CreatureClass = actor->GetCreatureToSpawn();
	}
}

#endif

AFGWorldScannableDataGenerator::AFGWorldScannableDataGenerator()
{
	PrimaryActorTick.bCanEverTick = false;

#if WITH_EDITORONLY_DATA
	bIsSpatiallyLoaded = false;
#endif
}

void AFGWorldScannableDataGenerator::BeginPlay()
{
	Super::BeginPlay();

#if WITH_EDITOR
	// Cache scannable data from the world if we have editor only data
	if (!GetPackage()->HasAnyPackageFlags(PKG_Cooked | PKG_FilterEditorOnly)) {
		CacheWorldScannableData();
	}
#endif

	if (AFGScannableSubsystem* scannableSubsystem = AFGScannableSubsystem::Get(GetWorld())) {
		scannableSubsystem->AssignScannableData(this);
	}
}

void AFGWorldScannableDataGenerator::PreSave(FObjectPreSaveContext SaveContext)
{
	Super::PreSave(SaveContext);
#if WITH_EDITOR
	// Cache scannable data from the world during the cooking process
	// Avoid attempting to cache the data on the CDOs and Archetypes, and objects without a world context
	if (SaveContext.IsCooking() && !HasAnyFlags(RF_ClassDefaultObject | RF_ArchetypeObject) && GetWorld() != nullptr) {
		CacheWorldScannableData();
	}
#endif
}

#if WITH_EDITOR

void AFGWorldScannableDataGenerator::CacheWorldScannableData()
{
	mItemPickups.Empty();
	mDropPods.Empty();

	const UWorldPartition* WorldPartition = GetWorld()->GetWorldPartition();

	// If there is no world partition, use TActorIterator to find all loaded actors and cache them immediately
	if (WorldPartition == nullptr) {
		for (TActorIterator<AFGItemPickup> It(GetWorld()); It; ++It) {
			mItemPickups.Add(FWorldScannableData(*It));
		}
		for (TActorIterator<AFGDropPod> It(GetWorld()); It; ++It) {
			mDropPods.Add(FWorldScannableData(*It));
		}
		return;
	}

	// This is a world partitioned level, so we need to use world partition actor iterator to find all actors. We do not actually need to load them to retrieve their data
	check(WorldPartition);
	UActorDescContainer* ActorDescContainer = WorldPartition->GetActorDescContainer();

	// Determine the path to the source asset in case we need to remap paths to PIE
	FString SourceAssetPath, UnusedRemappedPath;
	const bool bWorldHasBeenInstanced = GetWorld()->GetSoftObjectPathMapping(SourceAssetPath, UnusedRemappedPath);
	const FTopLevelAssetPath SourceAssetTopLevelPath(SourceAssetPath);

	// In PIE, if the world has been duplicated, it is likely that it's ActorDescContainer will not be initialized
	// Attempt to look up our actor desc container on our source world asset
	if (ActorDescContainer == nullptr && bWorldHasBeenInstanced) {
		if (const UWorld* OriginalWorldAsset = FindObject<UWorld>(SourceAssetTopLevelPath)) {
			const UWorldPartition* OriginalWorldPartition = OriginalWorldAsset->GetWorldPartition();
			if (OriginalWorldPartition != nullptr) {
				ActorDescContainer = OriginalWorldPartition->GetActorDescContainer();
			}
		}
	}
	// If we were unable to find the original world (it could have been garbage collected by now, or never had it's actor desc initialized),
	// create our own actor desc container using the original asset path
	if (ActorDescContainer == nullptr) {
		ActorDescContainer = NewObject<UActorDescContainer>(GetTransientPackage());
		ActorDescContainer->Initialize(UActorDescContainer::FInitializeParams(GetWorld(), SourceAssetTopLevelPath.GetPackageName()));
	}

	// At this point we should always have a valid actor desc container, but ensure and not crash if we do not
	if (!ensure(ActorDescContainer)) {
		UE_LOG(LogGame, Error, TEXT("Failed to find ActorDescContainer for World Partitioned world '%s' to gather scannables. Game features relying on the WorldScannableData will not work."), *GetWorld()->GetPathName());
		return;
	}

	// We have to fix up the path in case this is a PIE instance
	const int32 PIEInstanceIndex = GetWorld()->GetPackage()->GetPIEInstanceID();

	for (FActorDescList::TConstIterator<AActor> It(ActorDescContainer); It; ++It) {
		const FWorldPartitionActorDesc* ActorDescriptor = *It;
		const UClass* ActorNativeClass = ActorDescriptor->GetActorNativeClass();

		if (ActorNativeClass->IsChildOf(AFGItemPickup::StaticClass())) {
			mItemPickups.Add(FWorldScannableData(*It, PIEInstanceIndex));
		}
		if (ActorNativeClass->IsChildOf(AFGDropPod::StaticClass())) {
			mDropPods.Add(FWorldScannableData(*It, PIEInstanceIndex));
		}
	}
}

#endif
