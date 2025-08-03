// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

RELIABLEMESSAGING_API DECLARE_LOG_CATEGORY_EXTERN(LogReliableMessaging, Log, All);

class FBulkDataReplicationModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};
