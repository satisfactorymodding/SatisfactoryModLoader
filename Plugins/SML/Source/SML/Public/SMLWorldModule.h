#pragma once
#include "Module/GameWorldModule.h"
#include "SMLWorldModule.generated.h"

UCLASS()
class SML_API USMLWorldModule : public UGameWorldModule
{
	GENERATED_BODY()
public:
	USMLWorldModule();
	virtual void DispatchLifecycleEvent(ELifecyclePhase Phase) override;
	void WriteModMetadataToSave();
private:
	TArray<FString> IgnoredModReferences = {"FactoryGame", "SML"};
};
