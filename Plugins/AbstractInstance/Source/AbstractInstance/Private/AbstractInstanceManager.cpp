// Copyright Coffee Stain Studios. All Rights Reserved.


#include "AbstractInstanceManager.h"

#include "AbstractInstanceInterface.h"
#include "DrawDebugHelpers.h"
#include "InstanceData.h"
#include "TimerManager.h"
#include "Engine/World.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/PlayerController.h"

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

constexpr int32 NumCollisionInstances = 500;

#if !AI_PIE
AAbstractInstanceManager* AAbstractInstanceManager::StaticManager = nullptr;
#else
TMap<UWorld*,AAbstractInstanceManager*> AAbstractInstanceManager::StaticManager_PIE;
#endif

// Sets default values
AAbstractInstanceManager::AAbstractInstanceManager()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
	
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent->SetMobility( EComponentMobility::Static );
}

AAbstractInstanceManager* AAbstractInstanceManager::GetInstanceManager( UObject* WorldContext )
{
#if !AI_PIE
	if(!AAbstractInstanceManager::StaticManager)
	{
		AAbstractInstanceManager::StaticManager = WorldContext->GetWorld()->SpawnActor< AAbstractInstanceManager >();
	}

	return AAbstractInstanceManager::StaticManager;
#else
	if (StaticManager_PIE.Contains(WorldContext->GetWorld()))
	{
		return StaticManager_PIE[WorldContext->GetWorld()];
	}
	else
	{
		auto NewManager = WorldContext->GetWorld()->SpawnActor< AAbstractInstanceManager >();
		StaticManager_PIE.Add(WorldContext->GetWorld(),NewManager);

		return NewManager;
	}
#endif
}

AAbstractInstanceManager* AAbstractInstanceManager::GetInstanceManager()
{
#if !AI_PIE
	return AAbstractInstanceManager::StaticManager;
#else
	// TODO implement.
	return nullptr;
#endif
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

			for (const TTuple<FName, FInstanceComponentData>& instanceEntry : InstanceMap )
			{
				if ( instanceEntry.Value.bCastDistanceFieldShadows )
				{
					instanceEntry.Value.InstancedStaticMeshComponent->bAffectDistanceFieldLighting = true;
					instanceEntry.Value.InstancedStaticMeshComponent->MarkRenderStateDirty();
				}
			}
			
			bAllowLazySpawn = false;
		}
	}


#if !UE_BUILD_SHIPPING
	if (CVarDisplayLightWeightInstanceDebug.GetValueOnAnyThread() == 1)
	{
		DrawDebug();
	}
#endif
}

void AAbstractInstanceManager::SetInstancedStatic( AActor* OwnerActor, const FTransform& ActorTransform, const UAbstractInstanceDataObject* InstanceDataArray, TArray<FInstanceHandle*>& OutHandles, bool bInitializeHidden)
{
	QUICK_SCOPE_CYCLE_COUNTER( AAbstractInstanceManager_SetInstancedStatic )
	
	if ( const auto Manager = AAbstractInstanceManager::GetInstanceManager( OwnerActor ) )
	{
		if( InstanceDataArray )
		{
			for( const auto& InstanceDataEntry :  InstanceDataArray->GetInstanceData() )
			{
				// create handle, if we are dealing with lazy load we reduce this one, since the owning actor will have this handle too.
				FInstanceHandle* Handle = new FInstanceHandle();

				if( InstanceDataEntry.bAllowLazyInstance && Manager->CanLazyLoad() )
				{
					QUICK_SCOPE_CYCLE_COUNTER( Enqueue_LazyInstance )

					FLazySpawnEntry Entry = FLazySpawnEntry( Handle, InstanceDataEntry, OwnerActor, ActorTransform );
					const float Distance = FVector::Distance( Manager->CachedPlayerCharacter->GetActorLocation(), ActorTransform.GetLocation() );

					if( Distance < Manager->PriorityDistance )
					{
						Manager->PriorityLazyLoadTasks.Enqueue( FLazySpawnEntry( Handle, InstanceDataEntry, OwnerActor, ActorTransform ) );
					}
					else
					{
						Manager->LazyLoadTasks.Enqueue( FLazySpawnEntry( Handle, InstanceDataEntry, OwnerActor, ActorTransform ) );
					}
				}
				else
				{
					Manager->SetInstanced( OwnerActor, ActorTransform, InstanceDataEntry, Handle, bInitializeHidden );
					EditorCheck( Handle && Handle->IsValid() );
				}
				
				OutHandles.Add( Handle );
			}
		}
	}
}

void AAbstractInstanceManager::SetInstanceFromDataStatic( AActor* OwnerActor, const FTransform& ActorTransform, const FInstanceData& InstanceData, FInstanceHandle*& OutHandle, bool bInitializeHidden )
{
	QUICK_SCOPE_CYCLE_COUNTER( AAbstractInstanceManager_SetInstanceFromDataStatic )

	if ( const auto Manager = AAbstractInstanceManager::GetInstanceManager( OwnerActor ) )
	{
		// create handle, if we are dealing with lazy load we reduce this one, since the owning actor will have this handle too.
		FInstanceHandle* Handle = new FInstanceHandle();

		if(Manager->CanLazyLoad() && InstanceData.bAllowLazyInstance )
		{
			QUICK_SCOPE_CYCLE_COUNTER( Enqueue_LazyInstance )
			FLazySpawnEntry Entry = FLazySpawnEntry( Handle, InstanceData, OwnerActor, ActorTransform );
					
			const float Distance = FVector::Distance( Manager->CachedPlayerCharacter->GetActorLocation(), ActorTransform.GetLocation() );

			if( Distance < Manager->PriorityDistance )
			{
				Manager->PriorityLazyLoadTasks.Enqueue(
					FLazySpawnEntry(
						Handle,
						InstanceData,
						OwnerActor,
						ActorTransform) );
			}
			else
			{
				Manager->LazyLoadTasks.Enqueue(
					FLazySpawnEntry(
						Handle,
						InstanceData,
						OwnerActor,
						ActorTransform) );
			}
		}
		else
		{
			Manager->SetInstanced( OwnerActor, ActorTransform, InstanceData, Handle, bInitializeHidden);
			EditorCheck( Handle && Handle->IsValid() );
		}

		OutHandle = Handle;
	}
}

void AAbstractInstanceManager::SetInstanced( AActor* OwnerActor, const FTransform& ActorTransform, const FInstanceData& InstanceData, FInstanceHandle* &OutHandle, bool bInitializeHidden )
{
	// Generate unique name.
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
		EditorCheck( InstanceEntry->InstancedStaticMeshComponent );
#endif
	}
	
	int32 HandleID = INDEX_NONE;
	FTransform InstanceRelativeTransform = InstanceData.RelativeTransform;
	
	if( InstanceData.bApplyRandomOffsetOnInstance )
	{
		InstanceRelativeTransform.AddToTranslation( InstanceData.PositionOffset * ( FMath::FRand() * 2.f - 1.f) );
	}
	
	const FTransform InstanceSpawnLocation = InstanceRelativeTransform * ActorTransform;
	EditorCheck( InstanceSpawnLocation.IsValid() )

	const FVector Scale = InstanceSpawnLocation.GetScale3D();
	if (bInitializeHidden)
	{
		FTransform ZeroScaleTransform = InstanceSpawnLocation;
		ZeroScaleTransform.SetScale3D(FVector(0.01));
		ZeroScaleTransform.AddToTranslation( -FVector(0,0,AIM_BigOffset) );
		HandleID = InstanceEntry->InstancedStaticMeshComponent->AddInstance( ZeroScaleTransform, true );
	}
	else
	{
		HandleID = InstanceEntry->InstancedStaticMeshComponent->AddInstance( InstanceSpawnLocation, true );
	}
	
	// Add custom primitive data.
	if(InstanceData.DefaultPerInstanceCustomData.Num() > 0)
	{
		InstanceEntry->InstancedStaticMeshComponent->SetCustomData( HandleID,InstanceData.DefaultPerInstanceCustomData,true );
		OutHandle->CustomData = InstanceData.DefaultPerInstanceCustomData;
	}
	
	// Setup Collision
	ULightweightCollisionComponent* BatchCollisionComponent = nullptr;
	int32 CollisionID = INDEX_NONE;
	if( InstanceData.bUseBatchedCollision )
	{
		TArray<ULightweightCollisionComponent*>& InstanceCollisionComponent = InstanceEntry->InstancedCollisionComponents;
		const int32 InstanceMapId = HandleID == 0 ? 0 : ( HandleID / NumCollisionInstances );
		
		if ( !InstanceCollisionComponent.IsValidIndex( InstanceMapId ) )
		{
			BatchCollisionComponent = DuplicateObject( InstanceCollisionComponent[ 0 ],this );
			BatchCollisionComponent->ClearInstances();
			BatchCollisionComponent->ComponentTags.Empty(0);
			BatchCollisionComponent->AttachToComponent( GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform );
			BatchCollisionComponent->SetRelativeTransform( FTransform::Identity );

			const int32 BatchID =InstanceCollisionComponent.Add( BatchCollisionComponent );
			BatchCollisionComponent->ComponentTags.Add( FName( FString::FromInt( BatchID ) ) );
			BatchCollisionComponent->RegisterComponent();
		}
		else
		{
			BatchCollisionComponent = InstanceCollisionComponent[ InstanceMapId ];
		}

		EditorCheck( BatchCollisionComponent );
		CollisionID = BatchCollisionComponent->AddInstance( InstanceSpawnLocation, true );
	}

	OutHandle->HandleID = HandleID;
	OutHandle->CollisionHandleID = CollisionID;
	OutHandle->Owner = OwnerActor;
	OutHandle->InstancedStaticMeshComponent = InstanceEntry->InstancedStaticMeshComponent;
	OutHandle->BatchCollisionMeshComponent = BatchCollisionComponent;
	OutHandle->Scale = Scale;	// cache scale for hiding.
	OutHandle->SetIsBigOffsetHidden( bInitializeHidden ); 
	
	//OutHandle = new FInstanceHandle( HandleID, CollisionID, Owner, InstanceEntry->InstancedStaticMeshComponent, BatchCollisionComponent );
	// UE_LOG(LogTemp,Warning,TEXT("Added new handle[%d] collisionid[%d]"),HandleID,CollisionID);

	
	// Cache num before flushing
	OutHandle->NumPrimitiveFloatData = OutHandle->CustomData.Num();
		
	// Add handle to the list.
	const int32 AddedIndex = InstanceEntry->InstanceHandles.Add( OutHandle );
	
	EditorCheck( AddedIndex == HandleID );
}

void AAbstractInstanceManager::MarkDirtyDeferred( UInstancedStaticMeshComponent* MeshComponent )
{
	
}

void AAbstractInstanceManager::RemoveInstance( FInstanceHandle* Handle )
{
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
	
	// Handle redirects.
	UHierarchicalInstancedStaticMeshComponent* Component = Handle->GetInstanceComponent();
	check(Component);

	const FName KeyName = BuildUniqueName( Component );
	const uint32 HandleID = Handle->HandleID;
	const uint32 CollisionID = Handle->CollisionHandleID;
	const uint32 CollisionBucket = HandleID == 0 ? 0 : HandleID / NumCollisionInstances;

	EditorCheck( InstanceMap.Contains( KeyName ) )

	FInstanceComponentData& InstanceEntry = InstanceMap[ KeyName ];
	
	InstanceEntry.InstanceHandles.RemoveAtSwap( HandleID );
	//UE_LOG(LogTemp,Warning,TEXT("Removing handle %d"), HandleID)
	
	const bool ShouldRemapIndex = InstanceEntry.InstanceHandles.Num() > ( int32 )HandleID;

	{	// Solve visual instances.
		if( ShouldRemapIndex )
		{
			InstanceEntry.InstanceHandles[ HandleID ]->HandleID = HandleID;
		}

		Component->RemoveInstance( HandleID );

		if(InstanceEntry.InstanceHandles.Num() <= 0 )
		{
			Component->ClearInstances();
		}
		else
		{
			Component->MarkRenderStateDirty();
		}
	}

	if(InstanceEntry.bUsesBucketCollision)
	{	// Solve collision pieces.
		if( InstanceEntry.InstanceHandles.Num() > ( int32 )HandleID )
		{
			InstanceEntry.InstanceHandles[ HandleID ]->CollisionHandleID = CollisionID;
		}

		// Get the last instance, since that one got moved in place of our previous one. 
		FTransform Transform;

		// Get the last bucket that contains instance.
		ULightweightCollisionComponent* LastBucketComponent = nullptr;
		for( int32 i = InstanceEntry.InstancedCollisionComponents.Num() - 1; i >= 0; --i )
		{
			if ( InstanceEntry.InstancedCollisionComponents[ i ]->GetInstanceCount() != 0 )
			{
				LastBucketComponent = InstanceEntry.InstancedCollisionComponents[ i ];
				break;
			}
		}
		
		LastBucketComponent->GetInstanceTransform( LastBucketComponent->GetInstanceCount() - 1, Transform ); 
		InstanceEntry.InstancedCollisionComponents[ CollisionBucket ]->UpdateInstanceTransform( CollisionID, Transform, false, false, true  );

		// Remove last one since that one got "moved" to an other bucket.
		LastBucketComponent->RemoveInstance( LastBucketComponent->GetInstanceCount() -1 );
		
		if( LastBucketComponent->GetInstanceCount() <= 0 )
		{
			LastBucketComponent->ClearInstances();
		}
		else
		{
			LastBucketComponent->MarkRenderStateDirty();
			InstanceEntry.InstancedCollisionComponents[ CollisionBucket ]->MarkRenderStateDirty();
			if(ShouldRemapIndex)
			{
				InstanceEntry.InstanceHandles[ HandleID ]->BatchCollisionMeshComponent = InstanceEntry.InstancedCollisionComponents[ CollisionBucket ];
			}
		}
	}
}

void AAbstractInstanceManager::RemoveInstances( UObject* WorldContext, TArray<FInstanceHandle*>& Handles, bool bEmptyHandleArray )
{
	if( auto Manager = GetInstanceManager( WorldContext ) )
	{
		for( int32 i = Handles.Num() - 1; i >= 0; --i )
		{
			Manager->RemoveInstance( Handles[ i ] );
		}

		if ( bEmptyHandleArray )
		{
			Handles.Empty( );
		}
	}
}

void AAbstractInstanceManager::RemoveInstance( FInstanceHandle& InHandle )
{
	FInstanceHandle* Handle = &InHandle;
	RemoveInstance( Handle );
}

bool AAbstractInstanceManager::ResolveHit( const FHitResult& Result, FInstanceHandle& OutHandle )
{
	if ( Result.GetActor() == this )
	{
		if ( ULightweightCollisionComponent* HitCollision = Cast<ULightweightCollisionComponent>(Result.GetComponent() ) )
		{
			const FName BucketID = HitCollision->ComponentTags.IsValidIndex( 0 ) ? HitCollision->ComponentTags[ 0 ] : FName();
			const FName HandleHash = BuildUniqueName( HitCollision );
			
			check( !BucketID.IsNone() )
			
			const int32 BucketIndex = FCString::Atoi( *BucketID.ToString() );
			EditorCheck( InstanceMap[ HandleHash ].InstancedCollisionComponents[ BucketIndex ] == HitCollision )

			const int32 HandleId = BucketIndex * NumCollisionInstances + Result.Item;

			TArray<FInstanceHandle*>* HandleMapPtr = &InstanceMap[ HandleHash ].InstanceHandles;
			EditorCheck( HandleMapPtr )

			TArray<FInstanceHandle*>& HandleMapRef = *HandleMapPtr;
			EditorCheck( HandleMapRef.IsValidIndex( HandleId ) );

			if( !HandleMapRef.IsValidIndex( HandleId ) )
			{
				UE_LOG( LogTemp, Warning, TEXT("handle id %d is out of bounds %d outer: %s "),HandleId, HandleMapRef.Num(), *HandleHash.ToString() );
				return false;
			}
			
			FInstanceHandle* Handle = HandleMapRef[ HandleId ];
			EditorCheck( Handle->IsInstanced() )

			OutHandle = *Handle;
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
		
			const FName BucketID = HitCollision->ComponentTags.IsValidIndex( 0 ) ? HitCollision->ComponentTags[ 0 ] : FName();
			const FName HandleHash = BuildUniqueName( HitCollision );
		
			check( !BucketID.IsNone() )
		
			const int32 BucketIndex = FCString::Atoi( *BucketID.ToString() );
			EditorCheck( InstanceMap[ HandleHash ].InstancedCollisionComponents[ BucketIndex ] == HitCollision )

			const int32 HandleId = BucketIndex * NumCollisionInstances + Result.ItemIndex;

			TArray<FInstanceHandle*>* HandleMapPtr = &InstanceMap[ HandleHash ].InstanceHandles;
			EditorCheck( HandleMapPtr )

			TArray<FInstanceHandle*>& HandleMapRef = *HandleMapPtr;
			EditorCheck( HandleMapRef.IsValidIndex( HandleId ) );
		
			FInstanceHandle* Handle = HandleMapRef[ HandleId ];
			EditorCheck( Handle->IsInstanced() )

			OutHandle = *Handle;
			return true;
		}
	}

	return false;
}

UHierarchicalInstancedStaticMeshComponent* AAbstractInstanceManager::GetHandleInfo( const FInstanceHandle& Handle, int32& OutInstanceID )
{
	OutInstanceID = Handle.HandleID;
	return Handle.GetInstanceComponent();
}

void AAbstractInstanceManager::SetCustomPrimitiveDataOnHandle( const FInstanceHandle* Handle,const TArray<float>& Values, bool bMarkDirty )
{
	Handle->SetPrimitiveDataByArray( Values, bMarkDirty );
}

void AAbstractInstanceManager::SetCustomPrimitiveDataOnHandles( const TArray<FInstanceHandle*>& Handles,const TArray<float>& Values, bool bMarkDirty )
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

#if !AI_PIE
	AAbstractInstanceManager::StaticManager = nullptr;
#else
	AAbstractInstanceManager::StaticManager_PIE.Empty();
#endif
}

void AAbstractInstanceManager::BuildInstanceEntryData( const FName& Name, const FInstanceData& InstanceData, FInstanceComponentData* &OutInstanceData )
{
	const bool bIsLazyLoading = bAllowLazySpawn;
	const bool bEnableDistanceFieldShadows = !bIsLazyLoading && InstanceData.bCastDistanceFieldShadows;
	
	FInstanceComponentData ComponentData;
	ComponentData.bCastDistanceFieldShadows = InstanceData.bCastDistanceFieldShadows;
	ComponentData.bUsesBucketCollision = InstanceData.bUseBatchedCollision;
	
	// Setup visual comp.
	ComponentData.InstancedStaticMeshComponent = NewObject<ULightweightHierarchicalInstancedStaticMeshComponent>(this);
	ComponentData.InstancedStaticMeshComponent->SetStaticMesh( InstanceData.StaticMesh );
	ComponentData.InstancedStaticMeshComponent->OverrideMaterials = InstanceData.OverridenMaterials;
	ComponentData.InstancedStaticMeshComponent->SetCollisionEnabled( ECollisionEnabled::NoCollision );
	ComponentData.InstancedStaticMeshComponent->SetGenerateOverlapEvents( false );
	ComponentData.InstancedStaticMeshComponent->SetMobility( InstanceData.Mobility );
	ComponentData.InstancedStaticMeshComponent->AttachToComponent( GetRootComponent(),FAttachmentTransformRules::KeepRelativeTransform );
	ComponentData.InstancedStaticMeshComponent->SetRelativeTransform( FTransform::Identity );
	ComponentData.InstancedStaticMeshComponent->SetVisibility( true );
	ComponentData.InstancedStaticMeshComponent->NumCustomDataFloats = InstanceData.NumCustomDataFloats;
	ComponentData.InstancedStaticMeshComponent->SetCastShadow( InstanceData.bCastShadows ); 
	ComponentData.InstancedStaticMeshComponent->bAffectDistanceFieldLighting = bEnableDistanceFieldShadows; // distance fields are enabled after lazy loading.
	ComponentData.InstancedStaticMeshComponent->RegisterComponent();
	ComponentData.InstancedStaticMeshComponent->bSelectable = false; // If there are too many instances the editor will freeze when selected so its better to just not allow that to happen (until a proper fix has time allocated)
	ComponentData.InstancedStaticMeshComponent->WorldPositionOffsetDisableDistance = InstanceData.MaxWPODistance;
	ComponentData.InstancedStaticMeshComponent->bWorldPositionOffsetWritesVelocity = InstanceData.bWorldPositionOffsetWritesVelocity;
	
	// Setup draw distance.
	if(InstanceData.MaxDrawDistance > 0)
	{
		const float Modifier = CVarDrawDistanceModifier.GetValueOnGameThread();
		ComponentData.InstancedStaticMeshComponent->SetCullDistances( InstanceData.MaxDrawDistance * Modifier * 0.95, InstanceData.MaxDrawDistance * Modifier);
	}
	
	// Setup collision comp
	if(InstanceData.bUseBatchedCollision)
	{
		ComponentData.InstancedCollisionComponents.Add( NewObject<ULightweightCollisionComponent>(this) );
		ComponentData.InstancedCollisionComponents[ 0 ]->SetStaticMesh( InstanceData.StaticMesh );
		ComponentData.InstancedCollisionComponents[ 0 ]->OverrideMaterials = InstanceData.OverridenMaterials;
		ComponentData.InstancedCollisionComponents[ 0 ]->SetMobility( InstanceData.Mobility );
		ComponentData.InstancedCollisionComponents[ 0 ]->AttachToComponent( GetRootComponent(),FAttachmentTransformRules::KeepRelativeTransform );
		ComponentData.InstancedCollisionComponents[ 0 ]->SetRelativeTransform( FTransform::Identity );
		ComponentData.InstancedCollisionComponents[ 0 ]->SetVisibility( false );
		ComponentData.InstancedCollisionComponents[ 0 ]->SetCollisionProfileName( InstanceData.CollisionProfileName );
		ComponentData.InstancedCollisionComponents[ 0 ]->ComponentTags.Add( FName("0") );
		ComponentData.InstancedCollisionComponents[ 0 ]->bMultiBodyOverlap = true;
		ComponentData.InstancedCollisionComponents[ 0 ]->RegisterComponent();
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
		InstanceData.Value.InstancedStaticMeshComponent->SetVisibility( !bIsHidden );
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
		for(const auto& Handle : InstanceData.Value.InstanceHandles)
		{
			int32 HandleId = Handle->HandleID;
			FTransform T;
			InstanceData.Value.InstancedStaticMeshComponent->GetInstanceTransform( HandleId, T, true/* already in world space.*/ );
			if(FVector::Distance( PlayerLocation, T.GetLocation() ) < Range )
			{
				FString StringToDraw;
				StringToDraw.Append( Name + "\n" );
				StringToDraw.Appendf( TEXT("HandleID\t\t[ %d ] \n"), HandleId );
				StringToDraw.Appendf( TEXT("CollisionID\t[ %d ] \n"),Handle->CollisionHandleID );
				StringToDraw.Appendf( TEXT("%s \n"), *T.ToHumanReadableString() );
				
				DrawDebugString( GetWorld(), T.GetLocation(), StringToDraw, this, FColor::White, 0.0f );
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
