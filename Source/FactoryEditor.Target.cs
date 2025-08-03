// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class FactoryEditorTarget : TargetRules
{
	public FactoryEditorTarget( TargetInfo Target ) : base(Target)
	{
		Type = TargetType.Editor;
		
		IncludeOrderVersion = EngineIncludeOrderVersion.Latest;
		// [ZolotukhinN:11/03/2025] Re-enable ray tracing in editor to avoid modifying the shared editor build environment. It is still disabled in runtime.
		WindowsPlatform.bEnableRayTracing = true;

		ExtraModuleNames.AddRange(new string[] {
			"FactoryPreEarlyLoadingScreen",
            "FactoryGame",
            "FactoryEditor",
			// "FactoryUncookedOnly",
			"FactoryDedicatedServer",
			"FactoryDedicatedClient"
		});
	}
}
