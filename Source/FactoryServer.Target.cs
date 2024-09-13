// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class FactoryServerTarget : FactorySharedTarget
{
    public FactoryServerTarget(TargetInfo Target) : base(Target)
    {
	    Type = TargetType.Server;

	    // Build additional console application so that the server can be launched from command line on windows
	    bBuildAdditionalConsoleApp = true;
	    // Use custom config override to provide some platform overrides for the dedicated server
	    CustomConfig = "FactoryServer";

	    ExtraModuleNames.AddRange(new[] {
		    "FactoryDedicatedServer"
	    });
    }
}
