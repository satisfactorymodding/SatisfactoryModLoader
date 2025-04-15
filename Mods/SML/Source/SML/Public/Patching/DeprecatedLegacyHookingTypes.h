#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "DeprecatedLegacyHookingTypes.generated.h"

UCLASS(Deprecated)
class UDEPRECATED_BlueprintSCSHookData : public UDataAsset {
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, Category = "Default")
	TSubclassOf<class UActorComponent> ActorComponentClass;

	UPROPERTY(EditAnywhere, Category = "Default")
	FName VariableName;

	UPROPERTY(VisibleAnywhere, Category = "Default", meta = (ShowInnerProperties))
	UActorComponent* ActorComponentTemplate;

	UPROPERTY(EditAnywhere, Category = "Default")
	FName AttachToName;

	UPROPERTY(Instanced, VisibleAnywhere, Category = "Default")
	TArray<UObject*> Children;
};

UCLASS(Deprecated)
class UDEPRECATED_RootBlueprintSCSHookData : public UDEPRECATED_BlueprintSCSHookData {
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, Category = "Default", meta = (MultiLine = "true"))
	FString DeveloperComment;

	UPROPERTY(EditAnywhere, Category = "Default")
	TSoftClassPtr<class AActor> ActorClass;

	UPROPERTY(EditAnywhere, Category = "Default")
	FName ParentComponentName;
};
