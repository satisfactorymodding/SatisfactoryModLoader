#pragma once
#include "UObject/Class.h"

#include "FGErrorMessage.generated.h"

/**
 * Enum describing how the error should be handled by the system
 */
UENUM(BlueprintType)
enum EErrorResponse
{
	ER_NonIntrusivePopup UMETA(DisplayName="NonIntrusivePopup"),	// Shows a popup ingame or a popup in the main menu
	ER_SendToMainMenu UMETA(DisplayName="SendToMainMenu"),			// Sends the user to main menu and then shows a error message
	ER_Quit UMETA(DisplayName="Quit")								// Sends the user to main menu and and then quit the game
};

// @todo:	Should we rename UFGErrorMessage to something else (like: UFGUIMessage and have a subclass that UFGErrorMessage,
//			then we could implement messages about autosave and other in the same system)
// @todo: Move UFGErrorMesssage to another file
UCLASS(Blueprintable, abstract)
class FACTORYGAME_API UFGErrorMessage : public UObject
{
	GENERATED_BODY()
public:
	UFGErrorMessage();

	/** Get a localized error message */
	UFUNCTION(BlueprintPure,Category="Error")
	inline FText GetErrorMessage() const{ return mErrorMessage; }

	/** Get if the error sends the user to main menu */
	UFUNCTION(BlueprintPure,Category="Error")
	inline EErrorResponse GetErrorResponse() const{ return mErrorResponse; }

	/** Returns true if the error message should send the user to main menu */
	inline bool ShouldSendToMainMenu() const{ return mErrorResponse == EErrorResponse::ER_SendToMainMenu || mErrorResponse == EErrorResponse::ER_Quit; }
protected:
	/** Localized error message that we can push */
	UPROPERTY(EditDefaultsOnly,Category="Error")
	FText mErrorMessage;

	/** Shows how this error should be handled */
	UPROPERTY(EditDefaultsOnly,Category="Error")
	TEnumAsByte<EErrorResponse> mErrorResponse;

	// @todo:	Do we want to add string payload that can be used to attach more information about the error
	//			or are we content with creating a new error message for each error (potentially a "GenericError subclass that we can use that overloads "GetErrorMessage")?
	// @todo: Add priority for the order in which the user should be shown the errors or potentially remove errors of lower priority from the queue

public:
	FORCEINLINE ~UFGErrorMessage() = default;
};