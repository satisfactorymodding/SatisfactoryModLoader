// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine.h"
#include "MVVMViewModelBase.h"
#include "Online/Sessions.h"
#include "OnlineIntegrationTypes.h"

#include "SessionDefinition.generated.h"

class ULocalUserInfo;
class UOnlineIntegrationBackend;
struct FCommonSessionCreationSettings;

UENUM()
enum class ECustomSessionSettingType
{
	/**
	  * Unset.
	  */
	None,
	/**
	  * Boolean values.
	  */
	Bool,
	/**
	  * Signed 64 bit integers.
	  */
	Int64,
	/**
	  * Double precision floating point.
	  */
	Double,
	/**
	  * Variable length string data.
	  */
	String
};

inline UE::Online::ESchemaAttributeType MapAttributeType(ECustomSessionSettingType CustomSessionSetting)
{
	switch (CustomSessionSetting)
	{
		case ECustomSessionSettingType::None:
			return UE::Online::ESchemaAttributeType::None;
		case ECustomSessionSettingType::Bool:
			return UE::Online::ESchemaAttributeType::Bool;
		case ECustomSessionSettingType::Int64:
			return UE::Online::ESchemaAttributeType::Int64;
		case ECustomSessionSettingType::Double:
			return UE::Online::ESchemaAttributeType::Double;
		case ECustomSessionSettingType::String:
			return UE::Online::ESchemaAttributeType::String;
	}
	return UE::Online::ESchemaAttributeType::None;
}

inline ECustomSessionSettingType MapAttributeType(UE::Online::ESchemaAttributeType CustomSessionSetting)
{
	switch (CustomSessionSetting)
	{
		case UE::Online::ESchemaAttributeType::None:
			return ECustomSessionSettingType::None;
		case UE::Online::ESchemaAttributeType::Bool:
			return ECustomSessionSettingType::Bool;
		case UE::Online::ESchemaAttributeType::Int64:
			return ECustomSessionSettingType::Int64;
		case UE::Online::ESchemaAttributeType::Double:
			return ECustomSessionSettingType::Double;
		case UE::Online::ESchemaAttributeType::String:
			return ECustomSessionSettingType::String;
	}
	return ECustomSessionSettingType::None;
}


USTRUCT(BlueprintType)
struct FSessionCustomSettingWrapper
{
	GENERATED_BODY()

	FSessionCustomSettingWrapper() = default;
	FSessionCustomSettingWrapper(const FSessionCustomSettingWrapper&) = default;
	FSessionCustomSettingWrapper(FSessionCustomSettingWrapper&&) = default;

	FSessionCustomSettingWrapper& operator=(const FSessionCustomSettingWrapper&) = default;
	FSessionCustomSettingWrapper& operator=(FSessionCustomSettingWrapper&&) = default;

	explicit FSessionCustomSettingWrapper(UE::Online::FSchemaVariant Variant)
		: Type(MapAttributeType(Variant.GetType()))
	{
		switch (Variant.GetType())
		{
			case UE::Online::ESchemaAttributeType::Bool:
				BoolValue = Variant.GetBoolean();
				break;
			case UE::Online::ESchemaAttributeType::Int64:
				Int64Value = Variant.GetInt64();
				break;
			case UE::Online::ESchemaAttributeType::Double:
				DoubleValue = Variant.GetDouble();
				break;
			case UE::Online::ESchemaAttributeType::String:
				StringValue = Variant.GetString();
				break;
			default:
				break;
		}
	}

	explicit operator UE::Online::FSchemaVariant() const
	{
		switch (Type)
		{
			case ECustomSessionSettingType::Bool:
				return UE::Online::FSchemaVariant(BoolValue);
			case ECustomSessionSettingType::Int64:
				return UE::Online::FSchemaVariant(Int64Value);
			case ECustomSessionSettingType::Double:
				return UE::Online::FSchemaVariant(DoubleValue);
			case ECustomSessionSettingType::String:
				return UE::Online::FSchemaVariant(StringValue);
			default:
				break;
		}
		return UE::Online::FSchemaVariant();
	} 

private:
	UPROPERTY(EditAnywhere)
	ECustomSessionSettingType Type = ECustomSessionSettingType::None;

	UPROPERTY(EditAnywhere, meta=(EditCondition="Type==ECustomSessionSettingType::Bool", EditConditionHides))
	bool BoolValue = false;

	UPROPERTY(EditAnywhere, meta=(EditCondition="Type==ECustomSessionSettingType::Int64", EditConditionHides))
	int64 Int64Value = 0;
	
	UPROPERTY(EditAnywhere, meta=(EditCondition="Type==ECustomSessionSettingType::Double", EditConditionHides))
	double DoubleValue = 0.;

	UPROPERTY(EditAnywhere, meta=(EditCondition="Type==ECustomSessionSettingType::String", EditConditionHides))
	FString StringValue;
};


USTRUCT()
struct FSessionCustomSettingsWrapper
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	TMap<FName, FSessionCustomSettingWrapper> CustomSettings;
};

USTRUCT()
struct FSessionSettingsWrapper: public FSessionCustomSettingsWrapper
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	ECommonSessionJoinPolicy JoinPolicy = ECommonSessionJoinPolicy::InviteOnly;
};

USTRUCT(BlueprintType)
struct ONLINEINTEGRATION_API FSessionSettingsProfile
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName Name;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText DisplayName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText Description;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	ECommonSessionJoinPolicy DefaultJoinPolicy;

	UPROPERTY(EditAnywhere)
	TMap<FName, FSessionCustomSettingWrapper> DefaultCustomSettings;

	UPROPERTY(EditAnywhere)
	TMap<FName, FSessionSettingsWrapper> PerBackendSessionSettings;
};

/**
 *	
 */
UCLASS(Config=Engine, PerObjectConfig, BlueprintType)
class ONLINEINTEGRATION_API USessionDefinition: public UMVVMViewModelBase
{
	GENERATED_BODY()
public:	
	FName GetHostingBackend() const;
	bool ShouldCreateMirrorSessions() const;
	TMap<FString, FString> GetTravelArguments() const;

	static UE::Online::FCreateSession::Params MakeSessionCreationParams(const FCommonSessionCreationSettings& Settings, TOptional<FString> MainSessionIdStr, UOnlineIntegrationBackend* Backend);
	static UE::Online::FCreateSession::Params MakeSessionCreationParams(USessionDefinition* SessionDefinition, FName SessionProfile, ULocalUserInfo* Host, int32 MaxPlayerCount, TOptional<FString> MainSessionIdStr, UOnlineIntegrationBackend* Backend);
	
	void ConfigureNetDriverBeforeTravel(const FCommonSessionCreationSettings& Settings);
	
	UE::Online::FUpdateSessionSettings::Params MakeSessionSettingsUpdateParams(FName Backend, FName Profile);

	UFUNCTION(BlueprintCallable)
	bool GetProfile(FName Name, FSessionSettingsProfile& OutProfile);

	FName GetDefaultProfileName() const
	{
		return DefaultSettingsProfile;
	}

protected:
	
	// Begin UObject interface
	// virtual void OverridePerObjectConfigSection(FString& SectionName) override;
	virtual void PostInitProperties() override;
	// End UObject interface

	/**
	 * Display name for this session definition. Can be used in UI for presentation.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, FieldNotify)
	FText DisplayName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, FieldNotify)
	FText DescriptionText;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, FieldNotify)
	bool bCreateOnlineSession = false;

	UPROPERTY(EditAnywhere)
	bool bIsServerSession = false;

	/**
	 * If this identifies a valid online backend, a session will be created on this backend. The entire session depends on the ability to define a session on
	 * this backend.
	 */
	UPROPERTY(EditAnywhere, meta=(EditCondition=bCreateOnlineSession, EditConditionHides))
	FName HostingBackend;

	UPROPERTY(EditAnywhere, meta=(EditCondition=bCreateOnlineSession, EditConditionHides))
	TMap<FName, FSessionCustomSettingWrapper> DefaultCustomSettings;

	UPROPERTY(EditAnywhere, meta=(EditCondition=bCreateOnlineSession, EditConditionHides))
	TMap<FName, FSessionCustomSettingsWrapper> PerBackendDefaultCustomSettings;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(EditCondition=bCreateOnlineSession, EditConditionHides))
	TArray<FSessionSettingsProfile> SessionSettingsProfiles;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(EditCondition=bCreateOnlineSession, EditConditionHides))
	FName DefaultSettingsProfile;

	/**
	 * If defined, mirror sessions will be defined on all the online backends defined for all the session members.
	 */
	UPROPERTY(EditAnywhere, meta=(EditCondition=bCreateOnlineSession, EditConditionHides))
	bool bCreateMirrorSessions = false;

	/**
	 * Default travel arguments. Essential arguments such as "listen" *must* be defined here for this session mode.
	 */
	UPROPERTY(EditAnywhere)
	TMap<FString, FString> DefaultTravelArguments;

	UPROPERTY(EditAnywhere, meta=(EditCondition=bIsServerSession, EditConditionHides))
	FString NetDriverClassName;
	
	UPROPERTY(FieldNotify, BlueprintReadOnly)
	bool bConditionsFulfilled = false;

	UPROPERTY(FieldNotify, BlueprintReadOnly)
	FText FailureReason;
};
