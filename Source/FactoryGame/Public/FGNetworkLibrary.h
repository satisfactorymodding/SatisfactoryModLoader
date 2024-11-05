// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FGLocalPlayer.h"
#include "FGNetworkLibrary.generated.h"

//This is just the data from the feedback widget.
USTRUCT( BlueprintType )
struct FUserFeedbackFrontEndData
{
	GENERATED_BODY()

	UPROPERTY( BlueprintReadWrite, Category = "User Feedback" )
	bool isSatisfactory;

	UPROPERTY( BlueprintReadWrite, Category = "User Feedback" )
	FString typeOfFeedback;

	UPROPERTY( BlueprintReadWrite, Category = "User Feedback" )
	FString body;

	FUserFeedbackFrontEndData() : isSatisfactory( false ), typeOfFeedback( "" ), body( "" ) {}
};

UCLASS()
class UFGNetworkLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	/** 
	 * Opens a webpage to the specified url. 
	 * (In the case of steam, this opens the steam overlay with a webpage. Dunno what happens elsewhere).
	 * @note: DO NOT INCLUDE HTTP:// IN THE URL.
	 * @return returns true if it succeeds.
	 */
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Browser" )
	static bool OpenWebURL( const FString& Url );

	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Feedback" )
	static bool SubmitFeedback( FUserFeedbackFrontEndData frontEndFeedbackData, class APlayerController* playerController );
};
