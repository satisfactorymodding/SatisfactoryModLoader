#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "DeprecatedLegacyHookingTypes.generated.h"

/** DEPRECATED - to be removed. Only exists to make the migration to new Actor Mixins easier. */
UCLASS()
class UBlueprintSCSHookData : public UDataAsset {
	GENERATED_BODY()
public:
	UPROPERTY(VisibleDefaultsOnly, Category = "Default")
	TSubclassOf<class UActorComponent> ActorComponentClass;

	UPROPERTY(VisibleDefaultsOnly, Category = "Default")
	FName VariableName;

	UPROPERTY(VisibleDefaultsOnly, Category = "Default", meta = (ShowInnerProperties))
	UActorComponent* ActorComponentTemplate;

	UPROPERTY(VisibleDefaultsOnly, Category = "Default")
	FName AttachToName;

	UPROPERTY(Instanced, VisibleDefaultsOnly, Category = "Default")
	TArray<UObject*> Children;
};

/** DEPRECATED - to be removed. Only exists to make the migration to new Actor Mixins easier. */
UCLASS()
class URootBlueprintSCSHookData : public UBlueprintSCSHookData {
	GENERATED_BODY()
public:
	UPROPERTY(VisibleDefaultsOnly, Category = "Default", meta = (MultiLine = "true"))
	FString DeveloperComment;

	UPROPERTY(VisibleDefaultsOnly, Category = "Default")
	TSoftClassPtr<class AActor> ActorClass;

	UPROPERTY(VisibleDefaultsOnly, Category = "Default")
	FName ParentComponentName;
};
