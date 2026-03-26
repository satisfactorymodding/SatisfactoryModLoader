#include "Audio/AudioEventsCache.h"

FAudioEventsCache::~FAudioEventsCache(){ }
void FAudioEventsCache::AddSoftAudioEvent(TSoftObjectPtr<UAkAudioEvent> audioEvent){ }
void FAudioEventsCache::AddSoftAudioEvents(const TArray<TSoftObjectPtr<UAkAudioEvent>>& audioEvents){ }
void FAudioEventsCache::CacheAudioEvents(){ }
void FAudioEventsCache::ResetCache(){ }
void FAudioEventsCache::ResetSoftReferences(){ }
void FAudioEventsCache::HandleAllAudioEventsLoaded(){ }
bool FAudioEventsCache::IsAudioLoaded() const{ return false; }
void FAudioEventsCache::CancelActiveLoadingIfAny(){ }
