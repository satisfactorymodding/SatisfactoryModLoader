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
		bUseUnity = false; // Disable unity because mixing OnlineSubsystem and OnlineServices is no good (but OnlineGameActivityInterface.h only exists on OnlineSubsystem)
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
				"SlateCore",
				"EOSShared" // <FL> [KonradA, BGR] required for advanced EOS logging
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
				"OnlineServicesCommon",
				"OnlineSubsystem"
			});
		
		// <FL> [ZimmermannA] Needed to display xbox system messages during joining
			if (/*Target.Platform == UnrealTargetPlatform.XSX*/ false)
			{
				PrivateDependencyModuleNames.AddRange(new string[] {
					"OnlineSubsystemGDK",
				});
			}
		// </FL> 
		//<FL>[KonradA]
		if (/*Target.Platform == UnrealTargetPlatform.PS5*/ false)
		{
			PrivateDependencyModuleNames.AddRange(new string[] {
					"OnlineSubsystemSony"
				});
		}
		//</FL>
		if (/*Target.Platform == UnrealTargetPlatform.PS5 || Target.Platform == UnrealTargetPlatform.XSX*/ false)
		{
			PrivateDependencyModuleNames.AddRange(new string[] {
				"OnlineServicesOSSAdapter"
			});
		}
	}
}
