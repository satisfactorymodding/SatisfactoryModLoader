// Copyright 2018 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "UObject/Class.h"

#include "Kismet/BlueprintFunctionLibrary.h"
#include "FGMapFunctionLibrary.generated.h"


UCLASS()
class UFGMapFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:

	/** Get the bounds of the world */
	UFUNCTION( BlueprintPure, Category = "Map" )
	static void GetWorldBounds( class UObject* worldContext, FVector2D& min, FVector2D& max );

	/** Get the minimap capture actor */
	UFUNCTION( BlueprintPure, Category = "Map" )
	static class AFGMinimapCaptureActor* GetMinimapCaptureActor( class UObject* worldContext );
	
	UFUNCTION( BlueprintPure, Category = "Map" )
	static FVector2D GetMapPosition( const AFGMinimapCaptureActor* minimapCaptureActor, FVector worldLocation, float mapResolution );

	UFUNCTION( BlueprintPure, Category = "Map" )
	static FVector2D GetNormalizedPosition( const AFGMinimapCaptureActor* minimapCaptureActor, FVector worldLocation );

	UFUNCTION( BlueprintPure, Category = "Map" )
	static float GetMapDistance ( const AFGMinimapCaptureActor* minimapCaptureActor, float worldDistance, float mapResolution );

};