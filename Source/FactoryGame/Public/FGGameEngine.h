#pragma once
#include "Engine/World.h"
#include "UnrealString.h"
#include "UObject/Class.h"

#include "Engine/GameEngine.h"
#include "FGEngineCommon.h"
#include "FGWorldCreationInterface.h"
#include "FGGameEngine.generated.h"



UCLASS()
class FACTORYGAME_API UFGGameEngine : public UGameEngine, public IFGWorldCreationInterface
{
	GENERATED_BODY()
public:
	// Begin UEngine interface
	virtual void Init( IEngineLoop* inEngineLoop ) override;
	virtual void Start() override;
	virtual void PreExit() override;
	virtual void Tick( float deltaSeconds, bool idleMode ) override;
	// End UEngine interface

	//~ Begin IFGWorldCreationInterface interface
	virtual class UWorld* CreateWorld( const FString& worldName ) override;
	virtual void DestroyWorld( class UWorld* world ) override;
	//~ End IFGWorldCreationInterface interface

	virtual bool Exec( class UWorld* InWorld, const TCHAR* Cmd, FOutputDevice& Ar/* =*GLog */ ) override;
protected:
	/** Shared implementation for world creation */
	UPROPERTY()
	FFGEngineCommon mEngineCommonImp;

public:
	FORCEINLINE ~UFGGameEngine() = default;
};
