// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GameFramework/Actor.h"
#include "FGWorldScannableData.generated.h"


USTRUCT()
struct FWorldScannableData
{
	GENERATED_BODY()

	FWorldScannableData(){}
	FWorldScannableData( AActor* actor );

	UPROPERTY( VisibleAnywhere )
	FGuid ActorGuid;

	UPROPERTY( VisibleAnywhere )
	TSubclassOf< class AActor > ActorClass;

	UPROPERTY( VisibleAnywhere )
	FVector ActorLocation;
	
};

UCLASS( BlueprintType, Blueprintable )
class FACTORYGAME_API UFGWorldScannableData : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY( VisibleAnywhere )
	TArray<FWorldScannableData> mItemPickups;

#if WITH_EDITOR
	void GenerateWorldScannableData( UWorld* world );
#endif
};

UCLASS()
class FACTORYGAME_API AFGWorldScannableDataGenerator : public AActor
{
	GENERATED_BODY()
	
public:	
	AFGWorldScannableDataGenerator();

	virtual void BeginPlay() override;

private:
#if WITH_EDITOR
	UFUNCTION( BlueprintCallable, Category = "World Grid", meta = ( CallInEditor = "true" ) )
	void GenerateWorldScannableData();
#endif

	UPROPERTY( VisibleAnywhere )
	TArray<FWorldScannableData> mItemPickups;
};
