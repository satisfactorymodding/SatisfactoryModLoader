// This file has been automatically generated by the Unreal Header Implementation tool

#include "Server/FGServerAPIManagerInternals.h"

FFGRequestIORegistrar::FFGRequestIORegistrar(FRegistrationFunctionType InRegistrar){ }
void FFGRequestManagerRegistry::AddPendingRegistration(const FFGRequestIORegistrar::FRegistrationFunctionType& InDefinition){ }
void FFGRequestManagerRegistry::ProcessPendingRegistrations(){ }
bool FFGRequestManagerRegistry::FindHandlerDefinitionForFunction(const UFunction* Function, FFGRequestHandlerFunctionDefinition& OutFunctionDefinition){ return bool(); }
bool FFGRequestManagerRegistry::FindEmitterDefinitionForFunction(const UFunction* Function, FFGRequestEmitterFunctionDefinition& OutFunctionDefinition){ return bool(); }
FFGRequestManagerRegistry* FFGRequestManagerRegistry::Get(){ return nullptr; }
