// Copyright Yamahasxviper. All Rights Reserved.
// Direct port of Tools/BanSystem/src/apiServer.ts

#include "BanRestApi.h"
#include "BanDatabase.h"
#include "BanEnforcer.h"
#include "BanSystemConfig.h"
#include "PlayerSessionRegistry.h"
#include "PlayerWarningRegistry.h"
#include "BanAuditLog.h"
#include "BanDiscordNotifier.h"
#include "BanAppealRegistry.h"
#include "BanWebSocketPusher.h"
#include "ScheduledBanRegistry.h"

#include "HttpServerModule.h"
#include "IHttpRouter.h"
#include "HttpPath.h"
#include "HttpServerResponse.h"
#include "HttpServerRequest.h"
#include "GenericPlatform/GenericPlatformHttp.h"

#include "Misc/Paths.h"
#include "Dom/JsonObject.h"
#include "Serialization/JsonReader.h"
#include "Serialization/JsonWriter.h"
#include "Serialization/JsonSerializer.h"
#include "UObject/UnrealType.h"

DEFINE_LOG_CATEGORY(LogBanRestApi);

// ─────────────────────────────────────────────────────────────────────────────
//  PIMPL struct — hides TArray<FHttpRouteHandle> from the public header so that
//  UHT / MSVC never needs to instantiate it from the Public include path.
// ─────────────────────────────────────────────────────────────────────────────
struct FBanRestApiRoutes
{
    TArray<FHttpRouteHandle> Handles;
};

// ─────────────────────────────────────────────────────────────────────────────
//  Internal JSON helpers
// ─────────────────────────────────────────────────────────────────────────────
namespace BanJson
{
    static TSharedPtr<FJsonObject> EntryToJson(const FBanEntry& E)
    {
        TSharedPtr<FJsonObject> Obj = MakeShared<FJsonObject>();
        Obj->SetStringField(TEXT("id"),          FString::Printf(TEXT("%lld"), E.Id));
        Obj->SetStringField(TEXT("uid"),         E.Uid);
        Obj->SetStringField(TEXT("playerUID"),   E.PlayerUID);
        Obj->SetStringField(TEXT("platform"),    E.Platform);
        Obj->SetStringField(TEXT("playerName"),  E.PlayerName);
        Obj->SetStringField(TEXT("reason"),      E.Reason);
        Obj->SetStringField(TEXT("bannedBy"),    E.BannedBy);
        Obj->SetStringField(TEXT("banDate"),     E.BanDate.ToIso8601());
        if (E.bIsPermanent)
            Obj->SetField(TEXT("expireDate"),    MakeShared<FJsonValueNull>());
        else
            Obj->SetStringField(TEXT("expireDate"), E.ExpireDate.ToIso8601());
        Obj->SetBoolField  (TEXT("isPermanent"), E.bIsPermanent);

        // Category (optional).
        if (!E.Category.IsEmpty())
            Obj->SetStringField(TEXT("category"), E.Category);

        // Evidence (optional).
        if (E.Evidence.Num() > 0)
        {
            TArray<TSharedPtr<FJsonValue>> EvidArr;
            for (const FString& Ev : E.Evidence)
                EvidArr.Add(MakeShared<FJsonValueString>(Ev));
            Obj->SetArrayField(TEXT("evidence"), EvidArr);
        }

        return Obj;
    }

    static FString ObjectToString(const TSharedPtr<FJsonObject>& Obj)
    {
        FString Out;
        TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&Out);
        if (!FJsonSerializer::Serialize(Obj.ToSharedRef(), Writer))
        {
            UE_LOG(LogBanRestApi, Error, TEXT("BanRestApi: failed to serialize JSON object"));
            return TEXT("{}");
        }
        return Out;
    }

    static FString ArrayToString(const TArray<FBanEntry>& Bans)
    {
        TArray<TSharedPtr<FJsonValue>> Arr;
        Arr.Reserve(Bans.Num());
        for (const FBanEntry& E : Bans)
            Arr.Add(MakeShared<FJsonValueObject>(EntryToJson(E)));

        TSharedPtr<FJsonObject> Root = MakeShared<FJsonObject>();
        Root->SetNumberField(TEXT("count"), Bans.Num());
        Root->SetArrayField (TEXT("bans"),  Arr);
        return ObjectToString(Root);
    }

    static TUniquePtr<FHttpServerResponse> Json(
        const FString& Body,
        EHttpServerResponseCodes Code = EHttpServerResponseCodes::Ok)
    {
        auto R = FHttpServerResponse::Create(Body, TEXT("application/json"));
        R->Code = Code;
        return R;
    }

    static TUniquePtr<FHttpServerResponse> Error(const FString& Msg,
        EHttpServerResponseCodes Code = EHttpServerResponseCodes::BadRequest)
    {
        TSharedPtr<FJsonObject> Obj = MakeShared<FJsonObject>();
        Obj->SetStringField(TEXT("error"), Msg);
        return Json(ObjectToString(Obj), Code);
    }

    static TUniquePtr<FHttpServerResponse> Ok(const FString& Msg)
    {
        TSharedPtr<FJsonObject> Obj = MakeShared<FJsonObject>();
        Obj->SetStringField(TEXT("message"), Msg);
        return Json(ObjectToString(Obj));
    }

    static FString BodyToString(const FHttpServerRequest& Req)
    {
        if (Req.Body.Num() == 0) return TEXT("{}");

        // Guard against excessively large request bodies (e.g. accidental or
        // malicious oversized POST payloads).  1 MB is far more than any valid
        // JSON ban payload would ever require.
        static constexpr int32 MaxBodyBytes = 1 * 1024 * 1024;
        if (Req.Body.Num() > MaxBodyBytes)
        {
            UE_LOG(LogBanRestApi, Warning,
                TEXT("BanRestApi: request body too large (%d bytes, limit %d) — rejecting"),
                Req.Body.Num(), MaxBodyBytes);
            return TEXT("{}");
        }

        TArray<uint8> Buf = Req.Body;
        Buf.Add(0);
        return UTF8_TO_TCHAR(reinterpret_cast<const char*>(Buf.GetData()));
    }

    /**
     * Constant-time string equality — prevents timing side-channel attacks on
     * the API key.  FString::Equals short-circuits on the first mismatching
     * byte, leaking information via response latency.  This function always
     * inspects every byte of the shorter string before returning.
     */
    static bool ConstantTimeEquals(const FString& A, const FString& B)
    {
        const FTCHARToUTF8 Au(*A), Bu(*B);
        // Use uint32 so that length differences ≥ 256 are not masked by uint8 truncation.
        uint32 Diff = static_cast<uint32>(Au.Length() != Bu.Length() ? 1 : 0);
        const int32 N = FMath::Max(Au.Length(), Bu.Length());
        for (int32 i = 0; i < N; ++i)
        {
            const uint8 ByteA = (i < Au.Length()) ? static_cast<uint8>(Au.Get()[i]) : 0;
            const uint8 ByteB = (i < Bu.Length()) ? static_cast<uint8>(Bu.Get()[i]) : 0;
            Diff |= ByteA ^ ByteB;
        }
        return Diff == 0;
    }

    /**
     * Returns true when the request passes the API key check.
     * If RestApiKey is empty, always returns true (auth disabled).
     * If RestApiKey is non-empty, the request must supply either:
     *   - Header X-Api-Key with the matching value (primary, used by API clients
     *     and the dashboard's in-page JS fetch calls), OR
     *   - Query parameter ?key= with the matching value (used when a browser
     *     navigates directly to /dashboard?key=xxx, before the JS can store the
     *     key in sessionStorage and strip it from the address bar).
     */
    static bool CheckApiKey(const FHttpServerRequest& Req)
    {
        const UBanSystemConfig* Cfg = UBanSystemConfig::Get();
        if (!Cfg || Cfg->RestApiKey.IsEmpty()) return true;

        // Header-based auth (primary, used by API clients and the dashboard JS).
        const TArray<FString>* KeyHeaderValues = Req.Headers.Find(TEXT("X-Api-Key"));
        if (KeyHeaderValues && !KeyHeaderValues->IsEmpty() &&
            ConstantTimeEquals((*KeyHeaderValues)[0], Cfg->RestApiKey))
            return true;

        // Query-param auth (for browser navigation to /dashboard?key=xxx).
        const FString* QueryKey = Req.QueryParams.Find(TEXT("key"));
        if (QueryKey && ConstantTimeEquals(*QueryKey, Cfg->RestApiKey))
            return true;

        return false;
    }

    /**
     * Returns a non-null 413 error response when the request body exceeds the
     * 1 MB limit, otherwise returns nullptr (caller should proceed normally).
     * Use at the top of every POST/PATCH/PUT handler that doesn't already have
     * its own size guard, to give the caller a proper HTTP 413 instead of
     * silently treating the oversized body as an empty JSON object.
     */
    static TUniquePtr<FHttpServerResponse> CheckBodySize(const FHttpServerRequest& Req)
    {
        static constexpr int32 MaxBodyBytes = 1 * 1024 * 1024;
        if (Req.Body.Num() > MaxBodyBytes)
        {
            return Error(
                FString::Printf(TEXT("Request body too large (%d bytes, limit %d)"),
                    Req.Body.Num(), MaxBodyBytes),
                EHttpServerResponseCodes::RequestTooLarge);
        }
        return nullptr;
    }

    static TSharedPtr<FJsonObject> WarningToJson(const FWarningEntry& W)
    {
        TSharedPtr<FJsonObject> Obj = MakeShared<FJsonObject>();
        Obj->SetStringField(TEXT("id"),         FString::Printf(TEXT("%lld"), W.Id));
        Obj->SetStringField(TEXT("uid"),        W.Uid);
        Obj->SetStringField(TEXT("playerName"), W.PlayerName);
        Obj->SetStringField(TEXT("reason"),     W.Reason);
        Obj->SetStringField(TEXT("warnedBy"),   W.WarnedBy);
        Obj->SetStringField(TEXT("warnDate"),   W.WarnDate.ToIso8601());
        // int32 value — exactly representable in double; the int64-string
        // convention applies only to ID fields that could exceed 2^53.
        Obj->SetNumberField(TEXT("points"),     static_cast<double>(W.Points > 0 ? W.Points : 1));
        return Obj;
    }

    static TSharedPtr<FJsonObject> AppealToJson(const FBanAppealEntry& A)
    {
        TSharedPtr<FJsonObject> Obj = MakeShared<FJsonObject>();
        Obj->SetStringField(TEXT("id"),          FString::Printf(TEXT("%lld"), A.Id));
        Obj->SetStringField(TEXT("uid"),         A.Uid);
        Obj->SetStringField(TEXT("reason"),      A.Reason);
        Obj->SetStringField(TEXT("contactInfo"), A.ContactInfo);
        Obj->SetStringField(TEXT("submittedAt"), A.SubmittedAt.ToIso8601());

        FString StatusStr;
        switch (A.Status)
        {
        case EAppealStatus::Approved: StatusStr = TEXT("approved"); break;
        case EAppealStatus::Denied:   StatusStr = TEXT("denied");   break;
        default:                      StatusStr = TEXT("pending");  break;
        }
        Obj->SetStringField(TEXT("status"),     StatusStr);
        Obj->SetStringField(TEXT("reviewedBy"), A.ReviewedBy);
        Obj->SetStringField(TEXT("reviewNote"), A.ReviewNote);
        if (A.ReviewedAt != FDateTime(0))
            Obj->SetStringField(TEXT("reviewedAt"), A.ReviewedAt.ToIso8601());
        return Obj;
    }

    static TSharedPtr<FJsonObject> ScheduledToJson(const FScheduledBanEntry& S)
    {
        TSharedPtr<FJsonObject> Obj = MakeShared<FJsonObject>();
        Obj->SetStringField(TEXT("id"),              FString::Printf(TEXT("%lld"), S.Id));
        Obj->SetStringField(TEXT("uid"),             S.Uid);
        Obj->SetStringField(TEXT("playerName"),      S.PlayerName);
        Obj->SetStringField(TEXT("reason"),          S.Reason);
        Obj->SetStringField(TEXT("scheduledBy"),     S.ScheduledBy);
        Obj->SetStringField(TEXT("category"),        S.Category);
        // int32 value — exactly representable in double; string encoding not needed.
        Obj->SetNumberField(TEXT("durationMinutes"), static_cast<double>(S.DurationMinutes));
        Obj->SetStringField(TEXT("effectiveAt"),     S.EffectiveAt.ToIso8601());
        Obj->SetStringField(TEXT("createdAt"),       S.CreatedAt.ToIso8601());
        return Obj;
    }

    static TSharedPtr<FJsonObject> AuditToJson(const FAuditEntry& E)
    {
        TSharedPtr<FJsonObject> Obj = MakeShared<FJsonObject>();
        Obj->SetStringField(TEXT("id"),         FString::Printf(TEXT("%lld"), E.Id));
        Obj->SetStringField(TEXT("action"),     E.Action);
        Obj->SetStringField(TEXT("targetUid"),  E.TargetUid);
        Obj->SetStringField(TEXT("targetName"), E.TargetName);
        Obj->SetStringField(TEXT("adminUid"),   E.AdminUid);
        Obj->SetStringField(TEXT("adminName"),  E.AdminName);
        Obj->SetStringField(TEXT("details"),    E.Details);
        if (!E.ModVersion.IsEmpty())
            Obj->SetStringField(TEXT("modVersion"), E.ModVersion);
        Obj->SetStringField(TEXT("timestamp"),  E.Timestamp.ToIso8601());
        return Obj;
    }

    /**
     * Safe int64 parser for path parameters.
     * Returns true and sets OutId when IdStr is a valid positive int64.
     * Rejects empty strings, non-numeric strings, strings longer than 19 digits,
     * and 19-digit strings whose value exceeds INT64_MAX ("9223372036854775807").
     */
    static bool ParseInt64Param(const FString& IdStr, int64& OutId)
    {
        if (IdStr.IsEmpty() || !IdStr.IsNumeric()) return false;
        const int32 Len = IdStr.Len();
        if (Len > 19) return false;
        // A 19-digit string could still exceed INT64_MAX (e.g. "9999999999999999999").
        // Compare lexicographically against the decimal representation of INT64_MAX.
        if (Len == 19 && IdStr > TEXT("9223372036854775807")) return false;
        OutId = FCString::Atoi64(*IdStr);
        return OutId > 0;
    }
} // namespace BanJson

// ─────────────────────────────────────────────────────────────────────────────
//  USubsystem lifecycle
// ─────────────────────────────────────────────────────────────────────────────

void UBanRestApi::Initialize(FSubsystemCollectionBase& Collection)
{
    Collection.InitializeDependency<UBanDatabase>();
    Collection.InitializeDependency<UBanAppealRegistry>();
    Collection.InitializeDependency<UBanWebSocketPusher>();
    Super::Initialize(Collection);

    // Read port from DefaultBanSystem.ini via UBanSystemConfig.
    const UBanSystemConfig* Cfg = UBanSystemConfig::Get();
    ApiPort = Cfg ? Cfg->RestApiPort : 3000;

    if (ApiPort <= 0)
    {
        UE_LOG(LogBanRestApi, Log, TEXT("BanRestApi: REST API disabled (RestApiPort=0)"));
        return;
    }

    StartServer();
}

void UBanRestApi::Deinitialize()
{
    StopServer();
    Super::Deinitialize();
}

void UBanRestApi::StartServer()
{
    FHttpServerModule* HttpModule =
        FModuleManager::Get().LoadModulePtr<FHttpServerModule>(TEXT("HTTPServer"));
    if (!HttpModule)
    {
        UE_LOG(LogBanRestApi, Error,
            TEXT("BanRestApi: HTTPServer module not available"));
        return;
    }

    Router = HttpModule->GetHttpRouter(static_cast<uint32>(ApiPort),
                                       /*bFailOnBindError=*/false);
    if (!Router.IsValid())
    {
        UE_LOG(LogBanRestApi, Error,
            TEXT("BanRestApi: failed to get HTTP router on port %d"), ApiPort);
        return;
    }

    Routes = MakeShared<FBanRestApiRoutes>();
    RegisterRoutes();
    HttpModule->StartAllListeners();

    UE_LOG(LogBanRestApi, Log,
        TEXT("BanRestApi: REST API listening on port %d"), ApiPort);

    // Warn operators when no API key is configured — the entire REST API is
    // then accessible to any process that can reach the server's bind address.
    const UBanSystemConfig* Cfg = UBanSystemConfig::Get();
    if (!Cfg || Cfg->RestApiKey.IsEmpty())
        UE_LOG(LogBanRestApi, Warning,
            TEXT("BanRestApi: RestApiKey is empty — REST API is accessible WITHOUT authentication. "
                 "Set RestApiKey in DefaultBanSystem.ini to restrict access."));
}

void UBanRestApi::StopServer()
{
    if (!Router.IsValid()) return;

    if (Routes.IsValid())
    {
        for (FHttpRouteHandle& H : Routes->Handles)
            Router->UnbindRoute(H);
        Routes->Handles.Empty();
    }
    Routes.Reset();

    // NOTE: Do NOT call HttpModule->StopAllListeners() here — it would stop
    // every HTTP listener across every mod, not just ours.  Unbinding our routes
    // above is sufficient; the router will return 404 for future requests to our
    // paths and the port can be reused by other consumers.
    Router.Reset();
    UE_LOG(LogBanRestApi, Log, TEXT("BanRestApi: REST API stopped"));
}

// ─────────────────────────────────────────────────────────────────────────────
//  Route registration  (mirrors Express routes in apiServer.ts)
// ─────────────────────────────────────────────────────────────────────────────

void UBanRestApi::RegisterRoutes()
{
    // THREADING NOTE: UE's FHttpServerModule enqueues incoming HTTP requests and
    // dispatches route handler callbacks on the game thread via its own FTSTicker.
    // All lambdas registered below therefore run on the game thread — subsystem
    // lookups, delegate broadcasts (OnBanAdded / OnBanRemoved), timer operations,
    // and PlayerController iteration are all safe without additional locking.
    // The WeakGI capture below handles the case where the game instance is
    // destroyed before a pending request is dispatched.
    TWeakObjectPtr<UGameInstance> WeakGI(GetGameInstance());

    // ── GET /health ──────────────────────────────────────────────────────────
    Routes->Handles.Add(Router->BindRoute(
        FHttpPath(TEXT("/health")),
        EHttpServerRequestVerbs::VERB_GET,
        [](const FHttpServerRequest& Req, const FHttpResultCallback& Done) -> bool
        {
            TSharedPtr<FJsonObject> Obj = MakeShared<FJsonObject>();
            Obj->SetStringField(TEXT("status"), TEXT("ok"));
            Done(BanJson::Json(BanJson::ObjectToString(Obj)));
            return true;
        }
    ));

    // ── GET /bans ────────────────────────────────────────────────────────────
    Routes->Handles.Add(Router->BindRoute(
        FHttpPath(TEXT("/bans")),
        EHttpServerRequestVerbs::VERB_GET,
        [WeakGI](const FHttpServerRequest& Req, const FHttpResultCallback& Done) -> bool
        {
            if (!BanJson::CheckApiKey(Req)) { Done(BanJson::Error(TEXT("Unauthorized"), EHttpServerResponseCodes::Denied)); return true; }
            UGameInstance* GI = WeakGI.Get();
            if (!GI) { Done(BanJson::Error(TEXT("Server shutting down"), EHttpServerResponseCodes::ServiceUnavail)); return true; }
            UBanDatabase* DB = GI->GetSubsystem<UBanDatabase>();
            if (!DB) { Done(BanJson::Error(TEXT("Database unavailable"), EHttpServerResponseCodes::ServerError)); return true; }
            Done(BanJson::Json(BanJson::ArrayToString(DB->GetActiveBans())));
            return true;
        }
    ));

    // ── GET /bans/all ────────────────────────────────────────────────────────
    Routes->Handles.Add(Router->BindRoute(
        FHttpPath(TEXT("/bans/all")),
        EHttpServerRequestVerbs::VERB_GET,
        [WeakGI](const FHttpServerRequest& Req, const FHttpResultCallback& Done) -> bool
        {
            if (!BanJson::CheckApiKey(Req)) { Done(BanJson::Error(TEXT("Unauthorized"), EHttpServerResponseCodes::Denied)); return true; }
            UGameInstance* GI = WeakGI.Get();
            if (!GI) { Done(BanJson::Error(TEXT("Server shutting down"), EHttpServerResponseCodes::ServiceUnavail)); return true; }
            UBanDatabase* DB = GI->GetSubsystem<UBanDatabase>();
            if (!DB) { Done(BanJson::Error(TEXT("Database unavailable"), EHttpServerResponseCodes::ServerError)); return true; }
            Done(BanJson::Json(BanJson::ArrayToString(DB->GetAllBans())));
            return true;
        }
    ));

    // ── GET /bans/search?name= ───────────────────────────────────────────────
    // Search the ban list by player name substring (case-insensitive).
    // Must be registered BEFORE /bans/:uid to avoid route collision.
    Routes->Handles.Add(Router->BindRoute(
        FHttpPath(TEXT("/bans/search")),
        EHttpServerRequestVerbs::VERB_GET,
        [WeakGI](const FHttpServerRequest& Req, const FHttpResultCallback& Done) -> bool
        {
            if (!BanJson::CheckApiKey(Req)) { Done(BanJson::Error(TEXT("Unauthorized"), EHttpServerResponseCodes::Denied)); return true; }
            UGameInstance* GI = WeakGI.Get();
            if (!GI) { Done(BanJson::Error(TEXT("Server shutting down"), EHttpServerResponseCodes::ServiceUnavail)); return true; }
            UBanDatabase* DB = GI->GetSubsystem<UBanDatabase>();
            if (!DB) { Done(BanJson::Error(TEXT("Database unavailable"), EHttpServerResponseCodes::ServerError)); return true; }

            const FString* NameQuery = Req.QueryParams.Find(TEXT("name"));
            const FString Query = NameQuery ? *NameQuery : TEXT("");

            TArray<FBanEntry> All = DB->GetAllBans();
            TArray<TSharedPtr<FJsonValue>> Arr;
            for (const FBanEntry& B : All)
            {
                if (Query.IsEmpty() || B.PlayerName.Contains(Query, ESearchCase::IgnoreCase))
                    Arr.Add(MakeShared<FJsonValueObject>(BanJson::EntryToJson(B)));
            }

            TSharedPtr<FJsonObject> Root = MakeShared<FJsonObject>();
            Root->SetNumberField(TEXT("count"), Arr.Num());
            Root->SetArrayField (TEXT("bans"),  Arr);
            Done(BanJson::Json(BanJson::ObjectToString(Root)));
            return true;
        }
    ));

    // ── GET /bans/check/:uid ─────────────────────────────────────────────────
    // Must be registered BEFORE /bans/:uid to avoid route collision.
    Routes->Handles.Add(Router->BindRoute(
        FHttpPath(TEXT("/bans/check/:uid")),
        EHttpServerRequestVerbs::VERB_GET,
        [WeakGI](const FHttpServerRequest& Req, const FHttpResultCallback& Done) -> bool
        {
            if (!BanJson::CheckApiKey(Req)) { Done(BanJson::Error(TEXT("Unauthorized"), EHttpServerResponseCodes::Denied)); return true; }
            const FString RawUid   = Req.PathParams.FindRef(TEXT("uid"));
            const FString Uid      = FGenericPlatformHttp::UrlDecode(RawUid);

            UGameInstance* GI = WeakGI.Get();
            if (!GI) { Done(BanJson::Error(TEXT("Server shutting down"), EHttpServerResponseCodes::ServiceUnavail)); return true; }
            UBanDatabase* DB = GI->GetSubsystem<UBanDatabase>();
            if (!DB) { Done(BanJson::Error(TEXT("Database unavailable"), EHttpServerResponseCodes::ServerError)); return true; }

            FBanEntry Entry;
            const bool bBanned = DB->IsCurrentlyBannedByAnyId(Uid, Entry);

            TSharedPtr<FJsonObject> Obj = MakeShared<FJsonObject>();
            Obj->SetBoolField(TEXT("isBanned"), bBanned);
            if (bBanned)
            {
                Obj->SetObjectField(TEXT("record"), BanJson::EntryToJson(Entry));
                Obj->SetStringField(TEXT("message"), Entry.GetKickMessage());
            }
            else
            {
                Obj->SetStringField(TEXT("message"), TEXT("Player is not banned."));
            }
            Done(BanJson::Json(BanJson::ObjectToString(Obj)));
            return true;
        }
    ));

    // ── POST /bans ───────────────────────────────────────────────────────────
    Routes->Handles.Add(Router->BindRoute(
        FHttpPath(TEXT("/bans")),
        EHttpServerRequestVerbs::VERB_POST,
        [WeakGI](const FHttpServerRequest& Req, const FHttpResultCallback& Done) -> bool
        {
            if (!BanJson::CheckApiKey(Req)) { Done(BanJson::Error(TEXT("Unauthorized"), EHttpServerResponseCodes::Denied)); return true; }
            if (auto SizeErr = BanJson::CheckBodySize(Req)) { Done(MoveTemp(SizeErr)); return true; }

            UGameInstance* GI = WeakGI.Get();
            if (!GI) { Done(BanJson::Error(TEXT("Server shutting down"), EHttpServerResponseCodes::ServiceUnavail)); return true; }

            // Parse JSON body.
            const FString BodyStr = BanJson::BodyToString(Req);
            TSharedPtr<FJsonObject> Body;
            TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(BodyStr);
            if (!FJsonSerializer::Deserialize(Reader, Body) || !Body.IsValid())
            {
                Done(BanJson::Error(TEXT("Invalid JSON body")));
                return true;
            }

            FString PlayerUID, Platform;
            if (!Body->TryGetStringField(TEXT("playerUID"), PlayerUID) || PlayerUID.IsEmpty())
            {
                Done(BanJson::Error(TEXT("playerUID is required")));
                return true;
            }
            if (!Body->TryGetStringField(TEXT("platform"), Platform) || Platform.IsEmpty())
            {
                Done(BanJson::Error(TEXT("platform is required (EOS | UNKNOWN | IP)")));
                return true;
            }
            Platform = Platform.ToUpper();
            if (Platform != TEXT("EOS") && Platform != TEXT("UNKNOWN") && Platform != TEXT("IP"))
            {
                Done(BanJson::Error(TEXT("platform must be EOS, UNKNOWN, or IP")));
                return true;
            }

            FString PlayerName, Reason, BannedBy;
            Body->TryGetStringField(TEXT("playerName"), PlayerName);
            Body->TryGetStringField(TEXT("reason"),     Reason);
            Body->TryGetStringField(TEXT("bannedBy"),   BannedBy);

            double DurationMinutesDbl = 0.0;
            Body->TryGetNumberField(TEXT("durationMinutes"), DurationMinutesDbl);
            // Guard against out-of-range doubles: negative/zero means permanent.
            // Values larger than INT_MAX are clamped to INT_MAX (~4083 years) rather
            // than silently becoming a permanent ban (PATCH /bans/:uid uses the same cap).
            int32 DurationMinutes;
            if (DurationMinutesDbl <= 0.0)
                DurationMinutes = 0;                              // permanent
            else if (DurationMinutesDbl > static_cast<double>(INT_MAX))
                DurationMinutes = INT_MAX;                        // cap, not permanent
            else
                DurationMinutes = static_cast<int32>(DurationMinutesDbl);

            if (Reason.IsEmpty())   Reason   = TEXT("No reason given");
            if (BannedBy.IsEmpty()) BannedBy = TEXT("system");

            // Normalize EOS PUIDs to lowercase so they always match the lowercase
            // UIDs extracted from the ClientIdentity connection option in BanEnforcer.
            if (Platform == TEXT("EOS"))
            {
                PlayerUID = PlayerUID.ToLower();

                // Validate: EOS PUIDs must be exactly 32 lowercase hex characters.
                // A misformatted PUID will never match a real player in BanEnforcer,
                // silently polluting the ban database.
                bool bValidPuid = (PlayerUID.Len() == 32);
                for (int32 i = 0; bValidPuid && i < 32; ++i)
                {
                    const TCHAR C = PlayerUID[i];
                    bValidPuid = (C >= TEXT('0') && C <= TEXT('9')) || (C >= TEXT('a') && C <= TEXT('f'));
                }
                if (!bValidPuid)
                {
                    Done(BanJson::Error(TEXT("playerUID must be a valid 32-character hexadecimal EOS PUID")));
                    return true;
                }
            }

            FBanEntry Entry;
            Entry.Uid        = UBanDatabase::MakeUid(Platform, PlayerUID);
            Entry.PlayerUID  = PlayerUID;
            Entry.Platform   = Platform;
            Entry.PlayerName = PlayerName;
            Entry.Reason     = Reason;
            Entry.BannedBy   = BannedBy;
            const FDateTime Now = FDateTime::UtcNow();
            Entry.BanDate    = Now;
            Entry.bIsPermanent = (DurationMinutes <= 0);
            Entry.ExpireDate = Entry.bIsPermanent
                ? FDateTime(0)
                : Now + FTimespan::FromMinutes(DurationMinutes);

            UBanDatabase* DB = GI->GetSubsystem<UBanDatabase>();
            if (!DB) { Done(BanJson::Error(TEXT("Database unavailable"), EHttpServerResponseCodes::ServerError)); return true; }

            if (!DB->AddBan(Entry))
            {
                Done(BanJson::Error(TEXT("Failed to add ban"), EHttpServerResponseCodes::ServerError));
                return true;
            }

            // Kick the player immediately if they are currently connected.
            if (UWorld* World = GI->GetWorld())
            {
                UBanEnforcer::KickConnectedPlayer(World, Entry.Uid, Entry.GetKickMessage());
            }

            // Fetch the row back so we can return the assigned id (auto-incremented by AddBan).
            // Fall back to returning the in-memory entry if the lookup fails (should never
            // happen after a successful AddBan, but guards against a corrupt DB state).
            FBanEntry Saved;
            if (!DB->GetBanByUid(Entry.Uid, Saved))
            {
                UE_LOG(LogBanRestApi, Warning,
                    TEXT("BanRestApi: POST /bans — GetBanByUid failed for '%s' immediately after AddBan; returning in-memory entry"),
                    *Entry.Uid);
                Saved = Entry;
            }

            FBanDiscordNotifier::NotifyBanCreated(Saved);
            if (UBanAuditLog* AuditLog = GI->GetSubsystem<UBanAuditLog>())
                // REST API bans have no separate admin UID (BannedBy is a display name).
                // Pass an empty adminUid so the audit log does not record the name twice.
                AuditLog->LogAction(TEXT("ban"), Saved.Uid, Saved.PlayerName, TEXT(""), Saved.BannedBy, Saved.Reason);

            auto Resp = BanJson::Json(BanJson::ObjectToString(BanJson::EntryToJson(Saved)));
            Resp->Code = EHttpServerResponseCodes::Created;
            Done(MoveTemp(Resp));
            return true;
        }
    ));

    // ── DELETE /bans/id/:id ──────────────────────────────────────────────────
    // Register BEFORE /bans/:uid so the "id" literal segment wins.
    Routes->Handles.Add(Router->BindRoute(
        FHttpPath(TEXT("/bans/id/:id")),
        EHttpServerRequestVerbs::VERB_DELETE,
        [WeakGI](const FHttpServerRequest& Req, const FHttpResultCallback& Done) -> bool
        {
            if (!BanJson::CheckApiKey(Req)) { Done(BanJson::Error(TEXT("Unauthorized"), EHttpServerResponseCodes::Denied)); return true; }
            if (auto SizeErr = BanJson::CheckBodySize(Req)) { Done(MoveTemp(SizeErr)); return true; }

            const FString IdStr = Req.PathParams.FindRef(TEXT("id"));
            int64 Id = 0;
            if (!BanJson::ParseInt64Param(IdStr, Id))
            {
                Done(BanJson::Error(TEXT("id must be an integer")));
                return true;
            }

            UGameInstance* GI = WeakGI.Get();
            if (!GI) { Done(BanJson::Error(TEXT("Server shutting down"), EHttpServerResponseCodes::ServiceUnavail)); return true; }
            UBanDatabase* DB = GI->GetSubsystem<UBanDatabase>();
            if (!DB) { Done(BanJson::Error(TEXT("Database unavailable"), EHttpServerResponseCodes::ServerError)); return true; }

            // Use the overload that atomically captures the deleted entry's data
            // inside the database lock, eliminating the TOCTOU window that existed
            // when GetAllBans() + RemoveBanById() were called as two separate steps.
            FBanEntry DeletedEntry;
            if (!DB->RemoveBanById(Id, DeletedEntry))
            {
                Done(BanJson::Error(
                    FString::Printf(TEXT("No ban found with id %lld"), Id),
                    EHttpServerResponseCodes::NotFound));
                return true;
            }

            FBanDiscordNotifier::NotifyBanRemoved(DeletedEntry.Uid, DeletedEntry.PlayerName, TEXT("api"));
            if (UBanAuditLog* AuditLog = GI->GetSubsystem<UBanAuditLog>())
                AuditLog->LogAction(TEXT("unban"), DeletedEntry.Uid, DeletedEntry.PlayerName, TEXT("api"), TEXT("api"),
                    FString::Printf(TEXT("id=%lld"), Id));

            Done(BanJson::Ok(FString::Printf(TEXT("Ban id=%lld removed"), Id)));
            return true;
        }
    ));

    // ── GET /bans/export-csv ─────────────────────────────────────────────────
    // Must be registered before /bans/:uid to avoid route collision.
    Routes->Handles.Add(Router->BindRoute(
        FHttpPath(TEXT("/bans/export-csv")),
        EHttpServerRequestVerbs::VERB_GET,
        [WeakGI](const FHttpServerRequest& Req, const FHttpResultCallback& Done) -> bool
        {
            if (!BanJson::CheckApiKey(Req)) { Done(BanJson::Error(TEXT("Unauthorized"), EHttpServerResponseCodes::Denied)); return true; }
            UGameInstance* GI = WeakGI.Get();
            if (!GI) { Done(BanJson::Error(TEXT("Server shutting down"), EHttpServerResponseCodes::ServiceUnavail)); return true; }
            UBanDatabase* DB = GI->GetSubsystem<UBanDatabase>();
            if (!DB) { Done(BanJson::Error(TEXT("Database unavailable"), EHttpServerResponseCodes::ServerError)); return true; }

            TArray<FBanEntry> AllBans = DB->GetAllBans();

            auto CsvQuote = [](const FString& S) -> FString
            {
                // Escape embedded double-quotes per RFC 4180 and replace embedded
                // newlines with a space so that line-oriented CSV parsers don't break.
                FString Escaped = S.Replace(TEXT("\""), TEXT("\"\""));
                Escaped = Escaped.Replace(TEXT("\r\n"), TEXT(" "));
                Escaped = Escaped.Replace(TEXT("\r"),   TEXT(" "));
                Escaped = Escaped.Replace(TEXT("\n"),   TEXT(" "));
                return TEXT("\"") + Escaped + TEXT("\"");
            };

            FString Csv = TEXT("id,uid,playerUID,platform,playerName,reason,bannedBy,banDate,expireDate,isPermanent,linkedUids\n");
            for (const FBanEntry& E : AllBans)
            {
                FString LinkedStr;
                for (int32 i = 0; i < E.LinkedUids.Num(); ++i)
                {
                    if (i > 0) LinkedStr += TEXT("|");
                    LinkedStr += E.LinkedUids[i];
                }

                Csv += FString::Printf(TEXT("%lld,"), E.Id);
                Csv += CsvQuote(E.Uid)        + TEXT(",");
                Csv += CsvQuote(E.PlayerUID)  + TEXT(",");
                Csv += CsvQuote(E.Platform)   + TEXT(",");
                Csv += CsvQuote(E.PlayerName) + TEXT(",");
                Csv += CsvQuote(E.Reason)     + TEXT(",");
                Csv += CsvQuote(E.BannedBy)   + TEXT(",");
                Csv += CsvQuote(E.BanDate.ToIso8601())                                    + TEXT(",");
                Csv += CsvQuote(E.bIsPermanent ? FString() : E.ExpireDate.ToIso8601()) + TEXT(",");
                Csv += FString(E.bIsPermanent ? TEXT("true") : TEXT("false")) + TEXT(",");
                Csv += CsvQuote(LinkedStr)    + TEXT("\n");
            }

            auto R = FHttpServerResponse::Create(Csv, TEXT("text/csv"));
            R->Code = EHttpServerResponseCodes::Ok;
            R->Headers.Add(TEXT("Content-Disposition"),
                TArray<FString>{TEXT("attachment; filename=\"bans.csv\"")});
            Done(MoveTemp(R));
            return true;
        }
    ));

    // ── PATCH /bans/:uid ─────────────────────────────────────────────────────
    // Must be registered before DELETE /bans/:uid.
    Routes->Handles.Add(Router->BindRoute(
        FHttpPath(TEXT("/bans/:uid")),
        EHttpServerRequestVerbs::VERB_PATCH,
        [WeakGI](const FHttpServerRequest& Req, const FHttpResultCallback& Done) -> bool
        {
            if (!BanJson::CheckApiKey(Req)) { Done(BanJson::Error(TEXT("Unauthorized"), EHttpServerResponseCodes::Denied)); return true; }
            if (auto SizeErr = BanJson::CheckBodySize(Req)) { Done(MoveTemp(SizeErr)); return true; }

            const FString RawUid = Req.PathParams.FindRef(TEXT("uid"));
            const FString Uid    = FGenericPlatformHttp::UrlDecode(RawUid);

            UGameInstance* GI = WeakGI.Get();
            if (!GI) { Done(BanJson::Error(TEXT("Server shutting down"), EHttpServerResponseCodes::ServiceUnavail)); return true; }
            UBanDatabase* DB = GI->GetSubsystem<UBanDatabase>();
            if (!DB) { Done(BanJson::Error(TEXT("Database unavailable"), EHttpServerResponseCodes::ServerError)); return true; }

            const FString BodyStr = BanJson::BodyToString(Req);
            TSharedPtr<FJsonObject> Body;
            TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(BodyStr);
            if (!FJsonSerializer::Deserialize(Reader, Body) || !Body.IsValid())
            {
                Done(BanJson::Error(TEXT("Invalid JSON body")));
                return true;
            }

            // Capture all patch values before entering the database lock.
            FString NewReason, NewBannedBy;
            Body->TryGetStringField(TEXT("reason"),    NewReason);
            Body->TryGetStringField(TEXT("bannedBy"),  NewBannedBy);
            double DurationMinutesDbl = -1.0;
            Body->TryGetNumberField(TEXT("durationMinutes"), DurationMinutesDbl);

            // Atomically read-modify-write the ban record inside a single mutex
            // acquisition, eliminating the TOCTOU window that existed when
            // GetBanByUid() + AddBan() were called as two separate steps.
            FBanEntry Updated;
            const bool bUpdated = DB->UpdateBan(Uid,
                [&NewReason, &NewBannedBy, DurationMinutesDbl](FBanEntry& E)
                {
                    if (!NewReason.IsEmpty())
                        E.Reason = NewReason;
                    if (!NewBannedBy.IsEmpty())
                        E.BannedBy = NewBannedBy;
                    if (DurationMinutesDbl == 0.0)
                    {
                        E.bIsPermanent = true;
                        E.ExpireDate   = FDateTime(0);
                    }
                    else if (DurationMinutesDbl > 0.0)
                    {
                        const int32 Mins = (DurationMinutesDbl > static_cast<double>(INT_MAX))
                            ? INT_MAX
                            : static_cast<int32>(DurationMinutesDbl);
                        E.bIsPermanent = false;
                        E.ExpireDate   = FDateTime::UtcNow() + FTimespan::FromMinutes(Mins);
                    }
                    // negative DurationMinutesDbl (other than -1 sentinel) = don't change
                },
                Updated);

            if (!bUpdated)
            {
                Done(BanJson::Error(
                    FString::Printf(TEXT("No ban found for uid '%s'"), *Uid),
                    EHttpServerResponseCodes::NotFound));
                return true;
            }

            if (UBanAuditLog* AuditLog = GI->GetSubsystem<UBanAuditLog>())
                AuditLog->LogAction(TEXT("updateban"), Updated.Uid, Updated.PlayerName,
                    TEXT("api"), TEXT("api"),
                    FString::Printf(TEXT("reason=%s"), *Updated.Reason));

            Done(BanJson::Json(BanJson::ObjectToString(BanJson::EntryToJson(Updated))));
            return true;
        }
    ));

    // ── DELETE /bans/:uid ────────────────────────────────────────────────────
    Routes->Handles.Add(Router->BindRoute(
        FHttpPath(TEXT("/bans/:uid")),
        EHttpServerRequestVerbs::VERB_DELETE,
        [WeakGI](const FHttpServerRequest& Req, const FHttpResultCallback& Done) -> bool
        {
            if (!BanJson::CheckApiKey(Req)) { Done(BanJson::Error(TEXT("Unauthorized"), EHttpServerResponseCodes::Denied)); return true; }
            if (auto SizeErr = BanJson::CheckBodySize(Req)) { Done(MoveTemp(SizeErr)); return true; }

            const FString RawUid = Req.PathParams.FindRef(TEXT("uid"));
            const FString Uid    = FGenericPlatformHttp::UrlDecode(RawUid);

            UGameInstance* GI = WeakGI.Get();
            if (!GI) { Done(BanJson::Error(TEXT("Server shutting down"), EHttpServerResponseCodes::ServiceUnavail)); return true; }
            UBanDatabase* DB = GI->GetSubsystem<UBanDatabase>();
            if (!DB) { Done(BanJson::Error(TEXT("Database unavailable"), EHttpServerResponseCodes::ServerError)); return true; }

            // Atomically look up and remove — eliminates the TOCTOU window that
            // existed when GetBanByUid() + RemoveBanByUid() were called separately.
            FBanEntry OldEntry;
            if (!DB->RemoveBanByUid(Uid, OldEntry))
            {
                Done(BanJson::Error(
                    FString::Printf(TEXT("No ban found for uid '%s'"), *Uid),
                    EHttpServerResponseCodes::NotFound));
                return true;
            }

            FBanDiscordNotifier::NotifyBanRemoved(OldEntry.Uid, OldEntry.PlayerName, TEXT("api"));
            if (UBanAuditLog* AuditLog = GI->GetSubsystem<UBanAuditLog>())
                AuditLog->LogAction(TEXT("unban"), OldEntry.Uid, OldEntry.PlayerName, TEXT("api"), TEXT("api"), TEXT(""));

            Done(BanJson::Ok(FString::Printf(TEXT("Ban '%s' removed"), *Uid)));
            return true;
        }
    ));

    // ── POST /bans/prune ─────────────────────────────────────────────────────
    Routes->Handles.Add(Router->BindRoute(
        FHttpPath(TEXT("/bans/prune")),
        EHttpServerRequestVerbs::VERB_POST,
        [WeakGI](const FHttpServerRequest& Req, const FHttpResultCallback& Done) -> bool
        {
            if (!BanJson::CheckApiKey(Req)) { Done(BanJson::Error(TEXT("Unauthorized"), EHttpServerResponseCodes::Denied)); return true; }
            if (auto SizeErr = BanJson::CheckBodySize(Req)) { Done(MoveTemp(SizeErr)); return true; }

            UGameInstance* GI = WeakGI.Get();
            if (!GI) { Done(BanJson::Error(TEXT("Server shutting down"), EHttpServerResponseCodes::ServiceUnavail)); return true; }
            UBanDatabase* DB = GI->GetSubsystem<UBanDatabase>();
            if (!DB) { Done(BanJson::Error(TEXT("Database unavailable"), EHttpServerResponseCodes::ServerError)); return true; }

            const int32 Pruned = DB->PruneExpiredBans();
            if (Pruned > 0)
                UE_LOG(LogBanRestApi, Log, TEXT("BanRestApi: /bans/prune removed %d expired ban(s)."), Pruned);

            TSharedPtr<FJsonObject> Obj = MakeShared<FJsonObject>();
            Obj->SetNumberField(TEXT("pruned"), Pruned);
            Done(BanJson::Json(BanJson::ObjectToString(Obj)));
            return true;
        }
    ));

    // ── POST /bans/backup ────────────────────────────────────────────────────
    Routes->Handles.Add(Router->BindRoute(
        FHttpPath(TEXT("/bans/backup")),
        EHttpServerRequestVerbs::VERB_POST,
        [WeakGI](const FHttpServerRequest& Req, const FHttpResultCallback& Done) -> bool
        {
            if (!BanJson::CheckApiKey(Req)) { Done(BanJson::Error(TEXT("Unauthorized"), EHttpServerResponseCodes::Denied)); return true; }
            if (auto SizeErr = BanJson::CheckBodySize(Req)) { Done(MoveTemp(SizeErr)); return true; }

            UGameInstance* GI = WeakGI.Get();
            if (!GI) { Done(BanJson::Error(TEXT("Server shutting down"), EHttpServerResponseCodes::ServiceUnavail)); return true; }
            UBanDatabase* DB = GI->GetSubsystem<UBanDatabase>();
            if (!DB) { Done(BanJson::Error(TEXT("Database unavailable"), EHttpServerResponseCodes::ServerError)); return true; }

            const UBanSystemConfig* Cfg = UBanSystemConfig::Get();
            const int32 MaxBackups = Cfg ? Cfg->MaxBackups : 5;

            const FString BackupDir =
                FPaths::GetPath(DB->GetDatabasePath()) / TEXT("backups");
            const FString Dest = DB->Backup(BackupDir, MaxBackups);

            if (Dest.IsEmpty())
            {
                Done(BanJson::Error(TEXT("Backup failed"), EHttpServerResponseCodes::ServerError));
                return true;
            }

            TSharedPtr<FJsonObject> Obj = MakeShared<FJsonObject>();
            Obj->SetStringField(TEXT("path"), Dest);
            Done(BanJson::Json(BanJson::ObjectToString(Obj)));
            return true;
        }
    ));

    // ── GET /players ─────────────────────────────────────────────────────────
    Routes->Handles.Add(Router->BindRoute(
        FHttpPath(TEXT("/players")),
        EHttpServerRequestVerbs::VERB_GET,
        [WeakGI](const FHttpServerRequest& Req, const FHttpResultCallback& Done) -> bool
        {
            if (!BanJson::CheckApiKey(Req)) { Done(BanJson::Error(TEXT("Unauthorized"), EHttpServerResponseCodes::Denied)); return true; }
            UGameInstance* GI = WeakGI.Get();
            if (!GI) { Done(BanJson::Error(TEXT("Server shutting down"), EHttpServerResponseCodes::ServiceUnavail)); return true; }
            UPlayerSessionRegistry* Reg = GI->GetSubsystem<UPlayerSessionRegistry>();
            if (!Reg) { Done(BanJson::Error(TEXT("PlayerSessionRegistry unavailable"), EHttpServerResponseCodes::ServerError)); return true; }

            TArray<FPlayerSessionRecord> Players = Reg->GetAllRecords();
            TArray<TSharedPtr<FJsonValue>> Arr;
            Arr.Reserve(Players.Num());
            for (const FPlayerSessionRecord& P : Players)
            {
                TSharedPtr<FJsonObject> Obj = MakeShared<FJsonObject>();
                Obj->SetStringField(TEXT("uid"),         P.Uid);
                Obj->SetStringField(TEXT("displayName"), P.DisplayName);
                Obj->SetStringField(TEXT("lastSeen"),    P.LastSeen);
                Obj->SetStringField(TEXT("ipAddress"),   P.IpAddress);
                Arr.Add(MakeShared<FJsonValueObject>(Obj));
            }

            TSharedPtr<FJsonObject> Root = MakeShared<FJsonObject>();
            Root->SetNumberField(TEXT("count"),   Players.Num());
            Root->SetArrayField (TEXT("players"), Arr);
            Done(BanJson::Json(BanJson::ObjectToString(Root)));
            return true;
        }
    ));

    // ── GET /players/search?name= ────────────────────────────────────────────
    // Search player session records by display name substring (case-insensitive).
    // Must be registered BEFORE /players/:uid-type routes.
    Routes->Handles.Add(Router->BindRoute(
        FHttpPath(TEXT("/players/search")),
        EHttpServerRequestVerbs::VERB_GET,
        [WeakGI](const FHttpServerRequest& Req, const FHttpResultCallback& Done) -> bool
        {
            if (!BanJson::CheckApiKey(Req)) { Done(BanJson::Error(TEXT("Unauthorized"), EHttpServerResponseCodes::Denied)); return true; }
            UGameInstance* GI = WeakGI.Get();
            if (!GI) { Done(BanJson::Error(TEXT("Server shutting down"), EHttpServerResponseCodes::ServiceUnavail)); return true; }
            UPlayerSessionRegistry* Reg = GI->GetSubsystem<UPlayerSessionRegistry>();
            if (!Reg) { Done(BanJson::Error(TEXT("PlayerSessionRegistry unavailable"), EHttpServerResponseCodes::ServerError)); return true; }

            const FString* NameQuery = Req.QueryParams.Find(TEXT("name"));
            const FString Query = NameQuery ? *NameQuery : TEXT("");

            TArray<FPlayerSessionRecord> All = Reg->GetAllRecords();
            TArray<TSharedPtr<FJsonValue>> Arr;
            for (const FPlayerSessionRecord& P : All)
            {
                if (Query.IsEmpty() || P.DisplayName.Contains(Query, ESearchCase::IgnoreCase))
                {
                    TSharedPtr<FJsonObject> Obj = MakeShared<FJsonObject>();
                    Obj->SetStringField(TEXT("uid"),         P.Uid);
                    Obj->SetStringField(TEXT("displayName"), P.DisplayName);
                    Obj->SetStringField(TEXT("lastSeen"),    P.LastSeen);
                    Obj->SetStringField(TEXT("ipAddress"),   P.IpAddress);
                    Arr.Add(MakeShared<FJsonValueObject>(Obj));
                }
            }

            TSharedPtr<FJsonObject> Root = MakeShared<FJsonObject>();
            Root->SetNumberField(TEXT("count"),   Arr.Num());
            Root->SetArrayField (TEXT("players"), Arr);
            Done(BanJson::Json(BanJson::ObjectToString(Root)));
            return true;
        }
    ));

    // ── GET /warnings ────────────────────────────────────────────────────────
    Routes->Handles.Add(Router->BindRoute(
        FHttpPath(TEXT("/warnings")),
        EHttpServerRequestVerbs::VERB_GET,
        [WeakGI](const FHttpServerRequest& Req, const FHttpResultCallback& Done) -> bool
        {
            if (!BanJson::CheckApiKey(Req)) { Done(BanJson::Error(TEXT("Unauthorized"), EHttpServerResponseCodes::Denied)); return true; }
            UGameInstance* GI = WeakGI.Get();
            if (!GI) { Done(BanJson::Error(TEXT("Server shutting down"), EHttpServerResponseCodes::ServiceUnavail)); return true; }
            UPlayerWarningRegistry* WarnReg = GI->GetSubsystem<UPlayerWarningRegistry>();
            if (!WarnReg) { Done(BanJson::Error(TEXT("WarningRegistry unavailable"), EHttpServerResponseCodes::ServerError)); return true; }

            TArray<FWarningEntry> Entries;
            const FString* UidFilter = Req.QueryParams.Find(TEXT("uid"));
            if (UidFilter && !UidFilter->IsEmpty())
                Entries = WarnReg->GetWarningsForUid(*UidFilter);
            else
                Entries = WarnReg->GetAllWarnings();

            TArray<TSharedPtr<FJsonValue>> Arr;
            Arr.Reserve(Entries.Num());
            for (const FWarningEntry& W : Entries)
                Arr.Add(MakeShared<FJsonValueObject>(BanJson::WarningToJson(W)));

            TSharedPtr<FJsonObject> Root = MakeShared<FJsonObject>();
            Root->SetNumberField(TEXT("count"),    Entries.Num());
            Root->SetArrayField (TEXT("warnings"), Arr);
            Done(BanJson::Json(BanJson::ObjectToString(Root)));
            return true;
        }
    ));

    // ── POST /warnings ───────────────────────────────────────────────────────
    Routes->Handles.Add(Router->BindRoute(
        FHttpPath(TEXT("/warnings")),
        EHttpServerRequestVerbs::VERB_POST,
        [WeakGI](const FHttpServerRequest& Req, const FHttpResultCallback& Done) -> bool
        {
            if (!BanJson::CheckApiKey(Req)) { Done(BanJson::Error(TEXT("Unauthorized"), EHttpServerResponseCodes::Denied)); return true; }
            if (auto SizeErr = BanJson::CheckBodySize(Req)) { Done(MoveTemp(SizeErr)); return true; }

            UGameInstance* GI = WeakGI.Get();
            if (!GI) { Done(BanJson::Error(TEXT("Server shutting down"), EHttpServerResponseCodes::ServiceUnavail)); return true; }

            const FString BodyStr = BanJson::BodyToString(Req);
            TSharedPtr<FJsonObject> Body;
            TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(BodyStr);
            if (!FJsonSerializer::Deserialize(Reader, Body) || !Body.IsValid())
            {
                Done(BanJson::Error(TEXT("Invalid JSON body")));
                return true;
            }

            FString Uid, PlayerName, Reason, WarnedBy;
            if (!Body->TryGetStringField(TEXT("uid"), Uid) || Uid.IsEmpty())
            {
                Done(BanJson::Error(TEXT("uid is required")));
                return true;
            }
            Body->TryGetStringField(TEXT("playerName"), PlayerName);
            Body->TryGetStringField(TEXT("reason"),     Reason);
            Body->TryGetStringField(TEXT("warnedBy"),   WarnedBy);

            if (Reason.IsEmpty())   Reason   = TEXT("No reason given");
            if (WarnedBy.IsEmpty()) WarnedBy = TEXT("console");

            // Optional: caller may specify a custom point weight (defaults to 1).
            int32 Points = 1;
            {
                double PointsDbl = 0.0;
                if (Body->TryGetNumberField(TEXT("points"), PointsDbl) && PointsDbl > 0.0)
                {
                    if (PointsDbl > static_cast<double>(MAX_int32))
                        PointsDbl = static_cast<double>(MAX_int32);
                    Points = static_cast<int32>(PointsDbl);
                }
            }

            UPlayerWarningRegistry* WarnReg = GI->GetSubsystem<UPlayerWarningRegistry>();
            if (!WarnReg) { Done(BanJson::Error(TEXT("WarningRegistry unavailable"), EHttpServerResponseCodes::ServerError)); return true; }

            // Use the struct overload so a non-default point weight is preserved.
            FWarningEntry NewWarnEntry;
            NewWarnEntry.Uid        = Uid;
            NewWarnEntry.PlayerName = PlayerName;
            NewWarnEntry.Reason     = Reason;
            NewWarnEntry.WarnedBy   = WarnedBy;
            NewWarnEntry.Points     = Points;
            // AddWarning returns the stored entry (with the assigned Id and WarnDate) in
            // a single lock acquisition, avoiding a TOCTOU race with concurrent warnings.
            const FWarningEntry NewEntry = WarnReg->AddWarning(NewWarnEntry);
            const int32 WarnCount = WarnReg->GetWarningCount(Uid);

            FBanDiscordNotifier::NotifyWarningIssued(Uid, PlayerName, Reason, WarnedBy, WarnCount);
            if (UBanAuditLog* AuditLog = GI->GetSubsystem<UBanAuditLog>())
                AuditLog->LogAction(TEXT("warn"), Uid, PlayerName, TEXT("api"), WarnedBy, Reason);

            // Auto-ban if the warning threshold has been reached.
            // First, check escalation tiers; fall back to AutoBanWarnCount if no tiers.
            const UBanSystemConfig* Cfg = UBanSystemConfig::Get();
            if (Cfg)
            {
                const int32 WarnPoints = WarnReg->GetWarningPoints(Uid);
                int32 BanDurationMinutes = -1;

                // Check escalation tiers (highest matching tier wins).
                // When a tier has PointThreshold > 0, use accumulated points; otherwise use count.
                if (Cfg->WarnEscalationTiers.Num() > 0)
                {
                    int32 BestThreshold = -1;
                    for (const FWarnEscalationTier& Tier : Cfg->WarnEscalationTiers)
                    {
                        const bool bHit = (Tier.PointThreshold > 0)
                            ? (WarnPoints >= Tier.PointThreshold)
                            : (WarnCount  >= Tier.WarnCount);
                        const int32 ThisThreshold = (Tier.PointThreshold > 0)
                            ? Tier.PointThreshold : Tier.WarnCount;
                        if (bHit && ThisThreshold > BestThreshold)
                        {
                            BestThreshold      = ThisThreshold;
                            BanDurationMinutes = Tier.DurationMinutes;
                        }
                    }
                }
                else if (Cfg->AutoBanWarnCount > 0 && WarnCount >= Cfg->AutoBanWarnCount)
                {
                    BanDurationMinutes = Cfg->AutoBanWarnMinutes;
                }

                if (BanDurationMinutes >= 0)
                {
                    UBanDatabase* DB = GI->GetSubsystem<UBanDatabase>();
                    if (DB)
                    {
                        // Only auto-ban if the player is not already banned.
                        FBanEntry ExistingBan;
                        if (!DB->IsCurrentlyBannedByAnyId(Uid, ExistingBan))
                        {
                            FBanEntry AutoBan;
                            AutoBan.Uid        = Uid;
                            UBanDatabase::ParseUid(Uid, AutoBan.Platform, AutoBan.PlayerUID);
                            AutoBan.PlayerName   = PlayerName;
                            AutoBan.Reason       = TEXT("Auto-banned: reached warning threshold");
                            AutoBan.BannedBy     = TEXT("system");
                            const FDateTime AutoNow = FDateTime::UtcNow();
                            AutoBan.BanDate      = AutoNow;
                            AutoBan.bIsPermanent = (BanDurationMinutes <= 0);
                            AutoBan.ExpireDate   = AutoBan.bIsPermanent
                                ? FDateTime(0)
                                : AutoNow + FTimespan::FromMinutes(BanDurationMinutes);

                            DB->AddBan(AutoBan);
                            FBanDiscordNotifier::NotifyBanCreated(AutoBan);
                            FBanDiscordNotifier::NotifyAutoEscalationBan(AutoBan, WarnCount);
                            if (UBanAuditLog* AuditLog = GI->GetSubsystem<UBanAuditLog>())
                                AuditLog->LogAction(TEXT("ban"), Uid, PlayerName, TEXT("system"), TEXT("system"), AutoBan.Reason);
                            // Kick the player immediately if they are currently online.
                            if (UWorld* World = GI->GetWorld())
                                UBanEnforcer::KickConnectedPlayer(World, Uid, AutoBan.GetKickMessage());
                        }
                    }
                }
            }

            auto Resp = BanJson::Json(BanJson::ObjectToString(BanJson::WarningToJson(NewEntry)));
            Resp->Code = EHttpServerResponseCodes::Created;
            Done(MoveTemp(Resp));
            return true;
        }
    ));

    // ── DELETE /warnings/:uid ────────────────────────────────────────────────
    Routes->Handles.Add(Router->BindRoute(
        FHttpPath(TEXT("/warnings/:uid")),
        EHttpServerRequestVerbs::VERB_DELETE,
        [WeakGI](const FHttpServerRequest& Req, const FHttpResultCallback& Done) -> bool
        {
            if (!BanJson::CheckApiKey(Req)) { Done(BanJson::Error(TEXT("Unauthorized"), EHttpServerResponseCodes::Denied)); return true; }
            if (auto SizeErr = BanJson::CheckBodySize(Req)) { Done(MoveTemp(SizeErr)); return true; }

            const FString RawUid = Req.PathParams.FindRef(TEXT("uid"));
            const FString Uid    = FGenericPlatformHttp::UrlDecode(RawUid);

            UGameInstance* GI = WeakGI.Get();
            if (!GI) { Done(BanJson::Error(TEXT("Server shutting down"), EHttpServerResponseCodes::ServiceUnavail)); return true; }
            UPlayerWarningRegistry* WarnReg = GI->GetSubsystem<UPlayerWarningRegistry>();
            if (!WarnReg) { Done(BanJson::Error(TEXT("WarningRegistry unavailable"), EHttpServerResponseCodes::ServerError)); return true; }

            const int32 Cleared = WarnReg->ClearWarningsForUid(Uid);

            if (UBanAuditLog* AuditLog = GI->GetSubsystem<UBanAuditLog>())
                AuditLog->LogAction(TEXT("clearwarns"), Uid, TEXT(""), TEXT("api"), TEXT("api"),
                    FString::Printf(TEXT("cleared=%d"), Cleared));

            TSharedPtr<FJsonObject> Obj = MakeShared<FJsonObject>();
            Obj->SetNumberField(TEXT("cleared"), Cleared);
            Done(BanJson::Json(BanJson::ObjectToString(Obj)));
            return true;
        }
    ));

    // ── DELETE /warnings/id/:id ──────────────────────────────────────────────
    Routes->Handles.Add(Router->BindRoute(
        FHttpPath(TEXT("/warnings/id/:id")),
        EHttpServerRequestVerbs::VERB_DELETE,
        [WeakGI](const FHttpServerRequest& Request, const FHttpResultCallback& OnComplete) -> bool
        {
            if (!BanJson::CheckApiKey(Request)) { OnComplete(BanJson::Error(TEXT("Unauthorized"), EHttpServerResponseCodes::Denied)); return true; }
            if (auto SizeErr = BanJson::CheckBodySize(Request)) { OnComplete(MoveTemp(SizeErr)); return true; }

            UGameInstance* GI = WeakGI.Get();
            if (!GI) { OnComplete(BanJson::Error(TEXT("Server shutting down"), EHttpServerResponseCodes::ServiceUnavail)); return true; }

            const FString* IdParam = Request.PathParams.Find(TEXT("id"));
            int64 Id = 0;
            if (!IdParam || !BanJson::ParseInt64Param(*IdParam, Id))
            {
                OnComplete(BanJson::Error(TEXT("Invalid warning ID"), EHttpServerResponseCodes::BadRequest));
                return true;
            }

            UPlayerWarningRegistry* WarnReg = GI->GetSubsystem<UPlayerWarningRegistry>();
            if (!WarnReg)
            {
                OnComplete(BanJson::Error(TEXT("PlayerWarningRegistry unavailable"), EHttpServerResponseCodes::ServiceUnavail));
                return true;
            }

            if (!WarnReg->DeleteWarningById(Id))
            {
                OnComplete(BanJson::Error(
                    FString::Printf(TEXT("No warning found with id %lld"), Id),
                    EHttpServerResponseCodes::NotFound));
                return true;
            }

            UBanAuditLog* AuditLog = GI->GetSubsystem<UBanAuditLog>();
            if (AuditLog)
                AuditLog->LogAction(TEXT("deletewarn_id"),
                    FString::Printf(TEXT("warning#%lld"), Id), TEXT(""),
                    TEXT(""), TEXT("api"),
                    FString::Printf(TEXT("Deleted warning id %lld via REST"), Id));

            TSharedPtr<FJsonObject> Ok = MakeShared<FJsonObject>();
            Ok->SetBoolField(TEXT("success"), true);
            Ok->SetStringField(TEXT("id"), FString::Printf(TEXT("%lld"), Id));
            OnComplete(BanJson::Json(BanJson::ObjectToString(Ok)));
            return true;
        }));

    // ── GET /audit ───────────────────────────────────────────────────────────
    Routes->Handles.Add(Router->BindRoute(
        FHttpPath(TEXT("/audit")),
        EHttpServerRequestVerbs::VERB_GET,
        [WeakGI](const FHttpServerRequest& Req, const FHttpResultCallback& Done) -> bool
        {
            if (!BanJson::CheckApiKey(Req)) { Done(BanJson::Error(TEXT("Unauthorized"), EHttpServerResponseCodes::Denied)); return true; }
            UGameInstance* GI = WeakGI.Get();
            if (!GI) { Done(BanJson::Error(TEXT("Server shutting down"), EHttpServerResponseCodes::ServiceUnavail)); return true; }
            UBanAuditLog* AuditLog = GI->GetSubsystem<UBanAuditLog>();
            if (!AuditLog) { Done(BanJson::Error(TEXT("AuditLog unavailable"), EHttpServerResponseCodes::ServerError)); return true; }

            int32 Limit = 100;
            if (const FString* LimitStr = Req.QueryParams.Find(TEXT("limit")))
            {
                if (LimitStr->IsNumeric() && LimitStr->Len() <= 10)
                {
                    const int32 Parsed = FCString::Atoi(**LimitStr);
                    if (Parsed > 0) Limit = FMath::Min(Parsed, 1000);
                }
            }

            int32 Page = 1;
            if (const FString* PageStr = Req.QueryParams.Find(TEXT("page")))
            {
                if (PageStr->IsNumeric() && PageStr->Len() <= 10)
                {
                    const int32 Parsed = FCString::Atoi(**PageStr);
                    if (Parsed > 0) Page = Parsed;
                }
            }

            TArray<FAuditEntry> Entries;
            const FString* UidFilter = Req.QueryParams.Find(TEXT("uid"));
            if (UidFilter && !UidFilter->IsEmpty())
                Entries = AuditLog->GetEntriesForTarget(*UidFilter);
            else
                Entries = AuditLog->GetAllEntries();

            // Sort newest first before paginating.
            Entries.Sort([](const FAuditEntry& A, const FAuditEntry& B)
            {
                return A.Timestamp > B.Timestamp;
            });

            const int32 Total     = Entries.Num();
            // Use int64 arithmetic to avoid int32 overflow when Page is very large.
            const int64 Offset64  = static_cast<int64>(Page - 1) * static_cast<int64>(Limit);
            const int64 End64     = FMath::Min(Offset64 + static_cast<int64>(Limit), static_cast<int64>(Total));

            TArray<TSharedPtr<FJsonValue>> Arr;
            if (Offset64 < static_cast<int64>(Total))
            {
                // Offset64 is in [0, Total-1] here so both casts to int32 are safe.
                const int32 Offset = static_cast<int32>(Offset64);
                const int32 End    = static_cast<int32>(End64);
                Arr.Reserve(End - Offset);
                for (int32 i = Offset; i < End; ++i)
                    Arr.Add(MakeShared<FJsonValueObject>(BanJson::AuditToJson(Entries[i])));
            }

            TSharedPtr<FJsonObject> Root = MakeShared<FJsonObject>();
            Root->SetNumberField(TEXT("count"),      Arr.Num());
            Root->SetNumberField(TEXT("total"),      Total);
            Root->SetNumberField(TEXT("page"),       Page);
            Root->SetNumberField(TEXT("pageSize"),   Limit);
            Root->SetNumberField(TEXT("totalPages"), (static_cast<int64>(Total) + Limit - 1) / FMath::Max(Limit, 1));
            Root->SetArrayField (TEXT("entries"),    Arr);
            Done(BanJson::Json(BanJson::ObjectToString(Root)));
            return true;
        }
    ));

    // ── GET /metrics ─────────────────────────────────────────────────────────
    Routes->Handles.Add(Router->BindRoute(
        FHttpPath(TEXT("/metrics")),
        EHttpServerRequestVerbs::VERB_GET,
        [WeakGI](const FHttpServerRequest& Req, const FHttpResultCallback& Done) -> bool
        {
            if (!BanJson::CheckApiKey(Req)) { Done(BanJson::Error(TEXT("Unauthorized"), EHttpServerResponseCodes::Denied)); return true; }
            UGameInstance* GI = WeakGI.Get();
            if (!GI) { Done(BanJson::Error(TEXT("Server shutting down"), EHttpServerResponseCodes::ServiceUnavail)); return true; }

            UBanDatabase*           DB        = GI->GetSubsystem<UBanDatabase>();
            UPlayerWarningRegistry* WarnReg   = GI->GetSubsystem<UPlayerWarningRegistry>();
            UPlayerSessionRegistry* PlayerReg = GI->GetSubsystem<UPlayerSessionRegistry>();
            UBanAuditLog*           AuditLog  = GI->GetSubsystem<UBanAuditLog>();

            // Count temp bans expiring within 24 hours.
            int32 TempBansExpiringSoon = 0;
            if (DB)
            {
                const FDateTime Horizon = FDateTime::UtcNow() + FTimespan::FromHours(24.0);
                for (const FBanEntry& E : DB->GetActiveBans())
                {
                    if (!E.bIsPermanent && E.ExpireDate <= Horizon)
                        ++TempBansExpiringSoon;
                }
            }

            // Count warnings issued this week.
            int32 WarningsThisWeek = 0;
            if (WarnReg)
            {
                const FDateTime WeekAgo = FDateTime::UtcNow() - FTimespan::FromDays(7.0);
                for (const FWarningEntry& W : WarnReg->GetAllWarnings())
                {
                    if (W.WarnDate >= WeekAgo)
                        ++WarningsThisWeek;
                }
            }

            // Online player count from the world.
            int32 OnlinePlayers = 0;
            if (UWorld* World = GI->GetWorld())
            {
                for (FConstPlayerControllerIterator It = World->GetPlayerControllerIterator(); It; ++It)
                {
                    if (It->IsValid()) ++OnlinePlayers;
                }
            }

            // ── Per-day ban counts for the last 30 days ──────────────────────
            // Produces an array of { date: "YYYY-MM-DD", bans: N } objects.
            TArray<TSharedPtr<FJsonValue>> DailyBansArr;
            if (DB)
            {
                TMap<FString, int32> DayCounts;
                const FDateTime CutOff = FDateTime::UtcNow() - FTimespan::FromDays(30.0);
                for (const FBanEntry& E : DB->GetAllBans())
                {
                    if (E.BanDate < CutOff) continue;
                    const FString Day = E.BanDate.ToString(TEXT("%Y-%m-%d"));
                    int32& Cnt = DayCounts.FindOrAdd(Day);
                    ++Cnt;
                }
                // Sort by date ascending.
                TArray<FString> Days;
                DayCounts.GetKeys(Days);
                Days.Sort();
                for (const FString& Day : Days)
                {
                    TSharedPtr<FJsonObject> DayObj = MakeShared<FJsonObject>();
                    DayObj->SetStringField(TEXT("date"), Day);
                    DayObj->SetNumberField(TEXT("bans"), static_cast<double>(DayCounts[Day]));
                    DailyBansArr.Add(MakeShared<FJsonValueObject>(DayObj));
                }
            }

            // ── Top offenders by total ban count ─────────────────────────────
            // Produces an array of { uid, playerName, banCount } sorted descending.
            TArray<TSharedPtr<FJsonValue>> TopOffendersArr;
            if (DB)
            {
                TMap<FString, TPair<FString, int32>> OffenderMap; // uid → {name, count}
                for (const FBanEntry& E : DB->GetAllBans())
                {
                    if (E.Platform == TEXT("IP")) continue; // skip IP bans for this list
                    TPair<FString, int32>& Pair = OffenderMap.FindOrAdd(E.Uid);
                    Pair.Key = E.PlayerName;
                    ++Pair.Value;
                }
                TArray<TPair<FString, TPair<FString, int32>>> Sorted(OffenderMap.Array());
                Sorted.Sort([](const TPair<FString, TPair<FString, int32>>& A,
                               const TPair<FString, TPair<FString, int32>>& B)
                {
                    return A.Value.Value > B.Value.Value;
                });
                const int32 Limit = FMath::Min(Sorted.Num(), 10);
                for (int32 i = 0; i < Limit; ++i)
                {
                    TSharedPtr<FJsonObject> Off = MakeShared<FJsonObject>();
                    Off->SetStringField(TEXT("uid"),        Sorted[i].Key);
                    Off->SetStringField(TEXT("playerName"), Sorted[i].Value.Key);
                    Off->SetNumberField(TEXT("banCount"),   static_cast<double>(Sorted[i].Value.Value));
                    TopOffendersArr.Add(MakeShared<FJsonValueObject>(Off));
                }
            }

            TSharedPtr<FJsonObject> Obj = MakeShared<FJsonObject>();
            Obj->SetNumberField(TEXT("activeBans"),              DB        ? static_cast<double>(DB->GetActiveBans().Num())        : 0.0);
            Obj->SetNumberField(TEXT("totalBans"),               DB        ? static_cast<double>(DB->GetAllBans().Num())           : 0.0);
            Obj->SetNumberField(TEXT("tempBansExpiringSoon24h"), static_cast<double>(TempBansExpiringSoon));
            Obj->SetNumberField(TEXT("totalWarnings"),           WarnReg   ? static_cast<double>(WarnReg->GetAllWarnings().Num())  : 0.0);
            Obj->SetNumberField(TEXT("warningsThisWeek"),        static_cast<double>(WarningsThisWeek));
            Obj->SetNumberField(TEXT("totalAuditEntries"),       AuditLog  ? static_cast<double>(AuditLog->GetAllEntries().Num())  : 0.0);
            Obj->SetNumberField(TEXT("knownPlayers"),            PlayerReg ? static_cast<double>(PlayerReg->GetAllRecords().Num()) : 0.0);
            Obj->SetNumberField(TEXT("onlinePlayers"),           static_cast<double>(OnlinePlayers));
            {
                int32 PendingAppeals = 0;
                if (UBanAppealRegistry* AppReg = GI->GetSubsystem<UBanAppealRegistry>())
                    for (const FBanAppealEntry& A : AppReg->GetAllAppeals())
                        if (A.Status == EAppealStatus::Pending)
                            ++PendingAppeals;
                Obj->SetNumberField(TEXT("pendingAppeals"), static_cast<double>(PendingAppeals));
            }
            Obj->SetArrayField (TEXT("dailyBans30d"),            DailyBansArr);
            Obj->SetArrayField (TEXT("topOffenders"),            TopOffendersArr);
            Obj->SetStringField(TEXT("timestamp"),               FDateTime::UtcNow().ToIso8601());
            Done(BanJson::Json(BanJson::ObjectToString(Obj)));
            return true;
        }
    ));

    // ── POST /bans/ip ────────────────────────────────────────────────────────
    Routes->Handles.Add(Router->BindRoute(
        FHttpPath(TEXT("/bans/ip")),
        EHttpServerRequestVerbs::VERB_POST,
        [WeakGI](const FHttpServerRequest& Req, const FHttpResultCallback& Done) -> bool
        {
            if (!BanJson::CheckApiKey(Req)) { Done(BanJson::Error(TEXT("Unauthorized"), EHttpServerResponseCodes::Denied)); return true; }
            if (auto SizeErr = BanJson::CheckBodySize(Req)) { Done(MoveTemp(SizeErr)); return true; }

            UGameInstance* GI = WeakGI.Get();
            if (!GI) { Done(BanJson::Error(TEXT("Server shutting down"), EHttpServerResponseCodes::ServiceUnavail)); return true; }
            UBanDatabase* DB = GI->GetSubsystem<UBanDatabase>();
            if (!DB) { Done(BanJson::Error(TEXT("Database unavailable"), EHttpServerResponseCodes::ServerError)); return true; }

            const FString BodyStr = BanJson::BodyToString(Req);
            TSharedPtr<FJsonObject> Body;
            TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(BodyStr);
            if (!FJsonSerializer::Deserialize(Reader, Body) || !Body.IsValid())
            {
                Done(BanJson::Error(TEXT("Invalid JSON body")));
                return true;
            }

            FString IpAddress;
            if (!Body->TryGetStringField(TEXT("ipAddress"), IpAddress) || IpAddress.IsEmpty())
            {
                Done(BanJson::Error(TEXT("ipAddress is required")));
                return true;
            }

            // Validate IP address format: reject strings that are too long or contain
            // characters outside the set permitted in IPv4/IPv6 addresses ([0-9a-fA-F:.]).
            // This prevents garbage UIDs (e.g. path traversal strings) from being
            // persisted in the ban database and confusing enforcement/sync components.
            if (IpAddress.Len() > 45) // 45 chars: generous limit that accommodates any
                                      // valid IPv4 (15), full IPv6 (39), or mixed
                                      // IPv6/IPv4 notation (max 45 chars uncompressed)
            {
                Done(BanJson::Error(TEXT("ipAddress is invalid")));
                return true;
            }
            for (TCHAR Ch : IpAddress)
            {
                if (!((Ch >= '0' && Ch <= '9') || (Ch >= 'a' && Ch <= 'f') ||
                      (Ch >= 'A' && Ch <= 'F') || Ch == '.' || Ch == ':'))
                {
                    Done(BanJson::Error(TEXT("ipAddress is invalid")));
                    return true;
                }
            }

            FString Reason, BannedBy;
            Body->TryGetStringField(TEXT("reason"),   Reason);
            Body->TryGetStringField(TEXT("bannedBy"), BannedBy);
            if (Reason.IsEmpty())   Reason   = TEXT("IP ban");
            if (BannedBy.IsEmpty()) BannedBy = TEXT("system");

            FBanEntry Entry;
            Entry.Uid        = UBanDatabase::MakeUid(TEXT("IP"), IpAddress);
            Entry.PlayerUID  = IpAddress;
            Entry.Platform   = TEXT("IP");
            Entry.PlayerName = IpAddress;
            Entry.Reason     = Reason;
            Entry.BannedBy   = BannedBy;
            Entry.BanDate    = FDateTime::UtcNow();
            Entry.bIsPermanent = true;
            Entry.ExpireDate   = FDateTime(0);

            if (!DB->AddBan(Entry))
            {
                Done(BanJson::Error(TEXT("Failed to add IP ban"), EHttpServerResponseCodes::ServerError));
                return true;
            }

            // Fetch the row back so the response includes the assigned ID.
            // (AddBan assigns the ID inside its own local copy; Entry.Id is still 0 here.)
            FBanEntry Saved;
            if (!DB->GetBanByUid(Entry.Uid, Saved))
            {
                UE_LOG(LogBanRestApi, Warning,
                    TEXT("BanRestApi: POST /bans/ip — GetBanByUid failed for '%s' immediately after AddBan; returning in-memory entry"),
                    *Entry.Uid);
                Saved = Entry;
            }

            FBanDiscordNotifier::NotifyBanCreated(Saved);
            if (UBanAuditLog* AuditLog = GI->GetSubsystem<UBanAuditLog>())
                AuditLog->LogAction(TEXT("ban"), Saved.Uid, IpAddress, TEXT(""), BannedBy, Reason);

            auto Resp = BanJson::Json(BanJson::ObjectToString(BanJson::EntryToJson(Saved)));
            Resp->Code = EHttpServerResponseCodes::Created;
            Done(MoveTemp(Resp));
            return true;
        }
    ));

    // ── DELETE /bans/ip/:ip ──────────────────────────────────────────────────
    Routes->Handles.Add(Router->BindRoute(
        FHttpPath(TEXT("/bans/ip/:ip")),
        EHttpServerRequestVerbs::VERB_DELETE,
        [WeakGI](const FHttpServerRequest& Req, const FHttpResultCallback& Done) -> bool
        {
            if (!BanJson::CheckApiKey(Req)) { Done(BanJson::Error(TEXT("Unauthorized"), EHttpServerResponseCodes::Denied)); return true; }
            if (auto SizeErr = BanJson::CheckBodySize(Req)) { Done(MoveTemp(SizeErr)); return true; }

            const FString IpAddress = FGenericPlatformHttp::UrlDecode(Req.PathParams.FindRef(TEXT("ip")));

            UGameInstance* GI = WeakGI.Get();
            if (!GI) { Done(BanJson::Error(TEXT("Server shutting down"), EHttpServerResponseCodes::ServiceUnavail)); return true; }
            UBanDatabase* DB = GI->GetSubsystem<UBanDatabase>();
            if (!DB) { Done(BanJson::Error(TEXT("Database unavailable"), EHttpServerResponseCodes::ServerError)); return true; }

            const FString Uid = UBanDatabase::MakeUid(TEXT("IP"), IpAddress);
            if (!DB->RemoveBanByUid(Uid))
            {
                Done(BanJson::Error(
                    FString::Printf(TEXT("No IP ban found for '%s'"), *IpAddress),
                    EHttpServerResponseCodes::NotFound));
                return true;
            }

            FBanDiscordNotifier::NotifyBanRemoved(Uid, IpAddress, TEXT("api"));
            if (UBanAuditLog* AuditLog = GI->GetSubsystem<UBanAuditLog>())
                AuditLog->LogAction(TEXT("unban"), Uid, IpAddress, TEXT("api"), TEXT("api"), TEXT("ip ban removal"));

            Done(BanJson::Ok(FString::Printf(TEXT("IP ban for '%s' removed"), *IpAddress)));
            return true;
        }
    ));

    // ── POST /players/prune ──────────────────────────────────────────────────
    Routes->Handles.Add(Router->BindRoute(
        FHttpPath(TEXT("/players/prune")),
        EHttpServerRequestVerbs::VERB_POST,
        [WeakGI](const FHttpServerRequest& Req, const FHttpResultCallback& Done) -> bool
        {
            if (!BanJson::CheckApiKey(Req)) { Done(BanJson::Error(TEXT("Unauthorized"), EHttpServerResponseCodes::Denied)); return true; }
            if (auto SizeErr = BanJson::CheckBodySize(Req)) { Done(MoveTemp(SizeErr)); return true; }

            UGameInstance* GI = WeakGI.Get();
            if (!GI) { Done(BanJson::Error(TEXT("Server shutting down"), EHttpServerResponseCodes::ServiceUnavail)); return true; }
            UPlayerSessionRegistry* PlayerReg = GI->GetSubsystem<UPlayerSessionRegistry>();
            if (!PlayerReg) { Done(BanJson::Error(TEXT("PlayerSessionRegistry unavailable"), EHttpServerResponseCodes::ServerError)); return true; }

            const UBanSystemConfig* Cfg = UBanSystemConfig::Get();

            // Allow caller to override the retention window.
            int32 DaysToKeep = Cfg ? Cfg->SessionRetentionDays : 0;
            const FString BodyStr = BanJson::BodyToString(Req);
            if (BodyStr != TEXT("{}"))
            {
                TSharedPtr<FJsonObject> Body;
                TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(BodyStr);
                if (FJsonSerializer::Deserialize(Reader, Body) && Body.IsValid())
                {
                    double DaysDbl = 0.0;
                    if (Body->TryGetNumberField(TEXT("daysToKeep"), DaysDbl) && DaysDbl > 0.0)
                        DaysToKeep = static_cast<int32>(DaysDbl);
                }
            }

            if (DaysToKeep <= 0)
            {
                Done(BanJson::Error(
                    TEXT("daysToKeep must be > 0 (set in request body or SessionRetentionDays config)")));
                return true;
            }

            const int32 Pruned = PlayerReg->PruneOldRecords(DaysToKeep);

            TSharedPtr<FJsonObject> Obj = MakeShared<FJsonObject>();
            Obj->SetNumberField(TEXT("pruned"),     static_cast<double>(Pruned));
            Obj->SetNumberField(TEXT("daysToKeep"), static_cast<double>(DaysToKeep));
            Done(BanJson::Json(BanJson::ObjectToString(Obj)));
            return true;
        }
    ));

    // ── GET /audit/export-csv ────────────────────────────────────────────────
    Routes->Handles.Add(Router->BindRoute(
        FHttpPath(TEXT("/audit/export-csv")),
        EHttpServerRequestVerbs::VERB_GET,
        [WeakGI](const FHttpServerRequest& Req, const FHttpResultCallback& Done) -> bool
        {
            if (!BanJson::CheckApiKey(Req)) { Done(BanJson::Error(TEXT("Unauthorized"), EHttpServerResponseCodes::Denied)); return true; }
            UGameInstance* GI = WeakGI.Get();
            if (!GI) { Done(BanJson::Error(TEXT("Server shutting down"), EHttpServerResponseCodes::ServiceUnavail)); return true; }
            UBanAuditLog* AuditLog = GI->GetSubsystem<UBanAuditLog>();
            if (!AuditLog) { Done(BanJson::Error(TEXT("AuditLog unavailable"), EHttpServerResponseCodes::ServerError)); return true; }

            TArray<FAuditEntry> Entries = AuditLog->GetAllEntries();

            auto CsvQ = [](const FString& S) -> FString
            {
                FString Escaped = S.Replace(TEXT("\""), TEXT("\"\""));
                Escaped = Escaped.Replace(TEXT("\r\n"), TEXT(" "));
                Escaped = Escaped.Replace(TEXT("\r"),   TEXT(" "));
                Escaped = Escaped.Replace(TEXT("\n"),   TEXT(" "));
                return TEXT("\"") + Escaped + TEXT("\"");
            };

            FString Csv = TEXT("id,action,targetUid,targetName,adminUid,adminName,details,modVersion,timestamp\n");
            for (const FAuditEntry& E : Entries)
            {
                Csv += FString::Printf(TEXT("%lld,"), E.Id);
                Csv += CsvQ(E.Action)     + TEXT(",");
                Csv += CsvQ(E.TargetUid)  + TEXT(",");
                Csv += CsvQ(E.TargetName) + TEXT(",");
                Csv += CsvQ(E.AdminUid)   + TEXT(",");
                Csv += CsvQ(E.AdminName)  + TEXT(",");
                Csv += CsvQ(E.Details)    + TEXT(",");
                Csv += CsvQ(E.ModVersion) + TEXT(",");
                Csv += E.Timestamp.ToIso8601() + TEXT("\n");
            }

            auto R = FHttpServerResponse::Create(Csv, TEXT("text/csv"));
            R->Code = EHttpServerResponseCodes::Ok;
            Done(MoveTemp(R));
            return true;
        }
    ));

    // ── GET /notes ───────────────────────────────────────────────────────────
    Routes->Handles.Add(Router->BindRoute(
        FHttpPath(TEXT("/notes")),
        EHttpServerRequestVerbs::VERB_GET,
        [WeakGI](const FHttpServerRequest& Req, const FHttpResultCallback& Done) -> bool
        {
            if (!BanJson::CheckApiKey(Req)) { Done(BanJson::Error(TEXT("Unauthorized"), EHttpServerResponseCodes::Denied)); return true; }
            UGameInstance* GI = WeakGI.Get();
            if (!GI) { Done(BanJson::Error(TEXT("Server shutting down"), EHttpServerResponseCodes::ServiceUnavail)); return true; }

            // UPlayerNoteRegistry lives in BanChatCommands; reference it via a
            // forward-declared interface to avoid a hard module dependency.
            // We look it up by name through the GameInstance subsystem list.
            // Since notes are stored as a GameInstance subsystem that ships with
            // BanChatCommands, we gracefully return 404 when it isn't present.
            UGameInstanceSubsystem* NoteSubsys = nullptr;
            for (UGameInstanceSubsystem* S : GI->GetSubsystemArray<UGameInstanceSubsystem>())
            {
                if (S && S->GetClass()->GetName() == TEXT("PlayerNoteRegistry"))
                {
                    NoteSubsys = S;
                    break;
                }
            }

            if (!NoteSubsys)
            {
                Done(BanJson::Error(TEXT("PlayerNoteRegistry unavailable (BanChatCommands not installed)"), EHttpServerResponseCodes::NotFound));
                return true;
            }

            // Reflect into the subsystem to read the note count from the internal
            // Notes array property — this is safe across module boundaries because we
            // only read the array's element count, not the element layout.
            int32 NoteCount = 0;
            FArrayProperty* NotesProp = FindFProperty<FArrayProperty>(
                    NoteSubsys->GetClass(), TEXT("Notes"));
            if (!NotesProp)
            {
                // Property not found — BanChatCommands may have been updated and the
                // property renamed. Return a diagnostic error rather than silently
                // returning count=0.
                Done(BanJson::Error(TEXT("PlayerNoteRegistry.Notes property not found — BanChatCommands version mismatch"), EHttpServerResponseCodes::ServiceUnavail));
                return true;
            }
            {
                FScriptArrayHelper Helper(NotesProp,
                    NotesProp->ContainerPtrToValuePtr<void>(NoteSubsys));
                NoteCount = Helper.Num();
            }

            TArray<TSharedPtr<FJsonValue>> Arr;
            TSharedPtr<FJsonObject> Root = MakeShared<FJsonObject>();
            Root->SetNumberField(TEXT("count"), static_cast<double>(NoteCount));
            Root->SetArrayField (TEXT("notes"),  Arr);
            Root->SetStringField(TEXT("info"), TEXT("Note count is accurate. Full note data is accessible via BanChatCommands module directly."));
            Done(BanJson::Json(BanJson::ObjectToString(Root)));
            return true;
        }
    ));

    // ── GET /warnings/export-csv ─────────────────────────────────────────────
    Routes->Handles.Add(Router->BindRoute(
        FHttpPath(TEXT("/warnings/export-csv")),
        EHttpServerRequestVerbs::VERB_GET,
        [WeakGI](const FHttpServerRequest& Req, const FHttpResultCallback& Done) -> bool
        {
            if (!BanJson::CheckApiKey(Req)) { Done(BanJson::Error(TEXT("Unauthorized"), EHttpServerResponseCodes::Denied)); return true; }
            UGameInstance* GI = WeakGI.Get();
            if (!GI) { Done(BanJson::Error(TEXT("Server shutting down"), EHttpServerResponseCodes::ServiceUnavail)); return true; }
            UPlayerWarningRegistry* WarnReg = GI->GetSubsystem<UPlayerWarningRegistry>();
            if (!WarnReg) { Done(BanJson::Error(TEXT("WarningRegistry unavailable"), EHttpServerResponseCodes::ServerError)); return true; }

            TArray<FWarningEntry> Entries = WarnReg->GetAllWarnings();

            auto CsvQ = [](const FString& S) -> FString
            {
                FString Escaped = S.Replace(TEXT("\""), TEXT("\"\""));
                Escaped = Escaped.Replace(TEXT("\r\n"), TEXT(" "));
                Escaped = Escaped.Replace(TEXT("\r"),   TEXT(" "));
                Escaped = Escaped.Replace(TEXT("\n"),   TEXT(" "));
                return TEXT("\"") + Escaped + TEXT("\"");
            };

            FString Csv = TEXT("id,uid,playerName,reason,warnedBy,warnDate\n");
            for (const FWarningEntry& W : Entries)
            {
                Csv += FString::Printf(TEXT("%lld,"), W.Id);
                Csv += CsvQ(W.Uid)        + TEXT(",");
                Csv += CsvQ(W.PlayerName) + TEXT(",");
                Csv += CsvQ(W.Reason)     + TEXT(",");
                Csv += CsvQ(W.WarnedBy)   + TEXT(",");
                Csv += W.WarnDate.ToIso8601() + TEXT("\n");
            }

            auto R = FHttpServerResponse::Create(Csv, TEXT("text/csv"));
            R->Code = EHttpServerResponseCodes::Ok;
            Done(MoveTemp(R));
            return true;
        }
    ));

    // ── GET /players/export-csv ──────────────────────────────────────────────
    Routes->Handles.Add(Router->BindRoute(
        FHttpPath(TEXT("/players/export-csv")),
        EHttpServerRequestVerbs::VERB_GET,
        [WeakGI](const FHttpServerRequest& Req, const FHttpResultCallback& Done) -> bool
        {
            if (!BanJson::CheckApiKey(Req)) { Done(BanJson::Error(TEXT("Unauthorized"), EHttpServerResponseCodes::Denied)); return true; }
            UGameInstance* GI = WeakGI.Get();
            if (!GI) { Done(BanJson::Error(TEXT("Server shutting down"), EHttpServerResponseCodes::ServiceUnavail)); return true; }
            UPlayerSessionRegistry* PlayerReg = GI->GetSubsystem<UPlayerSessionRegistry>();
            if (!PlayerReg) { Done(BanJson::Error(TEXT("PlayerSessionRegistry unavailable"), EHttpServerResponseCodes::ServerError)); return true; }

            TArray<FPlayerSessionRecord> Players = PlayerReg->GetAllRecords();

            auto CsvQ = [](const FString& S) -> FString
            {
                FString Escaped = S.Replace(TEXT("\""), TEXT("\"\""));
                Escaped = Escaped.Replace(TEXT("\r\n"), TEXT(" "));
                Escaped = Escaped.Replace(TEXT("\r"),   TEXT(" "));
                Escaped = Escaped.Replace(TEXT("\n"),   TEXT(" "));
                return TEXT("\"") + Escaped + TEXT("\"");
            };

            FString Csv = TEXT("uid,displayName,lastSeen,ipAddress\n");
            for (const FPlayerSessionRecord& P : Players)
            {
                Csv += CsvQ(P.Uid)         + TEXT(",");
                Csv += CsvQ(P.DisplayName) + TEXT(",");
                Csv += CsvQ(P.LastSeen)    + TEXT(",");
                Csv += CsvQ(P.IpAddress)   + TEXT("\n");
            }

            auto R = FHttpServerResponse::Create(Csv, TEXT("text/csv"));
            R->Code = EHttpServerResponseCodes::Ok;
            Done(MoveTemp(R));
            return true;
        }
    ));

    // ── POST /appeals ────────────────────────────────────────────────────────
    // No auth required — players submit appeals from outside the game.
    Routes->Handles.Add(Router->BindRoute(
        FHttpPath(TEXT("/appeals")),
        EHttpServerRequestVerbs::VERB_POST,
        [WeakGI](const FHttpServerRequest& Req, const FHttpResultCallback& Done) -> bool
        {
            if (auto SizeErr = BanJson::CheckBodySize(Req)) { Done(MoveTemp(SizeErr)); return true; }

            // C1: Global rate limit — max 5 appeal submissions per minute regardless
            // of UID, preventing flooding with cycling UIDs.
            {
                static FCriticalSection AppealRateMutex;
                static TArray<FDateTime> AppealSubmissions;
                static constexpr int32 MaxAppealsPerMinute = 5;

                FScopeLock RateLock(&AppealRateMutex);
                const FDateTime Now = FDateTime::UtcNow();
                AppealSubmissions.RemoveAll([&Now](const FDateTime& T)
                {
                    return (Now - T).GetTotalMinutes() >= 1.0;
                });
                if (AppealSubmissions.Num() >= MaxAppealsPerMinute)
                {
                    Done(BanJson::Error(TEXT("Too many appeal submissions. Please try again later.")));
                    return true;
                }
                AppealSubmissions.Add(Now);
            }

            UGameInstance* GI = WeakGI.Get();
            if (!GI) { Done(BanJson::Error(TEXT("Server shutting down"), EHttpServerResponseCodes::ServiceUnavail)); return true; }
            UBanAppealRegistry* AppealsReg = GI->GetSubsystem<UBanAppealRegistry>();
            if (!AppealsReg) { Done(BanJson::Error(TEXT("AppealRegistry unavailable"), EHttpServerResponseCodes::ServerError)); return true; }

            const FString BodyStr = BanJson::BodyToString(Req);
            TSharedPtr<FJsonObject> Body;
            TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(BodyStr);
            if (!FJsonSerializer::Deserialize(Reader, Body) || !Body.IsValid())
            {
                Done(BanJson::Error(TEXT("Invalid JSON body")));
                return true;
            }

            FString Uid, Reason, ContactInfo;
            if (!Body->TryGetStringField(TEXT("uid"), Uid) || Uid.IsEmpty())
            {
                Done(BanJson::Error(TEXT("uid is required")));
                return true;
            }
            // Clamp player-supplied strings to prevent database bloat / DoS.
            Uid = Uid.Left(128).TrimStartAndEnd();
            Body->TryGetStringField(TEXT("reason"),      Reason);
            Body->TryGetStringField(TEXT("contactInfo"), ContactInfo);
            Reason      = Reason.Left(2000).TrimStartAndEnd();
            ContactInfo = ContactInfo.Left(500).TrimStartAndEnd();
            if (Reason.IsEmpty()) Reason = TEXT("No reason given");

            // Reject duplicate appeals atomically: AddAppealIfNoDuplicate checks for an
            // existing Pending entry and inserts the new one inside a single mutex lock,
            // closing the TOCTOU window that existed when doing GetAllAppeals()+AddAppeal().
            const FBanAppealEntry NewEntry = AppealsReg->AddAppealIfNoDuplicate(Uid, Reason, ContactInfo);
            if (NewEntry.Id == 0)
            {
                Done(BanJson::Error(TEXT("A pending appeal for this player already exists. Please wait for a response before submitting another.")));
                return true;
            }

            // AddAppeal() already broadcasts OnBanAppealSubmitted, which
            // BanDiscordSubsystem subscribes to when the bot is running.
            // Only fire the webhook directly when no bot listener is active,
            // to prevent duplicate appeal notifications in the same Discord
            // channel when both DiscordWebhookUrl and ModerationLogChannelId
            // are configured.
            if (!UBanAppealRegistry::OnBanAppealSubmitted.IsBound())
                FBanDiscordNotifier::NotifyAppealSubmitted(NewEntry);

            // WebSocket push.
            {
                TSharedPtr<FJsonObject> PushFields = MakeShared<FJsonObject>();
                PushFields->SetStringField(TEXT("uid"),         NewEntry.Uid);
                PushFields->SetStringField(TEXT("reason"),      NewEntry.Reason);
                PushFields->SetStringField(TEXT("contactInfo"), NewEntry.ContactInfo);
                PushFields->SetStringField(TEXT("submittedAt"), NewEntry.SubmittedAt.ToIso8601());
                UBanWebSocketPusher::PushEvent(TEXT("appeal"), PushFields);
            }

            TSharedPtr<FJsonObject> Obj = MakeShared<FJsonObject>();
            Obj->SetStringField(TEXT("id"),          FString::Printf(TEXT("%lld"), NewEntry.Id));
            Obj->SetStringField(TEXT("uid"),         NewEntry.Uid);
            Obj->SetStringField(TEXT("reason"),      NewEntry.Reason);
            Obj->SetStringField(TEXT("contactInfo"), NewEntry.ContactInfo);
            Obj->SetStringField(TEXT("submittedAt"), NewEntry.SubmittedAt.ToIso8601());

            auto Resp = BanJson::Json(BanJson::ObjectToString(Obj));
            Resp->Code = EHttpServerResponseCodes::Created;
            Done(MoveTemp(Resp));
            return true;
        }
    ));

    // ── GET /appeals ─────────────────────────────────────────────────────────
    Routes->Handles.Add(Router->BindRoute(
        FHttpPath(TEXT("/appeals")),
        EHttpServerRequestVerbs::VERB_GET,
        [WeakGI](const FHttpServerRequest& Req, const FHttpResultCallback& Done) -> bool
        {
            if (!BanJson::CheckApiKey(Req)) { Done(BanJson::Error(TEXT("Unauthorized"), EHttpServerResponseCodes::Denied)); return true; }

            UGameInstance* GI = WeakGI.Get();
            if (!GI) { Done(BanJson::Error(TEXT("Server shutting down"), EHttpServerResponseCodes::ServiceUnavail)); return true; }
            UBanAppealRegistry* AppealsReg = GI->GetSubsystem<UBanAppealRegistry>();
            if (!AppealsReg) { Done(BanJson::Error(TEXT("AppealRegistry unavailable"), EHttpServerResponseCodes::ServerError)); return true; }

            TArray<FBanAppealEntry> Appeals = AppealsReg->GetAllAppeals();

            // Optional status filter: ?status=pending|approved|denied
            const FString* StatusFilter = Req.QueryParams.Find(TEXT("status"));
            if (StatusFilter && !StatusFilter->IsEmpty())
            {
                EAppealStatus FilterStatus = EAppealStatus::Pending;
                const FString Norm = StatusFilter->ToLower();
                if (Norm == TEXT("approved"))      FilterStatus = EAppealStatus::Approved;
                else if (Norm == TEXT("denied"))   FilterStatus = EAppealStatus::Denied;
                Appeals.RemoveAll([FilterStatus](const FBanAppealEntry& A){ return A.Status != FilterStatus; });
            }

            TArray<TSharedPtr<FJsonValue>> Arr;
            Arr.Reserve(Appeals.Num());
            for (const FBanAppealEntry& E : Appeals)
                Arr.Add(MakeShared<FJsonValueObject>(BanJson::AppealToJson(E)));

            TSharedPtr<FJsonObject> Root = MakeShared<FJsonObject>();
            Root->SetNumberField(TEXT("count"),   static_cast<double>(Appeals.Num()));
            Root->SetArrayField (TEXT("appeals"), Arr);
            Done(BanJson::Json(BanJson::ObjectToString(Root)));
            return true;
        }
    ));

    // ── GET /appeals/:id ─────────────────────────────────────────────────────
    // Must be registered BEFORE DELETE /appeals/:id to avoid route collision.
    Routes->Handles.Add(Router->BindRoute(
        FHttpPath(TEXT("/appeals/:id")),
        EHttpServerRequestVerbs::VERB_GET,
        [WeakGI](const FHttpServerRequest& Req, const FHttpResultCallback& Done) -> bool
        {
            if (!BanJson::CheckApiKey(Req)) { Done(BanJson::Error(TEXT("Unauthorized"), EHttpServerResponseCodes::Denied)); return true; }

            const FString IdStr = Req.PathParams.FindRef(TEXT("id"));
            int64 Id = 0;
            if (!BanJson::ParseInt64Param(IdStr, Id))
            {
                Done(BanJson::Error(TEXT("Invalid appeal ID"), EHttpServerResponseCodes::BadRequest));
                return true;
            }

            UGameInstance* GI = WeakGI.Get();
            if (!GI) { Done(BanJson::Error(TEXT("Server shutting down"), EHttpServerResponseCodes::ServiceUnavail)); return true; }
            UBanAppealRegistry* AppealsReg = GI->GetSubsystem<UBanAppealRegistry>();
            if (!AppealsReg) { Done(BanJson::Error(TEXT("AppealRegistry unavailable"), EHttpServerResponseCodes::ServerError)); return true; }

            const FBanAppealEntry Entry = AppealsReg->GetAppealById(Id);
            if (Entry.Id == 0)
            {
                Done(BanJson::Error(
                    FString::Printf(TEXT("No appeal found with id %lld"), Id),
                    EHttpServerResponseCodes::NotFound));
                return true;
            }

            Done(BanJson::Json(BanJson::ObjectToString(BanJson::AppealToJson(Entry))));
            return true;
        }
    ));

    // ── GET /metrics/prometheus ──────────────────────────────────────────────
    // Prometheus text exposition format (https://prometheus.io/docs/instrumenting/exposition_formats/)
    Routes->Handles.Add(Router->BindRoute(
        FHttpPath(TEXT("/metrics/prometheus")),
        EHttpServerRequestVerbs::VERB_GET,
        [WeakGI](const FHttpServerRequest& Req, const FHttpResultCallback& Done) -> bool
        {
            if (!BanJson::CheckApiKey(Req)) { Done(BanJson::Error(TEXT("Unauthorized"), EHttpServerResponseCodes::Denied)); return true; }
            UGameInstance* GI = WeakGI.Get();
            if (!GI) { Done(BanJson::Error(TEXT("Server shutting down"), EHttpServerResponseCodes::ServiceUnavail)); return true; }

            UBanDatabase*           DB        = GI->GetSubsystem<UBanDatabase>();
            UPlayerWarningRegistry* WarnReg   = GI->GetSubsystem<UPlayerWarningRegistry>();
            UPlayerSessionRegistry* PlayerReg = GI->GetSubsystem<UPlayerSessionRegistry>();
            UBanAuditLog*           AuditLog  = GI->GetSubsystem<UBanAuditLog>();
            UBanAppealRegistry*     AppealReg = GI->GetSubsystem<UBanAppealRegistry>();

            int32 OnlinePlayers = 0;
            if (UWorld* World = GI->GetWorld())
                for (FConstPlayerControllerIterator It = World->GetPlayerControllerIterator(); It; ++It)
                    if (It->IsValid()) ++OnlinePlayers;

            FString Out;
            auto Gauge = [&Out](const FString& Name, const FString& Help, double Value)
            {
                Out += FString::Printf(TEXT("# HELP %s %s\n# TYPE %s gauge\n%s %.0f\n"),
                    *Name, *Help, *Name, *Name, Value);
            };

            Gauge(TEXT("bansystem_active_bans"),     TEXT("Number of currently active bans"),
                  DB        ? static_cast<double>(DB->GetActiveBans().Num())        : 0.0);
            Gauge(TEXT("bansystem_total_bans"),      TEXT("Total bans ever recorded"),
                  DB        ? static_cast<double>(DB->GetAllBans().Num())           : 0.0);
            Gauge(TEXT("bansystem_total_warnings"),  TEXT("Total warnings ever recorded"),
                  WarnReg   ? static_cast<double>(WarnReg->GetAllWarnings().Num())  : 0.0);
            Gauge(TEXT("bansystem_known_players"),   TEXT("Number of distinct player session records"),
                  PlayerReg ? static_cast<double>(PlayerReg->GetAllRecords().Num()) : 0.0);
            Gauge(TEXT("bansystem_audit_entries"),   TEXT("Number of audit log entries"),
                  AuditLog  ? static_cast<double>(AuditLog->GetAllEntries().Num())  : 0.0);
            Gauge(TEXT("bansystem_pending_appeals"), TEXT("Number of pending ban appeals"),
                  [AppealReg]() -> double {
                      if (!AppealReg) return 0.0;
                      double Count = 0.0;
                      for (const FBanAppealEntry& A : AppealReg->GetAllAppeals())
                          if (A.Status == EAppealStatus::Pending) ++Count;
                      return Count;
                  }());
            Gauge(TEXT("bansystem_online_players"),  TEXT("Number of players currently connected"),
                  static_cast<double>(OnlinePlayers));

            auto R = FHttpServerResponse::Create(Out, TEXT("text/plain; version=0.0.4; charset=utf-8"));
            R->Code = EHttpServerResponseCodes::Ok;
            Done(MoveTemp(R));
            return true;
        }
    ));

    // ── GET /appeals/portal ──────────────────────────────────────────────────
    // Lightweight HTML form that lets banned players submit an appeal from a browser.
    // No authentication required — the form POSTs to /appeals.
    Routes->Handles.Add(Router->BindRoute(
        FHttpPath(TEXT("/appeals/portal")),
        EHttpServerRequestVerbs::VERB_GET,
        [WeakGI](const FHttpServerRequest& Req, const FHttpResultCallback& Done) -> bool
        {
            // NOTE: The Host header is intentionally NOT injected into the page.
            // All API calls use relative URLs so the form works from any origin
            // without risking header-injection XSS.
            UGameInstance* GI = WeakGI.Get();
            const FString ServerName = [GI]() -> FString
            {
                if (!GI) return TEXT("this server");
                const UBanSystemConfig* Cfg = UBanSystemConfig::Get();
                return (Cfg && !Cfg->DatabasePath.IsEmpty())
                    ? FPaths::GetBaseFilename(Cfg->DatabasePath) : TEXT("this server");
            }();

            // HTML-escape ServerName before injecting into the page to prevent XSS.
            auto HtmlEscape = [](const FString& S) -> FString
            {
                FString Out;
                Out.Reserve(S.Len());
                for (TCHAR C : S)
                {
                    switch (C)
                    {
                    case TCHAR('&'):  Out += TEXT("&amp;");  break;
                    case TCHAR('<'):  Out += TEXT("&lt;");   break;
                    case TCHAR('>'):  Out += TEXT("&gt;");   break;
                    case TCHAR('"'):  Out += TEXT("&quot;"); break;
                    case TCHAR('\''): Out += TEXT("&#x27;"); break;
                    default:          Out.AppendChar(C);     break;
                    }
                }
                return Out;
            };
            const FString SafeServerName = HtmlEscape(ServerName);

            const FString Html = FString::Printf(TEXT(R"HTML(<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width,initial-scale=1">
  <title>Ban Appeal – %s</title>
  <style>
    body{font-family:system-ui,sans-serif;max-width:540px;margin:40px auto;padding:0 16px;background:#1a1a2e;color:#e0e0e0}
    h1{color:#a78bfa}
    label{display:block;margin-top:16px;font-size:.9rem;color:#9ca3af}
    input,textarea{width:100%%;box-sizing:border-box;padding:10px;margin-top:4px;background:#16213e;border:1px solid #4b5563;border-radius:6px;color:#e0e0e0;font-size:1rem}
    textarea{resize:vertical;min-height:100px}
    button{margin-top:24px;width:100%%;padding:12px;background:#7c3aed;color:#fff;border:none;border-radius:8px;font-size:1rem;cursor:pointer}
    button:hover{background:#6d28d9}
    #status{margin-top:16px;padding:12px;border-radius:6px;display:none}
    .ok{background:#065f46;color:#a7f3d0}.err{background:#7f1d1d;color:#fca5a5}
  </style>
</head>
<body>
  <h1>⚖️ Ban Appeal</h1>
  <p>You were banned from <strong>%s</strong>. Fill out this form to request a review.</p>
  <form id="appealForm">
    <label for="uid">Your EOS Player UID (32-character hex, from /whoami)</label>
    <input id="uid" name="uid" placeholder="e.g. 00020aed06f0a6958c3c067fb4b73d51" required pattern="[0-9a-fA-F]{32}">
    <label for="contact">Contact info (Discord handle, email, etc.)</label>
    <input id="contact" name="contact" placeholder="Discord: yourname#1234">
    <label for="reason">Your appeal (explain why the ban should be reconsidered)</label>
    <textarea id="reason" name="reason" placeholder="I believe I was banned because…" required></textarea>
    <button type="submit">Submit Appeal</button>
  </form>
  <div id="status"></div>
  <script>
    document.getElementById('appealForm').addEventListener('submit', async function(e){
      e.preventDefault();
      const uid = document.getElementById('uid').value.trim().toLowerCase();
      const contact = document.getElementById('contact').value.trim();
      const reason = document.getElementById('reason').value.trim();
      const st = document.getElementById('status');
      st.style.display='block'; st.className=''; st.textContent='Submitting…';
      try{
        const r = await fetch('/appeals',{method:'POST',headers:{'Content-Type':'application/json'},
          body:JSON.stringify({uid:uid,contactInfo:contact,reason:reason,platform:'EOS'})});
        const j = await r.json();
        if(r.ok){st.className='ok';st.textContent='✅ Appeal submitted (ID #'+j.id+'). Staff will review it shortly.';}
        else{st.className='err';st.textContent='❌ Error: '+(j.error||'Unknown error');}
      }catch(err){st.className='err';st.textContent='❌ Network error: '+err.message;}
    });
  </script>
</body>
</html>)HTML"), *SafeServerName, *SafeServerName);

            auto R = FHttpServerResponse::Create(Html, TEXT("text/html; charset=utf-8"));
            R->Code = EHttpServerResponseCodes::Ok;
            Done(MoveTemp(R));
            return true;
        }
    ));

    // ── DELETE /appeals/:id ──────────────────────────────────────────────────
    Routes->Handles.Add(Router->BindRoute(
        FHttpPath(TEXT("/appeals/:id")),
        EHttpServerRequestVerbs::VERB_DELETE,
        [WeakGI](const FHttpServerRequest& Req, const FHttpResultCallback& Done) -> bool
        {
            if (!BanJson::CheckApiKey(Req)) { Done(BanJson::Error(TEXT("Unauthorized"), EHttpServerResponseCodes::Denied)); return true; }
            if (auto SizeErr = BanJson::CheckBodySize(Req)) { Done(MoveTemp(SizeErr)); return true; }

            const FString IdStr = Req.PathParams.FindRef(TEXT("id"));
            int64 Id = 0;
            if (!BanJson::ParseInt64Param(IdStr, Id))
            {
                Done(BanJson::Error(TEXT("Invalid appeal ID"), EHttpServerResponseCodes::BadRequest));
                return true;
            }

            UGameInstance* GI = WeakGI.Get();
            if (!GI) { Done(BanJson::Error(TEXT("Server shutting down"), EHttpServerResponseCodes::ServiceUnavail)); return true; }
            UBanAppealRegistry* AppealsReg = GI->GetSubsystem<UBanAppealRegistry>();
            if (!AppealsReg) { Done(BanJson::Error(TEXT("AppealRegistry unavailable"), EHttpServerResponseCodes::ServerError)); return true; }

            if (!AppealsReg->DeleteAppeal(Id))
            {
                Done(BanJson::Error(
                    FString::Printf(TEXT("No appeal found with id %lld"), Id),
                    EHttpServerResponseCodes::NotFound));
                return true;
            }

            Done(BanJson::Ok(FString::Printf(TEXT("Appeal id=%lld dismissed"), Id)));
            return true;
        }
    ));

    // ── GET /dashboard ───────────────────────────────────────────────────────
    // Unified single-page HTML dashboard aggregating bans, players, warnings,
    // mutes, appeals, and audit log.
    // Access requires the API key (via X-Api-Key header or ?key= query param).
    // All JS API calls use relative URLs to avoid Host-header injection.
    Routes->Handles.Add(Router->BindRoute(
        FHttpPath(TEXT("/dashboard")),
        EHttpServerRequestVerbs::VERB_GET,
        [WeakGI](const FHttpServerRequest& Req, const FHttpResultCallback& Done) -> bool
        {
            if (!BanJson::CheckApiKey(Req)) { Done(BanJson::Error(TEXT("Unauthorized"), EHttpServerResponseCodes::Denied)); return true; }

            // Split the HTML into two string literals to stay within MSVC's 16380-char
            // string-literal limit (C2026).  Only the second part uses FString::Printf
            // because it contains the API base-URL placeholder (%s).
            FString Html = TEXT(R"HTML(<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width,initial-scale=1">
  <title>BanSystem Dashboard</title>
  <style>
    *{box-sizing:border-box;margin:0;padding:0}
    body{font-family:system-ui,sans-serif;background:#0f0f1a;color:#e0e0e0;min-height:100vh}
    header{background:#1a1a2e;padding:16px 24px;display:flex;align-items:center;gap:12px;border-bottom:1px solid #2d2d4e}
    header h1{color:#a78bfa;font-size:1.4rem}
    nav{display:flex;gap:4px;margin-top:10px;flex-wrap:wrap}
    nav button{padding:6px 14px;border:none;border-radius:6px;background:#2d2d4e;color:#c4b5fd;cursor:pointer;font-size:.85rem}
    nav button.active{background:#7c3aed;color:#fff}
    main{padding:20px 24px;max-width:1200px;margin:0 auto}
    .stats{display:grid;grid-template-columns:repeat(auto-fill,minmax(160px,1fr));gap:12px;margin-bottom:24px}
    .stat-card{background:#1a1a2e;border-radius:10px;padding:16px;text-align:center}
    .stat-card .num{font-size:2rem;font-weight:700;color:#a78bfa}
    .stat-card .lbl{font-size:.75rem;color:#9ca3af;margin-top:4px}
    table{width:100%%;border-collapse:collapse;font-size:.85rem}
    th{background:#2d2d4e;color:#c4b5fd;padding:10px 12px;text-align:left;font-weight:600}
    td{padding:9px 12px;border-bottom:1px solid #1e1e38}
    tr:hover td{background:#1a1a2e}
    .badge{padding:3px 8px;border-radius:12px;font-size:.75rem;font-weight:600}
    .badge-red{background:#7f1d1d;color:#fca5a5}
    .badge-yellow{background:#78350f;color:#fde68a}
    .badge-green{background:#065f46;color:#a7f3d0}
    .badge-blue{background:#1e3a5f;color:#93c5fd}
    .tab-content{display:none}
    .tab-content.active{display:block}
    input[type=text]{background:#1a1a2e;border:1px solid #4b5563;border-radius:6px;color:#e0e0e0;padding:7px 12px;font-size:.9rem;width:260px}
    .search-bar{margin-bottom:14px;display:flex;gap:8px;align-items:center}
    #loadingOverlay{position:fixed;inset:0;background:rgba(0,0,0,.6);display:flex;align-items:center;justify-content:center;font-size:1.2rem;z-index:999}
    #loadingOverlay.hidden{display:none}
    .error-msg{color:#fca5a5;margin-top:12px;font-size:.9rem}
  </style>
</head>
<body>
<div id="loadingOverlay">Loading…</div>
<header>
  <div>
    <h1>⚖️ BanSystem Dashboard</h1>
    <nav>
      <button class="active" onclick="switchTab('bans',this)">🚫 Bans</button>
      <button onclick="switchTab('players',this)">👥 Players</button>
      <button onclick="switchTab('warnings',this)">⚠️ Warnings</button>
      <button onclick="switchTab('appeals',this)">📩 Appeals</button>
      <button onclick="switchTab('audit',this)">📋 Audit Log</button>
      <button onclick="switchTab('metrics',this)">📊 Metrics</button>
    </nav>
  </div>
</header>
<main>
  <div class="stats" id="statsRow"></div>

  <!-- Bans -->
  <div id="tab-bans" class="tab-content active">
    <div class="search-bar">
      <input type="text" id="banSearch" placeholder="Search by name or UID…" oninput="filterTable('banTable',this.value)">
    </div>
    <table><thead><tr><th>UID</th><th>Name</th><th>Reason</th><th>By</th><th>Expires</th><th>Type</th></tr></thead>
    <tbody id="banTable"></tbody></table>
  </div>

  <!-- Players -->
  <div id="tab-players" class="tab-content">
    <div class="search-bar">
      <input type="text" id="playerSearch" placeholder="Search by name or IP…" oninput="filterTable('playerTable',this.value)">
    </div>
    <table><thead><tr><th>UID</th><th>Display Name</th><th>Last Seen</th><th>IP Address</th></tr></thead>
    <tbody id="playerTable"></tbody></table>
  </div>

  <!-- Warnings -->
  <div id="tab-warnings" class="tab-content">
    <div class="search-bar">
      <input type="text" id="warnSearch" placeholder="Search…" oninput="filterTable('warnTable',this.value)">
    </div>
    <table><thead><tr><th>ID</th><th>UID</th><th>Name</th><th>Reason</th><th>By</th><th>Date</th></tr></thead>
    <tbody id="warnTable"></tbody></table>
  </div>

  <!-- Appeals -->
  <div id="tab-appeals" class="tab-content">
    <table><thead><tr><th>ID</th><th>UID</th><th>Contact</th><th>Submitted</th><th>Reason</th></tr></thead>
    <tbody id="appealTable"></tbody></table>
  </div>

  <!-- Audit Log -->
  <div id="tab-audit" class="tab-content">
    <table><thead><tr><th>Time</th><th>Action</th><th>Target</th><th>By</th><th>Reason</th><th>Mod Ver</th></tr></thead>
    <tbody id="auditTable"></tbody></table>
  </div>

  <!-- Metrics -->
  <div id="tab-metrics" class="tab-content">
    <div id="metricsContent"></div>
  </div>

  <p class="error-msg" id="errorMsg"></p>
</main>)HTML");
            Html += TEXT(R"HTML(<script>
  // Read the key from the URL once (so it can be bookmarked as ?key=xxx),
  // persist it in sessionStorage, then immediately remove it from the address
  // bar so it is not stored in browser history or leaked in referrer headers.
  (function(){
    const params = new URLSearchParams(location.search);
    const urlKey = params.get('key');
    if(urlKey){
      sessionStorage.setItem('banApiKey', urlKey);
      params.delete('key');
      const newSearch = params.toString();
      history.replaceState(null,'', location.pathname + (newSearch ? '?'+newSearch : '') + location.hash);
    }
  })();
  const KEY = sessionStorage.getItem('banApiKey') || '';
  const API = '';

  async function apiFetch(path){
    const hdrs = {};
    if(KEY) hdrs['X-Api-Key'] = KEY;
    const r = await fetch(API+path,{headers:hdrs});
    if(!r.ok) throw new Error('HTTP '+r.status+' for '+path);
    return r.json();
  }

  function switchTab(name, btn){
    document.querySelectorAll('.tab-content').forEach(el=>el.classList.remove('active'));
    document.querySelectorAll('nav button').forEach(el=>el.classList.remove('active'));
    document.getElementById('tab-'+name).classList.add('active');
    btn.classList.add('active');
  }

  function filterTable(tbodyId, query){
    const rows = document.getElementById(tbodyId).querySelectorAll('tr');
    const q = query.toLowerCase();
    rows.forEach(r=>{r.style.display = r.textContent.toLowerCase().includes(q)?'':'none';});
  }

  function esc(s){
    return String(s||'').replace(/&/g,'&amp;').replace(/</g,'&lt;').replace(/>/g,'&gt;');
  }

  function badge(text, cls){ return `<span class="badge badge-${cls}">${esc(text)}</span>`; }

  async function loadAll(){
    document.getElementById('loadingOverlay').classList.remove('hidden');
    try {
      const [metrics, bans, players, warns, appeals, audit] = await Promise.allSettled([
        apiFetch('/metrics'),
        apiFetch('/bans/all'),
        apiFetch('/players'),
        apiFetch('/warnings'),
        apiFetch('/appeals'),
        apiFetch('/audit'),
      ]);

      // Stats row
      if(metrics.status==='fulfilled'){
        const m = metrics.value;
        const cards = [
          ['Active Bans', m.activeBans, 'red'],
          ['Total Bans', m.totalBans, 'blue'],
          ['Warnings', m.totalWarnings, 'yellow'],
          ['Players', m.knownPlayers, 'green'],
          ['Online', m.onlinePlayers, 'green'],
          ['Appeals', m.pendingAppeals||0, 'yellow'],
        ];
        document.getElementById('statsRow').innerHTML = cards.map(([l,v,c])=>
          `<div class="stat-card"><div class="num" style="color:${c==='red'?'#fca5a5':c==='yellow'?'#fde68a':'#a7f3d0'}">${v}</div><div class="lbl">${l}</div></div>`
        ).join('');
      }

      // Bans
      if(bans.status==='fulfilled'){
        const rows = (bans.value.bans||[]).map(b=>
          `<tr><td>${esc(b.uid)}</td><td>${esc(b.playerName)}</td><td>${esc(b.reason)}</td><td>${esc(b.bannedBy)}</td>
           <td>${b.isPermanent?badge('Permanent','red'):esc(b.expireDate)}</td>
           <td>${b.isPermanent?badge('Permanent','red'):badge('Temp','yellow')}</td></tr>`).join('');
        document.getElementById('banTable').innerHTML = rows || '<tr><td colspan="6" style="text-align:center;color:#9ca3af">No active bans</td></tr>';
      }

      // Players
      if(players.status==='fulfilled'){
        const rows = (players.value.players||[]).map(p=>
          `<tr><td>${esc(p.uid)}</td><td>${esc(p.displayName)}</td><td>${esc(p.lastSeen)}</td><td>${esc(p.ipAddress||'')}</td></tr>`).join('');
        document.getElementById('playerTable').innerHTML = rows || '<tr><td colspan="4" style="text-align:center;color:#9ca3af">No players</td></tr>';
      }

      // Warnings
      if(warns.status==='fulfilled'){
        const rows = (warns.value.warnings||[]).map(w=>
          `<tr><td>${w.id}</td><td>${esc(w.uid)}</td><td>${esc(w.playerName)}</td><td>${esc(w.reason)}</td><td>${esc(w.warnedBy)}</td><td>${esc(w.warnDate)}</td></tr>`).join('');
        document.getElementById('warnTable').innerHTML = rows || '<tr><td colspan="6" style="text-align:center;color:#9ca3af">No warnings</td></tr>';
      }

      // Appeals
      if(appeals.status==='fulfilled'){
        const rows = (appeals.value.appeals||[]).map(a=>
          `<tr><td>${a.id}</td><td>${esc(a.uid)}</td><td>${esc(a.contactInfo)}</td><td>${esc(a.submittedAt)}</td><td>${esc(a.reason)}</td></tr>`).join('');
        document.getElementById('appealTable').innerHTML = rows || '<tr><td colspan="5" style="text-align:center;color:#9ca3af">No pending appeals</td></tr>';
      }

      // Audit log
      if(audit.status==='fulfilled'){
        const rows = (audit.value.entries||[]).slice(0,200).map(e=>
          `<tr><td>${esc(e.timestamp)}</td><td>${badge(e.action,'blue')}</td><td>${esc(e.targetName||e.targetUid)}</td><td>${esc(e.adminName||'')}</td><td>${esc(e.details||'')}</td><td>${esc(e.modVersion||'')}</td></tr>`).join('');
        document.getElementById('auditTable').innerHTML = rows || '<tr><td colspan="6" style="text-align:center;color:#9ca3af">No audit entries</td></tr>';
      }

      // Metrics detail
      if(metrics.status==='fulfilled'){
        const m = metrics.value;
        let html = '<table><thead><tr><th>Metric</th><th>Value</th></tr></thead><tbody>';
        const items = [
          ['Active Bans', m.activeBans], ['Total Bans', m.totalBans],
          ['Temp Bans Expiring (24h)', m.tempBansExpiringSoon24h],
          ['Total Warnings', m.totalWarnings], ['Warnings This Week', m.warningsThisWeek],
          ['Audit Entries', m.totalAuditEntries], ['Known Players', m.knownPlayers],
          ['Online Players', m.onlinePlayers], ['Timestamp', m.timestamp],
        ];
        items.forEach(([l,v])=>{ html += `<tr><td>${esc(l)}</td><td>${esc(v)}</td></tr>`; });
        html += '</tbody></table>';
        if(m.topOffenders&&m.topOffenders.length){
          html += '<h3 style="margin-top:20px;color:#c4b5fd">Top Offenders</h3><table style="margin-top:8px"><thead><tr><th>Player</th><th>Ban Count</th></tr></thead><tbody>';
          m.topOffenders.forEach(o=>{ html += `<tr><td>${esc(o.playerName)} <small style="color:#9ca3af">${esc(o.uid)}</small></td><td>${o.banCount}</td></tr>`; });
          html += '</tbody></table>';
        }
        document.getElementById('metricsContent').innerHTML = html;
      }

    } catch(e){
      document.getElementById('errorMsg').textContent = 'Error loading data: '+e.message;
    } finally {
      document.getElementById('loadingOverlay').classList.add('hidden');
    }
  }

  loadAll();
</script>
</body>
</html>)HTML");

            auto R = FHttpServerResponse::Create(Html, TEXT("text/html; charset=utf-8"));
            R->Code = EHttpServerResponseCodes::Ok;
            Done(MoveTemp(R));
            return true;
        }
    ));

    // ── PATCH /appeals/:id ───────────────────────────────────────────────────
    // Review (approve or deny) a pending appeal.
    // Body: { "status": "approved"|"denied", "reviewedBy": "adminname", "reviewNote": "..." }
    Routes->Handles.Add(Router->BindRoute(
        FHttpPath(TEXT("/appeals/:id")),
        EHttpServerRequestVerbs::VERB_PATCH,
        [WeakGI](const FHttpServerRequest& Req, const FHttpResultCallback& Done) -> bool
        {
            if (!BanJson::CheckApiKey(Req)) { Done(BanJson::Error(TEXT("Unauthorized"), EHttpServerResponseCodes::Denied)); return true; }
            if (auto SizeErr = BanJson::CheckBodySize(Req)) { Done(MoveTemp(SizeErr)); return true; }

            const FString IdStr = Req.PathParams.FindRef(TEXT("id"));
            int64 Id = 0;
            if (!BanJson::ParseInt64Param(IdStr, Id))
            {
                Done(BanJson::Error(TEXT("Invalid appeal ID"), EHttpServerResponseCodes::BadRequest));
                return true;
            }

            UGameInstance* GI = WeakGI.Get();
            if (!GI) { Done(BanJson::Error(TEXT("Server shutting down"), EHttpServerResponseCodes::ServiceUnavail)); return true; }
            UBanAppealRegistry* AppealsReg = GI->GetSubsystem<UBanAppealRegistry>();
            if (!AppealsReg) { Done(BanJson::Error(TEXT("AppealRegistry unavailable"), EHttpServerResponseCodes::ServerError)); return true; }

            const FString BodyStr = BanJson::BodyToString(Req);
            TSharedPtr<FJsonObject> Body;
            TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(BodyStr);
            if (!FJsonSerializer::Deserialize(Reader, Body) || !Body.IsValid())
            {
                Done(BanJson::Error(TEXT("Invalid JSON body")));
                return true;
            }

            FString StatusStr, ReviewedBy, ReviewNote;
            if (!Body->TryGetStringField(TEXT("status"), StatusStr) || StatusStr.IsEmpty())
            {
                Done(BanJson::Error(TEXT("status is required (\"approved\" or \"denied\")")));
                return true;
            }
            Body->TryGetStringField(TEXT("reviewedBy"), ReviewedBy);
            Body->TryGetStringField(TEXT("reviewNote"), ReviewNote);

            const FString Norm = StatusStr.ToLower();
            EAppealStatus NewStatus;
            if (Norm == TEXT("approved"))      NewStatus = EAppealStatus::Approved;
            else if (Norm == TEXT("denied"))   NewStatus = EAppealStatus::Denied;
            else
            {
                Done(BanJson::Error(TEXT("status must be \"approved\" or \"denied\"")));
                return true;
            }

            if (!AppealsReg->ReviewAppeal(Id, NewStatus, ReviewedBy, ReviewNote))
            {
                Done(BanJson::Error(
                    FString::Printf(TEXT("No appeal found with id %lld"), Id),
                    EHttpServerResponseCodes::NotFound));
                return true;
            }

            // If approved, auto-unban the player.
            if (NewStatus == EAppealStatus::Approved)
            {
                const FBanAppealEntry Appeal = AppealsReg->GetAppealById(Id);
                if (!Appeal.Uid.IsEmpty())
                {
                    UBanDatabase* DB = GI->GetSubsystem<UBanDatabase>();
                    if (DB)
                    {
                        // Use the atomic RemoveBanByUid overload to capture the ban
                        // entry and delete it in a single mutex scope, eliminating the
                        // TOCTOU window that exists when GetBanByUid and RemoveBanByUid
                        // are called as two separate operations.
                        FBanEntry RemovedBan;
                        if (DB->RemoveBanByUid(Appeal.Uid, RemovedBan))
                        {
                            const FString PlayerName = RemovedBan.PlayerName.IsEmpty() ? Appeal.Uid : RemovedBan.PlayerName;
                            FBanDiscordNotifier::NotifyBanRemoved(Appeal.Uid, PlayerName, ReviewedBy);
                            if (UBanAuditLog* AuditLog = GI->GetSubsystem<UBanAuditLog>())
                                AuditLog->LogAction(TEXT("unban"), Appeal.Uid, PlayerName, ReviewedBy, ReviewedBy,
                                    FString::Printf(TEXT("Appeal #%lld approved: %s"), Id, *ReviewNote));
                        }
                    }
                }
            }

            if (UBanAuditLog* AuditLog = GI->GetSubsystem<UBanAuditLog>())
                AuditLog->LogAction(TEXT("appeal_review"),
                    FString::Printf(TEXT("appeal#%lld"), Id), TEXT(""),
                    ReviewedBy, ReviewedBy,
                    FString::Printf(TEXT("status=%s note=%s"), *Norm, *ReviewNote));

            Done(BanJson::Ok(
                FString::Printf(TEXT("Appeal #%lld %s"), Id, *Norm)));
            return true;
        }
    ));

    // ── GET /scheduled ───────────────────────────────────────────────────────
    Routes->Handles.Add(Router->BindRoute(
        FHttpPath(TEXT("/scheduled")),
        EHttpServerRequestVerbs::VERB_GET,
        [WeakGI](const FHttpServerRequest& Req, const FHttpResultCallback& Done) -> bool
        {
            if (!BanJson::CheckApiKey(Req)) { Done(BanJson::Error(TEXT("Unauthorized"), EHttpServerResponseCodes::Denied)); return true; }

            UGameInstance* GI = WeakGI.Get();
            if (!GI) { Done(BanJson::Error(TEXT("Server shutting down"), EHttpServerResponseCodes::ServiceUnavail)); return true; }
            UScheduledBanRegistry* SchReg = GI->GetSubsystem<UScheduledBanRegistry>();
            if (!SchReg) { Done(BanJson::Error(TEXT("ScheduledBanRegistry unavailable"), EHttpServerResponseCodes::ServerError)); return true; }

            TArray<FScheduledBanEntry> Pending = SchReg->GetAllPending();
            TArray<TSharedPtr<FJsonValue>> Arr;
            Arr.Reserve(Pending.Num());
            for (const FScheduledBanEntry& S : Pending)
                Arr.Add(MakeShared<FJsonValueObject>(BanJson::ScheduledToJson(S)));

            TSharedPtr<FJsonObject> Root = MakeShared<FJsonObject>();
            Root->SetNumberField(TEXT("count"),     static_cast<double>(Pending.Num()));
            Root->SetArrayField (TEXT("scheduled"), Arr);
            Done(BanJson::Json(BanJson::ObjectToString(Root)));
            return true;
        }
    ));

    // ── POST /scheduled ──────────────────────────────────────────────────────
    // Body: { "uid", "playerName", "reason", "scheduledBy", "effectiveAt" (ISO8601),
    //         "durationMinutes" (0=permanent), "category" (optional) }
    Routes->Handles.Add(Router->BindRoute(
        FHttpPath(TEXT("/scheduled")),
        EHttpServerRequestVerbs::VERB_POST,
        [WeakGI](const FHttpServerRequest& Req, const FHttpResultCallback& Done) -> bool
        {
            if (!BanJson::CheckApiKey(Req)) { Done(BanJson::Error(TEXT("Unauthorized"), EHttpServerResponseCodes::Denied)); return true; }
            if (auto SizeErr = BanJson::CheckBodySize(Req)) { Done(MoveTemp(SizeErr)); return true; }

            UGameInstance* GI = WeakGI.Get();
            if (!GI) { Done(BanJson::Error(TEXT("Server shutting down"), EHttpServerResponseCodes::ServiceUnavail)); return true; }
            UScheduledBanRegistry* SchReg = GI->GetSubsystem<UScheduledBanRegistry>();
            if (!SchReg) { Done(BanJson::Error(TEXT("ScheduledBanRegistry unavailable"), EHttpServerResponseCodes::ServerError)); return true; }

            const FString BodyStr = BanJson::BodyToString(Req);
            TSharedPtr<FJsonObject> Body;
            TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(BodyStr);
            if (!FJsonSerializer::Deserialize(Reader, Body) || !Body.IsValid())
            {
                Done(BanJson::Error(TEXT("Invalid JSON body")));
                return true;
            }

            FString Uid, PlayerName, Reason, ScheduledBy, EffectiveAtStr, Category;
            if (!Body->TryGetStringField(TEXT("uid"), Uid) || Uid.IsEmpty())
            {
                Done(BanJson::Error(TEXT("uid is required")));
                return true;
            }
            Body->TryGetStringField(TEXT("playerName"),  PlayerName);
            Body->TryGetStringField(TEXT("reason"),      Reason);
            Body->TryGetStringField(TEXT("scheduledBy"), ScheduledBy);
            Body->TryGetStringField(TEXT("effectiveAt"), EffectiveAtStr);
            Body->TryGetStringField(TEXT("category"),    Category);

            if (Reason.IsEmpty())      Reason      = TEXT("Scheduled ban");
            if (ScheduledBy.IsEmpty()) ScheduledBy = TEXT("api");

            FDateTime EffectiveAt = FDateTime::UtcNow() + FTimespan::FromMinutes(5.0);
            if (!EffectiveAtStr.IsEmpty() && !FDateTime::ParseIso8601(*EffectiveAtStr, EffectiveAt))
            {
                Done(BanJson::Error(TEXT("effectiveAt must be a valid ISO 8601 datetime")));
                return true;
            }

            double DurDbl = 0.0;
            Body->TryGetNumberField(TEXT("durationMinutes"), DurDbl);
            const int32 DurationMinutes = (DurDbl <= 0.0 || DurDbl > static_cast<double>(INT_MAX))
                ? 0 : static_cast<int32>(DurDbl);

            const FScheduledBanEntry NewEntry = SchReg->AddScheduled(
                Uid, PlayerName, Reason, ScheduledBy, EffectiveAt, DurationMinutes, Category);

            if (UBanAuditLog* AuditLog = GI->GetSubsystem<UBanAuditLog>())
                AuditLog->LogAction(TEXT("schedule_ban"), Uid, PlayerName,
                    ScheduledBy, ScheduledBy,
                    FString::Printf(TEXT("effectiveAt=%s reason=%s"), *EffectiveAt.ToIso8601(), *Reason));

            auto Resp = BanJson::Json(BanJson::ObjectToString(BanJson::ScheduledToJson(NewEntry)));
            Resp->Code = EHttpServerResponseCodes::Created;
            Done(MoveTemp(Resp));
            return true;
        }
    ));

    // ── DELETE /scheduled/:id ────────────────────────────────────────────────
    Routes->Handles.Add(Router->BindRoute(
        FHttpPath(TEXT("/scheduled/:id")),
        EHttpServerRequestVerbs::VERB_DELETE,
        [WeakGI](const FHttpServerRequest& Req, const FHttpResultCallback& Done) -> bool
        {
            if (!BanJson::CheckApiKey(Req)) { Done(BanJson::Error(TEXT("Unauthorized"), EHttpServerResponseCodes::Denied)); return true; }
            if (auto SizeErr = BanJson::CheckBodySize(Req)) { Done(MoveTemp(SizeErr)); return true; }

            const FString IdStr = Req.PathParams.FindRef(TEXT("id"));
            int64 Id = 0;
            if (!BanJson::ParseInt64Param(IdStr, Id))
            {
                Done(BanJson::Error(TEXT("Invalid scheduled ban ID"), EHttpServerResponseCodes::BadRequest));
                return true;
            }

            UGameInstance* GI = WeakGI.Get();
            if (!GI) { Done(BanJson::Error(TEXT("Server shutting down"), EHttpServerResponseCodes::ServiceUnavail)); return true; }
            UScheduledBanRegistry* SchReg = GI->GetSubsystem<UScheduledBanRegistry>();
            if (!SchReg) { Done(BanJson::Error(TEXT("ScheduledBanRegistry unavailable"), EHttpServerResponseCodes::ServerError)); return true; }

            if (!SchReg->DeleteScheduled(Id))
            {
                Done(BanJson::Error(
                    FString::Printf(TEXT("No scheduled ban found with id %lld"), Id),
                    EHttpServerResponseCodes::NotFound));
                return true;
            }

            Done(BanJson::Ok(FString::Printf(TEXT("Scheduled ban #%lld cancelled"), Id)));
            return true;
        }
    ));

    // ── GET /reputation/:uid ─────────────────────────────────────────────────
    // Returns a reputation summary: warnings, bans, kicks, first/last seen,
    // computed score.
    Routes->Handles.Add(Router->BindRoute(
        FHttpPath(TEXT("/reputation/:uid")),
        EHttpServerRequestVerbs::VERB_GET,
        [WeakGI](const FHttpServerRequest& Req, const FHttpResultCallback& Done) -> bool
        {
            if (!BanJson::CheckApiKey(Req)) { Done(BanJson::Error(TEXT("Unauthorized"), EHttpServerResponseCodes::Denied)); return true; }
            const FString RawUid = Req.PathParams.FindRef(TEXT("uid"));
            const FString Uid    = FGenericPlatformHttp::UrlDecode(RawUid);

            UGameInstance* GI = WeakGI.Get();
            if (!GI) { Done(BanJson::Error(TEXT("Server shutting down"), EHttpServerResponseCodes::ServiceUnavail)); return true; }

            UBanDatabase*           DB        = GI->GetSubsystem<UBanDatabase>();
            UPlayerWarningRegistry* WarnReg   = GI->GetSubsystem<UPlayerWarningRegistry>();
            UPlayerSessionRegistry* PlayerReg = GI->GetSubsystem<UPlayerSessionRegistry>();
            UBanAuditLog*           AuditLog  = GI->GetSubsystem<UBanAuditLog>();

            // Warning count and points.
            const int32 WarnCount  = WarnReg  ? WarnReg->GetWarningCount(Uid)  : 0;
            const int32 WarnPoints = WarnReg  ? WarnReg->GetWarningPoints(Uid) : 0;

            // Historical ban count (all bans, including expired).
            int32 TotalBans = 0;
            bool  bCurrentlyBanned = false;
            if (DB)
            {
                for (const FBanEntry& B : DB->GetAllBans())
                {
                    // MatchesUid checks both primary Uid and LinkedUids so that
                    // compound bans (EOS + IP) are counted for either identifier.
                    if (B.MatchesUid(Uid))
                    {
                        ++TotalBans;
                        if (!B.IsExpired()) bCurrentlyBanned = true;
                    }
                }
            }

            // Kick count from audit log.
            int32 KickCount = 0;
            if (AuditLog)
            {
                for (const FAuditEntry& E : AuditLog->GetEntriesForTarget(Uid))
                {
                    if (E.Action == TEXT("kick")) ++KickCount;
                }
            }

            // Session info.
            FString DisplayName, LastSeen;
            if (PlayerReg)
            {
                FPlayerSessionRecord Rec;
                if (PlayerReg->FindByUid(Uid, Rec))
                {
                    DisplayName = Rec.DisplayName;
                    LastSeen    = Rec.LastSeen;
                }
            }

            // Simple reputation score: 100 minus deductions.
            // Deductions: -5 per warn point, -15 per ban, -3 per kick.
            const int32 Score = FMath::Max(0,
                100 - (WarnPoints * 5) - (TotalBans * 15) - (KickCount * 3));

            TSharedPtr<FJsonObject> Obj = MakeShared<FJsonObject>();
            Obj->SetStringField(TEXT("uid"),             Uid);
            Obj->SetStringField(TEXT("displayName"),     DisplayName);
            Obj->SetStringField(TEXT("lastSeen"),        LastSeen);
            Obj->SetNumberField(TEXT("warnCount"),       static_cast<double>(WarnCount));
            Obj->SetNumberField(TEXT("warnPoints"),      static_cast<double>(WarnPoints));
            Obj->SetNumberField(TEXT("totalBans"),       static_cast<double>(TotalBans));
            Obj->SetBoolField  (TEXT("currentlyBanned"), bCurrentlyBanned);
            Obj->SetNumberField(TEXT("kickCount"),       static_cast<double>(KickCount));
            Obj->SetNumberField(TEXT("reputationScore"), static_cast<double>(Score));
            Done(BanJson::Json(BanJson::ObjectToString(Obj)));
            return true;
        }
    ));

    // ── POST /bans/bulk ──────────────────────────────────────────────────────
    // Body: { "uids": ["EOS:xxx", ...], "reason": "...", "bannedBy": "...",
    //         "durationMinutes": 0, "category": "" }
    Routes->Handles.Add(Router->BindRoute(
        FHttpPath(TEXT("/bans/bulk")),
        EHttpServerRequestVerbs::VERB_POST,
        [WeakGI](const FHttpServerRequest& Req, const FHttpResultCallback& Done) -> bool
        {
            if (!BanJson::CheckApiKey(Req)) { Done(BanJson::Error(TEXT("Unauthorized"), EHttpServerResponseCodes::Denied)); return true; }
            if (auto SizeErr = BanJson::CheckBodySize(Req)) { Done(MoveTemp(SizeErr)); return true; }

            UGameInstance* GI = WeakGI.Get();
            if (!GI) { Done(BanJson::Error(TEXT("Server shutting down"), EHttpServerResponseCodes::ServiceUnavail)); return true; }
            UBanDatabase* DB = GI->GetSubsystem<UBanDatabase>();
            if (!DB) { Done(BanJson::Error(TEXT("Database unavailable"), EHttpServerResponseCodes::ServerError)); return true; }

            const FString BodyStr = BanJson::BodyToString(Req);
            TSharedPtr<FJsonObject> Body;
            TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(BodyStr);
            if (!FJsonSerializer::Deserialize(Reader, Body) || !Body.IsValid())
            {
                Done(BanJson::Error(TEXT("Invalid JSON body")));
                return true;
            }

            const TArray<TSharedPtr<FJsonValue>>* UidsArr = nullptr;
            if (!Body->TryGetArrayField(TEXT("uids"), UidsArr) || !UidsArr || UidsArr->IsEmpty())
            {
                Done(BanJson::Error(TEXT("uids array is required and must be non-empty")));
                return true;
            }

            FString Reason, BannedBy, Category;
            Body->TryGetStringField(TEXT("reason"),   Reason);
            Body->TryGetStringField(TEXT("bannedBy"), BannedBy);
            Body->TryGetStringField(TEXT("category"), Category);
            if (Reason.IsEmpty())   Reason   = TEXT("Bulk ban");
            if (BannedBy.IsEmpty()) BannedBy = TEXT("api");

            double DurDbl = 0.0;
            Body->TryGetNumberField(TEXT("durationMinutes"), DurDbl);
            const int32 DurationMinutes = (DurDbl <= 0.0 || DurDbl > static_cast<double>(INT_MAX))
                ? 0 : static_cast<int32>(DurDbl);

            int32 Added = 0;
            TArray<TSharedPtr<FJsonValue>> ResultArr;
            // Capture a single timestamp for the entire batch so all entries share
            // the same BanDate/ExpireDate regardless of how long the loop takes.
            const FDateTime BatchBanNow = FDateTime::UtcNow();

            for (const TSharedPtr<FJsonValue>& Val : *UidsArr)
            {
                FString Uid;
                if (!Val.IsValid() || !Val->TryGetString(Uid) || Uid.IsEmpty()) continue;

                FBanEntry Ban;
                Ban.Uid        = Uid;
                UBanDatabase::ParseUid(Uid, Ban.Platform, Ban.PlayerUID);
                Ban.PlayerName      = TEXT("");
                Ban.Reason          = Reason;
                Ban.BannedBy        = BannedBy;
                Ban.BanDate         = BatchBanNow;
                Ban.Category        = Category;
                Ban.bIsPermanent    = (DurationMinutes <= 0);
                Ban.ExpireDate      = Ban.bIsPermanent
                    ? FDateTime(0)
                    : BatchBanNow + FTimespan::FromMinutes(DurationMinutes);

                if (DB->AddBan(Ban))
                {
                    FBanDiscordNotifier::NotifyBanCreated(Ban);
                    if (UBanAuditLog* AuditLog = GI->GetSubsystem<UBanAuditLog>())
                        AuditLog->LogAction(TEXT("ban"), Uid, TEXT(""), BannedBy, BannedBy, Reason);
                    // Kick the player if currently online.
                    if (UWorld* World = GI->GetWorld())
                        UBanEnforcer::KickConnectedPlayer(World, Uid, Ban.GetKickMessage());
                    ResultArr.Add(MakeShared<FJsonValueObject>(BanJson::EntryToJson(Ban)));
                    ++Added;
                }
            }

            TSharedPtr<FJsonObject> Root = MakeShared<FJsonObject>();
            Root->SetNumberField(TEXT("banned"), static_cast<double>(Added));
            Root->SetArrayField (TEXT("bans"),   ResultArr);
            auto Resp = BanJson::Json(BanJson::ObjectToString(Root));
            Resp->Code = EHttpServerResponseCodes::Created;
            Done(MoveTemp(Resp));
            return true;
        }
    ));

    // ── DELETE /bans/bulk ────────────────────────────────────────────────────
    // Body: { "uids": ["EOS:xxx", ...] }
    Routes->Handles.Add(Router->BindRoute(
        FHttpPath(TEXT("/bans/bulk")),
        EHttpServerRequestVerbs::VERB_DELETE,
        [WeakGI](const FHttpServerRequest& Req, const FHttpResultCallback& Done) -> bool
        {
            if (!BanJson::CheckApiKey(Req)) { Done(BanJson::Error(TEXT("Unauthorized"), EHttpServerResponseCodes::Denied)); return true; }
            if (auto SizeErr = BanJson::CheckBodySize(Req)) { Done(MoveTemp(SizeErr)); return true; }

            UGameInstance* GI = WeakGI.Get();
            if (!GI) { Done(BanJson::Error(TEXT("Server shutting down"), EHttpServerResponseCodes::ServiceUnavail)); return true; }
            UBanDatabase* DB = GI->GetSubsystem<UBanDatabase>();
            if (!DB) { Done(BanJson::Error(TEXT("Database unavailable"), EHttpServerResponseCodes::ServerError)); return true; }

            const FString BodyStr = BanJson::BodyToString(Req);
            TSharedPtr<FJsonObject> Body;
            TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(BodyStr);
            if (!FJsonSerializer::Deserialize(Reader, Body) || !Body.IsValid())
            {
                Done(BanJson::Error(TEXT("Invalid JSON body")));
                return true;
            }

            const TArray<TSharedPtr<FJsonValue>>* UidsArr = nullptr;
            if (!Body->TryGetArrayField(TEXT("uids"), UidsArr) || !UidsArr || UidsArr->IsEmpty())
            {
                Done(BanJson::Error(TEXT("uids array is required")));
                return true;
            }

            FString RemovedBy;
            Body->TryGetStringField(TEXT("removedBy"), RemovedBy);
            if (RemovedBy.IsEmpty()) RemovedBy = TEXT("api");

            int32 Removed = 0;
            for (const TSharedPtr<FJsonValue>& Val : *UidsArr)
            {
                FString Uid;
                if (!Val.IsValid() || !Val->TryGetString(Uid) || Uid.IsEmpty()) continue;
                if (DB->RemoveBanByUid(Uid))
                {
                    FBanDiscordNotifier::NotifyBanRemoved(Uid, TEXT(""), RemovedBy);
                    if (UBanAuditLog* AuditLog = GI->GetSubsystem<UBanAuditLog>())
                        AuditLog->LogAction(TEXT("unban"), Uid, TEXT(""), RemovedBy, RemovedBy, TEXT("bulk unban"));
                    ++Removed;
                }
            }

            TSharedPtr<FJsonObject> Root = MakeShared<FJsonObject>();
            Root->SetNumberField(TEXT("unbanned"), static_cast<double>(Removed));
            Done(BanJson::Json(BanJson::ObjectToString(Root)));
            return true;
        }
    ));
}
