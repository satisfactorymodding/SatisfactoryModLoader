// Copyright Ben de Hullu. All Rights Reserved.

#include "AbstractInstance.h"

#if AI_PIE
#include "AbstractInstanceManager.h"
#include "Editor.h"
#endif

#define LOCTEXT_NAMESPACE "FAbstractInstanceModule"

void FAbstractInstanceModule::StartupModule()
{
#if AI_PIE
	FEditorDelegates::BeginPIE.AddStatic(&AAbstractInstanceManager::BeginPIE);
	FEditorDelegates::PostPIEStarted.AddStatic(&AAbstractInstanceManager::PostPIEStarted);
	FWorldDelegates::OnWorldCleanup.AddStatic(&AAbstractInstanceManager::OnWorldCleanup);
#endif
}

void FAbstractInstanceModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FAbstractInstanceModule, AbstractInstance)