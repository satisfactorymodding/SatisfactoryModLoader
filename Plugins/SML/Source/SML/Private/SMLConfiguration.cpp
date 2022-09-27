#include "SMLConfiguration.h"
#include "Dom/JsonObject.h"

FSMLConfiguration::FSMLConfiguration() :
    bDevelopmentMode(false),
    bConsoleWindow(false),
    bEnableCheatConsoleCommands(false) {
}

void FSMLConfiguration::ReadFromJson(const TSharedPtr<FJsonObject>& Json, FSMLConfiguration& OutConfiguration, bool* OutIsMissingSections) {
    bool bIsMissingSectionsInternal = false;
    
    if (Json->HasTypedField<EJson::Boolean>(TEXT("developmentMode"))) {
        OutConfiguration.bDevelopmentMode = Json->GetBoolField(TEXT("developmentMode"));
    } else {
        bIsMissingSectionsInternal = true;
    }
    
    if (Json->HasTypedField<EJson::Boolean>(TEXT("consoleWindow"))) {
        OutConfiguration.bConsoleWindow = Json->GetBoolField(TEXT("consoleWindow"));
    } else {
        bIsMissingSectionsInternal = true;
    }
    
    if (Json->HasTypedField<EJson::Boolean>(TEXT("enableCheatConsoleCommands"))) {
        OutConfiguration.bEnableCheatConsoleCommands = Json->GetBoolField(TEXT("enableCheatConsoleCommands"));
    } else {
        bIsMissingSectionsInternal = true;
    }
    
    if (Json->HasTypedField<EJson::Array>(TEXT("disabledChatCommands"))) {
        const TArray<TSharedPtr<FJsonValue>>& DisabledChatCommands = Json->GetArrayField(TEXT("disabledChatCommands"));
        for (const TSharedPtr<FJsonValue>& Value : DisabledChatCommands) {
            if (Value->Type == EJson::String)
                OutConfiguration.DisabledChatCommands.Add(Value->AsString());
        }
    } else {
        bIsMissingSectionsInternal = true;
    }

    if (Json->HasTypedField<EJson::Array>(TEXT("acceptedCrashReportingEndpoints"))) {
        const TArray<TSharedPtr<FJsonValue>>& AcceptedCrashReportingEndpoints = Json->GetArrayField(TEXT("acceptedCrashReportingEndpoints"));
        for (const TSharedPtr<FJsonValue>& Value : AcceptedCrashReportingEndpoints) {
            if (Value->Type == EJson::String)
                OutConfiguration.AcceptedCrashReportingEndpoints.Add(Value->AsString());
        }
    } else {
        bIsMissingSectionsInternal = true;
    }

    if (Json->HasTypedField<EJson::Array>(TEXT("rejectedCrashReportingEndpoints"))) {
        const TArray<TSharedPtr<FJsonValue>>& RejectedCrashReportingEndpoints = Json->GetArrayField(TEXT("rejectedCrashReportingEndpoints"));
        for (const TSharedPtr<FJsonValue>& Value : RejectedCrashReportingEndpoints) {
            if (Value->Type == EJson::String)
                OutConfiguration.RejectedCrashReportingEndpoints.Add(Value->AsString());
        }
    } else {
        bIsMissingSectionsInternal = true;
    }

    if (Json->HasTypedField<EJson::Boolean>(TEXT("disableModdingCrashReporter"))) {
        OutConfiguration.bDisableModdingCrashReporter = Json->GetBoolField(TEXT("disableModdingCrashReporter"));
    } else {
        bIsMissingSectionsInternal = true;
    }

    if (OutIsMissingSections) {
        *OutIsMissingSections = bIsMissingSectionsInternal;
    }
}

void FSMLConfiguration::WriteToJson(const TSharedPtr<FJsonObject>& OutJson, const FSMLConfiguration& Configuration) {
    OutJson->SetBoolField(TEXT("developmentMode"), Configuration.bDevelopmentMode);
    OutJson->SetBoolField(TEXT("consoleWindow"), Configuration.bConsoleWindow);
    OutJson->SetBoolField(TEXT("enableCheatConsoleCommands"), Configuration.bEnableCheatConsoleCommands);

    TArray<TSharedPtr<FJsonValue>> DisabledChatCommands;
    for (const FString& Value : Configuration.DisabledChatCommands) {
        DisabledChatCommands.Add(MakeShareable(new FJsonValueString(Value)));
    }
    OutJson->SetArrayField(TEXT("disabledChatCommands"), DisabledChatCommands);

    TArray<TSharedPtr<FJsonValue>> AcceptedCrashReportingEndpoints;
    for (const FString& Value : Configuration.AcceptedCrashReportingEndpoints) {
        AcceptedCrashReportingEndpoints.Add(MakeShared<FJsonValueString>(Value));
    }
    OutJson->SetArrayField(TEXT("acceptedCrashReportingEndpoints"), AcceptedCrashReportingEndpoints);

    TArray<TSharedPtr<FJsonValue>> RejectedCrashReportingEndpoints;
    for (const FString& Value : Configuration.RejectedCrashReportingEndpoints) {
        RejectedCrashReportingEndpoints.Add(MakeShared<FJsonValueString>(Value));
    }
    OutJson->SetArrayField(TEXT("rejectedCrashReportingEndpoints"), RejectedCrashReportingEndpoints);

    OutJson->SetBoolField(TEXT("disableModdingCrashReporter"), Configuration.bDisableModdingCrashReporter);
}
