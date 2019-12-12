// Copyright 2016-2018 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "Array.h"
#include "UnrealString.h"
#include "UObject/Class.h"

#include "CoreMinimal.h"
#include "FGVersionFunctionLibrary.h"
#include "GameFramework/Actor.h"
#include "Interfaces/IHttpRequest.h"
#include "FGNewsFeedActor.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FOnNewsReceived, FText, news );

USTRUCT()
struct FNewsFeedMap
{
	GENERATED_BODY()

	UPROPERTY()
	EGameVersion GameVersion;

	UPROPERTY()
	FString URL;
};

UCLASS( BlueprintType, Config=Game )
class FACTORYGAME_API AFGNewsFeedActor : public AActor
{
	GENERATED_BODY()
	
public:
	AFGNewsFeedActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/** Get the desired news feed url */
	static FString GetNewsFeedURL();

	void OnResponseReceived( FHttpRequestPtr request, FHttpResponsePtr response, bool wasSuccessful );
protected:
	/** Fired when we get the result back from the HTTP Get request */
	UPROPERTY( BlueprintAssignable )
	FOnNewsReceived mOnNewsReceived;

	/** Yeah yeah, this is only a prototype class it breaks code convention, fix it when we make a proper news feed */
	UPROPERTY( BlueprintReadOnly )
	FText mNewFeedText;

	/** Display this text if we fail to get the news feed text */
	UPROPERTY( BlueprintReadOnly, EditDefaultsOnly, Category = "News Feed" )
	FText mNewsFeedRequestFailedText;

	UPROPERTY( Config )
	TArray< FNewsFeedMap > mNewsFeedURLs;
	
};
