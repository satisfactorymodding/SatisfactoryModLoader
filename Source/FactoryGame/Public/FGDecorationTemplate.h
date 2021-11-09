// Copyright Coffee Stain Studios. All Rights Reserved.
#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"
#include "Engine/SCS_Node.h"
#include "GameFramework/Actor.h"

#include "FGDecorationTemplate.generated.h"

class UBoxComponent;
UCLASS( Blueprintable )
class FACTORYGAME_API AFGDecorationTemplate : public AActor
{
	GENERATED_BODY()

	AFGDecorationTemplate();
	
public:

#if WITH_EDITORONLY_DATA
	/* Preview actor to make it easier to place component(s) */
	UPROPERTY(EditAnywhere, meta = ( AllowPrivateAccess = "true") )
	UChildActorComponent* mChildActorComponent;
#endif

	template< typename ComponentType >
	static ComponentType* SpawnComponentFromTemplate( AActor* TargetActor, ComponentType* sourceComponent, EComponentMobility::Type mobility );
	
	static TArray< class UFGPoolableProxyComponentBase* > GetPoolAbleComponentsFromSubclass( const UClass* InActorClass );

	static TArray< class USceneComponent* > GetSignificantComponentsFromSubclass( const UClass* InActorClass );

	template< typename ComponentType >
	static TArray< ComponentType* > GetComponentsFromSubclass( const UClass* InActorClass );
};

template< typename ComponentType >
TArray<ComponentType*> AFGDecorationTemplate::GetComponentsFromSubclass( const UClass* InActorClass )
{
	TArray< ComponentType* > outComponents;

	if ( IsValid( InActorClass ) )
	{
		if( const UBlueprintGeneratedClass* ActorBlueprintGeneratedClass = Cast< UBlueprintGeneratedClass >( InActorClass ) )
		{
			const TArray< USCS_Node* >& ActorBlueprintNodes = ActorBlueprintGeneratedClass->SimpleConstructionScript->GetAllNodes();

			for ( USCS_Node* Node : ActorBlueprintNodes )
			{
				if ( UClass::FindCommonBase( Node->ComponentClass, ComponentType::StaticClass() ) &&
                    !Node->IsEditorOnly() )
				{		
					if ( ComponentType* BlueprintComponent = Cast< ComponentType >( Node->ComponentTemplate ) )
					{
						outComponents.Add( BlueprintComponent );
					}
				}
			}
		}
	}

	return outComponents;
}

template< typename ComponentType >
ComponentType* AFGDecorationTemplate::SpawnComponentFromTemplate( AActor* TargetActor, ComponentType* sourceComponent, EComponentMobility::Type mobility )
{
	if( TargetActor && TargetActor->GetWorld() )
	{
		ComponentType* newComp = NewObject< ComponentType >( TargetActor, sourceComponent->GetClass(), NAME_None, RF_NoFlags, sourceComponent );
		newComp->SetupAttachment( TargetActor->GetRootComponent() );
		newComp->SetMobility( mobility );
		newComp->SetRelativeTransform( sourceComponent->GetRelativeTransform(), false );
		newComp->RegisterComponent();

		return newComp;
	}

	return nullptr;
}