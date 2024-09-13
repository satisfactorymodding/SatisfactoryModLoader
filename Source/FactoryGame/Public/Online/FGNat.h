// Copyright 2023 Coffee Stain Studios. All Rights Reserved.
#pragma once

#include "FactoryGame.h"
#include "OnlineIntegrationTypes.h"
#include "CommonUserNATType.h"
#include "FGNat.generated.h"

UENUM( BlueprintType )
enum class ECachedNATType : uint8
{
	CNT_Open		UMETA(DisplayName="Open", ToolTip="All peers can directly-connect to you"),
	CNT_Moderate	UMETA(DisplayName="Moderate", ToolTip="You can directly-connect to other Moderate and Open peers"),
	CNT_Strict		UMETA(DisplayName="Strict", ToolTip="You can only directly-connect to Open peers"),
	CNT_TBD			UMETA(DisplayName="TBD", ToolTip="NAT type has is not yet determined")
};

inline ECachedNATType MapNATType(ECommonUserNATType NATType)
{
	switch(NATType)
	{
		case ECommonUserNATType::Unknown:
			return ECachedNATType::CNT_TBD;
		case ECommonUserNATType::Open:
			return ECachedNATType::CNT_Open;
		case ECommonUserNATType::Moderate:
			return ECachedNATType::CNT_Moderate;
		case ECommonUserNATType::Strict:
			return ECachedNATType::CNT_Strict;
	}
	return ECachedNATType::CNT_TBD;
}
