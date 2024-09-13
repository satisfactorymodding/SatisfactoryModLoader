// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class OnlineIntegration : ModuleRules
{
	public OnlineIntegration(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
		CppStandard = CppStandardVersion.Cpp20;
		// <FL> [WuttkeP] Add PLATFORM_PS5 and PLATFORM_XSX defines.
		bAllowConfidentialPlatformDefines = true;
		// </FL>

		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				// ... add other public dependencies that you statically link with here ...
				"OnlineServicesInterface", 
				"Engine", 
				"UMG", 
				"ModelViewViewModel",
				"OnlineServicesInterface",
				"FieldNotification",
				"GameplayEvents",
				"SlateCore"
			}
		);

		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"ControlFlows",
				"CoreUObject",
				"Engine",
				"Slate",
				"DeveloperSettings",
				// ... add private dependencies that you statically link with here ...	
				"OnlineServicesCommonEngineUtils", 
				"OnlineSubsystemUtils",
				"GameplayTags", 
				"ApplicationCore", 
				"CoreOnline", 
				"InputCore", 
				"OnlineServicesCommon"
			});
	}
}
