#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

/**

* OnlineIntegrationPostSplashScreen
*
* This module exists to ensure that Epic Online Services (EOS), specifically the EOS Overlay,
* is initialized early enough in the engine startup sequence to function correctly with DX12.
*
* In UE 5.4+, initializing EOS at the default OnlineServices or GameInstanceSubsystem timing can
* be too late, as D3D12 or DXGI activity (device, queues, swapchain) may already have occurred.
* When this happens, the EOS overlay fails during its first DX12 swapchain probe and permanently
* disables itself.
*
* By loading this module at PostSplashScreen, we ensure that EOSShared and OnlineServicesEOSGS
* are loaded and that GetServices(Epic) is called before any relevant D3D12 or DXGI initialization.
* This allows the overlay to correctly hook DXGI, observe swapchain creation, and bind to DX12.
*
* This module intentionally contains no runtime logic beyond early initialization.
* At present, no config-based or platform-based gating is applied. This is a deliberate tradeoff.
* EOS is currently used on all supported targets, and this approach was chosen as a conservative
* and robust fix made late in a release cycle. Ideally, this early initialization would be
* conditionally gated by configuration.
  */
class FOnlineIntegrationPostSplashScreenModule : public IModuleInterface
{
public:
    virtual void StartupModule() override;
    virtual void ShutdownModule() override;
};
