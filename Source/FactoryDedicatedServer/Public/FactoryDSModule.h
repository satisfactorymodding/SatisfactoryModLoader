// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "Modules/ModuleManager.h"

FACTORYDEDICATEDSERVER_API DECLARE_LOG_CATEGORY_EXTERN( LogServer, Log, Log );

class FFactoryDSModule : public FDefaultGameModuleImpl
{
public:
	/**
	 * Called when the module is loaded into memory
	 */
	virtual void StartupModule() override;

	/**
	 * Called when the module is unloaded from memory
	 */
	virtual void ShutdownModule() override;

	/** We want this module to be hot reloaded */
	virtual bool IsGameModule() const override { return true; }
};