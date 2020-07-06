#pragma once
#include "UnrealString.h"
#include "UObject/Class.h"

#include "Blueprint/UserWidget.h"
#include "FGWidgetMultiplayer.generated.h"

UENUM( BlueprintType )
enum class EMultiplayerButtonType : uint8
{
	MBT_Join					UMETA( DisplayName = "Join" ),
	MBT_SendInvite				UMETA( DisplayName = "SendInvite" ),
	MBT_JoinInvite				UMETA( DisplayName = "JoinInvite" ),
	MBT_ManagePlayers			UMETA( DisplayName = "ManagePlayers" )
};

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

	UPROPERTY( BlueprintReadWrite )
	EMultiplayerButtonType mMultiplayerButtonType;

public:
	FORCEINLINE ~UFGWidgetMultiplayer() = default;
};
