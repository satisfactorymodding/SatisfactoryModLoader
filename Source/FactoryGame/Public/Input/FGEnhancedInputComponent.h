// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputComponent.h"
#include "FGInputSettings.h"
#include "GameplayTagContainer.h"
#include "Engine/Engine.h"
#include "FGEnhancedInputComponent.generated.h"

/**
 * Custom EnhancedInputComponent for Satisfactory, has functionality for binding inputs to gameplay tags, among other things.
 */
UCLASS()
class FACTORYGAME_API UFGEnhancedInputComponent : public UEnhancedInputComponent
{
	GENERATED_BODY()
public:
	/** Templated native function for binding a function to an InputAction which has been paired with a GameplayTag in FGInputSettings. */
	template< class UserClass, typename FuncType >
	void BindActionByTag( const FGameplayTag& InputTag, ETriggerEvent TriggerEvent, UserClass* Object, FuncType Func );
};

template< class UserClass, typename FuncType >
void UFGEnhancedInputComponent::BindActionByTag( const FGameplayTag& InputTag, ETriggerEvent TriggerEvent, UserClass* Object, FuncType Func )
{
	if( const UFGInputSettings* InputSettings = UFGInputSettings::Get() )
	{
		// Try to find an input action associated with this tag
		if( UInputAction* inputAction = InputSettings->GetInputActionForTag( InputTag ) )
		{
			// Bind to it
			BindAction( inputAction, TriggerEvent, Object, Func );
		}
		else
		{
			const FString ErrorString = FString::Printf( TEXT("UFGEnhancedInputComponent::BindActionByTag - Unable to find UInputAction associated with GameplayTag: \"%s\""), *InputTag.ToString() );
			
			UE_LOG( LogInput, Error, TEXT("%s"), *ErrorString );
			
			GEngine->AddOnScreenDebugMessage( uint64(uintptr_t(this)), 5.0f, FColor::Red, ErrorString );
		}
	}
}
