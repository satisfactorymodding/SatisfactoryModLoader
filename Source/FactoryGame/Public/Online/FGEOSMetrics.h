// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "FGEOSMetrics.generated.h"
// Forward Declarations

/**
* Enum of types of supported accounts.
*/
UENUM()
enum class ESupportedAccountType : uint8
{
	SAT_Unknown			UMETA( DisplayName = "Unknown" ),
	SAT_Epic			UMETA( DisplayName = "Epic" ),
	SAT_External		UMETA( DisplayName = "External" )
};

/**
* Enum of types of Input Controller Types.
*/
UENUM()
enum class EInputControllerType : uint8
{
	ICT_Unknown			UMETA( DisplayName = "Unknown" ),
	ICT_MouseKeyboard	UMETA( DisplayName = "Mouse/Keyboard" ),
	ICT_Gamepad			UMETA( DisplayName = "Gamepad" ),
	ICT_Touch			UMETA( DisplayName = "Touch" )
};

class FACTORYGAME_API UEOSMetrics 
{

public:

	/**
	* EOS Metrics Constructor.
	*/
	UEOSMetrics();

	/**
	* Initialization
	*
	* @return bool True if successfully initialised, otherwise false.
	*/
	bool InitMetric(class UWorld* context);

	static UEOSMetrics* GetHandle(class UWorld* context);

	/**
	* Logs metrics for a player session beginning
	*
	* @param DisplayName The name to associate with this Begin Session.  If using the Epic session, this will be taken from the Authentication.
	* @param TargetAccountType The type of account to use to register this Session.  Defaults to External.
	* @param ControllerType The type of input controller used during this play session.  Defaults to Mouse/Keyboard.
	*
	* @return bool True if successfully started the Player Session, otherwise false.
	*/
	bool BeginPlayerSession( FString DisplayName, ESupportedAccountType TargetAccountType = ESupportedAccountType::SAT_External, EInputControllerType ControllerType = EInputControllerType::ICT_MouseKeyboard );

	/**
	* Logs metrics for a player session ending
	*
	* @param DisplayName The name to associate with this End Session.  If using the Epic session, this will be taken from the Authentication.
	*
	* @return bool True if successfully ended the Player Session, otherwise false.
	*/
	bool EndPlayerSession( FString DisplayName );

	bool IsValid() const { return MetricsHandle != nullptr; }

protected:

	/** The Account type for this Metric.  Set when BeginPlayerSession is called.  Defaults to Unknown. */
	UPROPERTY()
	ESupportedAccountType AccountType;

private:
	
	/** Handle to EOS SDK metrics system */
	// EOS_HMetrics MetricsHandle;
	void* MetricsHandle;
};
