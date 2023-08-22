#include "AccessTransformersSubsystem.h"

#include "AccessTransformers.h"
#include "DirectoryWatcherModule.h"
#include "IDirectoryWatcher.h"
#include "Framework/Notifications/NotificationManager.h"
#include "Widgets/Notifications/SNotificationList.h"

#define LOCTEXT_NAMESPACE "AccessTransformers"

UStruct* FindStructBySourceName(const FString Name) {
	if(UStruct* EngineNameNoPackage = FindObject<UStruct>(ANY_PACKAGE, *Name)) {
		return EngineNameNoPackage;
	}
	if(UStruct* SourceNameNoPackage = FindObject<UStruct>(ANY_PACKAGE, *Name.RightChop(1))) {
		return SourceNameNoPackage;
	}
	return nullptr;
}

FPropertyReference FPropertyReference::FromConfigString(const FString& String) {
	FPropertyReference PropertyReference;
	StaticStruct()->ImportText(
		*String,
		&PropertyReference,
		nullptr,
		PPF_None,
		nullptr,
		StaticStruct()->GetName()
	);
	return PropertyReference;
}

FProperty* FPropertyReference::Resolve(FString& OutError, FString& OutWarning) const {
	UStruct* ResolvedClass = FindObject<UStruct>(nullptr, *Class);
	if (!ResolvedClass) {
		// Backwards compatibility for old structure (no package, allow source class name)
		ResolvedClass = FindStructBySourceName(*Class);
		if (!ResolvedClass) {
			OutError = FString::Printf(TEXT("Could not find class %s"), *Class);
			return nullptr;
		}
		OutWarning = FString::Printf(TEXT(
				   "Using deprecated class specification. The loaded class was %s. Please update your AccessTransformers config file. This will become an error in a future version."
			   ), *ResolvedClass->GetPathName());
	}
		
	FProperty* ResolvedProperty = FindFProperty<FProperty>(ResolvedClass, *Property);
	if(!ResolvedProperty) {
		OutError = FString::Printf(TEXT("Could not find property %s:%s"), *ResolvedClass->GetPathName(), *Property);
		return nullptr;
	}
	return ResolvedProperty;
}

FFunctionReference FFunctionReference::FromConfigString(const FString& String) {
	FFunctionReference FunctionReference;
	StaticStruct()->ImportText(
		*String,
		&FunctionReference,
		nullptr,
		PPF_None,
		nullptr,
		StaticStruct()->GetName()
	);
	return FunctionReference;
}

UFunction* FFunctionReference::Resolve(FString& OutError, FString& OutWarning) const {
	UStruct* ResolvedClass = FindObject<UStruct>(nullptr, *Class);
	if (!ResolvedClass) {
		// Backwards compatibility for old structure (no package, allow source class name)
		ResolvedClass = FindStructBySourceName(*Class);
		if (!ResolvedClass) {
			OutError = FString::Printf(TEXT("Could not find class %s"), *Class);
			return nullptr;
		}
		OutWarning = FString::Printf(
			   TEXT(
				   "Using deprecated class specification. The loaded class was %s. Please update your AccessTransformers config file. This will become an error in a future version."
			   ), *ResolvedClass->GetPathName());
	}
		
	UFunction* ResolvedFunction = FindUField<UFunction>(ResolvedClass, *Function);
	if(!ResolvedFunction) {
		OutError = FString::Printf(TEXT("Could not find function %s:%s"), *ResolvedClass->GetPathName(), *Function);
		return nullptr;
	}
	return ResolvedFunction;
}

void UAccessTransformersSubsystem::Initialize(FSubsystemCollectionBase& Collection) {
	Super::Initialize(Collection);

	OnAccessTransformersChanged = IDirectoryWatcher::FDirectoryChanged::CreateUObject(this, &UAccessTransformersSubsystem::AccessTransformersChanged);
	
	AccessTransformers.Empty();
	
	const TArray<TSharedRef<IPlugin>> EnabledPlugins = IPluginManager::Get().GetEnabledPlugins();

	for (TSharedRef<IPlugin> Plugin : EnabledPlugins) {
		if (Plugin->GetType() == EPluginType::Engine || Plugin->GetType() == EPluginType::Enterprise) {
			continue;
		}
		FPluginAccessTransformers PluginAccessTransformers;
		if (GetAccessTransformersForPlugin(Plugin.Get(), PluginAccessTransformers)) {
			AccessTransformers.Add(Plugin->GetName(), PluginAccessTransformers);
		}
		RegisterFileWatcher(Plugin.Get());
	}

	IPluginManager::Get().OnNewPluginCreated().AddUObject(this, &UAccessTransformersSubsystem::OnPluginCreated);
	
	ApplyTransformers();
}

void UAccessTransformersSubsystem::RegisterFileWatcher(IPlugin& Plugin) {
	if (IsRunningCommandlet()) {
		// Don't register file watchers when running commandlets
		return;
	}
	
	FDirectoryWatcherModule& DirectoryWatcherModule = FModuleManager::LoadModuleChecked<FDirectoryWatcherModule>(TEXT("DirectoryWatcher"));
	IDirectoryWatcher* DirectoryWatcher = DirectoryWatcherModule.Get();
	FString AccessTransformersPath = GetPluginAccessTransformersPath(Plugin);
	FString AccessTransformersDir = FPaths::GetPath(AccessTransformersPath);

	if (!FPaths::DirectoryExists(AccessTransformersDir)) {
		UE_LOG(LogAccessTransformers, Warning, TEXT("Config folder missing for %s. You will need to reload AccessTransformers manually when changed."), *Plugin.GetName());
		return;
	}

	FDelegateHandle Handle;
	if (!DirectoryWatcher->RegisterDirectoryChangedCallback_Handle(AccessTransformersDir, OnAccessTransformersChanged, Handle)) {
		UE_LOG(LogAccessTransformers, Warning, TEXT("Failed to register directory watcher for %s. You will need to reload AccessTransformers manually when changed."), *AccessTransformersPath);
	}
}

void UAccessTransformersSubsystem::AccessTransformersChanged(const TArray<FFileChangeData>& FileChangeData) {
	bool HasChanges = false;
	for (const FFileChangeData& FileChange : FileChangeData) {
		if (FPaths::GetCleanFilename(FileChange.Filename) == AccessTransformersFileName) {
			// File should be .../PluginDir/Config/AccessTransformers.ini
			FString PluginDir = FPaths::GetPath(FPaths::GetPath(FileChange.Filename));
			FString PluginName = FPaths::GetCleanFilename(PluginDir);
			TSharedPtr<IPlugin> Plugin = IPluginManager::Get().FindPlugin(PluginName);
			if (!Plugin.IsValid()) {
				UE_LOG(LogAccessTransformers, Error, TEXT("Failed to find plugin for %s"), *PluginName);
				continue;
			}
			FPluginAccessTransformers PluginAccessTransformers;
			if (GetAccessTransformersForPlugin(Plugin.ToSharedRef().Get(), PluginAccessTransformers)) {
				AccessTransformers.Add(Plugin->GetName(), PluginAccessTransformers);
				HasChanges = true;
			}
		}
	}
	if (HasChanges) {
		UE_LOG(LogAccessTransformers, Display, TEXT("AccessTransformers changed, reloading"));
		ApplyTransformers();

		// This isn't very efficient, but at least it covers all things that would get updated when modifying the code
		FCoreUObjectDelegates::ReloadCompleteDelegate.Broadcast(EReloadCompleteReason::None);
		
		FNotificationInfo Info( LOCTEXT("ReloadFinished", "Access Transformers reloaded!") );
		Info.ExpireDuration = 2.0f;
		TSharedPtr<SNotificationItem> NotificationItem = FSlateNotificationManager::Get().AddNotification(Info);
		NotificationItem->SetCompletionState(SNotificationItem::CS_Success);
	}
}

void UAccessTransformersSubsystem::OnPluginCreated(IPlugin& Plugin) {
	if (Plugin.GetType() == EPluginType::Engine || Plugin.GetType() == EPluginType::Enterprise) {
		return;
	}
	
	FPluginAccessTransformers PluginAccessTransformers;
	if (GetAccessTransformersForPlugin(Plugin, PluginAccessTransformers)) {
		AccessTransformers.Add(Plugin.GetName(), PluginAccessTransformers);
		ApplyTransformers();
	}
	
	RegisterFileWatcher(Plugin);
}

FString UAccessTransformersSubsystem::GetPluginAccessTransformersPath(IPlugin& Plugin) {
	return Plugin.GetBaseDir() / TEXT("Config") / AccessTransformersFileName;
}

bool UAccessTransformersSubsystem::GetAccessTransformersForPlugin(IPlugin& Plugin, FPluginAccessTransformers& OutPluginAccessTransformers) {
	FString AccessTransformersPath = GetPluginAccessTransformersPath(Plugin);
	if (!FPaths::FileExists(AccessTransformersPath)) {
		return false;
	}

	FConfigFile AccessTransformersConfig;
	AccessTransformersConfig.Read(AccessTransformersPath);

	FConfigSection* AccessTransformersSection = AccessTransformersConfig.Find(TEXT("AccessTransformers"));
	if (!AccessTransformersSection) {
		return false;
	}

	TArray<FConfigValue> BlueprintReadWrite;
	AccessTransformersSection->MultiFind(TEXT("BlueprintReadWrite"), BlueprintReadWrite);
	for (const FConfigValue& ConfigValue : BlueprintReadWrite) {
		OutPluginAccessTransformers.BlueprintReadWrite.Add(FPropertyReference::FromConfigString(ConfigValue.GetValue()));
	}

	TArray<FConfigValue> BlueprintCallable;
	AccessTransformersSection->MultiFind(TEXT("BlueprintCallable"), BlueprintCallable);
	for (const FConfigValue& ConfigValue : BlueprintCallable) {
		OutPluginAccessTransformers.BlueprintCallable.Add(FFunctionReference::FromConfigString(ConfigValue.GetValue()));
	}

	return true;
}

void UAccessTransformersSubsystem::ApplyTransformers() {
	// Instead of trying to apply only the changes needed, just reset and reapply everything
	Reset();

	for(const auto& PluginTransformers : AccessTransformers) {
		for (const FPropertyReference& BPRWPropertyReference : PluginTransformers.Value.BlueprintReadWrite) {
			FString Error, Warning;
			FProperty* Property = BPRWPropertyReference.Resolve(Error, Warning);
			if (!Warning.IsEmpty()) {
				UE_LOG(LogAccessTransformers, Warning, TEXT("Resolving BlueprintReadWrite %s requested by %s: %s"), *ToString(BPRWPropertyReference), *PluginTransformers.Key, *Warning);
			}
			if (!Property) {
				UE_LOG(LogAccessTransformers, Error, TEXT("Could not resolve property for BlueprintReadWrite %s requested by %s: %s"), *ToString(BPRWPropertyReference), *PluginTransformers.Key, *Error);
				continue;
			}
			
			if (!OriginalPropertyFlags.Contains(Property)) {
				// Only store the original flags if we haven't already
				// so we don't override this with modified flags
				OriginalPropertyFlags.Add(Property, Property->PropertyFlags);
			}
		
			// BlueprintReadWrite marks the property as BlueprintVisible and clears BlueprintReadOnly
			Property->SetPropertyFlags(CPF_BlueprintVisible);
			Property->ClearPropertyFlags(CPF_BlueprintReadOnly);
		}
	}

	for(const auto& PluginTransformers : AccessTransformers) {
		for (const FFunctionReference& BPCFunctionReference : PluginTransformers.Value.BlueprintCallable) {
			FString Error, Warning;
			UFunction* Function = BPCFunctionReference.Resolve(Error, Warning);
			if (!Warning.IsEmpty()) {
				UE_LOG(LogAccessTransformers, Warning, TEXT("Resolving BlueprintCallable %s requested by %s: %s"), *ToString(BPCFunctionReference), *PluginTransformers.Key, *Warning);
			}
			if (!Function) {
				UE_LOG(LogAccessTransformers, Error, TEXT("Could not resolve property for BlueprintCallable %s requested by %s: %s"), *ToString(BPCFunctionReference), *PluginTransformers.Key, *Error);
				continue;
			}
			
			if (!OriginalFunctionFlags.Contains(Function)) {
				// Only store the original flags if we haven't already
				// so we don't override this with modified flags
				OriginalFunctionFlags.Add(Function, Function->FunctionFlags);
			}
		
			Function->FunctionFlags |= FUNC_BlueprintCallable;
		}
	}
}

void UAccessTransformersSubsystem::Reset() {
	// Reset all property flags
	for (const TTuple<FProperty*, EPropertyFlags>& Property : OriginalPropertyFlags) {
		Property.Key->PropertyFlags = Property.Value;
	}
	OriginalPropertyFlags.Empty();

	// Reset all function flags
	for (const TTuple<UFunction*, EFunctionFlags>& Function : OriginalFunctionFlags) {
        Function.Key->FunctionFlags = Function.Value;
    }
	OriginalFunctionFlags.Empty();
}

const TCHAR* UAccessTransformersSubsystem::AccessTransformersFileName = TEXT("AccessTransformers.ini");

#undef LOCTEXT_NAMESPACE
