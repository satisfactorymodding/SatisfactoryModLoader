#pragma once
#include "UnrealString.h"

#include "CoreMinimal.h"
#include "Misc/AutomationTest.h"

#if (WITH_DEV_AUTOMATION_TESTS || WITH_PERF_AUTOMATION_TESTS)

/**
 * Run FPS chart command using for the actual duration of the matinee and some FG specific commands
 */
DEFINE_LATENT_AUTOMATION_COMMAND_ONE_PARAMETER( FMatineeFGPerformanceCaptureCommand, FString, matineeName );

#endif
