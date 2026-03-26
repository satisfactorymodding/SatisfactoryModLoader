// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"
#include "FGActorRepresentationInterface.h"
#include "Components/ActorComponent.h"
#include "FGActorRepresentationComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FACTORYGAME_API UFGActorRepresentationComponent : public UActorComponent, public IFGActorRepresentationInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UFGActorRepresentationComponent();

		/** Adds the actor to the actor representation manager */
	UFUNCTION( BlueprintCallable, Category = "Representation" )
	virtual bool AddAsRepresentation() override;

	/** Updates the actor in the actor representation manager */
	UFUNCTION( BlueprintCallable, Category = "Representation" )
	virtual bool UpdateRepresentation() override;

	/** Should be called when an actor is destroyed. Then we should remove this representation. */
	UFUNCTION( BlueprintCallable, Category = "Representation" )
	virtual bool RemoveAsRepresentation() override;

	/** Tells us if the actor is static or not. */
	UFUNCTION( BlueprintCallable, Category = "Representation" )
	virtual bool IsActorStatic() override;

	/** Called on the server to get the location of this actor so it can be replicated to clients. */
	UFUNCTION( BlueprintCallable, Category = "Representation" )
	virtual FVector GetRealActorLocation() override;

	/** Called on the server to get the rotation of this actor so it can be replicated to clients. */
	UFUNCTION( BlueprintCallable, Category = "Representation" )
	virtual FRotator GetRealActorRotation() override;

	/** Fetches the texture to use for this actors representation */
	UFUNCTION( BlueprintCallable, Category = "Representation" )
	virtual class UTexture2D* GetActorRepresentationTexture() override;

	/** Fetches the material to use for this actors representation */
	UFUNCTION( BlueprintCallable, Category = "Representation" )
	virtual UMaterialInterface* GetActorRepresentationCompassMaterial() override;
	
	/** Fetches the text to use for this actors representation */
	UFUNCTION( BlueprintCallable, Category = "Representation" )
	virtual FText GetActorRepresentationText() override;

	/** Set the text to use for this actors representation */
	UFUNCTION( BlueprintCallable, Category = "Representation" )
	virtual void SetActorRepresentationText( const FText& newText ) override;

	/** Fetches the color to use for this actors representation */
	UFUNCTION( BlueprintCallable, Category = "Representation" )
	virtual FLinearColor GetActorRepresentationColor() override;

	/** Set the color to use for this actors representation */
	UFUNCTION( BlueprintCallable, Category = "Representation" )
	virtual void SetActorRepresentationColor( FLinearColor newColor ) override;

	/** Fetches the representation type to use for this actor */
	UFUNCTION( BlueprintCallable, Category = "Representation" )
	virtual ERepresentationType GetActorRepresentationType() override;

	/** Should this actor ever be shown in the compass */
	UFUNCTION( BlueprintCallable, Category = "Representation" )
	virtual bool GetActorShouldShowInCompass() override;

	/** Should this actor ever be shown on the map*/
	UFUNCTION( BlueprintCallable, Category = "Representation" )
	virtual bool GetActorShouldShowOnMap() override;

	UFUNCTION( BlueprintCallable, Category = "Representation" )
	virtual EFogOfWarRevealType GetActorFogOfWarRevealType() override;

	UFUNCTION( BlueprintCallable, Category = "Representation" )
	virtual float GetActorFogOfWarRevealRadius() override;

	UFUNCTION( BlueprintCallable, Category = "Representation" )
	virtual ECompassViewDistance GetActorCompassViewDistance() override;

	UFUNCTION( BlueprintCallable, Category = "Representation" )
	virtual void SetActorCompassViewDistance( ECompassViewDistance compassViewDistance ) override;
//<FL>[KonradA]
	UFUNCTION( BlueprintCallable, Category = "Representation" )
	virtual FPlayerInfoHandle GetLastEditedBy() const override;
	UFUNCTION( BlueprintCallable, Category = "Representation" )
	virtual void SetActorLastEditedByHandle( const FPlayerInfoHandle& playerInfoHandle ) override;
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	virtual void EndPlay( const EEndPlayReason::Type EndPlayReason ) override;

protected:
	UPROPERTY( EditDefaultsOnly, Category = "Representation" )
	TObjectPtr<class UTexture2D> mActorRepresentationTexture;

	UPROPERTY( EditDefaultsOnly, Category = "Representation" )
	TObjectPtr<UMaterialInterface> mActorRepresentationCompassMaterial;
	
	UPROPERTY( EditDefaultsOnly, Category = "Representation" )
	FText mActorRepresentationText;

	UPROPERTY( EditDefaultsOnly, Category = "Representation" )
	FLinearColor mActorRepresentationColor = FLinearColor::White;

	UPROPERTY( EditDefaultsOnly, Category = "Representation" )
	ERepresentationType mActorRepresentationType = ERepresentationType::RT_Default;

	UPROPERTY( EditDefaultsOnly, Category = "Representation" )
	bool mShouldShowInCompass = false;

	UPROPERTY( EditDefaultsOnly, Category = "Representation" )
	bool mShouldShowOnMap = true;

	UPROPERTY( EditDefaultsOnly, Category = "Representation" )
	EFogOfWarRevealType mFogOfWarRevealType = EFogOfWarRevealType::FOWRT_None;

	UPROPERTY( EditDefaultsOnly, Category = "Representation" )
	float mFogOfWarRevealRadius = 0.0f;

	UPROPERTY( EditDefaultsOnly, Category = "Representation" )
	ECompassViewDistance mCompassViewDistance = ECompassViewDistance::CVD_Off;
};