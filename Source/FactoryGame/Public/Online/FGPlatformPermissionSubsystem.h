// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"
#include "FGGameState.h"
#include "Interfaces/OnlineExternalUIInterface.h"
#include "LocalUserInfo.h"
#include "Online/CoreOnline.h"
#include "Online/OnlineServices.h"
#include "Subsystems/EngineSubsystem.h"

#if PLATFORM_XSX
#include "Online/AuthOSSAdapter.h"
#include "Online/Privileges.h"
#include "OnlineUserInterfaceGDK.h"
#endif	// PLATFORM_XSX

#include "FGPlatformPermissionSubsystem.generated.h"

struct FLocalUserNetIdBundle;
class AFGPlayerController;
class USessionMemberInformation;
class USessionInformation;

enum class ESessionMemberPlatformType : int8
{
	Unknown = 0,
	PS5,
	Xbox
};

UENUM(BlueprintType)
enum class EPrivilegeCheckResult : uint8
{
	PCR_NoPrivilege = 0,
	PCR_InvalidResult,
	PCR_HasPrivilege,
	PCR_Pending
};

#if PLATFORM_XSX
using PlatformSpecificPermissionType = XblPermission;
#else
using PlatformSpecificPermissionType = uint32_t;
#endif	// PLATFORM_XSX

using FGenericPermissionMap = TMap<EUserPrivilege, EPrivilegeCheckResult>;
using FPerUserPermissionMap = TMap<FAccountId, TMap<PlatformSpecificPermissionType, EPrivilegeCheckResult>>;
using TextPermissionCheckedMap = TMap<FAccountId, EPrivilegeCheckResult>;
using EPrivilegeResults = UE::Online::EPrivilegeResults;
using EOnlineServices = UE::Online::EOnlineServices;
using IPrivilegesPtr = UE::Online::IPrivilegesPtr;

DECLARE_LOG_CATEGORY_EXTERN(LogPlatformPermission, Log, All);

// Broadcasted once the text permission privileges have been updated
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPermissionUpdated);
// Broadcasted when the session member permission map is being updated
DECLARE_MULTICAST_DELEGATE_OneParam(FOnGDKTextPermissionsChecked, TextPermissionCheckedMap isAllowedToReadMap);

DECLARE_DELEGATE_OneParam(FOnPrivilegeQueryDone, EPrivilegeResults privilegeResult);
// Separate delegate for premium checking as blueprints cant digest the EPrivilegeResults enum
DECLARE_DYNAMIC_DELEGATE_OneParam(FUserHasPremiumAccountDelegate, bool, hasPremium);

DECLARE_MULTICAST_DELEGATE_OneParam(FOnPermissionsHaveUpdated, class UFGPlatformPermissionSubsystem* sender);

DECLARE_DYNAMIC_DELEGATE(FPermissionUpdatedDelegate);

UCLASS()
class UPermissionContext : public UObject
{
	GENERATED_BODY()

   public:
	UPermissionContext() = default;

	ULocalUserInfo* pLocalUserInfo;

#if PLATFORM_XSX
	TSharedPtr<const FUniqueNetId> pUserId;
	IOnlineIdentityPtr pIdentityInterface;
	FOnlineUserGDKPtr pUserInterface;
	UE::Online::FAuthOSSAdapterPtr pAuthOSSPtr;
	IPrivilegesPtr pPrivilegePtr;
#elif PLATFORM_PS5
	IPrivilegesPtr pPrivilegePtr;
#endif

	// Creates the permission context, returns true if successful
	bool TryCreatePermissionContext(UWorld* world);

	// Checks for validity of the permission context
	bool IsContextValid() const;
};
/**
 *
 */
UCLASS()
class FACTORYGAME_API UFGPlatformPermissionSubsystem : public ULocalPlayerSubsystem
{
	GENERATED_BODY()

   public:
	////////////////
	// USubsystem
	////////////////
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
	virtual bool ShouldCreateSubsystem(UObject* Outer) const override;
	////////////////
	// ~USubsystem
	////////////////

	////////////////
	// Subsystem Interface
	////////////////
	UFUNCTION(BlueprintCallable, Category = "Permissions")
	bool IsSubsystemReady() const;

	EPrivilegeCheckResult GetTextCommunicationPrivilegeForUser( const UE::Online::FAccountId& LastUGCEditBy ) const;

	UFUNCTION(BlueprintCallable, Category = "Permissions")
	EPrivilegeCheckResult GetCrossplayPrivilege() const;

	UFUNCTION(BlueprintCallable, Category = "Permissions")
	EPrivilegeCheckResult GetUGCPrivilege() const;

	/* On xbox this function does not check if you can read the text of a specific user.
	it is better to use GetTextCommunicationPrivilegeForUser(LastUGCEditBy) for that. BUT only for visibiliyt! Not for
	text entry field validity!
	*/
	UFUNCTION(BlueprintCallable, Category = "Permissions")
	EPrivilegeCheckResult GetTextCommunicationPrivilege() const;

	UFUNCTION(BlueprintCallable, Category = "Permissions")
	EPrivilegeCheckResult GetViewProfilePrivilegeForUser( APlayerState* RequesteePlayerState ) const;
	UFUNCTION(BlueprintCallable, Category = "Permissions")
	EPrivilegeCheckResult GetViewProfilePrivilegeForOfflineUser( const FCachedPlayerInfo& RequesteeCachedPlayerInfo ) const;

	EPrivilegeCheckResult GetViewProfilePrivilegeForUser(const UE::Online::FAccountId& RequesteeAccountId ) const;

	EPrivilegeCheckResult GetViewUGCPrivilegeForUser(const UE::Online::FAccountId& RequesteeAccountId ) const;

	UFUNCTION( BlueprintCallable, Category = "Permissions" )
	EPrivilegeCheckResult GetViewUGCPrivilegeForSessionInfo(const USessionInformation * sessionInfo ) const;

	UPROPERTY(BlueprintAssignable)
	FOnPermissionUpdated OnPermissionUpdated;

	// This function is bindable from blueprint as well as dynamic bindable from c++
	UFUNCTION(BlueprintCallable)
	void PollPremiumPrivilege(FUserHasPremiumAccountDelegate completeDelegate);

	void PollPremiumPrivilegeQueryDone(EPrivilegeResults privilegeResult);

	// These functions is bindable from C++ via lambdas, used to communicate with the local user info.
	void PollPremiumPrivilegeFromCode(FOnPremiumCheckedDone completeDelegate);
	void PollPrivilegeFromCode(EUserPrivilege privilegeToQuery, FOnPrivilegeQueryDone completeDelegate);

	// Is getting called once the permission on the mPermissionMapCache was updated
	FOnGDKTextPermissionsChecked OnGDKTextPermissionChecked;

	// Checks for the privilege value in the local user permission map
	EPrivilegeCheckResult CheckPrivilegeValue( const EUserPrivilege& privilege ) const;

	// Checks if a certain user has a certain right in the mPermissionMapCache
	// Returns true if the user was found in the map, false otherwise
	bool HasUserThisRight( const UE::Online::FAccountId& accountId, const PlatformSpecificPermissionType& privilege,
						   EPrivilegeCheckResult& out_value ) const;

	void NotifyGameStateBeginPlay( AFGGameState* currentGameState );
	////////////////
	// ~Subsystem Interface
	////////////////

   private:
	UPROPERTY()
	TObjectPtr<UPermissionContext> mPermissionContext;

	UPROPERTY()
	TArray<FUserHasPremiumAccountDelegate> mPremiumPollCompleteDelegates;

	struct CrossplayPermissionResult
	{
		bool isFriendTextAllowed;
		bool isAnonymousTextAllowed;
	};

	// This is our user cache that is used for XSX to check if a certain user has a certain permission.
	FPerUserPermissionMap mPermissionMapCache;

	// Contains general permissions like crossplay, ugc, text communication
	FGenericPermissionMap mLocalUserPermissionMap;
	// Used to fill in the crossplay permission for ps5 users in the mPermissionMapCache
	TOptional<CrossplayPermissionResult> mCrossplayTextPermission;
	// Used to fill in the UGC permission for ps5 users in the mPermissionMapCache
	TOptional<CrossplayPermissionResult > mCrossplayUGCPermission;

	////////////////
	// Functions to retrieve permissions or privileges
	////////////////

	#if defined(PLATFORM_XSX) && PLATFORM_XSX
	void RetrieveCrossplayPermission_XSX( TOptional< CrossplayPermissionResult >& buffer, XblPermission permission ) const;
	#endif
	void RetrieveCrossplayPermissions( TOptional< CrossplayPermissionResult >& textCommunicationResult,
										  TOptional< CrossplayPermissionResult >& ugcVisibilityResult ) const;
	void PollUserPrivilege(const EUserPrivilege& PrivilegeToQuery, FOnPrivilegeQueryDone Callback);
	void UpdateBindingsAndPrivileges(UWorld* world);
	void UpdatePrivileges();
	void QueryPermissionInformationForCachedPlayers(const TArray<FCachedPlayerInfo>& gameState);
	void QueryAccountIdList( const TArray< FUniqueNetIdRef >& xboxUserToQuery, const TMap< FUniqueNetIdRef, UE::Online::FAccountId >& xboxUserInfos );
	////////////////
	// ~Functions to retrieve permissions or privileges
	////////////////

	////////////////
	// Delegate bindings
	////////////////
	void BindDelegates();

	UFUNCTION()
	void OnApplicationReactivate();

	UFUNCTION()
	void OnCachedPlayersUpdated( const FPlayerInfoHandle& playerInfoHandle );

	UFUNCTION()
	void OnFriendListUpdated( TArray<FUniqueNetIdRepl> friendList );

	UFUNCTION()
	void OnPostLoadMap(UWorld* world);

	UFUNCTION()
	void OnBackendLoginStatusChanged(ECommonUserLoginStatus loginStatus);


	UFUNCTION()
	// This seems random, but on consoles a virtual keyboard open often causes applications to lose focus. If a focus loss occured due to
	// an open virtual keyboard we don't want to trigger the usual application refocus permission requery
	void OnVirtualKeyboardWasOpened();
	

	////////////////
	// ~Delegate bindings
	////////////////

	////////////////
	// Helper functions
	////////////////
	ESessionMemberPlatformType GetPlatformFromSessionMemberInformation(USessionMemberInformation* sessionMemberInfo) const;
	FUniqueNetIdPtr GetUniqueNetIdFromSessionMemberInformation(USessionMemberInformation* sessionMemberInfo) const;
	UE::Online::FAccountId GetAccountIdFromSessionMemberInformation(USessionMemberInformation* sessionMemberInfo) const;
	EPrivilegeCheckResult PrivilegeResultToCheckResult(EPrivilegeResults privilegeResult) const;
	EPrivilegeCheckResult& GetUserPermissionRef(const UE::Online::FAccountId& accountId, const PlatformSpecificPermissionType& privilege);
	TMap<UE::Online::FAccountId, EPrivilegeCheckResult> GetPrivilgeResutsOfAllUsers(const PlatformSpecificPermissionType& privilege) const;
	////////////////
	// !Helper functions
	////////////////

	
	// Shows the premium shop on ps5
	void DisplayPremiumInformation( const FOnShowStoreUIClosedDelegate& OnShowStoreUIClosedDelegate
									= FOnShowStoreUIClosedDelegate() ) const;

	TWeakObjectPtr<AFGGameState> CurrentGameState;

	bool bSuppressRequeryOnNextReactivate = false;
};
