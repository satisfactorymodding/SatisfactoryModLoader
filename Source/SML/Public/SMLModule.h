#pragma once
#include "Modules/ModuleManager.h"

class SML_API FSMLModule : public FDefaultGameModuleImpl {
public:
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};