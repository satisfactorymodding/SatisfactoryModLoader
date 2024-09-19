#pragma once

#include "EditorSubsystem.h"
#include "EditorDebugString.h"
#include "EditorDebugSubsystem.generated.h"

UCLASS()
class FACTORYEDITOR_API UEditorDebugSubsystem : public UEditorSubsystem
{
	GENERATED_BODY()
public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

private:
	void DebugDrawCanvas(UCanvas* Canvas, APlayerController*);

	static void DrawEditorDebugString(FVector WorldLocation, const FString& Text, FLinearColor TextColor, float Duration,
	                           bool DrawShadow, int32 FontSize);

	static void ClearAllEditorDebugStrings();
	static void OnWorldPreActorTick(UWorld* World, ELevelTick TickType, float DeltaSeconds);

private:
	double LastDebugDrawTime;
	double DrawDebugDelta;
	TArray<FEditorDebugString> EditorDebugStrings;
	FDelegateHandle DrawDebugDelegateHandle;
};
