// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FGBuildable.h"
#include "Resources/FGPoleDescriptor.h"
#include "FGBuildablePoleBase.generated.h"

UCLASS( EditInlineNew )
class FACTORYGAME_API UPoleLightweightData : public UObject
{
	GENERATED_BODY()
	
public:
	UPROPERTY( EditDefaultsOnly )
	TArray< struct FPoleHeightMesh > mPoleVariations; 
};

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
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	virtual bool ShouldBeConsideredForBase_Implementation() override;

	virtual bool ShouldShowCenterGuidelinesForHologram( const AFGHologram* hologram ) const override;

	virtual float GetStackHeight() const
	{
		return mStackHeight;
	}

	/** Can this pole stack. */
	UPROPERTY( EditDefaultsOnly, Category = "Pole" )
	bool mCanStack = false;

	/** Height between two stacked poles excluding the poles height. */
	UPROPERTY( EditDefaultsOnly, Category = "Pole" )
	float mStackHeight = 200;

	struct FPoleHeightMesh FindBestHeightMesh( float inHeight ) const;

	virtual void PostLoad() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

#if WITH_EDITORONLY_DATA
	UPROPERTY( EditDefaultsOnly, Instanced, Category = "Buildable")
	UPoleLightweightData* mPoleLightweightData;
#endif

public:
	FORCEINLINE const UPoleLightweightData* GetPoleSparseDataObject() const { return mPoleLightweightDataCDO; }
	
private:
	UPROPERTY( VisibleDefaultsOnly )
	UPoleLightweightData* mPoleLightweightDataCDO;

#if WITH_EDITOR
private:
	virtual void PostEditChangeProperty( FPropertyChangedEvent& PropertyChangedEvent ) override;
#endif
};
