#include "FGPipelineIndicatorData.h"

bool FPipelineIndicatorData::UpdateFromFluidBox(const struct FFluidBox& FluidBox){ return bool(); }
float FPipelineIndicatorData::GetRawFlowPct() const{ return float(); }
float FPipelineIndicatorData::GetRawContentPct() const{ return float(); }
void FPipelineIndicatorData::CalculateSmoothFlowRateAndContentPct(float& smoothFlowRate, float& content, bool& stale, float DeltaTime) const{  }
void FPipelineIndicatorData::MarkDataStale(){  }
int8 FPipelineIndicatorData::PackFlowRate(float InFlowRate){ return int8(); }
uint8 FPipelineIndicatorData::PackContent(float InContent){ return uint8(); }