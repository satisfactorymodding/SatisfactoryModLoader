// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"
#include "FGAimAssistClient.generated.h"


class UCurveFloat;
// <FL> [MartinC] Interface class for objects that implements aim assist (tipically weaapons)
UINTERFACE( MinimalAPI )
class UFGAimAssistClient : public UInterface
{
	GENERATED_BODY()
};

USTRUCT( BlueprintType )
struct FACTORYGAME_API FMagnetismInfo
{
	GENERATED_BODY()

public:
	// <FL> [MartinC] Strength of the aim assist magnetism effect
	UPROPERTY( BlueprintReadWrite )
	float Strength = 1.f;

	// <FL> [MartinC] Blends magnetism strength between the aim target's OuterRadius and InnerRadius
	UPROPERTY( BlueprintReadWrite )
	TObjectPtr< UCurveFloat > RadiusBlendCurve;

	// <FL> [MartinC] Modifier for magnetism strength when there's no player input
	UPROPERTY( BlueprintReadWrite )
	float ZeroInputStrengthFactor = 0.f;
};


class FACTORYGAME_API IFGAimAssistClient
{
	GENERATED_BODY()

public:
	// <FL> [MartinC] Retrieves the current crosshair position
	UFUNCTION( BlueprintNativeEvent, Category = "Aim Assist" )
	FVector2D GetCrosshairPosition() const;

	// <FL> [MartinC] Checks if the magnetism is currently active
	UFUNCTION( BlueprintNativeEvent, Category = "Aim Assist|Magnetism" )
	bool IsMagnetismActive() const;

	// <FL> [MarinC] Gets the magnetism settings for the aim assist
	UFUNCTION( BlueprintNativeEvent, Category = "Aim Assist|Magnetism" )
	FMagnetismInfo GetMagnetismInfo() const;

	// <FL> Calculates the outer and inner radius for magnetism based on distance to the target
	UFUNCTION( BlueprintNativeEvent, Category = "Aim Assist|Magnetism" )
	void GetMagnetismRadiiByDistance( float Distance, float& OuterRadius, float& InnerRadius ) const;

};