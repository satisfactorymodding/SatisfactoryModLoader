// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "FGAimTargetComponent.generated.h"

// <FL> [MartinC] Component for aim assist targets
UCLASS( Blueprintable )
class FACTORYGAME_API UFGAimTargetComponent : public USceneComponent
{
	GENERATED_BODY()

public:	

	virtual void BeginPlay() override;

	virtual void EndPlay( EEndPlayReason::Type Reason ) override;


	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = "Magnetism" )
	bool bSupportsMagnetism;

	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = "Magnetism", meta = ( EditCondition = "bSupportsMagnetism" ) )
	float MagnetismSizeScale = 1.f;
		
};
