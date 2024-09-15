// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class FactoryGameEGSTarget : FactoryGameTarget
{
    public FactoryGameEGSTarget(TargetInfo Target) : base(Target)
    {
	    // CustomConfig = "EGS"; // MODDING EDIT: Cannot deploy targets with conflicting CustomConfig values 
	    GlobalDefinitions.Add("STOREFRONT_ID=epic");
	    
	    // Enable launcher checks for the game targets built for EGS
	    bUseLauncherChecks = true;
    }
}
