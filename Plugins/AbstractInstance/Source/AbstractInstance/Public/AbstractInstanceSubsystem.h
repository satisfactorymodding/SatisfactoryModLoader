// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "AbstractInstanceSubsystem.generated.h"

class AAbstractInstanceManager;

UCLASS()
class ABSTRACTINSTANCE_API UAbstractInstanceSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()
public:
	// Begin UWorldSubsystem interface
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void OnWorldBeginPlay(UWorld& InWorld) override;
	virtual bool DoesSupportWorldType(const EWorldType::Type WorldType) const override;
	// End UWorldSubsystem interface

	/** Creates the abstract instance manager immediately if it has not been created yet */
	void CreateAbstractInstanceManager();

	FORCEINLINE AAbstractInstanceManager* GetAbstractInstanceManager() const { return WorldAbstractInstanceManager; }
protected:
	UPROPERTY()
	AAbstractInstanceManager* WorldAbstractInstanceManager{};
};
