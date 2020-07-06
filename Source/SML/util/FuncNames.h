#pragma once
/**
 * Contains defines of the function signatures used for hooking
 * Keep in one place for easier updating and avoid string duplication
 */
/** UFGGameInstance::LoadComplete */
#define GAME_INSTANCE_LOAD_COMPLETE_FUNC_DESC "?LoadComplete@UFGGameInstance@@MEAAXMAEBVFString@@@Z"
/** AFGPlayerController::BeginPlay */
#define PLAYER_CONTROLLER_BEGIN_PLAY_FUNC_DESC "?BeginPlay@AFGPlayerController@@UEAAXXZ"
/* AFGPlayerController::EnterChatMessage */
#define ENTER_CHAT_MESSAGE_FUNC_DESC "?EnterChatMessage@AFGPlayerController@@IEAAXAEBVFString@@@Z"
/** UEngine::Browse */
#define ENGINE_BROWSE_MAP_FUNC_DESC "?Browse@UEngine@@UEAA?AW4Type@EBrowseReturnVal@@AEAUFWorldContext@@UFURL@@AEAVFString@@@Z"
/** AGameState::ReceiveGameModeClass */
#define GAME_STATE_RECEIVE_GAME_MODE_CLASS_FUNC_DESC "?ReceivedGameModeClass@AGameState@@UEAAXXZ"
/** AGameModeBase::PreLogin */
#define GAME_MODE_PRE_LOGIN_FUNC_DESC "?PreLogin@AGameModeBase@@UEAAXAEBVFString@@0AEBUFUniqueNetIdRepl@@AEAV2@@Z"
/** AFGGameState::Init */
#define FG_GAME_STATE_INIT_FUNC_DESC "?Init@AFGGameState@@UEAAXXZ"

/** FWindowsPlatformStackWalk::GetDownstreamStorage */
#define WIN_STACK_WALK_GET_DOWNSTREAM_STORAGE_FUNC_DESC "?GetDownstreamStorage@FWindowsPlatformStackWalk@@SA?AVFString@@XZ"
/** FGenericCrashContext::AddPortableCallStack */
#define CRASH_CONTEXT_ADD_CALL_STACK_FUNC_DESC "?AddPortableCallStack@FGenericCrashContext@@AEBAXXZ"
class FGenericCrashContextProto { public: void AddPortableCallStack() {} };