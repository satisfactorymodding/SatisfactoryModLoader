// Copyright 2016-2019 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "Array.h"
#include "UObject/Class.h"

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "FGMapWidget.generated.h"

/**
 * 
 */
UCLASS()
class FACTORYGAME_API UFGMapWidget : public UUserWidget
{
	GENERATED_BODY()
public:

	UFUNCTION( BlueprintImplementableEvent, Category = "Map" )
	void OnMapCentered( FVector2D normalizedWorldLocation );

protected:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

	
	UFUNCTION( BlueprintImplementableEvent, Category = "Map" )
	void OnObjectAddedToMap( class UFGActorRepresentation* actorRepresentation );

	UFUNCTION( BlueprintImplementableEvent, Category = "Map" )
	void OnObjectUpdatedOnMap( class UFGActorRepresentation* actorRepresentation );

	UFUNCTION( BlueprintImplementableEvent, Category = "Map" )
	void OnObjectRemovedFromMap( class UFGActorRepresentation* actorRepresentation );

	UFUNCTION( BlueprintPure, Category = "Map" )
	FORCEINLINE UTexture2D* GetFogOfWarTexture(){ return mFogOfWarTexture; }

private:
	void UpdateFogOfWarTexture();
	void SetupRepresentationManager();
	void BindActorRepresentationManager( class AFGActorRepresentationManager* representationManager );
	void RemoveBindings();
	
	UFUNCTION()
	void OnActorRepresentationAdded( class UFGActorRepresentation* actorRepresentation );
	UFUNCTION()
	void OnActorRepresentationUpdated( class UFGActorRepresentation* actorRepresentation );
	UFUNCTION()
	void OnActorRepresentationRemoved( class UFGActorRepresentation* actorRepresentation );

private:
	UPROPERTY()
	UTexture2D* mFogOfWarTexture;
	UPROPERTY()
	TArray<UFGActorRepresentation*> mMapActors;
	UPROPERTY( Transient )
	class AFGActorRepresentationManager* mActorRepresentationManager;
	


public:
	FORCEINLINE ~UFGMapWidget() = default;
};
