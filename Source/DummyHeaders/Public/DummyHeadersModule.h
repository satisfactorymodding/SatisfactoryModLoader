#pragma once
#include "Modules/ModuleManager.h"

class DUMMYHEADERS_API FDummyHeadersModule : public FDefaultGameModuleImpl {
public:
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};