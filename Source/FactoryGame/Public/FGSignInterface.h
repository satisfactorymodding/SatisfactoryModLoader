// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"
#include "FGSaveInterface.h"
#include "UObject/Interface.h"
#include "Buildables/FGBuildable.h"
#include "FGSignTypes.h"
#include "FGSignInterface.generated.h"


// Sign Interface
UINTERFACE( Blueprintable )
class UFGSignInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * Interface for Sign Buildables to be able to communicate with UI
 */
class FACTORYGAME_API IFGSignInterface
{
	GENERATED_BODY()

public:
	UFUNCTION( BlueprintCallable, BlueprintNativeEvent, Category = "SignData" )
	AFGBuildable* GetBuildable();

	/** Get the Sign Type data for the implementing class. This holds information about prefabs available */
	UFUNCTION( BlueprintCallable, BlueprintNativeEvent, Category = "SignData" )
	TSubclassOf< UFGSignTypeDescriptor > GetSignTypeDescriptor();

	/** Get the Widget Dimensions (width / height) of the sign */
	UFUNCTION( BlueprintCallable, BlueprintNativeEvent, Category = "SignData" )
	FVector2D GetSignDimensions();

	
	/** Get the world scale dimensions (width / height) of the sign
	 * @note from world space Y maps to X and Z maps to Y in the return value
	 */
	UFUNCTION( BlueprintCallable, BlueprintNativeEvent, Category = "SignData" )
	FVector2D GetWorldDimensions();


	/** Get the dimensions of the grid size ( the size of 1 grid square )
	*	Is used for creating "pixel" layouts on each layer
	*/
	UFUNCTION( BlueprintCallable, BlueprintNativeEvent, Category = "SignData" )
	FVector2D GetGridSquareDimensions();

};
