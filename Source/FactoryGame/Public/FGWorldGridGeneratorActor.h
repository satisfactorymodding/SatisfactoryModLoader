// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

#include "FGWorldGridSubsystem.h"
#include "GameFramework/Actor.h"
#include "FGWorldGridGeneratorActor.generated.h"

UCLASS()
class FACTORYGAME_API AFGWorldGridGeneratorActor : public AActor
{
	GENERATED_BODY()
	
public:	
	AFGWorldGridGeneratorActor();

	private:
#if WITH_EDITOR
	UFUNCTION( BlueprintCallable, Category = "World Grid", meta = ( CallInEditor = "true" ) )
    void ExportWorldGridData();
	void GenerateWorldGrid( TArray<FFGWorldGridCellData>& CellData, FVector2D& GridMin, FVector2D& GridMax ) const;
#endif

};
