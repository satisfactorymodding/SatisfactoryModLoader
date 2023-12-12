#pragma once

#include "FactoryGame.h"
#include "MVVMViewModelBase.h"
#include "OnlineInteractionHandlers.h"
#include "OnlineIntegrationSubsystem.h"
#include "OnlineIntegrationTypes.h"
#include "Async/Future.h"
#include "Components/ActorComponent.h"
#include "GameFramework/GameStateBase.h"
#include "FGFrontendStateComponent.generated.h"

using FControlFlowNodeRef = TSharedRef<class FControlFlowNode>;

UCLASS(BlueprintType)
class UFGOnlineModePreferenceViewModel: public UMVVMViewModelBase
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite)
	EOnlineIntegrationMode mMode = EOnlineIntegrationMode::LimitedCrossPlay;
};

UCLASS()
class UFGFrontendStateComponent: public UActorComponent, public IOnlineAuthenticationHandler
{
	GENERATED_BODY()
public:
	UFGFrontendStateComponent(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
	
	//~UActorComponent interface
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	//~End of UActorComponent interface

protected:
	// IOnlineAuthenticationHandler interface
	virtual void ConfigureOnlineIntegration(TPromise<FOnlineIntegrationPlatformSettings> &&promise) override;
	virtual void QueryOnlineIntegrationModePreference(TPromise<EOnlineIntegrationMode>&& Promise) override;
	virtual void AuthenticationSequenceComplete() override;
	virtual void ProgressUpdate(const FText& Status) override;
	// End of IOnlineAuthenticationHandler interface
	
	/** Gets the game state that owns the component, this will always be valid during gameplay but can return null in the editor */
	template <class T>
	T* GetGameState() const
	{
		static_assert(TPointerIsConvertibleFromTo<T, AGameStateBase>::Value, "'T' template parameter to GetGameState must be derived from AGameStateBase");
		return Cast<T>(GetOwner());
	}

	template <class T>
	T* GetGameStateChecked() const
	{
		static_assert(TPointerIsConvertibleFromTo<T, AGameStateBase>::Value, "'T' template parameter to GetGameStateChecked must be derived from AGameStateBase");
		return CastChecked<T>(GetOwner());
	}

	//////////////////////////////////////////////////////////////////////////////
	// GameState accessors, only valid if called during gameplay
	//////////////////////////////////////////////////////////////////////////////

	/** Gets the game mode that owns this component, this will always return null on the client */
	template <class T>
	T* GetGameMode() const
	{
		static_assert(TPointerIsConvertibleFromTo<T, AGameModeBase>::Value, "'T' template parameter to GetGameMode must be derived from AGameModeBase");
		return Cast<T>(GetGameStateChecked<AGameStateBase>()->AuthorityGameMode);
	}

private:
	UFUNCTION()
	void OnlineModeSelectionConfirmed(bool popupConfirmed);
	
	void TryShowMainScreen();

	UPROPERTY( Transient )
	TObjectPtr<class UFGOnlineStartupScreen> mOnlineStartupScreen;

	UPROPERTY()
	TObjectPtr<class UOnlineAsyncOperation> mAuthenticationSequence;

	TOptional< TPromise< EOnlineIntegrationMode > > mOnlineIntegrationModePromise;

	UPROPERTY()
	TObjectPtr< UFGOnlineModePreferenceViewModel > mOnlineIntegrationModeModel;
};
