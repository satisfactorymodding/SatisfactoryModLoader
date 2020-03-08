#pragma once
#include "UObject/Interface.h"
#include "Text.h"
#include "TextProperty.h"
#include "FGActorRepresentationInterface.generated.h"

/**
* This interface makes sure this actor gets a representation that is to be shown in compass and
* in the minimap and similar things.
*/
UINTERFACE( Blueprintable )
class FACTORYGAME_API UFGActorRepresentationInterface : public UInterface
{
	
 GENERATED_BODY()
	UFGActorRepresentationInterface(const class FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {} 

public:
	FORCEINLINE ~UFGActorRepresentationInterface() = default;
};

/**
*
*/
class FACTORYGAME_API IFGActorRepresentationInterface
{
	GENERATED_IINTERFACE_BODY()

	/** Adds the actor to the actor representation manager */
	UFUNCTION( BlueprintCallable, BlueprintNativeEvent, Category = "Representation" )
	bool AddAsRepresentation();

	/** Updates the actor in the actor representation manager */
	UFUNCTION( BlueprintCallable, BlueprintNativeEvent, Category = "Representation" )
	bool UpdateRepresentation();

	/** Should be called when an actor is destroyed. Then we should remove this representation. */
	UFUNCTION( BlueprintCallable, BlueprintNativeEvent, Category = "Representation" )
	bool RemoveAsRepresentation();

	/** Tells us if the actor is static or not. */
	UFUNCTION( BlueprintNativeEvent, Category = "Representation" )
	bool IsActorStatic();

	/** Called on the server to get the location of this actor so it can be replicated to clients. */
	UFUNCTION( BlueprintNativeEvent, Category = "Representation" )
	FVector GetRealActorLocation();

	/** Called on the server to get the rotation of this actor so it can be replicated to clients. */
	UFUNCTION( BlueprintNativeEvent, Category = "Representation" )
	FRotator GetRealActorRotation();

	/** Fetches the texture to use for this actors representation */
	UFUNCTION( BlueprintNativeEvent, Category = "Representation" )
	class UTexture2D* GetActorRepresentationTexture();

	/** Fetches the text to use for this actors representation */
	UFUNCTION( BlueprintCallable, BlueprintNativeEvent, Category = "Representation" )
	FText GetActorRepresentationText();

	/** Set the text to use for this actors representation */
	UFUNCTION( BlueprintCallable, BlueprintNativeEvent, Category = "Representation" )
	FText SetActorRepresentationText( const FText& newText );

	/** Fetches the color to use for this actors representation */
	UFUNCTION( BlueprintNativeEvent, Category = "Representation" )
	FLinearColor GetActorRepresentationColor();

	/** Set the color to use for this actors representation */
	UFUNCTION( BlueprintCallable, BlueprintNativeEvent, Category = "Representation" )
	void SetActorRepresentationColor( FLinearColor newColor );

	/** Fetches the representation type to use for this actor */
	UFUNCTION( BlueprintNativeEvent, Category = "Representation" )
	ERepresentationType GetActorRepresentationType();

	/** Should this actor ever be shown in the compass */
	UFUNCTION( BlueprintNativeEvent, Category = "Representation" )
	bool GetActorShouldShowInCompass();

	/** Should this actor ever be shown on the map*/
	UFUNCTION( BlueprintNativeEvent, Category = "Representation" )
	bool GetActorShouldShowOnMap();

	UFUNCTION( BlueprintNativeEvent, Category = "Representation" )
	EFogOfWarRevealType GetActorFogOfWarRevealType();

	UFUNCTION( BlueprintNativeEvent, Category = "Representation" )
	float GetActorFogOfWarRevealRadius();

	UFUNCTION( BlueprintCallable, BlueprintNativeEvent, Category = "Representation" )
	ECompassViewDistance GetActorCompassViewDistance();

	UFUNCTION( BlueprintCallable, BlueprintNativeEvent, Category = "Representation" )
	ECompassViewDistance SetActorCompassViewDistance( ECompassViewDistance compassViewDistance );

public:
	FORCEINLINE IFGActorRepresentationInterface() = default;
};