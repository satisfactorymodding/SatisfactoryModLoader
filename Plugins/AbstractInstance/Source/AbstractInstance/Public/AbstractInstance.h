// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

static float AIM_BigOffset = 200000; 

class FAbstractInstanceModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};

#define AI_PIE WITH_EDITOR
#if WITH_EDITOR
	#define EditorCheck(expr)		check(expr)
#else
	#define EditorCheck(expr)		{ CA_ASSUME(expr); }
#endif