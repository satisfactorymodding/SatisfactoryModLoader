// Copyright Ben de Hullu & Coffee Stain Studios 2022. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

class FInstancedSplinesComponentModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};

// For future reference.
#if ENGINE_MAJOR_VERSION > 4
#endif