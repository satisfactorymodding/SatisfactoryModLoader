#pragma once

#include "AkMetering.generated.h"

USTRUCT(BlueprintType)
struct FAkBusMeteringInfo
{
	GENERATED_BODY()
};

UENUM()
enum class EAkMeteringFlags : uint8
{
	EnableBusMeter_All
};

UINTERFACE()
class UAkBusMeteringInterface : public UInterface
{
	GENERATED_BODY()
};

class IAkBusMeteringInterface
{
	GENERATED_BODY()
public:
	virtual void BusMeteringInfoUpdate(const FAkBusMeteringInfo& meteringInfo) = 0;
};