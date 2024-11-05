// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "FGBuildable.h"
#include "FGBuildablePassthroughBase.h"
#include "FGBuildablePassthrough.generated.h"

/**
 * 
 */
UCLASS()
class FACTORYGAME_API AFGBuildablePassthrough : public AFGBuildablePassthroughBase
{
	GENERATED_BODY()
public:
	AFGBuildablePassthrough();

	// Begin Actor Interface
	virtual void GetLifetimeReplicatedProps( TArray<FLifetimeProperty>& OutLifetimeProps ) const override;
	// End Actor Interface

	// Begin IFGDismantleInterface
	virtual void StartIsLookedAtForDismantle_Implementation( class AFGCharacterPlayer* byCharacter ) override;
	virtual void StopIsLookedAtForDismantle_Implementation( class AFGCharacterPlayer* byCharacter ) override;
	virtual void GetChildDismantleActors_Implementation( TArray< AActor* >& out_ChildDismantleActors ) const override;
	// End IFGDismantleInterface
	
	// Get the connection component class
	FORCEINLINE TSubclassOf<class UFGConnectionComponent> GetConnectionClass() const { return mConnectionComponentClass; }

	// Outputs the normalized direction that a lift can snapped to this connection on. This will return a zero vector if both directions are valid
	// Returns false if no directions are valid
	bool GetValidAttachDirection( FVector& out_validDir ) const;

	void SetTopSnappedConnection( class UFGConnectionComponent* connection );
	void SetBottomSnappedConnection( class UFGConnectionComponent* connection );
	
	template<class ConnectionType>
	FORCEINLINE ConnectionType* GetBottomSnappedConnection() { return Cast< ConnectionType >( mBottomSnappedConnection ); }

	template<class ConnectionType>
	FORCEINLINE ConnectionType* GetTopSnappedConnection() { return Cast< ConnectionType >( mTopSnappedConnection ); }
	
	virtual void GetIgnoredBuildablesForClearance(TArray<AFGBuildable*>& out_ignoredBuildables) override;

	/** Called when an attached buildable is dismantled to let us know that it no longer needs to be considered */
	void OnAttachedBuildableDismantled( class AFGBuildable* dismantledBuildable );
protected:
	UPROPERTY( SaveGame, Replicated )
	class UFGConnectionComponent* mBottomSnappedConnection;

	UPROPERTY( SaveGame, Replicated )
	class UFGConnectionComponent* mTopSnappedConnection;
	
	UPROPERTY( EditDefaultsOnly )
	TSubclassOf< class UFGConnectionComponent > mConnectionComponentClass;
};
