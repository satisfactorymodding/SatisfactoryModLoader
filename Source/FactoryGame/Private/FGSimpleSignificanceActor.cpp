#include "FGSimpleSignificanceActor.h"

void AFGSimpleSignificanceActor::BeginPlay(){ Super::BeginPlay(); }
void AFGSimpleSignificanceActor::EndPlay(const EEndPlayReason::Type EndPlayReason){ Super::EndPlay(EndPlayReason); }
float AFGSimpleSignificanceActor::GetSignificanceRange_Implementation() const{ return IFGSignificanceInterface::GetSignificanceRange_Implementation(); }
void AFGSimpleSignificanceActor::GainedSignificance_Implementation(){ IFGSignificanceInterface::GainedSignificance_Implementation(); }
void AFGSimpleSignificanceActor::LostSignificance_Implementation(){ IFGSignificanceInterface::LostSignificance_Implementation(); }
FFGSignificanceTickRateSettings AFGSimpleSignificanceActor::GetSignificanceTickRateSettings_Implementation() const{ return IFGSignificanceInterface::GetSignificanceTickRateSettings_Implementation(); }
void AFGSimpleSignificanceActor::UpdateSignificanceTickRate_Implementation(float NewTickRate, bool bTickEnabled){ IFGSignificanceInterface::UpdateSignificanceTickRate_Implementation(NewTickRate, bTickEnabled); }
