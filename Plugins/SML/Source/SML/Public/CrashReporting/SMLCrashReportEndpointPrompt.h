#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ModLoading/ModLoadingLibrary.h"
#include "SMLCrashReportEndpointPrompt.generated.h"

USTRUCT(BlueprintType)
struct FSMLCrashReportEndpointSelection {
	GENERATED_BODY()
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FModInfo ModInfo;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool bAccepted = true;

	FSMLCrashReportEndpointSelection() = default;
	FSMLCrashReportEndpointSelection(const FModInfo& ModInfo) : ModInfo(ModInfo) {}
};

UCLASS(Blueprintable)
class SML_API USMLCrashReportEndpointPrompt : public UUserWidget {
	GENERATED_BODY()

public:
	static void ApplyMainMenuPatch(UUserWidget* MainMenu);

protected:
	UPROPERTY(BlueprintReadOnly)
	TArray<FSMLCrashReportEndpointSelection> EndpointSelections;

	UFUNCTION(BlueprintCallable)
	void LoadEndpointSelections();

	UFUNCTION(BlueprintCallable)
	void SaveEndpointSelections();

	UFUNCTION(BlueprintCallable)
	void DisableCrashReporter();
};
