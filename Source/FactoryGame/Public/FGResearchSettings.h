// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "Engine/DeveloperSettings.h"
#include "FGResearchSettings.generated.h"

UCLASS( config = Game, defaultconfig )
class FACTORYGAME_API UFGResearchSettings : public UDeveloperSettings
{
	GENERATED_BODY()
public:
	static const UFGResearchSettings* Get() { return GetDefault<UFGResearchSettings>(); };
public:
	/** Widget used to show that the user is setting up a server */
	UPROPERTY( EditAnywhere, config, Category = Research )
	int32 mNumSchematicsPerHardDrive = 2;

	/** Widget used to show the user when joining a session */
	UPROPERTY( EditAnywhere, config, Category = Research )
	int32 mNumRerollsPerHardDrive = 1;
	
};