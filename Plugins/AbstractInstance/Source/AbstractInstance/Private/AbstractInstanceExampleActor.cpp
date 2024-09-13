// Copyright Coffee Stain Studios. All Rights Reserved.


#include "AbstractInstanceExampleActor.h"
#include "AbstractInstanceManager.h"
#include "Engine/World.h"

// Sets default values
AAbstractInstanceExampleActor::AAbstractInstanceExampleActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AAbstractInstanceExampleActor::BeginPlay()
{
	Super::BeginPlay();

	if( InstanceData && InstanceData->HasValidInstanceData())
	{
		AAbstractInstanceManager* Manager = AAbstractInstanceManager::GetInstanceManager( GetWorld() );
		const FTransform ActorTransform = GetActorTransform();
		EditorCheck( ActorTransform.IsValid() )
		
		for( const auto& AbstractInstance : InstanceData->GetInstanceData() )
		{
			FInstanceHandle* Handle = new FInstanceHandle();
			Manager->SetInstanced(this, ActorTransform, AbstractInstance, Handle);
			InstanceHandles.Add( Handle );
		}
	}
}

void AAbstractInstanceExampleActor::Tick( float DeltaSeconds )
{
	Super::Tick( DeltaSeconds );
	for(int32 i = 0; i < InstanceHandles.Num(); i++)
	{
		if( !InstanceHandles[i]->IsValid() )
		{
			UE_LOG(LogTemp,Warning,TEXT("Handle is invalid!"));
		}
	}
}

void AAbstractInstanceExampleActor::EndPlay( const EEndPlayReason::Type EndPlayReason )
{
	Super::EndPlay( EndPlayReason );
	
	if( EndPlayReason == EEndPlayReason::Destroyed )
	{
		AAbstractInstanceManager* Manager = AAbstractInstanceManager::GetInstanceManager( GetWorld() );
		for( int32 i = 0; i < InstanceHandles.Num(); i++ )
		{
			Manager->RemoveInstance( InstanceHandles[ i ] );
		}
	}
}
