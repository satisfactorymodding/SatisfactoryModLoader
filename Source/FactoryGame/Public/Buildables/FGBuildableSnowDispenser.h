// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "FGSignificanceInterface.h"
#include "Buildables/FGBuildable.h"
#include "FGBuildableSnowDispenser.generated.h"

/**
 * [FreiholtzK:Tue/1-12-2020] Added this native class to implement significanceInterfarce
 * BP only implemented interface can be cast to nativly. https://answers.unrealengine.com/questions/315990/view.html
 * This is a ugly fix significance issues with snow dispenser
 * Turns out this issue is fixed on dev-steam @todoupdate4 We can kill this class if we want to
 */
UCLASS()
class FACTORYGAME_API AFGBuildableSnowDispenser : public AFGBuildable, public IFGSignificanceInterface
{
	GENERATED_BODY()
};
