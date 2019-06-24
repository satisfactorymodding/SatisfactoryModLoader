#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_MRMesh_structs.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// Class MRMesh.MeshReconstructorBase
// 0x0000 (0x0028 - 0x0028)
class UMeshReconstructorBase : public UObject
{
public:

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class MRMesh.MeshReconstructorBase");
		return ptr;
	}


	void StopReconstruction();
	void StartReconstruction();
	void PauseReconstruction();
	bool IsReconstructionStarted();
	bool IsReconstructionPaused();
	void DisconnectMRMesh();
	void ConnectMRMesh(class UMRMeshComponent* Mesh);
};


// Class MRMesh.MRMeshComponent
// 0x0040 (0x05A0 - 0x0560)
class UMRMeshComponent : public UPrimitiveComponent
{
public:
	class UMaterialInterface*                          Material;                                                 // 0x0560(0x0008) (Edit, ZeroConstructor, IsPlainOldData)
	bool                                               bCreateMeshProxySections;                                 // 0x0568(0x0001) (Edit, ZeroConstructor, IsPlainOldData)
	bool                                               bUpdateNavMeshOnMeshUpdate;                               // 0x0569(0x0001) (Edit, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData00[0x6];                                       // 0x056A(0x0006) MISSED OFFSET
	TArray<class UBodySetup*>                          BodySetups;                                               // 0x0570(0x0010) (ZeroConstructor, Transient)
	unsigned char                                      UnknownData01[0x20];                                      // 0x0580(0x0020) MISSED OFFSET

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class MRMesh.MRMeshComponent");
		return ptr;
	}


	bool IsConnected();
	void ForceNavMeshUpdate();
	void Clear();
};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
