// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "Components/SceneComponent.h"
#include "FGDotReceiverComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FOnDotReceiverCreated, class UFGDotReceiverComponent*, dotReceiver );

/** An active dot is a non-stacking dot which can come from multiple sources at once. Such as multiple gas clouds. */
USTRUCT( BlueprintType )
struct FACTORYGAME_API FActiveDOT
{
	GENERATED_BODY()

	FActiveDOT()
		: LastDamageTimestamp( -1.0f )
		, DamageCauserIndex( 0 )
		, ShouldRemove( false )
	{
	}

	/** What kind of DOT this is. */
	UPROPERTY( BlueprintReadOnly, Category = "DOT" )
	TSubclassOf< class UFGDamageOverTime > DotClass;

	/** Actors which are currently applying this dot to us. */
	UPROPERTY( BlueprintReadOnly, Category = "DOT" )
	TArray< AActor* > SourceActors;

	// Last time damage was taken by this DOT
	float LastDamageTimestamp;

	// Index used to cycle damage causer from the list of source actors when the dot deals damage
	int32 DamageCauserIndex;

	bool ShouldRemove;
};

/**
 * Component used for an actor to receive damage from DOT sources.
 */
UCLASS( hidecategories = ( Cooking, Collision, Rendering, Sockets ), ClassGroup = ( Custom ), meta = ( BlueprintSpawnableComponent, DisplayName = "DotReceiverComponent" ) )
class FACTORYGAME_API UFGDotReceiverComponent : public UActorComponent
{
	GENERATED_BODY()
public:
	UFGDotReceiverComponent();

	virtual void BeginPlay() override;
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

	/** Gets all active DOTs which are currently applied to this receiver. */
	UFUNCTION( BlueprintPure, Category = "Damage" )
	const TArray< FActiveDOT >& GetActiveDOTs() const { return mActiveDOTs; }

	/** Used to register an active dot on this character. The character will be damaged by this DOT until unregistered or the source actor is no longer valid. */
    UFUNCTION( BlueprintCallable, Category = "Damage" )
    void RegisterActiveDOT( TSubclassOf< class UFGDamageOverTime > DotClass, AActor* SourceActor );

    /** Used to unregister an active dot from this character. */
    UFUNCTION( BlueprintCallable, Category = "Damage" )
    void UnregisterActiveDOT( TSubclassOf< class UFGDamageOverTime > DotClass, AActor* SourceActor );

	/** Removes all active DOTs. */
	UFUNCTION( BlueprintCallable, Category = "Damage" )
	void ClearAllDOTs();

public:
	/** Called whenever a new DotReceiver is spawned. */
	static FOnDotReceiverCreated OnDOTReceiverCreated;
	
protected:	
	/** List of active damage over time effects affecting our character. */
	UPROPERTY( VisibleAnywhere, Category = "Damage" )
	TArray< FActiveDOT > mActiveDOTs;

private:
	void UpdateTickState();
};
