// Copyright Yamahasxviper. All Rights Reserved.

#include "BanWebSocketPusher.h"
#include "BanSystemConfig.h"
#include "SMLWebSocketClient.h"

#include "Async/Async.h"
#include "Dom/JsonObject.h"
#include "Serialization/JsonWriter.h"
#include "Serialization/JsonSerializer.h"

DEFINE_LOG_CATEGORY(LogBanWebSocketPusher);

TWeakObjectPtr<UBanWebSocketPusher> UBanWebSocketPusher::ActiveInstance;

// ─────────────────────────────────────────────────────────────────────────────
//  USubsystem lifecycle
// ─────────────────────────────────────────────────────────────────────────────

void UBanWebSocketPusher::Initialize(FSubsystemCollectionBase& Collection)
{
    Super::Initialize(Collection);

    const UBanSystemConfig* Cfg = UBanSystemConfig::Get();
    if (!Cfg || !Cfg->bPushEventsToWebSocket || Cfg->WebSocketPushUrl.IsEmpty())
    {
        UE_LOG(LogBanWebSocketPusher, Log,
            TEXT("BanWebSocketPusher: WebSocket push disabled (bPushEventsToWebSocket=false or WebSocketPushUrl empty)."));
        return;
    }

    Client = NewObject<USMLWebSocketClient>(this);
    if (!Client)
    {
        UE_LOG(LogBanWebSocketPusher, Error, TEXT("BanWebSocketPusher: failed to create USMLWebSocketClient."));
        return;
    }
    Client->bAutoReconnect = true;
    Client->ReconnectInitialDelaySeconds = 5.0f;
    Client->MaxReconnectDelaySeconds     = 60.0f;
    Client->Connect(Cfg->WebSocketPushUrl, TArray<FString>(), TMap<FString, FString>());

    ActiveInstance = this;

    UE_LOG(LogBanWebSocketPusher, Log,
        TEXT("BanWebSocketPusher: connecting to '%s'."), *Cfg->WebSocketPushUrl);
}

void UBanWebSocketPusher::Deinitialize()
{
    if (Client)
    {
        Client->Close();
        Client = nullptr;
    }

    if (ActiveInstance == this)
        ActiveInstance.Reset();

    Super::Deinitialize();
}

// ─────────────────────────────────────────────────────────────────────────────
//  Static push helper
// ─────────────────────────────────────────────────────────────────────────────

void UBanWebSocketPusher::PushEvent(const FString& EventType,
                                     const TSharedPtr<FJsonObject>& Fields)
{
    if (!IsInGameThread())
    {
        const FString EventTypeCopy = EventType;
        const TSharedPtr<FJsonObject> FieldsCopy = Fields;
        AsyncTask(ENamedThreads::GameThread, [EventTypeCopy, FieldsCopy]()
        {
            UBanWebSocketPusher::PushEvent(EventTypeCopy, FieldsCopy);
        });
        return;
    }

    UBanWebSocketPusher* Self = ActiveInstance.Get();
    if (!Self || !Self->Client)
        return;

    // Build the envelope.
    TSharedPtr<FJsonObject> Envelope = MakeShared<FJsonObject>();
    Envelope->SetStringField(TEXT("event"),     EventType);
    Envelope->SetStringField(TEXT("timestamp"), FDateTime::UtcNow().ToIso8601());

    // Merge caller-supplied fields into the envelope, skipping reserved keys
    // ("event" and "timestamp") that are already set above.
    if (Fields.IsValid())
    {
        for (const auto& Pair : Fields->Values)
        {
            if (Pair.Key == TEXT("event") || Pair.Key == TEXT("timestamp"))
                continue;
            Envelope->SetField(Pair.Key, Pair.Value);
        }
    }

    FString JsonStr;
    TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&JsonStr);
    if (!FJsonSerializer::Serialize(Envelope.ToSharedRef(), Writer))
    {
        UE_LOG(LogBanWebSocketPusher, Warning,
            TEXT("BanWebSocketPusher: failed to serialize event '%s'"), *EventType);
        return;
    }

    Self->Client->SendJson(JsonStr);
}

void UBanWebSocketPusher::PushMuteEvent(const FString& EventType,
                                         const FString& Uid,
                                         const FString& PlayerName,
                                         const FString& MutedBy,
                                         const FString& Reason,
                                         bool           bIsTimed,
                                         const FString& ExpiresAt)
{
    TSharedPtr<FJsonObject> Fields = MakeShared<FJsonObject>();
    Fields->SetStringField(TEXT("uid"), Uid);

    if (EventType == TEXT("mute"))
    {
        Fields->SetStringField(TEXT("playerName"), PlayerName);
        Fields->SetStringField(TEXT("mutedBy"),    MutedBy);
        Fields->SetStringField(TEXT("reason"),     Reason);
        Fields->SetBoolField  (TEXT("isTimed"),    bIsTimed);
        if (bIsTimed && !ExpiresAt.IsEmpty())
            Fields->SetStringField(TEXT("expiresAt"), ExpiresAt);
        else
            Fields->SetField(TEXT("expiresAt"), MakeShared<FJsonValueNull>());
    }
    else
    {
        // For unmute (and any future event types), include the metadata so
        // subscribers receive actionable context rather than a uid-only envelope.
        if (!PlayerName.IsEmpty())
            Fields->SetStringField(TEXT("playerName"), PlayerName);
        if (!MutedBy.IsEmpty())
            Fields->SetStringField(TEXT("mutedBy"), MutedBy);
        if (!Reason.IsEmpty())
            Fields->SetStringField(TEXT("reason"), Reason);
    }

    PushEvent(EventType, Fields);
}
