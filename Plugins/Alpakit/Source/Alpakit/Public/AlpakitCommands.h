// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"
#include "AlpakitStyle.h"

class FAlpakitCommands : public TCommands<FAlpakitCommands>
{
public:

	FAlpakitCommands()
		: TCommands<FAlpakitCommands>(TEXT("Alpakit"), NSLOCTEXT("Contexts", "Alpakit", "Alpakit Plugin"), NAME_None, FAlpakitStyle::GetStyleSetName())
	{
	}

	// TCommands<> interface
	virtual void RegisterCommands() override;

public:
	TSharedPtr< FUICommandInfo > OpenPluginWindow;
	TSharedPtr< FUICommandInfo > AlpakitOverwrite;
};