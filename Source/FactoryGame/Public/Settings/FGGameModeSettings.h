// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "FGAdvancedGameSettings.h"
#include "FGGameModeSettings.generated.h"


UCLASS( BlueprintType )
class FACTORYGAME_API UFGGameModeSettings : public UObject, public IFGAdvancedGameSettingsInterface
{
	GENERATED_BODY()

public:
	UFUNCTION( BlueprintCallable, Category= "GameMode" )
	void Initialize();


	// Begin IFGAdvancedGameSettingsInterface
	virtual void GetAllUserSettings( TArray< TObjectPtr< UFGUserSettingApplyType > >& out_userSettings ) const override;
	virtual void GetAllUserSettingsMap( TMap< FString, TObjectPtr< UFGUserSettingApplyType > >& out_userSettings ) const override;
	virtual UFGUserSettingApplyType* FindUserSetting( const FString& settingId ) const override;
	virtual bool HasAnyUnsavedOptionValueChanges() const override;
	virtual bool HasPendingApplyOptionValue( const FString& cvar ) const override;
	virtual void RevertUnsavedChanges() override;
	virtual void ApplyChanges() override;
	virtual IFGOptionInterface* GetPrimaryOptionInterface( UWorld* world ) const override;
	virtual bool IsInMainMenu() const override;
	// End IFGAdvancedGameSettingsInterface
private :
	bool IsAppliedImmediately() const;

	UPROPERTY( Transient )
	TMap< FString, TObjectPtr< class UFGUserSettingApplyType > > mUserSettings;
};