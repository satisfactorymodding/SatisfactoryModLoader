// Copyright 2016-2019 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "UObject/Class.h"

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "FGLocalSettings.generated.h"

/**
 * 
 */
UCLASS( config = Game, meta = ( DisplayName = "Satisfactory Local Settings" ) )
class FACTORYGAME_API UFGLocalSettings : public UDeveloperSettings
{
	GENERATED_BODY()
public:
	static const UFGLocalSettings* Get() { return GetDefault<UFGLocalSettings>(); };
public:
	UPROPERTY( EditAnywhere, config, Category = Focus, meta = (
		ToolTip = "Should widgets grab focus back on focus lost in PIE. Default is off to avoid intrusive behaviour when trying to work. This is a local change only" ) )
	bool mLocalGreedyFocusInPIE;

public:
	FORCEINLINE ~UFGLocalSettings() = default;
};
