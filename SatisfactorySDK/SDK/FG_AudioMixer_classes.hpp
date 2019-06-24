#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_AudioMixer_structs.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// Class AudioMixer.SynthComponent
// 0x0380 (0x05C0 - 0x0240)
class USynthComponent : public USceneComponent
{
public:
	class USoundAttenuation*                           AttenuationSettings;                                      // 0x0240(0x0008) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	struct FSoundAttenuationSettings                   AttenuationOverrides;                                     // 0x0248(0x02A8) (Edit, BlueprintVisible)
	class USoundConcurrency*                           ConcurrencySettings;                                      // 0x04F0(0x0008) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	class USoundClass*                                 SoundClass;                                               // 0x04F8(0x0008) (Edit, ZeroConstructor, IsPlainOldData)
	class USoundEffectSourcePresetChain*               SourceEffectChain;                                        // 0x0500(0x0008) (Edit, ZeroConstructor, IsPlainOldData)
	class USoundSubmix*                                SoundSubmix;                                              // 0x0508(0x0008) (Edit, ZeroConstructor, IsPlainOldData)
	TArray<struct FSoundSubmixSendInfo>                SoundSubmixSends;                                         // 0x0510(0x0010) (Edit, BlueprintVisible, ZeroConstructor)
	TArray<struct FSoundSourceBusSendInfo>             BusSends;                                                 // 0x0520(0x0010) (Edit, BlueprintVisible, ZeroConstructor)
	TArray<struct FSoundSourceBusSendInfo>             PreEffectBusSends;                                        // 0x0530(0x0010) (Edit, BlueprintVisible, ZeroConstructor)
	unsigned char                                      bIsUISound : 1;                                           // 0x0540(0x0001) (Edit, BlueprintVisible)
	unsigned char                                      bIsPreviewSound : 1;                                      // 0x0540(0x0001)
	unsigned char                                      UnknownData00[0x3];                                       // 0x0541(0x0003) MISSED OFFSET
	int                                                EnvelopeFollowerAttackTime;                               // 0x0544(0x0004) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	int                                                EnvelopeFollowerReleaseTime;                              // 0x0548(0x0004) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData01[0x4];                                       // 0x054C(0x0004) MISSED OFFSET
	struct FScriptMulticastDelegate                    OnAudioEnvelopeValue;                                     // 0x0550(0x0010) (ZeroConstructor, InstancedReference, BlueprintAssignable)
	unsigned char                                      UnknownData02[0x20];                                      // 0x0560(0x0020) MISSED OFFSET
	class USynthSound*                                 Synth;                                                    // 0x0580(0x0008) (ZeroConstructor, Transient, IsPlainOldData)
	class UAudioComponent*                             AudioComponent;                                           // 0x0588(0x0008) (ExportObject, ZeroConstructor, Transient, InstancedReference, IsPlainOldData)
	unsigned char                                      UnknownData03[0x30];                                      // 0x0590(0x0030) MISSED OFFSET

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class AudioMixer.SynthComponent");
		return ptr;
	}


	void Stop();
	void Start();
	void SetVolumeMultiplier(float VolumeMultiplier);
	void SetSubmixSend(class USoundSubmix* Submix, float SendLevel);
	bool IsPlaying();
};


// Class AudioMixer.AudioMixerBlueprintLibrary
// 0x0000 (0x0028 - 0x0028)
class UAudioMixerBlueprintLibrary : public UBlueprintFunctionLibrary
{
public:

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class AudioMixer.AudioMixerBlueprintLibrary");
		return ptr;
	}


	class USoundWave* StopRecordingOutput(class UObject* WorldContextObject, EAudioRecordingExportType ExportType, const class FString& Name, const class FString& Path, class USoundSubmix* SubmixToRecord, class USoundWave* ExistingSoundWaveToOverwrite);
	void StartRecordingOutput(class UObject* WorldContextObject, float ExpectedDuration, class USoundSubmix* SubmixToRecord);
	void SetBypassSourceEffectChainEntry(class UObject* WorldContextObject, class USoundEffectSourcePresetChain* PresetChain, int EntryIndex, bool bBypassed);
	void ResumeRecordingOutput(class UObject* WorldContextObject, class USoundSubmix* SubmixToPause);
	void RemoveSourceEffectFromPresetChain(class UObject* WorldContextObject, class USoundEffectSourcePresetChain* PresetChain, int EntryIndex);
	void RemoveMasterSubmixEffect(class UObject* WorldContextObject, class USoundEffectSubmixPreset* SubmixEffectPreset);
	void PauseRecordingOutput(class UObject* WorldContextObject, class USoundSubmix* SubmixToPause);
	int GetNumberOfEntriesInSourceEffectChain(class UObject* WorldContextObject, class USoundEffectSourcePresetChain* PresetChain);
	void ClearMasterSubmixEffects(class UObject* WorldContextObject);
	void AddSourceEffectToPresetChain(class UObject* WorldContextObject, class USoundEffectSourcePresetChain* PresetChain, const struct FSourceEffectChainEntry& Entry);
	void AddMasterSubmixEffect(class UObject* WorldContextObject, class USoundEffectSubmixPreset* SubmixEffectPreset);
};


// Class AudioMixer.SubmixEffectDynamicsProcessorPreset
// 0x0078 (0x00B8 - 0x0040)
class USubmixEffectDynamicsProcessorPreset : public USoundEffectSubmixPreset
{
public:
	unsigned char                                      UnknownData00[0x50];                                      // 0x0040(0x0050) MISSED OFFSET
	struct FSubmixEffectDynamicsProcessorSettings      Settings;                                                 // 0x0090(0x0028) (Edit, BlueprintVisible)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class AudioMixer.SubmixEffectDynamicsProcessorPreset");
		return ptr;
	}


	void SetSettings(const struct FSubmixEffectDynamicsProcessorSettings& InSettings);
};


// Class AudioMixer.SubmixEffectSubmixEQPreset
// 0x0048 (0x0088 - 0x0040)
class USubmixEffectSubmixEQPreset : public USoundEffectSubmixPreset
{
public:
	unsigned char                                      UnknownData00[0x38];                                      // 0x0040(0x0038) MISSED OFFSET
	struct FSubmixEffectSubmixEQSettings               Settings;                                                 // 0x0078(0x0010) (Edit, BlueprintVisible)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class AudioMixer.SubmixEffectSubmixEQPreset");
		return ptr;
	}


	void SetSettings(const struct FSubmixEffectSubmixEQSettings& InSettings);
};


// Class AudioMixer.SubmixEffectReverbPreset
// 0x0090 (0x00D0 - 0x0040)
class USubmixEffectReverbPreset : public USoundEffectSubmixPreset
{
public:
	unsigned char                                      UnknownData00[0x5C];                                      // 0x0040(0x005C) MISSED OFFSET
	struct FSubmixEffectReverbSettings                 Settings;                                                 // 0x009C(0x0034) (Edit, BlueprintVisible)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class AudioMixer.SubmixEffectReverbPreset");
		return ptr;
	}


	void SetSettingsWithReverbEffect(class UReverbEffect* InReverbEffect, float WetLevel, float DryLevel);
	void SetSettings(const struct FSubmixEffectReverbSettings& InSettings);
};


// Class AudioMixer.SynthSound
// 0x0020 (0x0280 - 0x0260)
class USynthSound : public USoundWaveProcedural
{
public:
	unsigned char                                      UnknownData00[0x20];                                      // 0x0260(0x0020) MISSED OFFSET

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class AudioMixer.SynthSound");
		return ptr;
	}

};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
