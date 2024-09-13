// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "FGOptionInterface.h"
#include "Settings/FGAdvancedGameSettings.h"
#include "FGServerObjectOptionInterface.generated.h"

class UFGUserSetting;
class UFGUserSettingApplyType;
class UFGServerObject;

/**
 * Implementation of the option interface for a remote controlled set of options
 * Used in combination with the UFGServerObject
 */
UCLASS( BlueprintType, Within = "FGServerObject" )
class FACTORYDEDICATEDCLIENT_API UFGServerObjectOptionAdapter : public UObject, public IFGAdvancedGameSettingsInterface
{
	GENERATED_BODY()
public:
	// Begin IFGAdvancedGameSettingsInterface
	virtual void GetAllUserSettings(TArray<UFGUserSettingApplyType*>& OutUserSettings) const override;
	virtual UFGUserSettingApplyType* FindUserSetting(const FString& SettingId) const override;
	virtual void ApplyChanges() override;
	virtual bool HasAnyUnsavedOptionValueChanges() const override;
	virtual bool HasPendingApplyOptionValue(const FString& cvar) const override;
	virtual void RevertUnsavedChanges() override;
	virtual TArray<FUserSettingCategoryMapping> GetCategorizedSettingWidgets( UObject* worldContext, UUserWidget* owningWidget ) override;
	virtual IFGOptionInterface* GetPrimaryOptionInterface(UWorld* world) const override;
	virtual bool IsInMainMenu() const override;
	// End IFGAdvancedGameSettingsInterface

	/** Returns the server object this manager maps to */
	UFUNCTION( BlueprintPure, Category = "Server" )
	UFGServerObject* GetServerObject() const;

	void Initialize( UClass* SettingManagerClass, bool bDedicatedServerRelevantOnly, bool bIsLocalManagerOnly = false );
	void ReceiveServerSettings( const TMap<FString, FString>& InServerSettings, const TMap<FString, FString>& PendingServerOptions );
	void WriteChangedSettings( TMap<FString, FString>& OutServerSettings );

protected:
	UPROPERTY( Transient )
	TMap<FString, UFGUserSettingApplyType*> mUserSettings;

	/** Setting values that are currently set on the server */
	TMap<FString, FVariant> mServerValues;

	/** True if this is a local only manager, and should never be synced to the server */
	bool mIsLocalManagerOnly{false};
};