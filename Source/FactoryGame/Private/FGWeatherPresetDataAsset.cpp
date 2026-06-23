#include "FGWeatherPresetDataAsset.h"

#include "FGWeatherReaction.h"

TSubclassOf<AFGWeatherReaction> UFGWeatherPresetDataAsset::RollNewWeatherState(TSubclassOf<AFGWeatherReaction> CurrentReaction, UFGWeatherPresetDataAsset* Preset, int32 DayNumber, float& OutDuration){ return TSubclassOf<AFGWeatherReaction>(); }
void UFGWeatherPresetDataAsset::LogWeatherChance(UFGWeatherPresetDataAsset* Preset){ }
bool UFGWeatherPresetDataAsset::IsWeatherPresetValid(UFGWeatherPresetDataAsset* PresetAsset){ return false; }
