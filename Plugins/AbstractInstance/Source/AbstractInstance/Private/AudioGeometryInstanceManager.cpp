// Copyright Coffee Stain Studios. All Rights Reserved.


#include "AudioGeometryInstanceManager.h"

#include "Async.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/PlayerController.h"

static TAutoConsoleVariable< float > CVarAudioGeometryGlobalOffset(
	TEXT( "lightweightinstances.AudioGeometryGlobalOffset" ),
	-10.0f,
	TEXT( "Global offset for audio geometry on Z coordinate." ),
	ECVF_Default );

//cvar for limiting the number of instances to process per frame
static TAutoConsoleVariable< int32 > CVarAudioGeometryInstanceLimit(
	TEXT( "lightweightinstances.AudioGeometryInstanceLimit" ),
	1000,
	TEXT( "Limit the number of audio geometry instances to process per frame." ),
	ECVF_Default );

//cvar for distance to player to process audio geometry instances
static TAutoConsoleVariable< float > CVarAudioGeometryDistanceLimit(
	TEXT( "lightweightinstances.AudioGeometryDistanceLimit" ),
	7500.0f,
	TEXT( "Distance from player to process audio geometry instances." ),
	ECVF_Default );

FBoxCenterAndExtent FAudioInstanceOctreeSemantics::GetBoundingBox( const FAudioInstanceData* InstanceData )
{
	if(InstanceData)
	{
		return InstanceData->Bounds;
	}
	return FBoxCenterAndExtent( FVector::ZeroVector, FVector::ZeroVector );
}

bool FAudioInstanceOctreeSemantics::AreElementsEqual( const FAudioInstanceData* A,
                                                      const FAudioInstanceData* B )
{
	return A->HandlePtr == B->HandlePtr;
}

void FAudioInstanceOctreeSemantics::SetElementId( FOctree& Octree, const FAudioInstanceData* Element,
                                                  FOctreeElementId2 OctreeElementID )
{
	static_cast< FAudioInstanceOctree& >(Octree).mElementIdMap.Add( Element->HandlePtr, OctreeElementID );
}

UAudioGeometryInstanceManager::UAudioGeometryInstanceManager()
{
	AudioInstanceOctree = FAudioInstanceOctree( FVector::ZeroVector, UE_OLD_HALF_WORLD_MAX );

	NewLocalAudioSurrounding.Reserve( CVarAudioGeometryInstanceLimit.GetValueOnGameThread() );
	LocalAudioSurrounding.Reserve( CVarAudioGeometryInstanceLimit.GetValueOnGameThread() );
}

UAudioGeometryInstanceManager::~UAudioGeometryInstanceManager()
{
	EnsureTaskComplete();
}

void UAudioGeometryInstanceManager::ProcessTick( const FVector& PlayerLocation )
{
#if !UE_SERVER
	QUICK_SCOPE_CYCLE_COUNTER( AAbstractInstanceManager_AudioGeometry )

	EnsureTaskComplete();

	auto AudioGeometryUpdateTaskWT = [this, PlayerLocation]()
	{
		FindAddsRemovesWT( PlayerLocation );
		//now broacast result to game thread
		AsyncTask( ENamedThreads::GameThread, [this]()
		{
			PerformAddsRemovesGT();
		} );
	};

	//Create function task
	AudioGeometryUpdateTask = FSimpleDelegateGraphTask::CreateAndDispatchWhenReady(
		FSimpleDelegateGraphTask::FDelegate::CreateLambda( AudioGeometryUpdateTaskWT ),
		TStatId(),
		nullptr,
		ENamedThreads::AnyBackgroundThreadNormalTask
		);
#endif
}

void UAudioGeometryInstanceManager::FindAddsRemovesWT( const FVector& PlayerLocation )
{
	QUICK_SCOPE_CYCLE_COUNTER( STAT_AudioGeometryUpdateTask_WorkerThread );
	
	int InstancesLimit = CVarAudioGeometryInstanceLimit.GetValueOnAnyThread();
	float DistanceLimit = CVarAudioGeometryDistanceLimit.GetValueOnAnyThread();

	NewLocalAudioSurrounding.Empty();
	AudioInstanceOctree.FindElementsWithBoundsTest(
		FBoxCenterAndExtent( PlayerLocation, FVector::OneVector * DistanceLimit ),
		[this, InstancesLimit]( FAudioInstanceData* hism )
		{
			if(NewLocalAudioSurrounding.Num() < InstancesLimit)
			{
				NewLocalAudioSurrounding.Add( hism );
			}
		} );

	RemovedInstances = LocalAudioSurrounding.Difference( NewLocalAudioSurrounding );
	AddedInstances = NewLocalAudioSurrounding.Difference( LocalAudioSurrounding );

	LocalAudioSurrounding = NewLocalAudioSurrounding;
}


void UAudioGeometryInstanceManager::PerformAddsRemovesGT()
{
	QUICK_SCOPE_CYCLE_COUNTER( STAT_AudioGeometryUpdateTask_GameThread );

	//That is a rare edge case, but it is possible that a new task will be spawned before we sync the previous one. Just wait until new transaction is scheduled
	EnsureTaskComplete();

	//First remove old ones.
	for(FAudioInstanceData* Instance: RemovedInstances)
	{
		if(Instance->AddedToAkComponent)
		{
			Instance->Component->RemoveGeometryInstance( Instance->HandlePtr );
			Instance->AddedToAkComponent = false;
		}
	}

	//Then add new ones.
	for(FAudioInstanceData* Instance: AddedInstances)
	{
		if(!Instance->AddedToAkComponent)
		{
			Instance->AddedToAkComponent = true;
			Instance->Component->
			          AddGeometryInstance( Instance->Position, Instance->Rotation, Instance->Scale, Instance->HandlePtr );
		}
	}
}


void UAudioGeometryInstanceManager::AddAudioGeometryInstance( const FTransform& InstanceLocation, const FVector& BoxExtent,
                                                              const FVector& Scale, UAkInstancedGeometryComponent* GeometryOwnerComponent,
                                                              void* HandlePtr )
{
#if !UE_SERVER
	EnsureTaskComplete();

	FBoxCenterAndExtent Bounds = FBoxCenterAndExtent( InstanceLocation.GetLocation(), BoxExtent );
	//Geometry instance is added with a global offset to mitigate of incorrect setup of sound emitters, that are placed below the ground. This will be removed in the future after buildable audio will be configured in one common way
	FVector SpawnLocation = InstanceLocation.GetLocation() + FVector( 0, 0, CVarAudioGeometryGlobalOffset.GetValueOnGameThread() );
	FRotator Rotation = InstanceLocation.Rotator();
	AudioInstanceOctree.AddElement( new FAudioInstanceData{ GeometryOwnerComponent, HandlePtr, SpawnLocation, Rotation, Scale, Bounds,
	                                                        false } );
#endif
}

void UAudioGeometryInstanceManager::RemoveAudioGeometryInstance( void* HandlePtr )
{
#if !UE_SERVER
	EnsureTaskComplete();

	FOctreeElementId2 ElementId = AudioInstanceOctree.mElementIdMap.FindRef( HandlePtr );
	auto& AudioInstance = AudioInstanceOctree.GetElementById( ElementId );

	//Remove ak instance
	if(AudioInstance->AddedToAkComponent)
	{
		AudioInstance->Component->RemoveGeometryInstance( AudioInstance->HandlePtr );
	}
	//Remove it from frame cache
	LocalAudioSurrounding.Remove( AudioInstance );
	//Remove it from octree as well
	AudioInstanceOctree.RemoveElement( ElementId );
#endif
}

void UAudioGeometryInstanceManager::EnsureTaskComplete()
{
	if(AudioGeometryUpdateTask && !AudioGeometryUpdateTask->IsComplete())
	{
		QUICK_SCOPE_CYCLE_COUNTER( STAT_AudioGeometryUpdateTask_Wait );
		FTaskGraphInterface::Get().WaitUntilTaskCompletes( AudioGeometryUpdateTask );
	}
}