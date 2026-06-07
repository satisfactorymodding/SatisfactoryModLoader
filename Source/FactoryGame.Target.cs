// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class FactoryGameTarget : FactorySharedTarget
{
    public FactoryGameTarget(TargetInfo Target) : base(Target)
    {
	    //DefaultWarningLevel = WarningLevel.Error;
	    //bWarningsAsErrors = true;
	    //CppCompileWarningSettings.DeprecationWarningLevel = WarningLevel.Error;

	    Type = TargetType.Game;

	    // Compile automation tests for the test game builds
	    if (Configuration == UnrealTargetConfiguration.Test)
	    {
		    bForceCompilePerformanceAutomationTests = true;
	    }

	    // Additional client modules to compile for the game
	    ExtraModuleNames.AddRange( new[] {
		    "FactoryPreEarlyLoadingScreen",
		    "FactoryDedicatedClient"
	    });
    }
}
