// Copyright 2023 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "FGNetConstructionFunctionLibrary.h"

#include "FGOnlineHelpers.generated.h"

UENUM( BlueprintType )
enum class EEosAccountConnectionResult : uint8
{
	Success = 0,
	NoConnecedId,
	SuccessButDifferentAccountConnected, //if we have an epic account logged in that is associated with a different product user ID
	NoConnecedIdButDifferentAccountConnected,
	Error,
	SignedOutEpicUsingSteam,
	Close
};

#define EOS_HANDLE_FORWARD(Type, HandleType) \
struct Type; \
typedef Type* HandleType

#define EOS_STRUCT_FORWARD(StructName) \
struct _tag##StructName; \
typedef _tag##StructName StructName

EOS_HANDLE_FORWARD(EOS_EpicAccountIdDetails, EOS_EpicAccountId);
EOS_HANDLE_FORWARD(EOS_ProductUserIdDetails, EOS_ProductUserId);
EOS_HANDLE_FORWARD(EOS_PlatformHandle, EOS_HPlatform);
EOS_HANDLE_FORWARD(EOS_ConnectHandle, EOS_HConnect);


#define CSS_USER_PRESENCE_SESSION_ID "SES_CSS_SessionId"
#define CSS_USER_PRESENCE_SESSION_ID_L TEXT(CSS_USER_PRESENCE_SESSION_ID)
const FString CSS_USER_PRESENCE_SESSION_ID_STR = CSS_USER_PRESENCE_SESSION_ID_L;

#define CSS_USER_PRESENCE_PRODUCT_ID "SES_CSS_ProductId"
#define CSS_USER_PRESENCE_PRODUCT_ID_L TEXT(CSS_USER_PRESENCE_PRODUCT_ID)
const FString CSS_USER_PRESENCE_PRODUCT_ID_STR = CSS_USER_PRESENCE_PRODUCT_ID_L;

typedef struct EOS_P2PHandle* EOS_HP2P;


typedef struct EOS_ContinuanceTokenDetails* EOS_ContinuanceToken;

EOS_STRUCT_FORWARD(EOS_Connect_QueryExternalAccountMappingsCallbackInfo);
EOS_STRUCT_FORWARD(EOS_P2P_OnQueryNATTypeCompleteInfo);
EOS_STRUCT_FORWARD(EOS_P2P_SocketId);

typedef uint64_t EOS_NotificationId;

#undef EOS_HANDLE_FORWARD
#undef EOS_STRUCT_FORWARD

class IOnlineSubsystem;

class FACTORYGAME_API RefreshEOSConnectionForPlayer
{
public:
	virtual ~RefreshEOSConnectionForPlayer()
	{}
	int32 mLocalPlayerNum;
	FUniqueNetIdWrapper mUserId; //will only be used for future type checks in the CallLoginRefresh, currently we know it's steam
	FString mToken;
	virtual void StartRefreshLogin(IOnlineSubsystem* systemEos) {}
	void CallLoginRefresh(IOnlineSubsystem* systemEos);
};

DECLARE_MULTICAST_DELEGATE_TwoParams( FOnEOSAccountConnectionComplete, EEosAccountConnectionResult, EOS_ContinuanceToken );
typedef FOnEOSAccountConnectionComplete::FDelegate FOnEOSAccountConnectionCompleteDelegate;

DECLARE_MULTICAST_DELEGATE_OneParam(FOnEOSAccountUnlinkComplete, bool);
typedef FOnEOSAccountUnlinkComplete::FDelegate FOnEOSAccountUnlinkCompleteDelegate;

/**
* Helper utilities
*/
class FACTORYGAME_API FEOSAccountHelpers
{
public:
	/**
	* Constructor
	*/
	FEOSAccountHelpers() noexcept(false);

	/**
	* No copying or copy assignment allowed for this class.
	*/
	FEOSAccountHelpers(FEOSAccountHelpers const&) = delete;
	FEOSAccountHelpers& operator=(FEOSAccountHelpers const&) = delete;

	/**
	* Destructor
	*/
	virtual ~FEOSAccountHelpers();

	/**
	* Utility to convert account id to a string.
	* @warning: Next call to this functions will trample the text you got back
	*
	* @param InAccountId - Account id to convert
	*
	* @return String representing account id. Returns string representation of error in case of bad account id.
	*/
	static const TCHAR* EpicAccountIDToString(EOS_EpicAccountId InAccountId);
	// @warning: Next call to this functions will trample the text you got back
	static const TCHAR* ProductUserIDToString(EOS_ProductUserId InAccountId);


	////Functions related to logging in/connecting a user to EOS

	/** ConnectAccount
	* Connect and add a local user to EOS. The onComplete will be called once we know the result.
	  The given enum should be Success, otherwise further action is likely needed. The functions below here should then likely be used.
	* @param worldContext - used to fetch the correct OSS.
	* @param LocalUserNum - The local number of the user. Will be used to compare the user to a potentially existing Epic account login, or for adding this user to an EOS mapping
	* @param userId - The net ID of the user to add. //Currently only supports steam.
	* @param token - The token needed by EOS for the given platform. Check the EOS documentation for that. Needs to be in string form.
	* @param onComplete - Delegate called with the result, as this is an asynchronous function
	*/
	static void ConnectAccount(UObject* worldContext, int32 LocalUserNum, TSharedRef<const FUniqueNetId> userId, FString token, const FOnEOSAccountConnectionCompleteDelegate& onComplete);
	
	/** ConnectLinkAccountToExistingEOSAccount
	* Can only be called after getting an EOS_ContinuanceToken in a reply from ConnectAccount and when told another EOS account existed but the new user didn't have a connection.

	* @param onComplete - should expect to get a success here, but can be an error if input parameters were bad or the EOS backend failed. Check log in that case for more info.
	*/
	static void ConnectLinkAccountToExistingEOSAccount(UObject* worldContext, int32 LocalUserNum, EOS_ContinuanceToken token, const FOnEOSAccountConnectionCompleteDelegate& onComplete);
	
	/** CreateNewAccountConnection
	*  Can only be called after getting an EOS_ContinuanceToken in a reply from ConnectAccount and when told there were no eos connect account logged in and the current one was not connected

	* @param onComplete - should expect to get a success here, but can be an error if input parameters were bad or the EOS backend failed. Check log in that case for more info.
	*/
	static void CreateNewAccountConnection(UObject* worldContext, int32 LocalUserNum, TSharedRef<const FUniqueNetId> userId, EOS_ContinuanceToken token, const FOnEOSAccountConnectionCompleteDelegate& onComplete);
	
	/** LogoutAndForgetPresistent
	* will log out a persistent token for an Epic account and forget that token. Stopping future startups for automatically log in. Will also remove the local user from the OSS.
	*/
	static void LogoutAndForgetPresistent(UObject* worldContext, int32 LocalUserNum);

	/** 
	* Will unlink the given userid from it's current PUID
	*/
	static void UnlinkAccount(UObject* worldContext, TSharedRef<const FUniqueNetId> userId, const FOnEOSAccountUnlinkCompleteDelegate& onComplete);
	
	//Should be called in the end as part of the login process and after the ConnectAccount is finished. Will add the product user ID to the user's presence.
	static void AddIdentificationToPresence(UObject* worldContext, TSharedRef<const FUniqueNetId> userId, TSharedPtr<class FOnlineUserPresence> presnce);

	/** GetProductUserId
	* Gets the product user ID. Wraps logic to get it directly from the EOS mapping if it's an EOS ID, otherwise getting it from the presence of the appropriate OSS.
	* Assuming it was setup with the AddIdentificationToPresence above. Should work even for EOS IDs when the epic account is invalid.

	* @param id - net ID to get the product ID from
	*/
	static FString GetProductUserId(const FUniqueNetId& id);

	//static void RefreshConnection(UObject* worldContext, int32 LocalUserNum, TSharedRef<const FUniqueNetId> userId, FString token, const FOnEOSAccountConnectionCompleteDelegate& onComplete);
	static void SetupLoginRefreshForUser(UObject* worldContext, RefreshEOSConnectionForPlayer* refreshObj);


	//Pure Wrapper functions for the different IDs that make up en EOS UniqueNetID
	static bool ProductUserIDIsValid(EOS_ProductUserId ProductUserId);
	static bool EpicAccountIDIsValid(EOS_EpicAccountId InAccountId);

	//used to cehck if a net ID is EOS, and if it is, if it's also fully complete with an Epic account. 
	//If not, it might actually be of an non epic type and require lookup with the product user ID to find the real net ID.
	//Usually only used when we get an ID from an invatation or similar, that we don't have an EOS mapping for.
	static bool IsNetIDEpicAccountIDValid(const FUniqueNetId& id);

	//Used to get a session ID from a users presence. Users should update their presence to include this ID while in a session, and empty it out when not.
	//@TODO:[Gafgar:Thu/02-07-2020] we should probably make a function for updating/adding this to a presence, 
	//so we don't rely on users to do this, and make all this local to here. Meaning it will be easier to track bugs and update.
	static bool GetCssEosSessionIdFromPresence(TSharedPtr<class FOnlineUserPresence> presnce, FString& out_buffer);
	static bool GetCssEosSessionIdFromPresence(const class FOnlineUserPresence& presnce, FString& out_buffer);

};

struct FACTORYGAME_API EOSId
{
	static bool GetProductUserId( const FUniqueNetId& netId, FString& out_ProductUserIdString );
	static bool GetEpicUserId( const FUniqueNetId& netId, FString& out_EpicUserIdString );
};


