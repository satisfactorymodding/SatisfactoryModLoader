// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Framework/Application/NavigationConfig.h" // MODDING EDIT

/**
 * This class is created to override how widget navigation with keys is handled. 
 */
class FACTORYGAME_API FFGNavigationConfig : public FNavigationConfig
{
public:
	FFGNavigationConfig();

	virtual EUINavigationAction GetNavigationActionFromKey(const FKeyEvent& InKeyEvent) const override;

	/* Set if we should enable navigation with tab and arrow keys. Stops UE4 to hog tab and arrow key input bindings in widgets*/
	static void EnableTabAndNavKeys( bool enable );
};
