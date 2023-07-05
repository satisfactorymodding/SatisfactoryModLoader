#pragma once

#include "CoreMinimal.h"

#include "NAT.generated.h"

UENUM(BlueprintType)
enum class ECachedNATType : uint8
{
	CNT_Open		UMETA(DisplayName="Open", ToolTip="All peers can directly-connect to you"),
	CNT_Moderate	UMETA(DisplayName="Moderate", ToolTip="You can directly-connect to other Moderate and Open peers"),
	CNT_Strict		UMETA(DisplayName="Strict", ToolTip="You can only directly-connect to Open peers"),
	CNT_TBD			UMETA(DisplayName="TBD", ToolTip="NAT type has is not yet determined")
};

UENUM()
enum class EEosAccountConnectionResult
{
	Success
};

class EOS_ContinuanceTokenClass
{

};

typedef EOS_ContinuanceTokenClass* EOS_ContinuanceToken;