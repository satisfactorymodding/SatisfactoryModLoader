#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Anim_Truck_structs.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// AnimBlueprintGeneratedClass Anim_Truck.Anim_Truck_C
// 0x5340 (0x5CB0 - 0x0970)
class UAnim_Truck_C : public UVehicleAnimInstance
{
public:
	struct FPointerToUberGraphFrame                    UberGraphFrame;                                           // 0x0970(0x0008) (ZeroConstructor, Transient, DuplicateTransient)
	struct FAnimNode_Root                              AnimGraphNode_Root_C09B9D6C4777A02867D183B071A63AE2;      // 0x0978(0x0040)
	struct FAnimNode_CopyBone                          AnimGraphNode_CopyBone_FEFE362141A32AE98E454B84710126A3;  // 0x09B8(0x0128)
	struct FAnimNode_CopyBone                          AnimGraphNode_CopyBone_8F8C725D4A0378182AEF0AB3FDEF1168;  // 0x0AE0(0x0128)
	struct FAnimNode_CopyBone                          AnimGraphNode_CopyBone_63CA10104D8D58D14CD5AE98D34BF094;  // 0x0C08(0x0128)
	struct FAnimNode_CopyBone                          AnimGraphNode_CopyBone_5113F3CA4463C9FF77652B8781A99330;  // 0x0D30(0x0128)
	unsigned char                                      UnknownData00[0x8];                                       // 0x0E58(0x0008) MISSED OFFSET
	struct FAnimNode_LookAt                            AnimGraphNode_LookAt_8194163541C33670DBF2108FCEA910D3;    // 0x0E60(0x0220)
	struct FAnimNode_LookAt                            AnimGraphNode_LookAt_A21D61C64F1A5B36DEFB6B9B2810BDE3;    // 0x1080(0x0220)
	struct FAnimNode_LookAt                            AnimGraphNode_LookAt_07E246504D622ED9653308AD576A0773;    // 0x12A0(0x0220)
	struct FAnimNode_LookAt                            AnimGraphNode_LookAt_26E3E742454D24E77E4E79BE61A49693;    // 0x14C0(0x0220)
	struct FAnimNode_CopyBone                          AnimGraphNode_CopyBone_A38076A3458404F59E6CB081864F10B1;  // 0x16E0(0x0128)
	struct FAnimNode_CopyBone                          AnimGraphNode_CopyBone_2CAD380248FEF356DF09F692088C7409;  // 0x1808(0x0128)
	struct FAnimNode_CopyBone                          AnimGraphNode_CopyBone_7A931EE1415E5D6CAEF8CC9AAB4104F6;  // 0x1930(0x0128)
	struct FAnimNode_CopyBone                          AnimGraphNode_CopyBone_0E3B69C44363D1C10F7A599B19437565;  // 0x1A58(0x0128)
	struct FAnimNode_LookAt                            AnimGraphNode_LookAt_5B8F180841B35604C6F611BC630BD2CA;    // 0x1B80(0x0220)
	struct FAnimNode_LookAt                            AnimGraphNode_LookAt_3C43A7F7457567F75CE2B5975E8531C2;    // 0x1DA0(0x0220)
	struct FAnimNode_LookAt                            AnimGraphNode_LookAt_ED5D1A1149643528CF9983B9584AD47A;    // 0x1FC0(0x0220)
	struct FAnimNode_LookAt                            AnimGraphNode_LookAt_177D6D8F454809A6E8D439AC6E2C98C4;    // 0x21E0(0x0220)
	struct FAnimNode_CopyBone                          AnimGraphNode_CopyBone_C8298DC348B4B703484663A5CCAACB03;  // 0x2400(0x0128)
	struct FAnimNode_CopyBone                          AnimGraphNode_CopyBone_E91CB5A1489A71E15C705E8C39DA1D7B;  // 0x2528(0x0128)
	struct FAnimNode_CopyBone                          AnimGraphNode_CopyBone_841A73F9438B76EFC4A089A81CBABA12;  // 0x2650(0x0128)
	struct FAnimNode_CopyBone                          AnimGraphNode_CopyBone_36F83B8F40582D3C6E6C34BCFE30CE18;  // 0x2778(0x0128)
	struct FAnimNode_LookAt                            AnimGraphNode_LookAt_A301C15340C07B54B789379E6E65EB46;    // 0x28A0(0x0220)
	struct FAnimNode_LookAt                            AnimGraphNode_LookAt_C86BEE8F4FE419E638F9D88CC9F7673A;    // 0x2AC0(0x0220)
	struct FAnimNode_CopyBone                          AnimGraphNode_CopyBone_47F4204B499EDF94DA6382A8054F61F4;  // 0x2CE0(0x0128)
	struct FAnimNode_CopyBone                          AnimGraphNode_CopyBone_29DDEA4346B1AE040E23C09E0B4CD2D4;  // 0x2E08(0x0128)
	struct FAnimNode_CopyBone                          AnimGraphNode_CopyBone_5EE5EE83419D460C6D048D8BB002D029;  // 0x2F30(0x0128)
	struct FAnimNode_CopyBone                          AnimGraphNode_CopyBone_76389EE7406A9F015DD35988C56200D6;  // 0x3058(0x0128)
	struct FAnimNode_LookAt                            AnimGraphNode_LookAt_B5F6A435422CF9754CA9F097CA0D03C1;    // 0x3180(0x0220)
	struct FAnimNode_LookAt                            AnimGraphNode_LookAt_C7158EF6479C7B3E416EC7AEBA7BFCDE;    // 0x33A0(0x0220)
	struct FAnimNode_LookAt                            AnimGraphNode_LookAt_824EDD0348BD653FBE79D5B62BA91269;    // 0x35C0(0x0220)
	struct FAnimNode_LookAt                            AnimGraphNode_LookAt_C4ED77BB467391FDADBB95B118F675DC;    // 0x37E0(0x0220)
	struct FAnimNode_CopyBone                          AnimGraphNode_CopyBone_7C702ED1487CA6B7D1EF819A88393F7B;  // 0x3A00(0x0128)
	struct FAnimNode_CopyBone                          AnimGraphNode_CopyBone_69B4DD94497D48E2F84AF4A4B17A75B5;  // 0x3B28(0x0128)
	struct FAnimNode_CopyBone                          AnimGraphNode_CopyBone_81F06D7F43B2EC44FF0B73A292E86DCD;  // 0x3C50(0x0128)
	struct FAnimNode_CopyBone                          AnimGraphNode_CopyBone_80C39AE04BEB4BB39D8B8598B30AD588;  // 0x3D78(0x0128)
	struct FAnimNode_MeshSpaceRefPose                  AnimGraphNode_MeshRefPose_76A20F1E4FEF5298A9A77999206B1967;// 0x3EA0(0x0030)
	struct FAnimNode_WheelHandler                      AnimGraphNode_WheelHandler_4063B47641C1547322FD8DB14A1A2582;// 0x3ED0(0x0108)
	struct FAnimNode_ConvertComponentToLocalSpace      AnimGraphNode_ComponentToLocalSpace_6CFCA2F743CB9582F27E1982BDD4F767;// 0x3FD8(0x0040)
	struct FAnimNode_CopyBone                          AnimGraphNode_CopyBone_C706D45C4F94D319A21AA6965670829E;  // 0x4018(0x0128)
	struct FAnimNode_CopyBone                          AnimGraphNode_CopyBone_5F6C1F2F458F80AADD0FDFB1813A90A5;  // 0x4140(0x0128)
	unsigned char                                      UnknownData01[0x8];                                       // 0x4268(0x0008) MISSED OFFSET
	struct FAnimNode_LookAt                            AnimGraphNode_LookAt_60752EA14DEB7D1EECFC3799537EB2FF;    // 0x4270(0x0220)
	struct FAnimNode_LookAt                            AnimGraphNode_LookAt_642920AC48A1111C527BAEA4D7A9844A;    // 0x4490(0x0220)
	struct FAnimNode_CopyBone                          AnimGraphNode_CopyBone_5047633D4C515E3EAFC1F591E2CEFBA5;  // 0x46B0(0x0128)
	struct FAnimNode_CopyBone                          AnimGraphNode_CopyBone_E0ADD5EF4BAA6EA68DC3BFAB6300D7E4;  // 0x47D8(0x0128)
	struct FAnimNode_LookAt                            AnimGraphNode_LookAt_F3DAEE624758202F00D254B8E53F3831;    // 0x4900(0x0220)
	struct FAnimNode_LookAt                            AnimGraphNode_LookAt_4B018F504E614DF5CC84E981D6EC7579;    // 0x4B20(0x0220)
	struct FAnimNode_CopyBone                          AnimGraphNode_CopyBone_2EF9E57F4B9243CEDFCF4FB780161D5A;  // 0x4D40(0x0128)
	struct FAnimNode_CopyBone                          AnimGraphNode_CopyBone_61D5E97C41D75CE56CF561B257FDF501;  // 0x4E68(0x0128)
	struct FAnimNode_LookAt                            AnimGraphNode_LookAt_FD4AD0F84E8229C719915080CCA5D265;    // 0x4F90(0x0220)
	struct FAnimNode_LookAt                            AnimGraphNode_LookAt_F1E79C0D4C3B9878542B65BF0A2A596E;    // 0x51B0(0x0220)
	struct FAnimNode_CopyBone                          AnimGraphNode_CopyBone_3DC334E74FAA242EFF1F8E8FF002114A;  // 0x53D0(0x0128)
	struct FAnimNode_CopyBone                          AnimGraphNode_CopyBone_1D7657F94E40E672CE81FAA6CD204051;  // 0x54F8(0x0128)
	struct FAnimNode_LookAt                            AnimGraphNode_LookAt_DDD93A3E4B588DD629509BBC462BCBCD;    // 0x5620(0x0220)
	struct FAnimNode_LookAt                            AnimGraphNode_LookAt_06EE7ECD40E706063F432BA463814357;    // 0x5840(0x0220)
	struct FAnimNode_CopyBone                          AnimGraphNode_CopyBone_7B7EFB4F454EF1D842A2F2BC74D7647B;  // 0x5A60(0x0128)
	struct FAnimNode_CopyBone                          AnimGraphNode_CopyBone_F9DF2A294BFA696F96F90D893D266C36;  // 0x5B88(0x0128)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("AnimBlueprintGeneratedClass Anim_Truck.Anim_Truck_C");
		return ptr;
	}


	void ExecuteUbergraph_Anim_Truck(int EntryPoint);
};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
