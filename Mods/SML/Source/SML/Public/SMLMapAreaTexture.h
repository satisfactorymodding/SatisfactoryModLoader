#pragma once

#include "CoreMinimal.h"
#include "FGMapAreaTexture.h"
#include "SMLMapAreaTexture.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogSMLMapAreaTexture, Log, All);

UCLASS(Blueprintable)
class SML_API USMLMapAreaTexture : public UFGMapAreaTexture
{
	GENERATED_BODY()
public:
	USMLMapAreaTexture();

	UFUNCTION(BlueprintCallable)
	void DoInitMapAreaTexture(AFGMinimapCaptureActor* inCaptureActor)
	{
		InitMapAreaTexture(inCaptureActor);
	}

	UFUNCTION(BlueprintCallable)
	FVector2D GetUpperLeftWorld() const
	{
		//UE_LOG(LogSMLMapAreaTexture, Log, TEXT("%s: GetUpperLeftWorld returns %s"), *GetPathName(), *mUpperLeftWorld.ToString());
		return mUpperLeftWorld;
	}

	UFUNCTION(BlueprintCallable)
	void SetUpperLeftWorld(FVector2D Vec)
	{
		//UE_LOG(LogSMLMapAreaTexture, Log, TEXT("%s: SetUpperLeftWorld %s = %s"), *GetPathName(), *mUpperLeftWorld.ToString(), *Vec.ToString());
		mUpperLeftWorld = Vec;
	}

	UFUNCTION(BlueprintCallable)
	float GetWorldToMapScale() const
	{
		return mWorldToMapScale;
	}

	UFUNCTION(BlueprintCallable)
	void SetWorldToMapScale(float Scale)
	{
		mWorldToMapScale = Scale;
	}

#if WITH_EDITOR
	/** When this is changed in the editor, propagate the changes to the preview window */
	virtual void PostEditChangeProperty(struct FPropertyChangedEvent& propertyChangedEvent) override;
#endif

private:
#if WITH_EDITOR
	bool ProcessAreaTexture();
#endif
	void SummarizeData();
};
