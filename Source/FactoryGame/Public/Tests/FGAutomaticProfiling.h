// Copyright Coffee Stain Studios. All Rights Reserved.
// @Ben de Hullu
#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"

#if WITH_PERF_AUTOMATION_TESTS

/* Latent action for running the capture spline */

DEFINE_LATENT_AUTOMATION_COMMAND_FOUR_PARAMETER( FCaptureFGPerformanceFromSpline, FString, SplineName, float, Duration, bool, CaptureThreads, bool, CaptureRenderingStats );
DEFINE_LATENT_AUTOMATION_COMMAND_TWO_PARAMETER( FFGStartProfileActor,AActor*, SplineActor, float, Duration );

#endif