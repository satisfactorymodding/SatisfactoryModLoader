#pragma once

#include <HookLoader.h>
#include "../SatisfactorySDK/SDK.hpp"

DEFINE_METHOD(SDK::AFGPlayerControllerBase::ReceiveBeginPlay);

DEFINE_METHOD(SDK::UFGBuildGunStateBuild::Client_OnBuildableConstructed);