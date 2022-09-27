#include "CrashReporting/SMLCrashReportEndpointPrompt.h"
#include "SatisfactoryModLoader.h"
#include "Components/Overlay.h"
#include "Components/OverlaySlot.h"
#include "ModLoading/ModLoadingLibrary.h"
#include "Reflection/ReflectionHelper.h"

#define SML_CRASH_REPORT_ENDPOINT_PROMPT TEXT("/SML/CrashReporEndpointPrompt/Widget_CrashReportEndpointPrompt.Widget_CrashReportEndpointPrompt_C")

void USMLCrashReportEndpointPrompt::ApplyMainMenuPatch(UUserWidget* MainMenu) {
	FSMLConfiguration Configuration = FSatisfactoryModLoader::GetSMLConfiguration();
	if (Configuration.bDisableModdingCrashReporter) return;
	
	UUserWidget* InviteNotification = FReflectionHelper::GetObjectPropertyValue<UUserWidget>(MainMenu, TEXT("Widget_InviteNotification"));
	UOverlay* Overlay = Cast<UOverlay>(InviteNotification->GetParent());
	checkf(Overlay, TEXT("Widget_InviteNotification parent is not a overlay"));

	UClass* MenuBaseClass = LoadObject<UClass>(NULL, SML_CRASH_REPORT_ENDPOINT_PROMPT);
	checkf(MenuBaseClass, TEXT("Failed to load SML menu page asset from path '%s'"), SML_CRASH_REPORT_ENDPOINT_PROMPT);

	USMLCrashReportEndpointPrompt* NewWidget = Cast<USMLCrashReportEndpointPrompt>(CreateWidgetInstance(*MainMenu->GetWorld(), MenuBaseClass, TEXT("ModListSubMenu")));
	NewWidget->LoadEndpointSelections();
	if (NewWidget->EndpointSelections.Num() > 0) {
		UOverlaySlot* Slot = Overlay->AddChildToOverlay(NewWidget);
		Slot->SetVerticalAlignment(VAlign_Fill);
		Slot->SetHorizontalAlignment(HAlign_Fill);
	}
}

void USMLCrashReportEndpointPrompt::LoadEndpointSelections() {
	FSMLConfiguration Configuration = FSatisfactoryModLoader::GetSMLConfiguration();

	UModLoadingLibrary* SubSys = GEngine->GetEngineSubsystem<UModLoadingLibrary>();
	TArray<FModInfo> Mods = SubSys->GetLoadedMods();

	EndpointSelections.Empty();

	for (const FModInfo& Mod : Mods) {
		FString URL = Mod.CrashReportingEndpoint;
		if (URL.IsEmpty()) continue;
		if (Configuration.AcceptedCrashReportingEndpoints.Contains(URL)) continue;
		if (Configuration.RejectedCrashReportingEndpoints.Contains(URL)) continue;

		EndpointSelections.Add(FSMLCrashReportEndpointSelection(Mod));
	}
}

void USMLCrashReportEndpointPrompt::SaveEndpointSelections() {
#if !WITH_EDITOR
	FSMLConfiguration& Configuration = FSatisfactoryModLoader::GetSMLConfiguration();
	
	for (const FSMLCrashReportEndpointSelection& Selection : EndpointSelections) {
		const FString& URL = Selection.ModInfo.CrashReportingEndpoint;
		if (Selection.bAccepted) {
			Configuration.AcceptedCrashReportingEndpoints.AddUnique(URL);
			Configuration.RejectedCrashReportingEndpoints.Remove(URL);
		} else {
			Configuration.RejectedCrashReportingEndpoints.AddUnique(URL);
			Configuration.AcceptedCrashReportingEndpoints.Remove(URL);
		}
	}
	
	FSatisfactoryModLoader::SaveSMLConfiguration();
#endif
}

void USMLCrashReportEndpointPrompt::DisableCrashReporter() {
	FSMLConfiguration& Configuration = FSatisfactoryModLoader::GetSMLConfiguration();
	Configuration.bDisableModdingCrashReporter = true;
	FSatisfactoryModLoader::SaveSMLConfiguration();
}
