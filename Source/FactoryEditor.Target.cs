// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class FactoryEditorTarget : TargetRules
{
	public FactoryEditorTarget( TargetInfo Target ) : base(Target)
	{
		Type = TargetType.Editor;
		
		IncludeOrderVersion = EngineIncludeOrderVersion.Latest;

		ExtraModuleNames.AddRange(new string[] {
			"FactoryPreEarlyLoadingScreen",
            "FactoryGame",
            "FactoryEditor",
			"FactoryUncookedOnly",
			"FactoryDedicatedServer",
			"FactoryDedicatedClient"
		});
	}
}
