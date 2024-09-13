// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class FactoryDedicatedServer : ModuleRules
{
	public FactoryDedicatedServer( ReadOnlyTargetRules Target ) : base(Target)
	{
		CppStandard = CppStandardVersion.Cpp20;
		DefaultBuildSettings = BuildSettingsVersion.Latest;
		
		// For FSocketBSD include (for TLS pass-through on the Server API, and Multi-Bind sockets)
		PrivateIncludePaths.Add($"{EngineDirectory}/Source/Runtime/Sockets/Private");

		PublicDependencyModuleNames.AddRange( new string[] { 
			"Core", 
			"CoreUObject", 
			"Engine", 
			"FactoryGame",
			"Json",
			"PacketHandler",
			"CoreOnline",
			"OnlineSubsystemUtils",
			"OnlineIntegration"
		});

		PrivateDependencyModuleNames.AddRange(new string[]
		{
			"OpenSSL",
			"SSL",
			"HTTPServer",
			"Sockets",
			"zlib",
			"JsonUtilities",
			"NetCore"
		});

		if (Target.bCompileAgainstEditor)
		{
			PrivateDependencyModuleNames.Add("UnrealEd");
		}
	}
}
