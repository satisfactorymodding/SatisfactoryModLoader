#pragma once

#include "CoreMinimal.h"
#include "Interfaces/IPluginManager.h"
#include "EditorSubsystem.h"
#include "IDirectoryWatcher.h"
#include "AccessTransformersSubsystem.generated.h"

USTRUCT()
struct ACCESSTRANSFORMERS_API FPropertyReference {
	GENERATED_BODY()

	static FPropertyReference FromConfigString(const FString& String);
	
	UPROPERTY(Config)
	FString Class;

	UPROPERTY(Config)
	FString Property;
	
	FProperty* Resolve(FString& OutError, FString& OutWarning) const;
};

inline FString ToString(const FPropertyReference& PropertyReference) {
	return PropertyReference.Class + TEXT(":") + PropertyReference.Property;
}

USTRUCT()
struct ACCESSTRANSFORMERS_API FFunctionReference {
	GENERATED_BODY()

	static FFunctionReference FromConfigString(const FString& String);

	UPROPERTY(Config)
	FString Class;

	UPROPERTY(Config)
	FString Function;
	
	UFunction* Resolve(FString& OutError, FString& OutWarning) const;
};

inline FString ToString(const FFunctionReference& FunctionReference) {
	return FunctionReference.Class + TEXT(":") + FunctionReference.Function;
}

USTRUCT()
struct ACCESSTRANSFORMERS_API FPluginAccessTransformers {
	GENERATED_BODY()

	UPROPERTY()
	TArray<FPropertyReference> BlueprintReadWrite;

	UPROPERTY()
	TArray<FFunctionReference> BlueprintCallable;
};

UCLASS()
class ACCESSTRANSFORMERS_API UAccessTransformersSubsystem : public UEditorSubsystem
{
	GENERATED_BODY()

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	void ApplyTransformers();
	void Reset();
	
	static const TCHAR* AccessTransformersFileName;
private:
	static FString GetPluginAccessTransformersPath(IPlugin& Plugin);
	bool GetAccessTransformersForPlugin(IPlugin& Plugin, FPluginAccessTransformers& OutPluginAccessTransformers);

	void OnPluginCreated(IPlugin& Plugin);
	void RegisterFileWatcher(IPlugin& Plugin);
	void AccessTransformersChanged(const TArray<FFileChangeData>& FileChangeData);
	
	TMap<FString, FPluginAccessTransformers> AccessTransformers;

	TMap<FProperty*, EPropertyFlags> OriginalPropertyFlags;

	TMap<UFunction*, EFunctionFlags> OriginalFunctionFlags;
	
	IDirectoryWatcher::FDirectoryChanged OnAccessTransformersChanged;
};
