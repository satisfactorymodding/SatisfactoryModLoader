#pragma once
#include "UObject/Class.h"


#pragma once

#include "FGBuildable.h"
#include "FGBuildablePoleBase.generated.h"


/**
 * A pole based used for making stacking supported between types.
//@TODO:[DavalliusA:Fri/14-02-2020]   I would like to move over more stuff from poles and pipe supports here, as they share so many things, but they have named them
a bitt differently for no real reason, and it's a bit scary to do that without proper testing and time to adjust. 
So we'll not  do that now. But one day we should probably unify a good base here.
 */
UCLASS( Abstract )
class FACTORYGAME_API AFGBuildablePoleBase : public AFGBuildable
{
	GENERATED_BODY()
public:


	/** Can this pole stack. */
	UPROPERTY( EditDefaultsOnly, Category = "Pole" )
	bool mCanStack = false;

	/** Height between two stacked poles excluding the poles height. */
	UPROPERTY( EditDefaultsOnly, Category = "Pole" )
	float mStackHeight = 200;

	virtual float GetStackHeight()
	{
		return mStackHeight;
	}

public:
	FORCEINLINE ~AFGBuildablePoleBase() = default;
};
