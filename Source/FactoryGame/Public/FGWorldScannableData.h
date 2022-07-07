// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"
#include "FGWorldScannableData.generated.h"


USTRUCT()
struct FWorldScannableData
{
	GENERATED_BODY()

	FWorldScannableData(){}
	FWorldScannableData( AActor* actor );

	/* FObjectReferenceDisc isn't a UStruct and thereby can't be a UProperty so let's save it as a string to avoid custom serializing. */
	UPROPERTY( VisibleAnywhere )
	FString ObjectReferenceDiscAsString;

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

private:
#if WITH_EDITOR
	UFUNCTION( BlueprintCallable, Category = "World Grid", meta = ( CallInEditor = "true" ) )
	void GenerateWorldScannableData();
#endif

};
