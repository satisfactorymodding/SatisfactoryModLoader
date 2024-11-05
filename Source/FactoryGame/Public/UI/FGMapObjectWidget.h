// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

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

	UFUNCTION( BlueprintPure, Category = "Representation" )
	virtual bool CanBeHighlighted() const;

	UFUNCTION( BlueprintCallable, Category = "Representation" )
	virtual void SetHighlighted( bool highlighted );

	UFUNCTION( BlueprintPure, Category = "Representation" )
	virtual UPARAM(DisplayName = "HighlightColor") FLinearColor IsHighlighted( UPARAM(DisplayName = "IsHighlighted") bool& out_IsHighlighted, UPARAM(DisplayName = "HighlightedByLocalPlayer") bool& out_HighlightedByLocalPlayer ) const;

protected:
	virtual void NativeConstruct() override;
	virtual void NativeTick( const FGeometry& MyGeometry, float InDeltaTime ) override;

	/** Event called when a map object is added to the map when it's already opened. This means objects available when opening the map won't get this event
	 *  markerCreatedByOwningPlayer is only ever true for map markers and stamps 
	 */
	UFUNCTION( BlueprintImplementableEvent, Category = "Map" )
	void WhenAddedConstruct( bool markerCreatedByOwningPlayer );

	UFUNCTION( BlueprintImplementableEvent, Category = "Map" )
	void OnObjectFiltered( bool visible );

	UFUNCTION( BlueprintImplementableEvent, Category = "Map" )
	void OnObjectMoved( FVector2D normalizedLocation );

	UFUNCTION( BlueprintImplementableEvent, Category = "Map" )
	void OnHighlightedUpdated( bool highlighted, bool IsHighlightedByLocalPlayer, FLinearColor color );

private:
	// Initialize map object. Right now it just plays a waiting game until parent widget is setup properly 
	void InitMapObject();
	// Setup inital map postion for the object. Assumes all widgets are ready to do so.
	void InitMapObjectPostion();

	UFUNCTION()
	void OnActorRepresentationFiltered( ERepresentationType representationType, bool visible );

	UFUNCTION()
	void OnMarkerHighlightUpdated( class UFGActorRepresentation* actorRepresentation, bool highlighted, class AFGPlayerState* playerState  );

protected:
	
	UPROPERTY( BlueprintReadOnly, Category = "Map", Meta = ( ExposeOnSpawn = "true" ) )
	class UFGActorRepresentation* mActorRepresentation;

	UPROPERTY( BlueprintReadOnly, Category = "Map", Meta = ( ExposeOnSpawn = "true" ) )
	class UFGMapWidget* mMapWidget;

	/* True if this object was added after map was opened */ 
	UPROPERTY( BlueprintReadOnly, Category = "Map", Meta = ( ExposeOnSpawn = "true" )  )
	bool mAddedAfterMapOpened;

	// If this map object is visible by it's representation type on the map
	UPROPERTY( BlueprintReadOnly, Category = "Map" )
	bool mFilteredVisibility;

private:
	bool mIsActorStatic;
	UPROPERTY()
	class AFGMinimapCaptureActor* mMinimapCaptureActor;


};
