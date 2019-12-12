// Fill out your copyright notice in the Description page of Project Settings.

#include "SBL.h"

void UDebugLogger::logInfo(FString str, bool ignoreDebugMode) {}
void UDebugLogger::logWarning(FString str, bool ignoreDebugMode) {}
void UDebugLogger::logError(FString str, bool ignoreDebugMode) {}
void UDebugLogger::logDebug(FString str, bool ignoreDebugMode) {}

bool UModHandler::isDebugMode() { return false; }
void UModHandler::broadcastEvent(FString event) {}
bool UModHandler::doesPakExist(FString pak) { return false; }
bool UModHandler::isDllLoaded(FString dll) { return false; }
