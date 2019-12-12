// Copyright 2016-2018 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "Array.h"
#include "SubclassOf.h"
#include "UObject/Class.h"

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CanvasPanel.h"
#include "FGCompassWidget.generated.h"

/**
 * 
 */
UCLASS()
class FACTORYGAME_API UFGCompassWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFGCompassWidget( const FObjectInitializer& ObjectInitializer );
	virtual void NativeConstruct();
	virtual void NativeTick( const FGeometry& MyGeometry, float InDeltaTime );
	virtual void Destruct();

	/** 
	* Binds a ActorRepresentationManager with the widget, adding representations in the compass as they're updated in the manager
	* If nullptr is passed into the function, all events are unbound. This should be done at the destruction of this widget.
	*
	* When binding the ActorRepresentationManager, all compass objects will reflect it in this function. i.e. it will instantly
	* populate it with the current existing actor representations. If nullptr is passed it will also reflect this by removing
	* all currently showing actor representations.
	*/
	UFUNCTION( BlueprintCallable, Category = "Compass" )
	void BindActorRepresentationManager( class AFGActorRepresentationManager* representationManager );
	
	/** Creates and adds the given FGActorRepresentation represented in the compass */
	UFUNCTION( BlueprintCallable, Category = "Compass" )
	class UFGCompassObjectWidget* AddCompassObjectForRepresentation( TSubclassOf<class UFGCompassObjectWidget> compassObjectTemplate, class UFGActorRepresentation* actorRepresentation );

	/** Removes the CompassObject that is affiliated with the given FGActorRepresentation ptr */
	UFUNCTION( BlueprintCallable, Category = "Compass" )
	void RemoveCompassObjectForRepresentation( class UFGActorRepresentation* actorRepresentation );

protected:
	UFUNCTION( BlueprintCallable, Category = "Compass" )
	void AddAllCompassRepresentations( class AFGActorRepresentationManager* representationManager );

	UFUNCTION( BlueprintCallable, Category = "Compass" )
	void RemoveAllCompassRepresentations();

	/** Creates a widget in the compass from an actor representation and adds it to the compass panel */
	UFUNCTION(BlueprintCallable, Category = "Compass")
	class UFGCompassObjectWidget* CreateCompassObject( TSubclassOf<class UFGCompassObjectWidget> compassObjectTemplate, class UFGActorRepresentation* actorRepresentation );

	/** Creates a CompassObject widget, but without the actor representation data. The texture is optional and may be nullptr */
	UFUNCTION( BlueprintCallable, Category = "Compass" )
	class UFGCompassObjectWidget* CreatePrimitiveCompassObject( TSubclassOf<class UFGCompassObjectWidget> compassObjectTemplate, class UTexture2D* texture);

	/** Creates compass objects for all cardinal directions (North, East, South, West) */
	UFUNCTION( BlueprintCallable, Category = "Compass" )
	void AddAllCardinalDirections( TSubclassOf<UFGCompassObjectWidget> compassObjectTemplate, UTexture2D* northTex, UTexture2D* eastTex, UTexture2D* southTex, UTexture2D* westTex,
			UTexture2D* northWestTex, UTexture2D* southEastTex, UTexture2D* southWestText, UTexture2D* northEastTex );

	UFUNCTION( BlueprintImplementableEvent, Category = "Compass" )
	TSubclassOf<UFGCompassObjectWidget> GetCompassObjectWidgetClass( class UFGActorRepresentation* actorRepresentation );

	UFUNCTION( BlueprintNativeEvent, Category = "Compass" )
	FVector2D GetCompassLineOffset();

	/** Adds a CompassObject to this widget's Compass Panel */
	void AddToCompassPanel( class UFGCompassObjectWidget* compassObject );

	/** Removes a CompassObject from this widget's Compass panel, compassObject can be nullptr */
	void RemoveFromCompassPanel( class UFGCompassObjectWidget* compassObject );

	UFUNCTION()
	void OnActorRepresentationAdded( class UFGActorRepresentation* actorRepresentation );

	UFUNCTION()
	void OnActorRepresentationRemoved( class UFGActorRepresentation* actorRepresentation );

	UFUNCTION()
	void OnActorRepresentationUpdated( class UFGActorRepresentation* actorRepresentation );

	UFUNCTION()
	void OnActorRepresentationFiltered( ERepresentationType type, bool visible );

	FORCEINLINE float GetCompassPanelHalfWidth() { return mCompassPanel ? mCompassPanel->GetDesiredSize().X / 2.f : 0.f; };

private:
	bool IsPawnLocalPlayerControlled( APawn* pawn );
	void CalculateCenteredResourceObjects();
	void CalculateCenteredObject();

protected:
	UPROPERTY( BlueprintReadWrite, Category = "Compass", Meta=(BindWidget) )
	class UCanvasPanel* mCompassPanel;

	UPROPERTY( BlueprintReadWrite, Category = "Compass", Meta = ( BindWidget ) )
	class UCanvasPanel* mContentPanel;

	UPROPERTY( BlueprintReadWrite, Category = "Compass", Meta = ( BindWidget ) )
	class UImage* mCompassLine;

	UPROPERTY( Transient )
	TArray<UFGCompassObjectWidget*> mCompassObjects;

	UPROPERTY( Transient )
	TArray<UFGCompassObjectWidget*> mCenterableCompassObjects;

	UPROPERTY( Transient )
	TArray<UFGCompassObjectWidget*> mCenterableResourceCompassObjects;

	UPROPERTY( Transient )
	class AFGActorRepresentationManager* mActorRepresentationManager;
	
	UPROPERTY( Transient )
	TArray<UFGCompassObjectWidget*> mCurrentCenteredResourceObjects;

	UPROPERTY( Transient )
	class UFGCompassObjectWidget* mCurrentCenteredObject;

	UPROPERTY( EditDefaultsOnly, Category = "Compass" )
	float mThresholdForCenteredObjects;

	UPROPERTY( EditDefaultsOnly, Category = "Compass" )
	float mThresholdForCenteredResourceObjects;
};
