// Copyright Coffee Stain Studios. All Rights Reserved.


#include "AbstractInstanceManager.h"

#include "AbstractInstanceInterface.h"
#include "AbstractInstanceSubsystem.h"
#include "AkGeometryComponent.h"
#include "AkInstancedGeometryComponent.h"
#include "AudioGeometryInstanceManager.h"
#include "DrawDebugHelpers.h"
#include "InstanceData.h"
#include "PrimitiveSceneProxy.h"
#include "SceneInterface.h"
#include "TimerManager.h"
#include "Engine/World.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/PlayerController.h"
#include "Private/ScenePrivate.h"

static TAutoConsoleVariable<int32> CVarAllowLazySpawning(
	TEXT("lightweightinstances.AllowLazySpawn"),
	0,
	TEXT("Enable/Disable lazy spawning of instances when enabeld per instance data (Temp disabled.)."),
	ECVF_Default );

static TAutoConsoleVariable<int32> CVarLazySpawnCount(
	TEXT("lightweightinstances.LazySpawnCount"),
	100,
	TEXT("Number of instances to lazy spawn per frame."),
	ECVF_Default );

static TAutoConsoleVariable<float> CVarLazySpawnPriorityRange(
	TEXT("lightweightinstances.PriorityRange"),
	33333,
	TEXT("."),
	ECVF_Default );

static TAutoConsoleVariable<int32> CVarPriorityLazySpawnCount(
	TEXT("lightweightinstances.PriorityLazySpawnCount"),
	1000,
	TEXT("Number of Priority instances to lazy spawn per frame."),
	ECVF_Default );

static TAutoConsoleVariable<int32> CVarHideLightWeightInstancesDebug(
	TEXT("lightweightinstances.DebugHideInstances"),
	0,
	TEXT("Debug hide instances"),
	ECVF_Cheat | ECVF_RenderThreadSafe );

static TAutoConsoleVariable<int32> CVarAudioGeometryEnabled(
	TEXT("lightweightinstances.AudioGeometryEnabled"),
	1,
	TEXT("Enable/Disable audio support for instances."),
	ECVF_Default );

static TAutoConsoleVariable<int32> CVarDisplayLightWeightInstanceDebug(
	TEXT("lightweightinstances.DrawDebug"),
	0,
	TEXT(""),
	ECVF_RenderThreadSafe);

static TAutoConsoleVariable<float> CVarDisplayLightWeightInstanceDebugRange(
	TEXT("lightweightinstances.DrawDebugRange"),
	1000,
	TEXT(""),
	ECVF_RenderThreadSafe);

static TAutoConsoleVariable<float> CVarDrawDistanceModifier(
	TEXT("lightweightinstances.DrawDistanceModifier"),
	1,
	TEXT("Modifier value applied to the draw dinstance,TODO needs reinistance to apply "),
	ECVF_RenderThreadSafe);

bool CVar_UseDirtyRenderStateOnCustomDataSet = true;
static FAutoConsoleVariableRef CVarUseDirtyRenderStateOnCustomDataSet(
	TEXT("lightweightinstances.UseDirtyRenderStateOnCustomDataSet"),
	CVar_UseDirtyRenderStateOnCustomDataSet,
	TEXT("When true setting the custom data of an instance will MarkRenderStateDirty to update custom data without needing a full MarkDirty call"),
	ECVF_RenderThreadSafe);

int32 CvarBucketLightweightComponentsInstanceCount = 0;
static FAutoConsoleVariableRef CVar_BucketLightweightComponentsInstanceCount(
	TEXT("lightweight.BucketLightweightComponentsInstanceCount"),
	CvarBucketLightweightComponentsInstanceCount,
	TEXT("Must be set before first instance entry to have any effect. If non-zero will split visuals into a new component after X number of instances are added (Clamped to be at minimum the number of collision instances per bucket)"),
	ECVF_Scalability);

constexpr int32 NumCollisionInstances = 500;

FInstanceComponentData::FInstanceComponentData( AActor* owner, const FInstanceData& instanceData, bool castDistanceFieldShadows ) : Owner( owner ), InstanceData( instanceData ), bUsesBucketCollision( InstanceData.bUseBatchedCollision ), bCastDistanceFieldShadows( castDistanceFieldShadows )
{
	// Determine if we are bucketing the visual instances
	if( CvarBucketLightweightComponentsInstanceCount > 0 )
	{
		NumVisualInstancesPerComponent =  FMath::Clamp( CvarBucketLightweightComponentsInstanceCount, NumCollisionInstances, MAX_int32 );
	}
	else if( InstanceData.MaxMeshInstancePerComponent > 0 )
	{
		NumVisualInstancesPerComponent = FMath::Clamp(  InstanceData.MaxMeshInstancePerComponent ,NumCollisionInstances, MAX_int32 );
	}

	// If we are bucketing visuals we store how many collision components need to be created per visual component
	NumCollisionComponentsPerVisual = NumVisualInstancesPerComponent > 0 ? FMath::Clamp( FMath::CeilToInt( static_cast<float>(NumVisualInstancesPerComponent) / NumCollisionInstances ), 1, MAX_int32 ) : 0;

	// Create the first / default Mesh component (More may be created later if we are bucketing visual components)
	AddLightweightMeshComponent();
	
	// If we are using bucket collision then we will manage the collision components internally
	// However, we Don't add one if we are bucketing visual components as they are already added during mesh component creation
	if( bUsesBucketCollision && NumCollisionComponentsPerVisual <= 0 )
	{
		AddLightweightCollisionComponent();
	}

	// If specified create AkGeometry component
	if ( InstanceData.bUseAkGeometry && CVarAudioGeometryEnabled.GetValueOnGameThread() )
	{
		AddAkGeometryComponent();
	}
}

void FInstanceComponentData::AddInstance( const FTransform& Transform, bool WorldSpace, bool InitializeHidden, FInstanceAdditionData& OutInstanceAdditionData )
{
	ULightweightHierarchicalInstancedStaticMeshComponent* VisualMeshComponent = nullptr;

	// Only true if we are bucketing visuals into seperate components
	if( NumVisualInstancesPerComponent > 0 )
	{
		if( InstancedStaticMeshComponents[CurrentMeshComponentIndex]->GetInstanceCount() >= NumVisualInstancesPerComponent )
		{
			UpdateCurrentMeshComponentIndex();
		}
	}
	VisualMeshComponent = InstancedStaticMeshComponents[CurrentMeshComponentIndex];

	if( InitializeHidden )
	{
		FTransform ZeroScaleTransform = Transform;
		ZeroScaleTransform.SetScale3D(FVector(0.01));
		ZeroScaleTransform.AddToTranslation( -FVector(0,0,AIM_BigOffset) );
		OutInstanceAdditionData.VisualData.InstanceID = VisualMeshComponent->AddInstance( ZeroScaleTransform, WorldSpace );
	}
	else
	{
		OutInstanceAdditionData.VisualData.InstanceID = VisualMeshComponent->AddInstance( Transform, WorldSpace );
	}
	
	OutInstanceAdditionData.VisualData.ComponentIndex = CurrentMeshComponentIndex;

	// Add the collision instance for this new instance
	if( bUsesBucketCollision )
	{
		AddCollisionInstance( Transform, WorldSpace, OutInstanceAdditionData);
	}
}

void FInstanceComponentData::RemoveInstance( FInstanceOwnerHandlePtr& HandlePtr)
{
	// For NON-Bucketed Visual Instances
	/*	The visual are in a linear array, 
	 *	[0,1,2,3....]
	 *	Collision buckets are in groups
	 *	{0}[0,1,2,3,4],{1}[0,1,2,3,4],{2}[0,1,2,3,4]
	 *
	 *	Once a instance will be remove, we do a swap and remove unless its the last one.
	 *	for the collision component this means we have to remap the remove instance in
	 *	the current instance bucket to the last instance transform
	 *
	 *	Example: We remove instance 6
	 *	Visuals:	[0,1,2,3,4,5,6,7,8,9....13]
	 *	Collision:	{0}[0..9],{1}[0,1,2,3]
	 *
	 *	Visuals, 13 becomes 6 with swap remove.
	 *	Collision, {0}[6] becomes {1}[3], we set location on {0}[6] with {1}[3] and remove {1}[3] */

	// For Bucketed Visual Instances
	/*	The visuals are in a linear array with the addition of an offset into the collision array based on the number of components needed to accomodate the visual comp max instance count 
	 *	For example:	We have an InstanceData array that specifies the Max Num Visual Elements is 2000. Our Collision Components can only hold 500 instances.
	 *					From this we determine that there are 4 collision components per visual component (CollisionCompsPerVisual).
	 *					Using the Handles Visual Component Index (vIdx) we offset vIdx * CollisionCompsPerVisual into the CollisionComponent Array.
	 *					Finally we use the previous method of dividing the VisualHandleID by the MaxCollisionComponents to determine which collision comp the handle resides in for that visual comp
	 *
	 *	Data Layout Example based on our previously used numbers
	 *	VisualComp0 [0,1,2,3...1999] VisualComp1 [0,1,2,3...1999] VisualComp2 [0,1,2,3...1999]
	 *	CollsionComp{0-3} Holds Collision for VisualComp0 -- CollisionComp{4-7} Holds Collision for VisualComp1 and so on 
	 *	The above swap logic is carried out as explained above. The only difference is that we have multiple "Linear Handle Arrays" of visuals corresponding to groups of CollisionComponents
	*/
	
	const uint32 HandleId = HandlePtr->HandleID;
	const int32 MeshCompIndex = HandlePtr->MeshComponentIndex;
	const uint32 CollisionHandleId = HandlePtr->CollisionHandleID;
	
	InstanceHandles[MeshCompIndex].RemoveAtSwap( HandleId );
	const bool ShouldRemapIndex = InstanceHandles[MeshCompIndex].Num() > static_cast<int32>( HandleId );

	// Solve visual instances.
	if( ShouldRemapIndex )
	{
		InstanceHandles[MeshCompIndex][ HandleId ]->HandleID = HandleId;
	}

	InstancedStaticMeshComponents[MeshCompIndex]->RemoveInstance( HandleId );

	if(InstanceHandles[MeshCompIndex].Num() <= 0 )
	{
		InstancedStaticMeshComponents[MeshCompIndex]->ClearInstances();
	}
	else
	{
		InstancedStaticMeshComponents[MeshCompIndex]->MarkRenderStateDirty();
	}

	if( bUsesBucketCollision )
	{
		// If bucketing visuals then we offset the collision comp index by the Visual Handle ID (each visual comp has a set range of collision components it uses for syncing Handle ID to collision ID)
		const int32 CollisionCompIndex = NumCollisionComponentsPerVisual == 0 ? HandleId / NumCollisionInstances : (MeshCompIndex * NumCollisionComponentsPerVisual) + (HandleId / NumCollisionInstances);
		const int32 LastCollisionCompIndexForVisual = NumCollisionComponentsPerVisual == 0 ? InstancedCollisionComponents.Num() - 1 : ((( MeshCompIndex + 1 ) * NumCollisionComponentsPerVisual ) - 1);
		ULightweightCollisionComponent* CollisionComp = GetLightweightCollisionComponent( CollisionCompIndex );
		
		if( InstanceHandles[MeshCompIndex].Num() > static_cast<int32>(HandleId) )
		{
			InstanceHandles[MeshCompIndex][ HandleId ]->CollisionHandleID = CollisionHandleId;
		}
		
		ULightweightCollisionComponent* LastBucketComp = nullptr;
		for( int32 i = LastCollisionCompIndexForVisual; i >= CollisionCompIndex; --i )
		{
			if( GetLightweightCollisionComponent( i )->GetInstanceCount() != 0 )
			{
				LastBucketComp = GetLightweightCollisionComponent( i );
				break;
			}
		}
		
		FTransform MoveTransform;
		LastBucketComp->GetInstanceTransform( LastBucketComp->GetInstanceCount() - 1, MoveTransform );
		int32 LastIndex = LastBucketComp->GetInstanceCount() - 1;
		CollisionComp->UpdateInstanceTransform( CollisionHandleId, MoveTransform, false, false, true );
		LastBucketComp->RemoveInstance( LastIndex );

		if( LastBucketComp->GetInstanceCount() <= 0 )
		{
			LastBucketComp->ClearInstances();
		}
		else
		{
			LastBucketComp->MarkRenderStateDirty();
			CollisionComp->MarkRenderStateDirty();
			if(ShouldRemapIndex)
			{
				InstanceHandles[MeshCompIndex][ HandleId ]->BatchCollisionMeshComponent = CollisionComp;
			}
		}

		if ( AkInstancedGeometryComponent )
		{
			AAbstractInstanceManager* abstractManager = Cast<AAbstractInstanceManager>( Owner );
			abstractManager->AudioGeometryInstanceManager->RemoveAudioGeometryInstance( HandlePtr.Get() );
		}
	}
}

void FInstanceComponentData::AddCollisionInstance( const FTransform& Transform, bool WorldSpace, FInstanceAdditionData& OutInstanceAdditionData )
{
	ULightweightCollisionComponent* CollisionComp = nullptr;
	int32 CollisionCompIndex = INDEX_NONE;
	
	// If we have limited size visual meshes we need to place the collision into the appropriate group
	if( NumCollisionComponentsPerVisual > 0)
	{
		const int32 FirstCompIndex = OutInstanceAdditionData.VisualData.ComponentIndex * NumCollisionComponentsPerVisual;
		const int32 CompOffset = OutInstanceAdditionData.VisualData.InstanceID / NumCollisionInstances;
		CollisionCompIndex = FirstCompIndex + CompOffset;
		CollisionComp = InstancedCollisionComponents[ CollisionCompIndex ];
	}
	else
	{
		CollisionCompIndex = OutInstanceAdditionData.VisualData.InstanceID / NumCollisionInstances;
		if( !InstancedCollisionComponents.IsValidIndex( CollisionCompIndex ) )
		{
			AddLightweightCollisionComponent();
		}
		CollisionComp = InstancedCollisionComponents[ CollisionCompIndex ];
	}

	OutInstanceAdditionData.CollisionData.ComponentIndex = CollisionCompIndex;
	OutInstanceAdditionData.CollisionData.InstanceID = CollisionComp->AddInstance( Transform, WorldSpace );
}

int32 FInstanceComponentData::AddLightweightMeshComponent()
{
	int32 idx = InstancedStaticMeshComponents.Add( NewObject<ULightweightHierarchicalInstancedStaticMeshComponent>( Owner ) );
	ULightweightHierarchicalInstancedStaticMeshComponent* newMeshComp = InstancedStaticMeshComponents[idx];
	newMeshComp->SetStaticMesh( InstanceData.StaticMesh );
	newMeshComp->OverrideMaterials = InstanceData.OverridenMaterials;
	newMeshComp->SetCollisionEnabled( ECollisionEnabled::NoCollision );
	newMeshComp->SetGenerateOverlapEvents( false );
	newMeshComp->SetMobility( InstanceData.Mobility );
	newMeshComp->AttachToComponent( Owner->GetRootComponent(),FAttachmentTransformRules::KeepRelativeTransform );
	newMeshComp->SetRelativeTransform( FTransform::Identity );
	newMeshComp->SetVisibility( true );
	newMeshComp->SetNumCustomDataFloats( InstanceData.NumCustomDataFloats );
	newMeshComp->SetCastShadow( InstanceData.bCastShadows ); 
	newMeshComp->bAffectDistanceFieldLighting = bCastDistanceFieldShadows; // distance fields are enabled after lazy loading.
	newMeshComp->RegisterComponent();
	newMeshComp->bSelectable = false; // If there are too many instances the editor will freeze when selected so its better to just not allow that to happen (until a proper fix has time allocated)
	newMeshComp->WorldPositionOffsetDisableDistance = InstanceData.MaxWPODistance;
	newMeshComp->bWorldPositionOffsetWritesVelocity = InstanceData.bWorldPositionOffsetWritesVelocity;

	if(InstanceData.MaxDrawDistance > 0)
	{
		const float Modifier = CVarDrawDistanceModifier.GetValueOnGameThread();
		newMeshComp->SetCullDistances( InstanceData.MaxDrawDistance * Modifier * 0.95, InstanceData.MaxDrawDistance * Modifier);
	}
	
	if( CurrentMeshComponentIndex == INDEX_NONE )
	{
		UpdateCurrentMeshComponentIndex();
	}

	// If we're using batched visuals we automatically add the needed Collision Components (rather than creating them when the buckets fill up)
	if( NumCollisionComponentsPerVisual > 0 )
	{
		for( int32 i = 0; i < NumCollisionComponentsPerVisual; ++ i)
		{
			AddLightweightCollisionComponent();
		}
	}
	
	return idx;
}


void FInstanceComponentData::UpdateCurrentMeshComponentIndex()
{
	if( NumVisualInstancesPerComponent <= 0 )
	{
		CurrentMeshComponentIndex = 0;
		return;
	}

	for( int32 i = 0; i < InstancedStaticMeshComponents.Num(); ++i )
	{
		if( InstancedStaticMeshComponents[i]->GetInstanceCount() < NumVisualInstancesPerComponent )
		{
			CurrentMeshComponentIndex = i;
			return;
		}
	}

	CurrentMeshComponentIndex = AddLightweightMeshComponent();
}

int32 FInstanceComponentData::AddLightweightCollisionComponent()
{
	int32 idx = InstancedCollisionComponents.Add( NewObject<ULightweightCollisionComponent>( Owner ) );
	ULightweightCollisionComponent* newCollisionComp = InstancedCollisionComponents[idx];
	newCollisionComp->SetStaticMesh( InstanceData.StaticMesh );
	newCollisionComp->OverrideMaterials = InstanceData.OverridenMaterials;
	newCollisionComp->SetMobility( InstanceData.Mobility );
	newCollisionComp->AttachToComponent( Owner->GetRootComponent() ,FAttachmentTransformRules::KeepRelativeTransform );
	newCollisionComp->SetRelativeTransform( FTransform::Identity );
	newCollisionComp->SetVisibility( false );
	newCollisionComp->SetCollisionProfileName( InstanceData.CollisionProfileName );
	newCollisionComp->bMultiBodyOverlap = true;

	int32 visualGroup = 0;
	int32 collisionGroup = 0;
	if( NumCollisionComponentsPerVisual > 0 )
	{
		visualGroup = idx / NumCollisionComponentsPerVisual;
		collisionGroup = idx % NumCollisionComponentsPerVisual;
	}
	else
	{
		collisionGroup = idx;
	}
	
	newCollisionComp->ComponentTags.Add( FName( FString::FromInt( visualGroup ) ) );
	newCollisionComp->ComponentTags.Add( FName( FString::FromInt( collisionGroup ) ) );
	
	newCollisionComp->RegisterComponent();
	
	return idx;
}

void FInstanceComponentData::AddAkGeometryComponent()
{
	AkInstancedGeometryComponent = NewObject<UAkInstancedGeometryComponent>( Owner );
	
	AkInstancedGeometryComponent->CollisionMeshSurfaceOverride = InstanceData.CollisionMeshSurfaceOverride;
	AkInstancedGeometryComponent->MeshType = InstanceData.MeshType;

	//these are super expensive, so we are explicitly disabling it until we'll have a good use case
	AkInstancedGeometryComponent->bEnableDiffraction = false;
	AkInstancedGeometryComponent->bEnableDiffractionOnBoundaryEdges = false;

	AkInstancedGeometryComponent->SetStaticMesh( InstanceData.StaticMesh );
	AkInstancedGeometryComponent->SetMobility( InstanceData.Mobility );
	AkInstancedGeometryComponent->AttachToComponent( Owner->GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform );
	AkInstancedGeometryComponent->SetRelativeTransform( FTransform::Identity );
	AkInstancedGeometryComponent->SetVisibility( false );
	AkInstancedGeometryComponent->ComponentTags.Add( FName( "0" ) );
	AkInstancedGeometryComponent->RegisterComponent();
}


// Sets default values
AAbstractInstanceManager::AAbstractInstanceManager()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
	
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent->SetMobility( EComponentMobility::Static );

	AudioGeometryInstanceManager = CreateDefaultSubobject<UAudioGeometryInstanceManager>( TEXT("AudioGeometryInstanceManager") );
}

AAbstractInstanceManager* AAbstractInstanceManager::GetInstanceManager(UObject* WorldContext)
{
	if (const UWorld* World = GEngine->GetWorldFromContextObject(WorldContext, EGetWorldErrorMode::LogAndReturnNull))
	{
		if (const UAbstractInstanceSubsystem* Subsystem = World->GetSubsystem<UAbstractInstanceSubsystem>())
		{
			return Subsystem->GetAbstractInstanceManager();
		}
	}
	return nullptr;
}

void AAbstractInstanceManager::Tick( float DeltaSeconds )
{
	Super::Tick( DeltaSeconds );

	if ( bAllowLazySpawn )
	{
		QUICK_SCOPE_CYCLE_COUNTER( AAbstractInstanceManager_LazySpawn )
		
		FLazySpawnEntry Entry;
		int32 Count = 0;

		int32 MaxPerFrame = CVarLazySpawnCount.GetValueOnGameThread();
		PriorityDistance = CVarLazySpawnPriorityRange.GetValueOnGameThread();

		TQueue< FLazySpawnEntry >* Queue = &LazyLoadTasks;

		// assign the priority queue.
		if( !PriorityLazyLoadTasks.IsEmpty() )
		{
			Queue = &PriorityLazyLoadTasks;
			MaxPerFrame = CVarPriorityLazySpawnCount.GetValueOnGameThread();
		}
		
		while( Count < MaxPerFrame && Queue->Dequeue( Entry ) )
		{
			if( AActor* OwnerActor = Entry.OwnerActor.Get() )
			{
				SetInstanced(
					OwnerActor,
					Entry.
					T,
					Entry.InstanceData,
					Entry.TargetHandle );

				if( LastResolvedLazyTaskActor != OwnerActor )
				{
					if( LastResolvedLazyTaskActor && LastResolvedLazyTaskActor->GetClass()->ImplementsInterface( UAbstractInstanceInterface::StaticClass() ) )
					{
						IAbstractInstanceInterface::Execute_PostLazySpawnInstances( LastResolvedLazyTaskActor );
					}
					
					LastResolvedLazyTaskActor = OwnerActor;	
				}
			}
			
			Count++;
		}
		
		// Disable lazy spawn after loading.
		if ( PriorityLazyLoadTasks.IsEmpty() && LazyLoadTasks.IsEmpty() )
		{
			QUICK_SCOPE_CYCLE_COUNTER( STAT_FinishedLazyLoad )
			// Re-enable df on all meshes.

			for (const TPair<FName, FInstanceComponentData>& entryPair : InstanceMap )
			{
				if ( entryPair.Value.bCastDistanceFieldShadows )
				{
					for( auto& MeshComp : entryPair.Value.InstancedStaticMeshComponents )
					{
						MeshComp->bAffectDistanceFieldLighting = true;
						MeshComp->MarkRenderStateDirty();
					}
				}
			}
			
			bAllowLazySpawn = false;
		}
	}

	if(AudioGeometryInstanceManager)
	{
		if(auto PlayerController = GetWorld()->GetFirstPlayerController())
		{
			if(PlayerController->GetPawnOrSpectator())
			{
				AudioGeometryInstanceManager->ProcessTick( PlayerController->GetPawnOrSpectator()->GetActorLocation() );
			}
		}
	}

#if !UE_BUILD_SHIPPING
	if (CVarDisplayLightWeightInstanceDebug.GetValueOnAnyThread() == 1)
	{
		DrawDebug();
	}
#endif
}

void AAbstractInstanceManager::SetInstancedStatic( AActor* OwnerActor, const FTransform& ActorTransform, const UAbstractInstanceDataObject* InstanceDataArray, TArray<FInstanceOwnerHandlePtr>& OutHandles, bool bInitializeHidden )
{
	QUICK_SCOPE_CYCLE_COUNTER( AAbstractInstanceManager_SetInstancedStatic )
	
	if ( AAbstractInstanceManager* Manager = GetInstanceManager( OwnerActor ) )
	{
		for( const FInstanceData& InstanceDataEntry : InstanceDataArray->GetInstanceData() )
		{
			FInstanceOwnerHandlePtr NewInstanceHandle;
			Manager->SetInstanced( OwnerActor, ActorTransform, InstanceDataEntry, NewInstanceHandle, bInitializeHidden );
			OutHandles.Add( NewInstanceHandle );
		}
	}
}

void AAbstractInstanceManager::SetInstanceFromDataStatic( AActor* OwnerActor, const FTransform& ActorTransform, const FInstanceData& InstanceData, FInstanceOwnerHandlePtr& OutHandle, bool bInitializeHidden )
{
	if ( AAbstractInstanceManager* Manager = GetInstanceManager( OwnerActor ) )
	{
		Manager->SetInstanced(OwnerActor, ActorTransform, InstanceData, OutHandle, bInitializeHidden);
	}
}

void AAbstractInstanceManager::SetInstanced( AActor* OwnerActor, const FTransform& ActorTransform, const FInstanceData& InstanceData, FInstanceOwnerHandlePtr& OutHandle, bool bInitializeHidden )
{
	// Generate unique name.
	if(!IsValid( InstanceData.StaticMesh ) )
	{
		UE_LOG(LogTemp,Error,TEXT("Actor:[%s] trying to add instances to abstract instance mananger without an static mesh assigned!"),OwnerActor ? *OwnerActor->GetName() : TEXT("NONE"));
		return;
	}
	// If we were not provided a valid instance handle to write the data into, create a new one now
	if (!OutHandle.IsValid())
	{
		OutHandle = MakeShared<FInstanceOwnershipHandle, ESPMode::NotThreadSafe>();
	}
	
	const FName Name = BuildUniqueName( InstanceData );
	FInstanceComponentData* InstanceEntry = InstanceMap.Find( Name );

	if(!InstanceEntry)
	{
		// create instance.
		BuildInstanceEntryData( Name, InstanceData, InstanceEntry );

#if WITH_EDITOR
		if(InstanceEntry->bUsesBucketCollision )
		{
			EditorCheck( InstanceEntry->InstancedCollisionComponents.IsValidIndex( 0 )  );	
		}
		
		EditorCheck( InstanceEntry );
		EditorCheck( InstanceEntry->GetLightweightMeshComponent(0) ); // Every Entry should have at least one Mesh Comp on initialize
#endif
	}

	// Data to hold our visual/collision handle and component information
	FInstanceAdditionData InstanceAdditionData;
	FTransform InstanceRelativeTransform = InstanceData.RelativeTransform;
	
	if( InstanceData.bApplyRandomOffsetOnInstance )
	{
		InstanceRelativeTransform.AddToTranslation( InstanceData.PositionOffset * ( FMath::FRand() * 2.f - 1.f) );
	}
	
	const FTransform InstanceSpawnLocation = InstanceRelativeTransform * ActorTransform;
	EditorCheck( InstanceSpawnLocation.IsValid() )
	const FVector Scale = InstanceSpawnLocation.GetScale3D();
	
	InstanceEntry->AddInstance( InstanceSpawnLocation, true, bInitializeHidden, InstanceAdditionData);
	
	// Add custom primitive data.
	if(InstanceData.DefaultPerInstanceCustomData.Num() > 0)
	{
		InstanceEntry->GetLightweightMeshComponent( InstanceAdditionData.VisualData.ComponentIndex )->SetCustomData( InstanceAdditionData.VisualData.InstanceID,InstanceData.DefaultPerInstanceCustomData,true );
		OutHandle->CustomData = InstanceData.DefaultPerInstanceCustomData;
	}
	
	// Setup Collision
	ULightweightCollisionComponent* BatchCollisionComponent = nullptr;
	if( InstanceData.bUseBatchedCollision )
	{
		BatchCollisionComponent = InstanceEntry->GetLightweightCollisionComponent( InstanceAdditionData.CollisionData.ComponentIndex );
	}
	
	OutHandle->HandleID = InstanceAdditionData.VisualData.InstanceID;
	OutHandle->MeshComponentIndex = InstanceAdditionData.VisualData.ComponentIndex;
	OutHandle->CollisionHandleID = InstanceAdditionData.CollisionData.InstanceID;
	OutHandle->Owner = OwnerActor;
	OutHandle->InstancedStaticMeshComponent = InstanceEntry->GetLightweightMeshComponent( InstanceAdditionData.VisualData.ComponentIndex );
	OutHandle->BatchCollisionMeshComponent = BatchCollisionComponent;
	OutHandle->AkInstancedGeometryComponent = InstanceEntry->AkInstancedGeometryComponent;
	OutHandle->Scale = Scale;	// cache scale for hiding.
	OutHandle->Internal_SetIsBigOffsetHidden( bInitializeHidden ); 

	//Setup Audio geometry
	if (InstanceEntry->AkInstancedGeometryComponent)
	{
		AudioGeometryInstanceManager->AddAudioGeometryInstance( InstanceSpawnLocation, InstanceData.StaticMesh->GetBoundingBox().GetExtent(),
																Scale, InstanceEntry->AkInstancedGeometryComponent, OutHandle.Get() );
	}
	
	// Cache num before flushing
	OutHandle->NumPrimitiveFloatData = OutHandle->CustomData.Num();
		
	// Add handle to the list.
	const int32 AddedIndex = InstanceEntry->AddInstanceHandle( OutHandle );
	
	EditorCheck( AddedIndex == InstanceAdditionData.VisualData.InstanceID );
}

void AAbstractInstanceManager::MarkDirtyDeferred( UInstancedStaticMeshComponent* MeshComponent )
{
	
}

void AAbstractInstanceManager::RemoveInstance( FInstanceOwnerHandlePtr& Handle )
{
	EditorCheck( Handle.IsValid() );
	
	// Handle redirects.
	UHierarchicalInstancedStaticMeshComponent* Component = Handle->GetInstanceComponent();
	check(Component);

	const FName KeyName = BuildUniqueName( Component );
	
	EditorCheck( InstanceMap.Contains( KeyName ) )
	
	FInstanceComponentData& InstanceEntry = InstanceMap[ KeyName ];
	InstanceEntry.RemoveInstance( Handle);

	// Reset the instance handle IDs and then the provided pointer
	Handle->ResetHandle();
	Handle.Reset();
}

void AAbstractInstanceManager::RemoveInstances( UObject* WorldContext, TArray<FInstanceOwnerHandlePtr>& Handles )
{
	if( AAbstractInstanceManager* Manager = GetInstanceManager( WorldContext ) )
	{
		for( int32 i = Handles.Num() - 1; i >= 0; --i )
		{
			Manager->RemoveInstance( Handles[i] );
		}
		Handles.Empty();
	}
}

bool AAbstractInstanceManager::ResolveHit( const FHitResult& Result, FInstanceHandle& OutHandle )
{
	if ( Result.GetActor() == this )
	{
		if ( ULightweightCollisionComponent* HitCollision = Cast<ULightweightCollisionComponent>(Result.GetComponent() ) )
		{
			const FName VisualIDBucket = HitCollision->ComponentTags.IsValidIndex( 0 ) ? HitCollision->ComponentTags[ 0 ] : FName();
			const FName CollisionIDBucket = HitCollision->ComponentTags.IsValidIndex( 1 ) ? HitCollision->ComponentTags[ 1 ] : FName();
			const FName HandleHash = BuildUniqueName( HitCollision );
		
			const int32 VisualCompIndex = FCString::Atoi( *VisualIDBucket.ToString() ); 
			const int32 CollisionPerVisual = InstanceMap[HandleHash].NumCollisionComponentsPerVisual;
			const int32 CollisionBucketIndex = (FCString::Atoi( *CollisionIDBucket.ToString() ));
			const int32 BucketIndex = (VisualCompIndex * CollisionPerVisual) + CollisionBucketIndex;
			EditorCheck( InstanceMap[ HandleHash ].InstancedCollisionComponents[ BucketIndex ] == HitCollision )
			
			const int32 HandleId = (CollisionBucketIndex * NumCollisionInstances) + Result.Item;

			const TArray<FInstanceOwnerHandlePtr>& InstanceHandleLookup = InstanceMap[ HandleHash ].InstanceHandles[VisualCompIndex];
			if( !InstanceHandleLookup.IsValidIndex( HandleId ) )
			{
				UE_LOG( LogTemp, Warning, TEXT("handle id %d is out of bounds %d outer: %s "),HandleId, InstanceHandleLookup.Num(), *HandleHash.ToString() );
				return false;
			}
			
			const FInstanceOwnerHandlePtr& Handle = InstanceHandleLookup[ HandleId ];
			EditorCheck( Handle->IsInstanced() )

			// Intentionally slice off data that is not relevant to read-only FInstanceHandle from FInstanceOwnershipHandle
			OutHandle = FInstanceHandle(*Handle);
			return true;
		}
	}
	
	return false;
}

bool AAbstractInstanceManager::ResolveOverlap( const FOverlapResult& Result, FInstanceHandle& OutHandle )
{
	if( Result.GetActor() == this )
	{
		if( ULightweightCollisionComponent* HitCollision = Cast< ULightweightCollisionComponent >( Result.GetComponent() ) )
		{
			// Fence against hims, they are not allowed.
			if( HitCollision->IsA(UHierarchicalInstancedStaticMeshComponent::StaticClass() ) )
			{
				return false;
			}
		
			const FName VisualIDBucket = HitCollision->ComponentTags.IsValidIndex( 0 ) ? HitCollision->ComponentTags[ 0 ] : FName();
			const FName CollisionIDBucket = HitCollision->ComponentTags.IsValidIndex( 1 ) ? HitCollision->ComponentTags[ 1 ] : FName();
			const FName HandleHash = BuildUniqueName( HitCollision );
		
			const int32 VisualCompIndex = FCString::Atoi( *VisualIDBucket.ToString() ); 
			const int32 CollisionPerVisual = InstanceMap[HandleHash].NumCollisionComponentsPerVisual;
			const int32 CollisionBucketIndex = (FCString::Atoi( *CollisionIDBucket.ToString() ));
			const int32 BucketIndex = (VisualCompIndex * CollisionPerVisual) + CollisionBucketIndex;
			EditorCheck( InstanceMap[ HandleHash ].InstancedCollisionComponents[ BucketIndex ] == HitCollision )
			
			const int32 HandleId = (CollisionBucketIndex * NumCollisionInstances) + Result.ItemIndex;

			const TArray<FInstanceOwnerHandlePtr>& InstanceHandleLookup = InstanceMap[ HandleHash ].InstanceHandles[VisualCompIndex];
			if( !InstanceHandleLookup.IsValidIndex( HandleId ) )
			{
				UE_LOG( LogTemp, Warning, TEXT("handle id %d is out of bounds %d outer: %s "),HandleId, InstanceHandleLookup.Num(), *HandleHash.ToString() );
				return false;
			}

			const FInstanceOwnerHandlePtr& Handle = InstanceHandleLookup[ HandleId ];
			EditorCheck( Handle->IsInstanced() )

			// Intentionally slice off data that is not relevant to read-only FInstanceHandle from FInstanceOwnershipHandle
			OutHandle = FInstanceHandle(*Handle);
			return true;
		}
	}

	return false;
}

const UHierarchicalInstancedStaticMeshComponent* AAbstractInstanceManager::GetHandleInfo( const FInstanceHandle& Handle, int32& OutInstanceID )
{
	OutInstanceID = Handle.HandleID;
	return Handle.GetInstanceComponent();
}

void AAbstractInstanceManager::SetCustomPrimitiveDataOnHandle( const FInstanceOwnerHandlePtr& Handle,const TArray<float>& Values, bool bMarkDirty )
{
	Handle->SetPrimitiveDataByArray( Values, bMarkDirty );
	// If we are not marking dirty then we need to manually mark the Render Instance Dirty. This is a little hacky to force an update of the custom data (without triggering a rebuild)
	// This operation is relatively cheap. So its not too problematic to assume we want this done if we have changed any of the custom data so we can actually see the changes  
	// For this to work we have to manually set the cmd buffers custom data num (it will crash otherwise as we are side stepping some logic to avoid overhead here)
	if( !bMarkDirty && CVar_UseDirtyRenderStateOnCustomDataSet )
	{
		if( FPrimitiveSceneProxy* sceneProxy = Handle->GetInstanceComponent()->SceneProxy )
		{
			if( sceneProxy->HasPerInstanceCustomData() )
			{
				const int32 PrevNumCustomDataFloats = sceneProxy->GetInstanceSceneData().Num() ? sceneProxy->GetInstanceCustomData().Num() / sceneProxy->GetInstanceSceneData().Num() : Values.Num();
				Handle->GetInstanceComponent()->InstanceUpdateCmdBuffer.NumCustomDataFloats = PrevNumCustomDataFloats;
				Handle->GetInstanceComponent()->MarkRenderInstancesDirty();
			}
		}
	}
}

void AAbstractInstanceManager::SetCustomPrimitiveDataOnHandles( const TArray<FInstanceOwnerHandlePtr>& Handles,const TArray<float>& Values, bool bMarkDirty )
{
	for(int32 i = 0; i < Handles.Num(); i++)
	{
		SetCustomPrimitiveDataOnHandle( Handles[i], Values, i == Handles.Num() -1 && bMarkDirty );
	}
}

// Called when the game starts or when spawned
void AAbstractInstanceManager::BeginPlay()
{
	Super::BeginPlay();
	
	bAllowLazySpawn = CVarAllowLazySpawning.GetValueOnGameThread() == 1;
	PriorityDistance = CVarLazySpawnPriorityRange.GetValueOnGameThread();

	if(bAllowLazySpawn)
	{
		if ( GetWorld()->GetFirstPlayerController() && GetWorld()->GetFirstPlayerController()->GetPawn() )
		{
			CachedPlayerCharacter = GetWorld()->GetFirstPlayerController();
		}
	}
}

void AAbstractInstanceManager::EndPlay( const EEndPlayReason::Type EndPlayReason )
{
	Super::EndPlay( EndPlayReason );

}

ULightweightCollisionComponent* AAbstractInstanceManager::CreateLightweightCollisionComponent( const FInstanceData& InstanceData )
{
	ULightweightCollisionComponent* CollisionComponent = NewObject<ULightweightCollisionComponent>( this );
	CollisionComponent->SetStaticMesh( InstanceData.StaticMesh );
	CollisionComponent->OverrideMaterials = InstanceData.OverridenMaterials;
	CollisionComponent->SetMobility( InstanceData.Mobility );
	CollisionComponent->AttachToComponent( GetRootComponent(),FAttachmentTransformRules::KeepRelativeTransform );
	CollisionComponent->SetRelativeTransform( FTransform::Identity );
	CollisionComponent->SetVisibility( false );
	CollisionComponent->SetCollisionProfileName( InstanceData.CollisionProfileName );
	CollisionComponent->bMultiBodyOverlap = true;
	return CollisionComponent;
}

void AAbstractInstanceManager::BuildInstanceEntryData( const FName& Name, const FInstanceData& InstanceData, FInstanceComponentData* &OutInstanceData )
{
	const bool bIsLazyLoading = bAllowLazySpawn;
	const bool bEnableDistanceFieldShadows = !bIsLazyLoading && InstanceData.bCastDistanceFieldShadows;

	// Component Creation handles creation of initial visual and collision components
	FInstanceComponentData ComponentData(this, InstanceData, bEnableDistanceFieldShadows );
	// Gets the first visual mesh comp (create during Component Data construction)
	ULightweightHierarchicalInstancedStaticMeshComponent* MeshComp = ComponentData.GetLightweightMeshComponent(0); // Get the first (potentially only) mesh component
	
	// Setup draw distance.
	if(InstanceData.MaxDrawDistance > 0)
	{
		const float Modifier = CVarDrawDistanceModifier.GetValueOnGameThread();
		MeshComp->SetCullDistances( InstanceData.MaxDrawDistance * Modifier * 0.95, InstanceData.MaxDrawDistance * Modifier);
	}
	
	OutInstanceData = &InstanceMap.Add( Name, ComponentData );
}

FName AAbstractInstanceManager::BuildUniqueName( const FInstanceData& InstanceData )
{
	// Do we deal with overriden materials?
	if ( InstanceData.OverridenMaterials.Num() > 0 )
	{
		uint32 Hash = 0;
		for	( const UMaterialInterface* Material: InstanceData.OverridenMaterials )
		{
			if( Material )
			{
				Hash = HashCombine( Hash, GetTypeHash( Material->GetFName() ) );
			}
		}
		
		return FName( InstanceData.StaticMesh->GetName(), Hash );
	}

	return InstanceData.StaticMesh->GetFName();
}

FName AAbstractInstanceManager::BuildUniqueName( const UInstancedStaticMeshComponent* MeshComponent )
{
	if (MeshComponent->OverrideMaterials.Num() > 0)
	{
		uint32 hash = 0;
		for	( const UMaterialInterface* Material: MeshComponent->OverrideMaterials )
		{
			if( Material )
			{
				hash = HashCombine( hash, GetTypeHash( Material->GetFName() ) );
			}
		}

		return FName(MeshComponent->GetStaticMesh()->GetFName(), hash );
	}

	return FName( MeshComponent->GetStaticMesh()->GetFName() ); 
}

void AAbstractInstanceManager::StartDrawDebug( bool bEnabled )
{
	if ( bEnabled )
	{
		GetWorld()->GetTimerManager().ClearAllTimersForObject( this );

		FTimerHandle Handle;
		GetWorld()->GetTimerManager().SetTimer( Handle, this, &AAbstractInstanceManager::DrawDebug, 0.1f,true);
	}
	else
	{
		FlushDebugStrings( GetWorld() );
		GetWorld()->GetTimerManager().ClearAllTimersForObject( this );
	}
}

void AAbstractInstanceManager::HideAllInstance( bool bIsHidden )
{
	for( const TTuple< FName, FInstanceComponentData >& InstanceData: InstanceMap )
	{
		for( auto meshComp : InstanceData.Value.InstancedStaticMeshComponents)
		{
			meshComp->SetVisibility( !bIsHidden );
		}
	}
}

void AAbstractInstanceManager::DrawDebug()
{
	FVector PlayerLocation;
	if ( GetWorld()->GetFirstPlayerController() )
	{
		PlayerLocation = GetWorld()->GetFirstPlayerController()->GetPawnOrSpectator()->GetActorLocation();
	}
	
	const float Range = CVarDisplayLightWeightInstanceDebugRange.GetValueOnAnyThread(  );
	
	for(const TTuple< FName, FInstanceComponentData >& InstanceData: InstanceMap)
	{
		FString Name = InstanceData.Key.ToString();
		
		for(const auto& CompIndexToHandleArray : InstanceData.Value.InstanceHandles)
		{
			for( auto& HandlePtr : CompIndexToHandleArray.Get<1>() )
			{
				int32 HandleId = HandlePtr->HandleID;
				FTransform T;
				InstanceData.Value.GetLightweightMeshComponent( CompIndexToHandleArray.Key )->GetInstanceTransform( HandleId, T, true/* already in world space.*/ );
				if(FVector::Distance( PlayerLocation, T.GetLocation() ) < Range )
				{
					FString StringToDraw;
					StringToDraw.Append( Name + "\n" );
					StringToDraw.Appendf( TEXT("HandleID\t\t[ %d ] \n"), HandleId );
					StringToDraw.Appendf( TEXT("HandleID\t\t[ %d ] \n"), HandlePtr->MeshComponentIndex );
					StringToDraw.Appendf( TEXT("CollisionID\t[ %d ] \n"), HandlePtr->CollisionHandleID );
					StringToDraw.Appendf( TEXT("%s \n"), *T.ToHumanReadableString() );
					
					DrawDebugString( GetWorld(), T.GetLocation(), StringToDraw, this, FColor::White, 0.0f );
				}
			}
		}
	}
}

void AAbstractInstanceManager::HandleDeferredDirtyComponents()
{
	if(DeferredMarkDirtySet.Num() == 0)
	{
		UE_LOG(LogTemp,Error,TEXT("AAbstractInstanceManager::HandleDeferredDirtyComponents Called while the set is empty. please investiage!"));
	}

	for( UInstancedStaticMeshComponent* ism: DeferredMarkDirtySet )
	{
		ism->MarkRenderStateDirty();
	}

	DeferredMarkDirtySet.Empty( );
	UpdateDeferredTimerHandle.Invalidate();
}

void OnToggleDebug()
{
#if 0
	if ( GEngine && IsValid(GWorld) )
	{
		if ( auto Manager = AAbstractInstanceManager::GetInstanceManager( ) )
		{
			if( IsValid(Manager) && Manager->IsActorInitialized() )
			{
				Manager->StartDrawDebug( CVarDisplayLightWeightInstanceDebug.GetValueOnAnyThread() == 1 );
			}
		}
	}
#endif
}

void OnToggleHide()
{
#if 0
	if ( GEngine && IsValid(GWorld) )
	{
		if ( auto Manager = AAbstractInstanceManager::GetInstanceManager( ) )
		{
			if( IsValid(Manager) && Manager->IsActorInitialized() )
			{
				Manager->HideAllInstance(CVarHideLightWeightInstancesDebug.GetValueOnAnyThread( ) == 1);
			}
		}
	}
#endif
}


FAutoConsoleVariableSink CDisplayLightWeightInstanceDebugSink( FConsoleCommandDelegate::CreateStatic( &OnToggleDebug ));
FAutoConsoleVariableSink CHideLightWeightInstancesDebugSink( FConsoleCommandDelegate::CreateStatic( &OnToggleHide ));