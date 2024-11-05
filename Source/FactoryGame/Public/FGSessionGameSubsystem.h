// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "FGSessionGameSubsystem.generated.h"

class USessionInformation;
class UFGSessionInformationModel;
namespace UE::FieldNotification
{
struct FFieldId;
}
/**
 *
 */
UCLASS()
class FACTORYGAME_API UFGSessionGameSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
public:
	UFGSessionGameSubsystem();
	
	UFGSessionInformationModel* GetSessionInformationModel() const
	{
		return mSessionInfoModel;
	}
protected:
	/** Implement this for initialization of instances of the system */
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	UFUNCTION()
	void FirstLocalUserInfoCreated(ULocalUserInfo* userInfo);

	void GameSessionChanged(UObject*, UE::FieldNotification::FFieldId);
	void OnPendingSessionMigrationChanged(UObject*, UE::FieldNotification::FFieldId);

	UFUNCTION()
	void AboutToTravel(USessionInformation* onlineSessionInfo);

	UFUNCTION()
	void PostLoadMap(UWorld* world);

#if WITH_EDITOR
	UFUNCTION()
	void OnPostBeginPIE(bool boolParam);
#endif

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UFGSessionInformationModel> mSessionInfoModel;

	UPROPERTY()
	TObjectPtr<ULocalUserInfo> mFirstLocalUser;
};
