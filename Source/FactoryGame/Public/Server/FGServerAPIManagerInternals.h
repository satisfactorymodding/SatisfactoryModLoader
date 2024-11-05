// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectPtr.h"

struct FACTORYGAME_API FFGRequestHandlerFunctionDefinition
{
	TObjectPtr<UFunction> Function{};
	FString RequestHandlerName;
	FString PrivilegeLevel;
	TObjectPtr<UFunction> AsyncCompleteRequestFunction{};
	bool bEnableCompression{};
};

struct FACTORYGAME_API FFGRequestEmitterFunctionDefinition
{
	TObjectPtr<UFunction> SendRequestFunction{};
	TObjectPtr<UFunction> ReceiveResponseFunction{};
	FString RequestName;
	FString PrivilegeLevel;
	TArray<FName> PassThroughParameterNames;
};

class FACTORYGAME_API FFGRequestIORegistrar
{
public:
	using FRegistrationFunctionType = void(*)(TArray<FFGRequestHandlerFunctionDefinition>&, TArray<FFGRequestEmitterFunctionDefinition>&);

	FFGRequestIORegistrar( FRegistrationFunctionType InRegistrar );
};

class FACTORYGAME_API FFGRequestManagerRegistry
{
	TMap<UFunction*, FFGRequestHandlerFunctionDefinition> RegisteredHandlerFunctions;
	TMap<UFunction*, FFGRequestEmitterFunctionDefinition> RegisteredEmitterFunctions;

	TArray<FFGRequestIORegistrar::FRegistrationFunctionType> PendingRegistrations;
public:
	void AddPendingRegistration( const FFGRequestIORegistrar::FRegistrationFunctionType& InDefinition );

	void ProcessPendingRegistrations();

	bool FindHandlerDefinitionForFunction( const UFunction* Function, FFGRequestHandlerFunctionDefinition& OutFunctionDefinition );
	bool FindEmitterDefinitionForFunction( const UFunction* Function, FFGRequestEmitterFunctionDefinition& OutFunctionDefinition );

	static FFGRequestManagerRegistry* Get();
};
