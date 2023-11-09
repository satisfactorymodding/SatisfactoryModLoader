// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "CommonSessionTypes.h"
#include "MVVMViewModelBase.h"
#include "OnlineFriendTypes.h"
#include "Styling/SlateBrush.h"
#include "OnlineIntegrationViewModels.generated.h"

UENUM(BlueprintType)
enum class EOnlineSessionAttributeType: uint8
{
	None,
	Bool,
	Int64,
	Double,
	String
};

inline EOnlineSessionAttributeType MapAttributeType(UE::Online::ESchemaAttributeType Type)
{
	// Pretty risky move here but this should be a temporary solution until we figure out a proper API for sessions
	static_assert(std::is_same_v<std::underlying_type_t<EOnlineSessionAttributeType>, std::underlying_type_t<UE::Online::ESchemaAttributeType>>);
	return static_cast<EOnlineSessionAttributeType>(Type);
}

USTRUCT(BlueprintType)
struct FOnlineSessionAttribute
{
	GENERATED_BODY()

	// explicit FOnlineSessionAttribute(const UE::Online::FSchemaVariant InData)
	// 	: Type(MapAttributeType(InData.GetType()))
	// 	, Data(InData)
	// {
	// 	
	// }
	//
	// FOnlineSessionAttribute() = default;
	// FOnlineSessionAttribute(const FOnlineSessionAttribute&) = default;
	// FOnlineSessionAttribute(FOnlineSessionAttribute&&) = default;
	
	UPROPERTY(BlueprintReadWrite)
	EOnlineSessionAttributeType Type;

	UE::Online::FSchemaVariant Data;
};

UCLASS(NotBlueprintable, BlueprintType)
class ONLINEINTEGRATION_API UOnlineSessionInfoViewModel: public UMVVMViewModelBase
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void SetSessionHandle(const FCommonSession& InSessionHandle, class UCommonSessionSubsystem* SessionSubsystem);

	UFUNCTION(BlueprintCallable)
	void InviteFriend(const UOnlineFriend* Friend);

	UFUNCTION(BlueprintCallable)
	void InvitePressed();

protected:
	void OnSessionUpdateReceived(const UE::Online::FSessionUpdate &SessionUpdate, TSharedRef<const UE::Online::ISession> Session);

	UPROPERTY(BlueprintReadOnly, FieldNotify)
	ECommonSessionJoinPolicy JoinPolicy = ECommonSessionJoinPolicy::InviteOnly;

	UPROPERTY(BlueprintReadOnly, FieldNotify)
	bool IsOnlineSession = false;

	UPROPERTY(BlueprintReadOnly, FieldNotify)
	FString SessionIdString;

private:
	UPROPERTY()
	FCommonSession SessionHandle;
};

UCLASS(BlueprintType)
class ONLINEINTEGRATION_API UOnlineModelConversionFunctionLibrary: public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:

	UFUNCTION(BlueprintPure, Category=OnlineIntegrationConversionFunctions)
	static FSlateBrush MakeBrushFromPlayerAvatar(const struct FPlayerAvatar& PlayerAvatar);
};
