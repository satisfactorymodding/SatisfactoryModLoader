// Copyright 2016-2019 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "Array.h"
#include "UObject/Class.h"

#include "CoreMinimal.h"
#include "FGPipeConnectionComponent.h"
#include "FGFluidIntegrantInterface.h"
#include "FGPipeConnectionFactory.generated.h"

/**
 * Pipe connection component for Pipe connections residing on factory buildings that produce or consume
 * These connections implement the fluid integrant interface and thus can belong to a pipe network.
 */
UCLASS( ClassGroup = ( Custom ), meta = ( BlueprintSpawnableComponent ) )
class FACTORYGAME_API UFGPipeConnectionFactory : public UFGPipeConnectionComponent, public IFGFluidIntegrantInterface
{
	GENERATED_BODY()
public:
	UFGPipeConnectionFactory();

	// Begin ActorComponent Interface
	virtual void BeginPlay() override;
	virtual void EndPlay( const EEndPlayReason::Type reason ) override;
	// End ActorComponent Interface

	// Begin FluidIntegrantInterface
	virtual FFluidBox* GetFluidBox() override;
	virtual TArray< UFGPipeConnectionComponent* > GetPipeConnections() override;
	// End FluidIntegrantInterface

	/** Called from PipeConnectionComponent ClearConnection before resetting the connection */
	virtual void OnDisconnectedFrom();

protected:
	/** Fluid box managed by this connection. This is special to PipeConnectionFactory as other connections do not have their own fluid box */
	FFluidBox mFluidBox;

private:
	/** If this connection is a producer type, should it apply the factory settings default pressure? */
	UPROPERTY( EditDefaultsOnly, Category = "Connection" )
	bool mApplyAdditionalPressure;

public:
	FORCEINLINE ~UFGPipeConnectionFactory() = default;
};
