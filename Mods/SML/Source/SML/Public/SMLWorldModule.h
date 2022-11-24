#pragma once
#include "Module/GameWorldModule.h"
#include "SMLWorldModule.generated.h"

UCLASS()
class SML_API USMLWorldModule : public UGameWorldModule {
	GENERATED_BODY()
protected:
	/** Mod references that will be left out of save mod metadata */
	UPROPERTY(EditDefaultsOnly, Category = "SML")
	TArray<FString> IgnoredModReferences;
public:
	virtual void DispatchLifecycleEvent(ELifecyclePhase Phase) override;
private:
	void WriteModMetadataToSave();
};
