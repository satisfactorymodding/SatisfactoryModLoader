#pragma once

#include "Modules/ModuleManager.h"

class FSMLModule : public FDefaultGameModuleImpl {
public:
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

	virtual bool IsGameModule() const override { return true; }
};