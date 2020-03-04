// Copyright 2016-2019 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "UObject/Class.h"

#include "CoreMinimal.h"
#include "Components/TextRenderComponent.h"
#include "FGBoundedTextRenderComponent.generated.h"

/**
 * Clips Rendered Text defined by a bounding box. 
 * @todo: Only top alignment is supported for vertical clipping. Implement appropriate alignment clipping.
 */
UCLASS( meta = ( BlueprintSpawnableComponent ) )
class FACTORYGAME_API UFGBoundedTextRenderComponent : public UTextRenderComponent
{
	GENERATED_BODY()
	
public:	
	
	//~ Begin UPrimitiveComponent Interface.
	virtual FPrimitiveSceneProxy* CreateSceneProxy() override;
	//~ End UPrimitiveComponent Interface.
	
	/** Assigns the box to use as bounds for this text */
	UFUNCTION(BlueprintCallable, Category="BoundedTextRenderComponent")
	void AssignBoundingBox( UBoxComponent* boxComponent );

	UPROPERTY( )
	UBoxComponent* mBoundingBox;

	

public:
	FORCEINLINE ~UFGBoundedTextRenderComponent() = default;
};
