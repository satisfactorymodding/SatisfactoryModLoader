// Copyright Coffee Stain Studios. All Rights Reserved.

#include "AbstractInstanceSubsystem.h"
#include "AbstractInstanceManager.h"
#include "Engine/World.h"

void UAbstractInstanceSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
}

void UAbstractInstanceSubsystem::OnWorldBeginPlay(UWorld& InWorld)
{
	Super::OnWorldBeginPlay(InWorld);

	// Spawn abstract instance manager before BeginPlay is dispatched to actors unless it has been spawned earlier
	CreateAbstractInstanceManager();
}

void UAbstractInstanceSubsystem::CreateAbstractInstanceManager()
{
	check(IsInGameThread());
	check(GetWorld()->IsInitialized());
	check(GetWorld()->PersistentLevel);

	if (WorldAbstractInstanceManager == nullptr)
	{
		FActorSpawnParameters ActorSpawnParameters{};
		ActorSpawnParameters.Name = TEXT("AbstractInstanceManager");
		ActorSpawnParameters.NameMode = FActorSpawnParameters::ESpawnActorNameMode::Requested;
#if WITH_EDITOR
		ActorSpawnParameters.bCreateActorPackage = false;
#endif
		ActorSpawnParameters.ObjectFlags = RF_Transactional | RF_Transient;
		ActorSpawnParameters.OverrideLevel = GetWorld()->PersistentLevel;
	
		WorldAbstractInstanceManager = GetWorld()->SpawnActor<AAbstractInstanceManager>();
	}
}

bool UAbstractInstanceSubsystem::DoesSupportWorldType(const EWorldType::Type WorldType) const
{
	return WorldType == EWorldType::PIE || WorldType == EWorldType::Game;
}
