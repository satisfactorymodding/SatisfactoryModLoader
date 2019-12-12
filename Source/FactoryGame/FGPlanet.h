#pragma once
#include "UObject/Class.h"

#include "GameFramework/Actor.h"
#include "FGPlanet.generated.h"

UCLASS()
class AFGPlanet : public AActor
{
	GENERATED_BODY()
public:
	// Begin AActor interface
	virtual void PostActorCreated() override;
	virtual void PostLoad() override;
	virtual void BeginDestroy() override;
#if WITH_EDITOR
	virtual void PostEditChangeChainProperty( struct FPropertyChangedChainEvent& propertyChangedEvent ) override;
#endif

	/** Update the preview of the planet in the editor */	
	UFUNCTION( BlueprintImplementableEvent, BlueprintCallable, meta = ( CallInEditor = "true" ) )
	void UpdatePreview();
private:
#if WITH_EDITOR
	/** Setup so that we get calls to UpdatePreview whenever time of day is updated in the editor */
	void SetupPreviewDelegate();
#endif
#if WITH_EDITORONLY_DATA
	/** How the sunlight changes during the day */
	UPROPERTY( EditInstanceOnly, Category = "Preview", meta = ( UIMin = 0, UIMax = 24, ClampMin = 0, ClampMax = 24 ) )
	float mPreviewTime;

	// In editor, receive updates for whenever the time of day is updated
	FDelegateHandle mTimeOfDayUpdated;
#endif
};