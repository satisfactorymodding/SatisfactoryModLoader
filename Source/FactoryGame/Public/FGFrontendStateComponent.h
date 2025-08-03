#pragma once

#include "FactoryGame.h"
#include "Async/Future.h"
#include "Components/ActorComponent.h"
#include "FGGameUserSettings.h"
#include "GameFramework/GameStateBase.h"
#include "MVVMViewModelBase.h"
#include "OnlineIntegrationSubsystem.h"
#include "FGFrontendStateComponent.generated.h"

class UOnlineAsyncOperation;
using FControlFlowNodeRef = TSharedRef<class FControlFlowNode>;

UCLASS(BlueprintType)
class UFGOnlineModePreferenceViewModel: public UMVVMViewModelBase
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite)
	EOnlineIntegrationMode mMode = EOnlineIntegrationMode::Undefined;
};

UCLASS()
class UFGFrontendStateComponent: public UActorComponent
{
	GENERATED_BODY()
public:
	UFGFrontendStateComponent(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
	
	//~UActorComponent interface
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	//~End of UActorComponent interface

	//<FL>[KonradA]
	UFUNCTION( BlueprintCallable )
	void BootstrapAuth();
	//</FL>

protected:
	UFUNCTION()
	void OnOnlineIntegrationModeChanged(EOnlineIntegrationMode mode, bool bInvokedByUser); // <FL> [KonradA] Added bInvokedByUser to keep track if the platform or the user executed this change (e.g. for error messages)
	void AuthenticationSequenceComplete(UOnlineAsyncOperation* InAsyncOp);
	// <FL>
	void StartConsoleFlow(bool bSuppressErrors);
	UFUNCTION()
	void OnPremiumChecked(bool hasPremium);
	UFUNCTION()
	void TickCheckInvalidOnlineIntegrationState();
	
	//[KonradA] Keep track of last auth error
	TArray< UE::Online::FOnlineError > mLastAuthError;
	bool bSuppressPlatformReauth = false; // Keep track of reauth attempts
	//</FL>
	
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

	// <FL> [ZimmermannA] necessary to fulfill TRC 5061
		// This function does nothing on platforms that dont require this message dialog.
	void ShowUGCCommRestrictionDialog();
	void HandleAppResume();
	// </FL>

	UPROPERTY()
	TObjectPtr<class UOnlineAsyncOperation> mAuthenticationSequence;

	TOptional< TPromise< EOnlineIntegrationMode > > mOnlineIntegrationModePromise;

	bool mUserInitiatedCrossPlayLogin = false;

	UPROPERTY()
	TObjectPtr< UFGOnlineModePreferenceViewModel > mOnlineIntegrationModeModel;
};
