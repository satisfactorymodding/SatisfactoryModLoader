// Fill out your copyright notice in the Description page of Project Settings.

#include "SignificanceManagerAccelerated.h"

#include "Async/ParallelFor.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/PlayerController.h"

// MODDING EDIT: Rider shows this in red, we're not using it as far as I can tell
// #if INTEL_ISPC
// #include "SignificanceISPC.ispc.generated.h"
// #endif

bool USignificanceManagerAccelerated::DoesSupportWorldType(const EWorldType::Type WorldType) const{ return Super::DoesSupportWorldType(WorldType); }
bool USignificanceManagerAccelerated::ShouldCreateSubsystem(UObject* Outer) const{ return Super::ShouldCreateSubsystem(Outer); }
void USignificanceManagerAccelerated::Tick(float DeltaTime){ Super::Tick(DeltaTime); }
TStatId USignificanceManagerAccelerated::GetStatId() const{ return TStatId(); }
void USignificanceManagerAccelerated::RegisterObject(UObject* Object, bool bIsDynamicObject){
	if (IsRunningDedicatedServer())
	{
		return;
	}

	// MODDING EDIT: Honestly no idea how to adapt the old code to this.
}
void USignificanceManagerAccelerated::RemoveObject(UObject* Object) {
	if (IsRunningDedicatedServer())
	{
		return;
	}

	// MODDING EDIT: Adapted this from whatever we had from Ben's repo, but that hasn't been updated and we didn't receive .cpps for plugins

	TWeakObjectPtr<UObject> Target = Object;
	const int32 Index = StaticEntriesObjects.IndexOfByPredicate([Target]( const FStaticAcceleratedManagedObjectInfo Entry)
	{
		return Entry.ManagedObject == Target;
	});

	StaticEntriesObjects.RemoveAt(Index);

	StaticEntries.RemoveAt(Index);

	StaticEntries.Shrink();
	StaticEntriesObjects.Shrink();
}
void USignificanceManagerAccelerated::UpdateStaticObjectSignificanceRange(UObject* Object){ }
void USignificanceManagerAccelerated::DumpSignificanceDebugData()
{
	for (int32 i = 0; i < StaticEntries.Num(); i++)
	{
		FString Name = {"missing"};
		const bool bIsSignificant = StaticEntries[i].bIsSignificant == SignificanceState::Significant;
		const float Significance = StaticEntries[i].CurrentSignificance;
		bool bIsActorTickEnabled = false;
		
		if ( auto Object = StaticEntriesObjects[i].ManagedObject.Get() )
		{
			Name = Object->GetName();

			if (AActor* Actor = Cast<AActor>(Object))
			{
				bIsActorTickEnabled = Actor->IsActorTickEnabled();
			}
		}

		UE_LOG(LogTemp,Warning,TEXT("[SMA] %s, %s, %f, Tick Enabled: %s "),*Name,bIsSignificant ? TEXT("Enabled") : TEXT("Disabled"), Significance, bIsActorTickEnabled ? TEXT("Enabled") : TEXT("Disabled"));
	}
}
void USignificanceManagerAccelerated::CalculatePlayerViewpoints(TArray<FVector3f>& OutPlayerViewpoints) const{ }
int32 USignificanceManagerAccelerated::AllocateEntryIndex(){ return 0; }
void USignificanceManagerAccelerated::ReleaseEntryIndex(int32 EntryIndex){ }
bool USignificanceManagerAccelerated::CalculateImmediateSignificanceState(const FStaticAcceleratedManagedSignificanceInfo& SignificanceInfo){ return false; }

