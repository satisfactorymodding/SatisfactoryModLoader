// Copyright 2016-2019 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "UObject/Class.h"

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "FGMapObjectWidget.generated.h"

/**
 * 
 */
UCLASS()
class FACTORYGAME_API UFGMapObjectWidget : public UUserWidget
{
	GENERATED_BODY()

public: 
	UFUNCTION( BlueprintCallable, BlueprintImplementableEvent, Category = "Map" )
	void OnActorRepresentationUpdated();

protected:
	virtual void NativeConstruct() override;
	virtual void NativeTick( const FGeometry& MyGeometry, float InDeltaTime ) override;

	UFUNCTION( BlueprintImplementableEvent, Category = "Map" )
	void OnObjectFiltered( bool visible );

	UFUNCTION( BlueprintImplementableEvent, Category = "Map" )
	void OnObjectMoved( FVector2D normalizedLocation );

private:
	void initMapObject();

	UFUNCTION()
	void OnActorRepresentationFiltered( ERepresentationType representationType, bool visible );

protected:
	
	UPROPERTY( BlueprintReadOnly, Category = "Map", Meta = ( ExposeOnSpawn = "true" ) )
	class UFGActorRepresentation* mActorRepresentation;

	UPROPERTY( BlueprintReadOnly, Category = "Map", Meta = ( ExposeOnSpawn = "true" ) )
	class UFGMapWidget* mMapWidget;

	// If this map object is visible by it's representation type on the map
	UPROPERTY( BlueprintReadOnly, Category = "Map" )
	bool mFilteredVisibility;

private:
	bool mIsActorStatic;
	UPROPERTY()
	class AFGMinimapCaptureActor* mMinimapCaptureActor;



public:
	FORCEINLINE ~UFGMapObjectWidget() = default;
};
