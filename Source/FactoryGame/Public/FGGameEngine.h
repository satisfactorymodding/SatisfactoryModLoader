// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "Engine/GameEngine.h"
#include "FGEngineCommon.h"
#include "FGGameEngine.generated.h"


UCLASS()
class FACTORYGAME_API UFGGameEngine : public UGameEngine
{
	GENERATED_BODY()
public:
	// Begin UEngine interface
	virtual void Init( IEngineLoop* inEngineLoop ) override;
	virtual void Start() override;
	virtual void PreExit() override;
	virtual void Tick( float deltaSeconds, bool idleMode ) override;
	virtual bool LoadMap( FWorldContext& WorldContext, FURL URL, class UPendingNetGame* Pending, FString& Error ) override;
	// End UEngine interface

	virtual bool Exec( class UWorld* InWorld, const TCHAR* Cmd, FOutputDevice& Ar/* =*GLog */ ) override;
protected:
	/** Shared implementation for world creation */
	UPROPERTY()
	FFGEngineCommon mEngineCommonImp;
};
