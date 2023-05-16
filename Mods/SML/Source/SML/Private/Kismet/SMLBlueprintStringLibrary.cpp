#include "Kismet/SMLBlueprintStringLibrary.h"

bool USMLBlueprintStringLibrary::Less_StringString(const FString& A, const FString& B) {
	return A < B;
}

bool USMLBlueprintStringLibrary::Greater_StringString(int32 A, int32 B) {
	return A > B;
}

bool USMLBlueprintStringLibrary::LessEqual_StringString(const FString& A, const FString& B) {
	return A <= B;
}

bool USMLBlueprintStringLibrary::GreaterEqual_StringString(int32 A, int32 B) {
	return A >= B;
}
