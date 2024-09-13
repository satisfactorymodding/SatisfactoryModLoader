// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class FactoryClientTarget : FactoryGameTarget
{
    public FactoryClientTarget(TargetInfo Target) : base(Target)
    {
	    Type = TargetType.Client;
    }
}
