#pragma once
#include "UnrealString.h"
#include "UObject/Class.h"

#include "Blueprint/UserWidget.h"
#include "FGWidgetMultiplayer.generated.h"

UCLASS()
class FACTORYGAME_API UFGWidgetMultiplayer : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite)
	bool mIsOnline;

	UPROPERTY(BlueprintReadWrite)
	bool mIsPlayingSatisfactory;

	UPROPERTY(BlueprintReadWrite)
	FString mTitle;

public:
	FORCEINLINE ~UFGWidgetMultiplayer() = default;
};
