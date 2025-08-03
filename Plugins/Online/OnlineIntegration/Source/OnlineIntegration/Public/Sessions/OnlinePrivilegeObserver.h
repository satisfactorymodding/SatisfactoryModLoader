// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "MVVMViewModelBase.h"
#include "Auth.h"
#include "OnlineIntegrationTypes.h"
#include "OnlinePrivilegeObserver.generated.h"

class ULocalUserInfo;
class USessionDefinition;
class UOnlineIntegrationBackend;

USTRUCT()
struct ONLINEINTEGRATION_API FCachedPrivilegeResult
{
	GENERATED_BODY()

	FCachedPrivilegeResult() = default;
	FCachedPrivilegeResult(const FCachedPrivilegeResult&) = default;
	FCachedPrivilegeResult(FCachedPrivilegeResult&&) = default;
	
	explicit FCachedPrivilegeResult(ECommonUserPrivilege InPrivilege)
		: Privilege(InPrivilege) {}

	FCachedPrivilegeResult& operator=(const FCachedPrivilegeResult&) = default;
	FCachedPrivilegeResult& operator=(FCachedPrivilegeResult&&) = default;
	
	ECommonUserPrivilege Privilege = ECommonUserPrivilege::Invalid_Count;
	ECommonUserPrivilegeResult Result = ECommonUserPrivilegeResult::Unknown;
	TMap<ECommonUserPrivilegeResult, FText> FailureReasonDescriptions;
};

/**
 * Encapsulates the result of a failed privilege check. Also has references to the backend and the privilege that failed for convenience.
 * Set up as an object so it can be used as a ListView entry. 
 */
UCLASS()
class ONLINEINTEGRATION_API UFailedPrivilegeCheckResult: public UMVVMViewModelBase
{
	GENERATED_BODY()

public:
	void Reset(UOnlineIntegrationBackend* InBackend, ECommonUserPrivilege InPrivilege, ECommonUserPrivilegeResult InResult, const FText& InFailureDescription);
	
	UPROPERTY(BlueprintReadOnly, FieldNotify)
	TObjectPtr<UOnlineIntegrationBackend> Backend;

	UPROPERTY(BlueprintReadOnly, FieldNotify)
	ECommonUserPrivilege Privilege = ECommonUserPrivilege::Invalid_Count;

	UPROPERTY(BlueprintReadOnly, FieldNotify)
	ECommonUserPrivilegeResult Result = ECommonUserPrivilegeResult::Unknown;

	UPROPERTY(BlueprintReadOnly, FieldNotify)
	FText FailureDescription;
};

USTRUCT()
struct ONLINEINTEGRATION_API FCachedPrivilegeSet
{
	GENERATED_BODY()
	
	TArray<FCachedPrivilegeResult> Privileges;
};

/**
 *	An object that keeps track of privilege availability for an arbitrary number of privileges over an arbitrary number of backends, for a specific local user.
 *	Can give a summarized yes/no wrt to the availability of all observed privileges as well as individual results.
 *
 *	This object may be instantiated anywhere for any privilege derived functionality. 
 */
UCLASS()
class ONLINEINTEGRATION_API UOnlinePrivilegeObserver : public UMVVMViewModelBase
{
	GENERATED_BODY()
public:
	/**
	 * Initializes the privilege tracker from a session definition. Specifically, it takes the privilege requirements from the session definition
	 * and tracks them for the given user.
	 */
	void Initialize(ULocalUserInfo* UserInfo, const USessionDefinition* SessionDefinition);

protected:
	void OnBackendLoginStateChanged(ULocalUserInfo* UserInfo, TSharedRef<UE::Online::FAccountInfo> AccountInfo, UOnlineIntegrationBackend* Backend);
	void OnBackendConnectionStateChanged(UObject*, UE::FieldNotification::FFieldId);
	UFUNCTION()
	void OnApplicationReactivated();
	void OnPrivilegeQueryDone(UOnlineIntegrationBackend* Backend, ECommonUserPrivilege Privilege, ECommonUserPrivilegeResult PrivilegeResult);

	void QueryAllPrivilegesForBackend(UOnlineIntegrationBackend* Backend);

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<ULocalUserInfo> UserInfo;
	
	UPROPERTY()
	TMap<TObjectPtr<UOnlineIntegrationBackend>, FCachedPrivilegeSet> RequiredPrivilegesPerBackend;

	/**
	 * A flat list of all failed privilege checks. This will be updated as the privilege checks are completed.
	 */
	UPROPERTY(FieldNotify, BlueprintReadOnly)
	TArray<TObjectPtr<UFailedPrivilegeCheckResult>> FailedPrivilegeChecks;

	/**
	 * The ultimate result of all required privileges query.
	 * This will be the result of the most recent query, and will be used to determine if the user can host a session with this definition.
	 *
	 * Defaults to true so when no privileges are required, availability is assumed.
	 */
	UPROPERTY(FieldNotify, BlueprintReadOnly)
	bool bIsAvailable = true;

	/*
	* If this Observer instance should re-query all priveleges after the application re-enter foreground. (Important on consoles where putting the
	* application into background could have the user change account settings that alter their account privileges.)
	*/
	UPROPERTY(FieldNotify, BlueprintReadOnly)
	bool bReQueryPrivilegesOnAppReactivate = true;

};
