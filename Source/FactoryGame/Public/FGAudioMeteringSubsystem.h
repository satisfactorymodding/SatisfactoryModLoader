// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "AkGameplayTypes.h"
#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "UObject/NoExportTypes.h"
#include "FGAudioMeteringSubsystem.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FBusMeteringCallback, const struct FAkBusMeteringInfo&, MeteringInfo );
DECLARE_MULTICAST_DELEGATE_OneParam( FNativeBusMeteringCallback, const FAkBusMeteringInfo& MeteringInfo );


UCLASS(BlueprintType)
class UFGAudioBusMonitor : public UObject, public IAkBusMeteringInterface
{
	GENERATED_BODY()
	friend class UFGAudioMeteringSubsystem;
public:
	UPROPERTY(BlueprintAssignable, Category=AudioBusMetering)
	FBusMeteringCallback OnBusMeteringInfoUpdate;
	
	FNativeBusMeteringCallback OnNativeBusMeteringInfoUpdate;

	UFUNCTION(BlueprintCallable)
	void SetMeteringFlags(UPARAM(meta = (Bitmask, BitmaskEnum = "/Script/AkAudio.EAkMeteringFlags") ) EAkMeteringFlags MeteringFlags);
	
	virtual void BusMeteringInfoUpdate( const FAkBusMeteringInfo& meteringInfo ) override;

protected:
	void Register();
	
	UPROPERTY(BlueprintReadOnly)
	FString BusName;
	
	UPROPERTY(BlueprintReadOnly)
	EAkMeteringFlags MeteringFlags = EAkMeteringFlags::EnableBusMeter_All;
};

/**
 * 
 */
UCLASS(BlueprintType)
class FACTORYGAME_API UFGAudioMeteringSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	UFUNCTION( BlueprintCallable, Category=AudioBusMetering )
	UFGAudioBusMonitor* GetAudioBusMonitor(const FString& BusName);
	
private:
	UPROPERTY()
	TMap<FString, UFGAudioBusMonitor*> mRegisteredMonitors;
};
