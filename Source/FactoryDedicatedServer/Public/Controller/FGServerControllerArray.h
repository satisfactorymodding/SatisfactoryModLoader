// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "Controller/FGServerAuthenticationController.h"
#include "FGServerControllerArray.generated.h"

class UFGServerDebugController;
class UFGServerAPIManager;
class UFGServerManagementController;
class UFGServerSaveGameController;
class UFGServerStateController;
class UFGServerAuthenticationController;

UCLASS()
class FACTORYDEDICATEDSERVER_API UFGServerControllerArray : public UObject
{
	GENERATED_BODY()
public:
	UFGServerControllerArray();

	void RegisterControllers( UFGServerAPIManager* ServerAPIManager ) const;
protected:
	UPROPERTY()
	UFGServerAuthenticationController* mServerAuthenticationController;

	UPROPERTY()
	UFGServerStateController* mServerStateController;

	UPROPERTY()
	UFGServerSaveGameController* mServerSaveGameController;

	UPROPERTY()
	UFGServerManagementController* mServerManagementController;

	UPROPERTY()
	UFGServerDebugController* mServerDebugController;
};