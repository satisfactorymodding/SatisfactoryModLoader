#include "Kismet/SMLBlueprintSystemLibrary.h"

#include "Misc/App.h"

bool USMLBlueprintSystemLibrary::IsGEditor() {
	return GIsEditor;
}

FString USMLBlueprintSystemLibrary::GetProjectName() {
	return FApp::GetProjectName();
}

FString USMLBlueprintSystemLibrary::GetAppName() {
	return FApp::GetName();
}

FString USMLBlueprintSystemLibrary::GetBuildBranch() {
	return FApp::GetBuildVersion();
}

FString USMLBlueprintSystemLibrary::GetBuildDate() {
	return FApp::GetBuildDate();
}

FString USMLBlueprintSystemLibrary::GetBuildConfiguration() {
	return LexToString(FApp::GetBuildConfiguration());
}

FString USMLBlueprintSystemLibrary::GetBuildTargetType() {
	return LexToString(FApp::GetBuildTargetType());
}
