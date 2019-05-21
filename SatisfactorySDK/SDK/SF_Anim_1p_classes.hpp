#pragma once

// Satisfactory SDK (V0.1.6 - CL#98445)

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "SF_Anim_1p_structs.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// AnimBlueprintGeneratedClass Anim_1p.Anim_1p_C
// 0x15467 (0x15917 - 0x04B0)
class UAnim_1p_C : public UFGAnimPlayer
{
public:
	struct FPointerToUberGraphFrame                    UberGraphFrame;                                           // 0x04B0(0x0008) (Transient, DuplicateTransient)
	struct FAnimNode_UseCachedPose                     AnimGraphNode_UseCachedPose_5C7F9E76475E48F0C2A7B98B5D1B8EB3;// 0x04B8(0x0050)
	struct FAnimNode_LayeredBoneBlend                  AnimGraphNode_LayeredBoneBlend_8BBA0DA44A61CBF3D2B4EBA21D3CB1F6;// 0x0508(0x00E0)
	struct FAnimNode_TransitionResult                  AnimGraphNode_TransitionResult_98FBC23F4C9A713C0FB93D9AD6EEE9B4;// 0x05E8(0x0048)
	struct FAnimNode_TransitionResult                  AnimGraphNode_TransitionResult_41486603465DA2EE45A05285737B6F37;// 0x0630(0x0048)
	struct FAnimNode_TransitionResult                  AnimGraphNode_TransitionResult_72A79E6D45404B548CB614A287C4B26C;// 0x0678(0x0048)
	struct FAnimNode_TransitionResult                  AnimGraphNode_TransitionResult_5039F38743640F2D676C48BFB75282A9;// 0x06C0(0x0048)
	struct FAnimNode_TransitionResult                  AnimGraphNode_TransitionResult_FE2D69DD4977FC45382F1EA75A0059DA;// 0x0708(0x0048)
	struct FAnimNode_TransitionResult                  AnimGraphNode_TransitionResult_650862FA4B1F7229923D688CA2759DEF;// 0x0750(0x0048)
	struct FAnimNode_TransitionResult                  AnimGraphNode_TransitionResult_8110100E44167500A9386FBBC4AF4756;// 0x0798(0x0048)
	struct FAnimNode_TransitionResult                  AnimGraphNode_TransitionResult_29E470814ED65B9558A8DEA14BC39066;// 0x07E0(0x0048)
	struct FAnimNode_TransitionResult                  AnimGraphNode_TransitionResult_E06F5E1B412E03A618C8DA9390B5A2D4;// 0x0828(0x0048)
	struct FAnimNode_TransitionResult                  AnimGraphNode_TransitionResult_3AB9574D497C4152E7E0B29DC8D7EDCA;// 0x0870(0x0048)
	struct FAnimNode_TransitionResult                  AnimGraphNode_TransitionResult_B17FCA464B6FA53AE37EC1921486EDD1;// 0x08B8(0x0048)
	struct FAnimNode_TransitionResult                  AnimGraphNode_TransitionResult_F948AAE7488B4C18BC7BD3995671074F;// 0x0900(0x0048)
	struct FAnimNode_TransitionResult                  AnimGraphNode_TransitionResult_51B03D77497B352DA91F9280A6878691;// 0x0948(0x0048)
	struct FAnimNode_TransitionResult                  AnimGraphNode_TransitionResult_B22AF35D4BCF08D326922D9EED21F2CB;// 0x0990(0x0048)
	struct FAnimNode_BlendSpacePlayer                  AnimGraphNode_BlendSpacePlayer_D6C0685E408BBFC5EDB85DB32257F453;// 0x09D8(0x0128)
	struct FAnimNode_Root                              AnimGraphNode_StateResult_52119FBA49F8E0F4A06BE8ACC87B8ACF;// 0x0B00(0x0048)
	struct FAnimNode_StateMachine                      AnimGraphNode_StateMachine_50967A16404DBB09894D7DA0602D06F6;// 0x0B48(0x00E0)
	struct FAnimNode_Root                              AnimGraphNode_StateResult_7EAC83C34C96A77B8CE3B4997B73DE9C;// 0x0C28(0x0048)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_996B481E4B58E303BE9E5B872B8926E6;// 0x0C70(0x00B0)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_D85CF65E41A9D0363AE966870336787C;// 0x0D20(0x00B0)
	struct FAnimNode_LayeredBoneBlend                  AnimGraphNode_LayeredBoneBlend_14C3E9424421256A7AF388A3C2178530;// 0x0DD0(0x00E0)
	struct FAnimNode_BlendListByBool                   AnimGraphNode_BlendListByBool_68F2D8E4434D8ED200EBC4A512C84709;// 0x0EB0(0x00D0)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_DBF86C8042311645F210BCAC452933D3;// 0x0F80(0x00B0)
	struct FAnimNode_BlendListByEnum                   AnimGraphNode_BlendListByEnum_A72EFCEB4FB0E6C451891FA9AE2361BE;// 0x1030(0x00E0)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_A19915A642CEA8B6DC0F6B8E41B879A4;// 0x1110(0x00B0)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_587BA1204446F40C606E288070A55BF8;// 0x11C0(0x00B0)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_DC9101484907DCD200C2C9844ADCD5BD;// 0x1270(0x00B0)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_6FB87DDA45FAD483801302B7D3ED1C46;// 0x1320(0x00B0)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_B51ECD554EBEAA64F87216BDCD22B6BB;// 0x13D0(0x00B0)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_A845D3574A4B1D8203B76AAE6AF4A882;// 0x1480(0x00B0)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_56E61D474423534A946495AA03F2E8E7;// 0x1530(0x00B0)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_01E8C3B74C716D48EC32558293F72BC0;// 0x15E0(0x00B0)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_D6C366BA4FC8B77F9E3DCBADF9C939E0;// 0x1690(0x00B0)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_A2AA58B54E2F840C9459CAB5865F6B99;// 0x1740(0x00B0)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_FF48C04B4372126E3552D7B0D7495ACF;// 0x17F0(0x00B0)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_410E9078418FCD0E4BDC26B8FCE702F1;// 0x18A0(0x00B0)
	struct FAnimNode_Root                              AnimGraphNode_StateResult_6BFECA254FD78B30A2E0938819D54A2D;// 0x1950(0x0048)
	struct FAnimNode_TransitionResult                  AnimGraphNode_TransitionResult_7F63D8814D03208D6BBAA29EF891D7F8;// 0x1998(0x0048)
	struct FAnimNode_TransitionResult                  AnimGraphNode_TransitionResult_10B1324041E8974CD639CB91EA071499;// 0x19E0(0x0048)
	struct FAnimNode_TransitionResult                  AnimGraphNode_TransitionResult_8741F1A4423A331D860F629FE6A60CB3;// 0x1A28(0x0048)
	struct FAnimNode_TransitionResult                  AnimGraphNode_TransitionResult_2025F2404EA061FA9D9697A9B542D25B;// 0x1A70(0x0048)
	struct FAnimNode_TransitionResult                  AnimGraphNode_TransitionResult_40E3382B4B538B1FC5BACDB687986EDB;// 0x1AB8(0x0048)
	struct FAnimNode_TransitionResult                  AnimGraphNode_TransitionResult_9EAA692B4875136C0123118C321CE9BC;// 0x1B00(0x0048)
	struct FAnimNode_TransitionResult                  AnimGraphNode_TransitionResult_8F3D2C6646223988B4B8CF9C40EF52CF;// 0x1B48(0x0048)
	struct FAnimNode_TransitionResult                  AnimGraphNode_TransitionResult_3F088D9849F7BB96258384A8FA66C903;// 0x1B90(0x0048)
	struct FAnimNode_TransitionResult                  AnimGraphNode_TransitionResult_1B7A325746C172AE5C0B46B794AE5F3B;// 0x1BD8(0x0048)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_65702E2440FC34E36F651B80E7E7664E;// 0x1C20(0x00B0)
	struct FAnimNode_LayeredBoneBlend                  AnimGraphNode_LayeredBoneBlend_785644274AFA4759563940A33BB8E3EE;// 0x1CD0(0x00E0)
	struct FAnimNode_BlendListByBool                   AnimGraphNode_BlendListByBool_04BE55DE4BDAF8E4297155B3FAD4912B;// 0x1DB0(0x00D0)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_DA55888042C3646766E3039C56351733;// 0x1E80(0x00B0)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_E7BA0FC0456ED2C5B5A9A8A10F3462DC;// 0x1F30(0x00B0)
	struct FAnimNode_BlendListByEnum                   AnimGraphNode_BlendListByEnum_CC1A2B1945E10B7B29887BAF4DD28125;// 0x1FE0(0x00E0)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_D808172241800287216930AE9593BA4A;// 0x20C0(0x00B0)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_F57A916D4093B05B062C5D88F7A1F76C;// 0x2170(0x00B0)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_AA70866B4CACBDD1E8017DA5CC912B5B;// 0x2220(0x00B0)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_75249F4C441493A5B0EFE8B397718C69;// 0x22D0(0x00B0)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_9F22F03345F67763997E868D9C757C61;// 0x2380(0x00B0)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_6374867541DF67E1F9308693BD6BD12D;// 0x2430(0x00B0)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_5AE521B14D9254220E9ABEAC1578072C;// 0x24E0(0x00B0)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_133618EF4E80C919A8AC96A566312470;// 0x2590(0x00B0)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_2E6C588B4DB316CF2E7148B5FEB44990;// 0x2640(0x00B0)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_04FEEAD74CC24D0FFBE9BD8FD827141E;// 0x26F0(0x00B0)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_A17BBA654536D20531CE75A107C47E05;// 0x27A0(0x00B0)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_7EC8072644CCD538327DE4877C551D08;// 0x2850(0x00B0)
	struct FAnimNode_Root                              AnimGraphNode_StateResult_04B4F2814D1E638EA5E99091863C7CE9;// 0x2900(0x0048)
	struct FAnimNode_RefPose                           AnimGraphNode_IdentityPose_B17FC0554FA5ABC82756049CB84018EC;// 0x2948(0x0038)
	struct FAnimNode_Root                              AnimGraphNode_StateResult_5BC54B2B467EA2FB1B1DA8BE42FD1B21;// 0x2980(0x0048)
	struct FAnimNode_LayeredBoneBlend                  AnimGraphNode_LayeredBoneBlend_10BC90734DE256D739868F915E3863D1;// 0x29C8(0x00E0)
	struct FAnimNode_BlendListByBool                   AnimGraphNode_BlendListByBool_E4EE153048B41B2C8299A9A723F4A7CE;// 0x2AA8(0x00D0)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_A5988DF14DC4D3CE4DFCE4B6E2DF8DF3;// 0x2B78(0x00B0)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_C5457A3C4C89439BB7A5578F25C47A26;// 0x2C28(0x00B0)
	struct FAnimNode_BlendListByEnum                   AnimGraphNode_BlendListByEnum_F3F23A7D4725B4CD568ADF9A00250B44;// 0x2CD8(0x00E0)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_AC261AB34898DDE487D743AEBC5D54EE;// 0x2DB8(0x00B0)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_0A46283A4F4A377E680F859A46D874AA;// 0x2E68(0x00B0)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_D41C3AA74950C560BC88DBBDA902143A;// 0x2F18(0x00B0)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_010814574EB7E8DD9F31E2A003FB0708;// 0x2FC8(0x00B0)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_8301669F4CD42169BAE729A945519657;// 0x3078(0x00B0)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_B4BF4BEA48DCB9B1D813F39CC02C5348;// 0x3128(0x00B0)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_6B78154543C4F7B1841090916A6C242A;// 0x31D8(0x00B0)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_36634ED24207FA78031D68ACCBDE036D;// 0x3288(0x00B0)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_FE408E8C47A8E28AAE6254878554FF5F;// 0x3338(0x00B0)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_3F8DCFF747E0C17AED3D71BEBB07B4E7;// 0x33E8(0x00B0)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_EF0E857B4549A4BA6B78EDB76D338BAA;// 0x3498(0x00B0)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_D02B38974AF58A6BBE66288CF0AF54BD;// 0x3548(0x00B0)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_F59E4F8C4AB97B57A02232A6033B348E;// 0x35F8(0x00B0)
	struct FAnimNode_Root                              AnimGraphNode_StateResult_0C5111DB43B18719FA4774ABAA6DE00E;// 0x36A8(0x0048)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_6C25F6C341FF8099E441DFB13B66194A;// 0x36F0(0x00B0)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_58EA15C2448E9FE13400B0B88C62C4B3;// 0x37A0(0x00B0)
	struct FAnimNode_LayeredBoneBlend                  AnimGraphNode_LayeredBoneBlend_000BBE864DC4957B29586CB4F5B65472;// 0x3850(0x00E0)
	struct FAnimNode_BlendListByBool                   AnimGraphNode_BlendListByBool_599A6FCE45A0F124DEF114A3E45F195A;// 0x3930(0x00D0)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_CDE055B54380332944A2E083D7A983F3;// 0x3A00(0x00B0)
	struct FAnimNode_BlendSpacePlayer                  AnimGraphNode_BlendSpacePlayer_088B7D584B0B84B4EB98978859751C5B;// 0x3AB0(0x0128)
	struct FAnimNode_BlendListByBool                   AnimGraphNode_BlendListByBool_6E244A9D44FC15B17498D9BB01211FE4;// 0x3BD8(0x00D0)
	struct FAnimNode_BlendListByEnum                   AnimGraphNode_BlendListByEnum_1A59E2DB4793058EFF6EF6B6E652AE42;// 0x3CA8(0x00E0)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_D94EAA2F46D683AE9C974788D63F1E32;// 0x3D88(0x00B0)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_2F7623F0480EC967991920A7A71C3A5B;// 0x3E38(0x00B0)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_B462351948DD881973DB2E805F20B885;// 0x3EE8(0x00B0)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_CD41A3DB46DD3E77FF80E49DAB4A72B3;// 0x3F98(0x00B0)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_0A1CE608472218B6F699BEA183E3D3A2;// 0x4048(0x00B0)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_022B8DE34B3FC4594010C9B1D49C727E;// 0x40F8(0x00B0)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_7AAFCC66439DC6AD2C9AEAA1EA0D12EB;// 0x41A8(0x00B0)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_1A37CAFF47DB392A73DFA293D99BDBA6;// 0x4258(0x00B0)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_BBE678F44B9907AEFA3EF68AF15C5CEF;// 0x4308(0x00B0)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_75C0015442395AC3E20D40AF3EB74BD5;// 0x43B8(0x00B0)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_3EC6F6D1492D469C48A2CBA6124BB1B7;// 0x4468(0x00B0)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_AB427931418C81AFA995D4BDA5AC0B4E;// 0x4518(0x00B0)
	struct FAnimNode_Root                              AnimGraphNode_StateResult_318F0D3D47E0C7F43206C28692F71D26;// 0x45C8(0x0048)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_2346E25D4D47F57EEE1760906A2C1F4D;// 0x4610(0x00B0)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_F84D238D464892DE01606FA3BFD73926;// 0x46C0(0x00B0)
	struct FAnimNode_LayeredBoneBlend                  AnimGraphNode_LayeredBoneBlend_F3A20F6145D2C12CD94C0281C90F76F4;// 0x4770(0x00E0)
	struct FAnimNode_BlendListByBool                   AnimGraphNode_BlendListByBool_A77B04554A25FEF5BCD27ABCAEA3D9DB;// 0x4850(0x00D0)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_02B349484AFE84163C4A039361119FB0;// 0x4920(0x00B0)
	struct FAnimNode_BlendListByEnum                   AnimGraphNode_BlendListByEnum_C8A0CDDE449DD5FE7DE5ADAE8672235E;// 0x49D0(0x00E0)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_C63F7D104AA339BFE6137B9E096F829F;// 0x4AB0(0x00B0)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_5FE435104652128B4DED769540DF2669;// 0x4B60(0x00B0)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_5204E21D46DD942CF8FB5795AE300ECB;// 0x4C10(0x00B0)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_B9B84ACC46A3459ACB63ED94830AE951;// 0x4CC0(0x00B0)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_F202681348D55868ADF4BF99B2A044E7;// 0x4D70(0x00B0)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_3B387A9B4CC5113A8AB1B287631800A5;// 0x4E20(0x00B0)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_67C08E37417201C76AF9F5BC4C6404FD;// 0x4ED0(0x00B0)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_0DEDFEF64953B86B4E0BFCA8614ABC46;// 0x4F80(0x00B0)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_3186CECD48244E4949BF4D8E895A135A;// 0x5030(0x00B0)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_C56FDE1546A47F8746F7239CC2FCB986;// 0x50E0(0x00B0)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_22BB9F974F7052BC62870591A0F2CD9B;// 0x5190(0x00B0)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_CD3199414EB1F822885A1BA4FEEA3B7B;// 0x5240(0x00B0)
	struct FAnimNode_Root                              AnimGraphNode_StateResult_30D74AC44460B8B62CF376A17421BC0A;// 0x52F0(0x0048)
	struct FAnimNode_StateMachine                      AnimGraphNode_StateMachine_3598F28B420EA7C518CEDDAF3222039C;// 0x5338(0x00E0)
	struct FAnimNode_Root                              AnimGraphNode_StateResult_D42E71034A8BF7F6E9CB67982B2040AB;// 0x5418(0x0048)
	struct FAnimNode_TransitionResult                  AnimGraphNode_TransitionResult_CAFC295140982C1AE6B3448C333C7A68;// 0x5460(0x0048)
	struct FAnimNode_TransitionResult                  AnimGraphNode_TransitionResult_DD0BD6BD41CB1D9FFCE1D9BA49984BE9;// 0x54A8(0x0048)
	struct FAnimNode_TransitionResult                  AnimGraphNode_TransitionResult_718AF9734FAD904546F3D9AD33140564;// 0x54F0(0x0048)
	struct FAnimNode_TransitionResult                  AnimGraphNode_TransitionResult_AACAA52D49A3AA8F307990A1AAAEE275;// 0x5538(0x0048)
	struct FAnimNode_TransitionResult                  AnimGraphNode_TransitionResult_200748904D648F095E8D7081C7D7E311;// 0x5580(0x0048)
	struct FAnimNode_TransitionResult                  AnimGraphNode_TransitionResult_D2070F6E4CA79E0B77A729B8056DBF50;// 0x55C8(0x0048)
	struct FAnimNode_TransitionResult                  AnimGraphNode_TransitionResult_485ACC644FE59DD1953D1C949B574894;// 0x5610(0x0048)
	struct FAnimNode_TransitionResult                  AnimGraphNode_TransitionResult_1C430D2D45AFC02D733E23A8FB7B20E2;// 0x5658(0x0048)
	struct FAnimNode_TransitionResult                  AnimGraphNode_TransitionResult_F1D0BC5E40C38AB7A05E3D8D185A67C8;// 0x56A0(0x0048)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_FE6C17B44372F735803E829F3197B0B5;// 0x56E8(0x00B0)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_7BBC555549E23664171DEDAA0041B703;// 0x5798(0x00B0)
	struct FAnimNode_BlendListByBool                   AnimGraphNode_BlendListByBool_D6090B114FF238CF6B662DB165E64ED7;// 0x5848(0x00D0)
	struct FAnimNode_LayeredBoneBlend                  AnimGraphNode_LayeredBoneBlend_C15D8D5844B3819A704D2FB22F74A136;// 0x5918(0x00E0)
	struct FAnimNode_BlendSpacePlayer                  AnimGraphNode_BlendSpacePlayer_08A98FC84D862A3ED8E484B15DB79D14;// 0x59F8(0x0128)
	struct FAnimNode_BlendListByEnum                   AnimGraphNode_BlendListByEnum_575B095A4B4AFEE0DB448BB769CAF7D6;// 0x5B20(0x00E0)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_3B66EE1C407FE87B139D34B4778A1006;// 0x5C00(0x00B0)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_E1E9821B46DC716C72E69FA563D29D91;// 0x5CB0(0x00B0)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_1B42B28A4827305A9FAA5BB4E89D1FC3;// 0x5D60(0x00B0)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_BC46938845A596DE301BAAAC9CB5F40E;// 0x5E10(0x00B0)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_809757B045E612E00143D5B5D031E085;// 0x5EC0(0x00B0)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_DEB7D5B04A446468EAE72D8637CBCFAF;// 0x5F70(0x00B0)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_1441EDC043067240DD33A69947A13821;// 0x6020(0x00B0)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_E4290A8F428CD9F255776898A40B67CC;// 0x60D0(0x00B0)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_00C79359481A1EFA748F13897F59F5D6;// 0x6180(0x00B0)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_E7309B6D49E7B3A8F68216968C0CD90C;// 0x6230(0x00B0)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_4B3E9DE8441637E6D7D1AE8ED9E3A80E;// 0x62E0(0x00B0)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_B055CF2144AFC56CC86AA0AFCBD3C4B1;// 0x6390(0x00B0)
	struct FAnimNode_Root                              AnimGraphNode_StateResult_F02C261340207F527AC5DAB895097DCF;// 0x6440(0x0048)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_8BFAE0A842704D1D5F2CA3A3CAB07532;// 0x6488(0x00B0)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_D31E5D064E0AD261F12558ABACEBD11E;// 0x6538(0x00B0)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_DAB256E74D1289BBF624D399E0D70FCF;// 0x65E8(0x00B0)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_BBA8A76C43DC1CA0762FD39A0621DDF0;// 0x6698(0x00B0)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_7E50FC81464769DCBDEE06997385E811;// 0x6748(0x00B0)
	struct FAnimNode_BlendListByBool                   AnimGraphNode_BlendListByBool_16E8534945D938CACF56D39E39C0FD2F;// 0x67F8(0x00D0)
	struct FAnimNode_LayeredBoneBlend                  AnimGraphNode_LayeredBoneBlend_8976CD9A4D858FB855D32F99EF84D6AF;// 0x68C8(0x00E0)
	struct FAnimNode_BlendListByBool                   AnimGraphNode_BlendListByBool_E8691C96472C595D84958892D3697CE1;// 0x69A8(0x00D0)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_AA222FEA4323081237FCEEBF34E5EC98;// 0x6A78(0x00B0)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_D9F9EEF1430C38CF1F364194038FC4C2;// 0x6B28(0x00B0)
	struct FAnimNode_BlendListByBool                   AnimGraphNode_BlendListByBool_D301098B4B194CD46BD65389D483A3B5;// 0x6BD8(0x00D0)
	struct FAnimNode_BlendListByEnum                   AnimGraphNode_BlendListByEnum_7A8BB8044DC0F9EC9F33CA8DF7803845;// 0x6CA8(0x00E0)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_6F0021C443F683F84029D796FF721C24;// 0x6D88(0x00B0)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_47212A674AF9396062AD7EB30C796A6E;// 0x6E38(0x00B0)
	struct FAnimNode_BlendListByBool                   AnimGraphNode_BlendListByBool_6B8959F1411EE629F76D929645BA68FA;// 0x6EE8(0x00D0)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_778B8CFA4588AEE4D1C044B21950374C;// 0x6FB8(0x00B0)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_58065DCB48651079F7DC23A3F877AFC3;// 0x7068(0x00B0)
	struct FAnimNode_BlendListByBool                   AnimGraphNode_BlendListByBool_5E3E088D4DBD66AF0E79CD93C53E2344;// 0x7118(0x00D0)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_22A591F34BD7E880502DFAA83F80EA97;// 0x71E8(0x00B0)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_91C75CEE409C8A8F5C47678E33CB72A6;// 0x7298(0x00B0)
	struct FAnimNode_BlendListByBool                   AnimGraphNode_BlendListByBool_FC15D9B94278E36EDE1BCF8479C9F89C;// 0x7348(0x00D0)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_234404AA493FA4B99B99959E1915BE60;// 0x7418(0x00B0)
	struct FAnimNode_BlendListByBool                   AnimGraphNode_BlendListByBool_E0BF1B2D4E14E08A237EC58F05ABF90C;// 0x74C8(0x00D0)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_3AD77E03498CE00667C58CA5CC0345E2;// 0x7598(0x00B0)
	struct FAnimNode_BlendListByBool                   AnimGraphNode_BlendListByBool_C201C89F4FF362F861C1FA9AAB9DE7CE;// 0x7648(0x00D0)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_DE895984497BE1233EC63EAE327843A3;// 0x7718(0x00B0)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_0B775E3749D528C8DEC97AAD36E72F2B;// 0x77C8(0x00B0)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_DE909C084FAEBE2F4D25A6B623A5FD30;// 0x7878(0x00B0)
	struct FAnimNode_BlendListByBool                   AnimGraphNode_BlendListByBool_6672D63C40D1E6EC3F204D883C306029;// 0x7928(0x00D0)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_8B7205EA43041A24E5EACF8A5A09E6BA;// 0x79F8(0x00B0)
	struct FAnimNode_BlendListByBool                   AnimGraphNode_BlendListByBool_44C598054328748E388D148494B2F738;// 0x7AA8(0x00D0)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_DD3E7CB442E7DE3D28500282F1202E14;// 0x7B78(0x00B0)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_03DFE33947D4DD185E7955BA6487E963;// 0x7C28(0x00B0)
	struct FAnimNode_BlendListByBool                   AnimGraphNode_BlendListByBool_B63E2CE845CF551F8769E7B1288F9250;// 0x7CD8(0x00D0)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_885E0A5B433ECD29F09A71A7B71D31BF;// 0x7DA8(0x00B0)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_C694115540BE15A628D14C8195A5A129;// 0x7E58(0x00B0)
	struct FAnimNode_BlendListByBool                   AnimGraphNode_BlendListByBool_C48152554428A444E554BE997E9B090C;// 0x7F08(0x00D0)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_77F935D54EF242E86CE6798D52A9FEE2;// 0x7FD8(0x00B0)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_B93BB639401B333A27925AA45EA4AC02;// 0x8088(0x00B0)
	struct FAnimNode_BlendListByBool                   AnimGraphNode_BlendListByBool_8552BC1A4363A53DF9BBD3A5AAD1CE87;// 0x8138(0x00D0)
	struct FAnimNode_BlendSpacePlayer                  AnimGraphNode_BlendSpacePlayer_C4302A564DD4DC47986961B310548E0E;// 0x8208(0x0128)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_88438351458F07FA17B269B3E8107ED3;// 0x8330(0x00B0)
	struct FAnimNode_BlendListByBool                   AnimGraphNode_BlendListByBool_12CA6B404969F07201205EBE48FCBC18;// 0x83E0(0x00D0)
	struct FAnimNode_BlendSpacePlayer                  AnimGraphNode_BlendSpacePlayer_1C506563437EE93E4A008BAB7C81CAB1;// 0x84B0(0x0128)
	struct FAnimNode_BlendSpacePlayer                  AnimGraphNode_BlendSpacePlayer_BA77F76D4423368082F3EF89AEBC8A4A;// 0x85D8(0x0128)
	struct FAnimNode_BlendListByBool                   AnimGraphNode_BlendListByBool_9A29840E4DF86CAED998D79665BE7144;// 0x8700(0x00D0)
	struct FAnimNode_Root                              AnimGraphNode_StateResult_332B5E8F4742D7B2F303829EC967102A;// 0x87D0(0x0048)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_CA81FF8D43A4B5C70DD1E8AAFAF6E037;// 0x8818(0x00B0)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_CD000C704EE24EA07D2AF2B1449B809B;// 0x88C8(0x00B0)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_1B36E00745F9D54DAE5E6581DE786907;// 0x8978(0x00B0)
	struct FAnimNode_LayeredBoneBlend                  AnimGraphNode_LayeredBoneBlend_57F89C284BF3AEBFA2889CAA9AC1E702;// 0x8A28(0x00E0)
	struct FAnimNode_BlendListByBool                   AnimGraphNode_BlendListByBool_ECCC88264F9300DED167ACB9070AFF57;// 0x8B08(0x00D0)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_58FC8E9843D12191CD60519A7E307F4E;// 0x8BD8(0x00B0)
	struct FAnimNode_BlendListByEnum                   AnimGraphNode_BlendListByEnum_682EE13E4C162D8A18D84D87844B36A8;// 0x8C88(0x00E0)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_D48A4A2C447ADA994290E7AB0A22083F;// 0x8D68(0x00B0)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_818A4537472878DF467D56B718DA4156;// 0x8E18(0x00B0)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_282EFCAB487AB07846E75CBA4712EAE7;// 0x8EC8(0x00B0)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_C4F2C05443DCEE2A47F3B7A510B4080A;// 0x8F78(0x00B0)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_F14A73A042B539206B7A65B93E1DF58B;// 0x9028(0x00B0)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_E302200E48406DE25E337DB5726D800A;// 0x90D8(0x00B0)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_F736B75443EA79490ACB18A7DFB2EC42;// 0x9188(0x00B0)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_DD4A67D44C51002C9ABFB0815D480CD8;// 0x9238(0x00B0)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_E36F45A54F1065910C8DAFAE5BCC534D;// 0x92E8(0x00B0)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_70C791E744BAB9D25CA859A997E03FB1;// 0x9398(0x00B0)
	struct FAnimNode_BlendSpacePlayer                  AnimGraphNode_BlendSpacePlayer_4BB10171424F09F42F994A9CB73B009B;// 0x9448(0x0128)
	struct FAnimNode_Root                              AnimGraphNode_StateResult_0B7679284E58F16E108FE18553ED91FC;// 0x9570(0x0048)
	struct FAnimNode_StateMachine                      AnimGraphNode_StateMachine_0722D98242855A2D2D61D0A31E0D4056;// 0x95B8(0x00E0)
	struct FAnimNode_Root                              AnimGraphNode_StateResult_B1FB286A4B9F335B00679DB9659E6B59;// 0x9698(0x0048)
	struct FAnimNode_TransitionResult                  AnimGraphNode_TransitionResult_EA87E8294D8EABDC183F65BF5E749D1E;// 0x96E0(0x0048)
	struct FAnimNode_TransitionResult                  AnimGraphNode_TransitionResult_CC1797A944CBA36012F80BAE3C5CE5CC;// 0x9728(0x0048)
	struct FAnimNode_TransitionResult                  AnimGraphNode_TransitionResult_3FEC73CD415CE6EA644F3A86A8396318;// 0x9770(0x0048)
	struct FAnimNode_TransitionResult                  AnimGraphNode_TransitionResult_8DA8A992420A431E9924B2ADBE3EEC11;// 0x97B8(0x0048)
	struct FAnimNode_TransitionResult                  AnimGraphNode_TransitionResult_C290BA2642DAC287EAEB10B8358EC88C;// 0x9800(0x0048)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_8F7DB4CD4B106D52E249CA964AD89CDA;// 0x9848(0x00B0)
	struct FAnimNode_BlendListByBool                   AnimGraphNode_BlendListByBool_D725CE99432C6CF2E288D9B8906BBEBC;// 0x98F8(0x00D0)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_771A12434699643C42C0DABE8F421866;// 0x99C8(0x00B0)
	struct FAnimNode_Root                              AnimGraphNode_StateResult_464AB3C9415C184B09EB44BA50857733;// 0x9A78(0x0048)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_5C5660D1464A004DE293E3A65E016CF5;// 0x9AC0(0x00B0)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_C7DBBE24496718EA09D308A520007BC1;// 0x9B70(0x00B0)
	struct FAnimNode_LayeredBoneBlend                  AnimGraphNode_LayeredBoneBlend_1844998C474BAA66BB97868D84BE64C9;// 0x9C20(0x00E0)
	struct FAnimNode_BlendListByBool                   AnimGraphNode_BlendListByBool_C446F2544F525016F2A25A90AB8B1637;// 0x9D00(0x00D0)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_ECFDDF204BCC6FA61157899D62917946;// 0x9DD0(0x00B0)
	struct FAnimNode_BlendListByEnum                   AnimGraphNode_BlendListByEnum_7215F8D6436EE5EA4DC3DF831ECDB30A;// 0x9E80(0x00E0)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_F55B2EB64B417CDAA78E2DBE017B3A00;// 0x9F60(0x00B0)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_0BDE5869459B5D0EB1A1E58191B760CF;// 0xA010(0x00B0)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_3A5D9A3E4160143CED3CB7B74B8ACB9E;// 0xA0C0(0x00B0)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_A646955440CC8774B86A48A7A726A613;// 0xA170(0x00B0)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_E0CD79314CC35BBC65F9368EE6A74114;// 0xA220(0x00B0)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_DE5757814F8EE9A8FD7229B65D2D4C34;// 0xA2D0(0x00B0)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_558E1EB348CFC6DF00CFAF9B154D6E96;// 0xA380(0x00B0)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_E23B48994B5CD821090A0386381667F4;// 0xA430(0x00B0)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_ED375D2B44F4AA27EEA9ACB95E1FF937;// 0xA4E0(0x00B0)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_7C25874C4B46939DE0278AA4CAAAADA3;// 0xA590(0x00B0)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_A3C9B73B4DE7B5B327D25899F1775565;// 0xA640(0x00B0)
	struct FAnimNode_BlendSpacePlayer                  AnimGraphNode_BlendSpacePlayer_8C59E95B4687323C83CCFE860D76B660;// 0xA6F0(0x0128)
	struct FAnimNode_Root                              AnimGraphNode_StateResult_39043B534762A5B7D510FCB77D892B95;// 0xA818(0x0048)
	struct FAnimNode_SequenceEvaluator                 AnimGraphNode_SequenceEvaluator_A0FC8CBE4C605B2F9BC2AAAE90263C53;// 0xA860(0x0070)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_03BFEECF42BDE7D09E0B31B901A6C431;// 0xA8D0(0x00B0)
	struct FAnimNode_SequenceEvaluator                 AnimGraphNode_SequenceEvaluator_1E5C89B0437C6ECAAEAD3C9930131FBD;// 0xA980(0x0070)
	struct FAnimNode_TwoWayBlend                       AnimGraphNode_TwoWayBlend_9DC4A06D4B5CC99B884D9FA724AC2A07;// 0xA9F0(0x0120)
	struct FAnimNode_SequenceEvaluator                 AnimGraphNode_SequenceEvaluator_42F2812F48269C3D274A1E85B28DC5F4;// 0xAB10(0x0070)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_3727C55E47F442D7FAD1BD8046773F10;// 0xAB80(0x00B0)
	struct FAnimNode_LayeredBoneBlend                  AnimGraphNode_LayeredBoneBlend_62C90D614705E35D616E6FA18B0830A3;// 0xAC30(0x00E0)
	struct FAnimNode_BlendListByBool                   AnimGraphNode_BlendListByBool_84CFC89C431486EA92B4C19A9C8F9A38;// 0xAD10(0x00D0)
	struct FAnimNode_SequenceEvaluator                 AnimGraphNode_SequenceEvaluator_0C5806234646BC9B91FC49BEA96DD40F;// 0xADE0(0x0070)
	struct FAnimNode_BlendListByEnum                   AnimGraphNode_BlendListByEnum_8A89B11646C0EABB4DB11C99E7E7A5CE;// 0xAE50(0x00E0)
	struct FAnimNode_SequenceEvaluator                 AnimGraphNode_SequenceEvaluator_77CB344E4488111A8431118F0AC4DED6;// 0xAF30(0x0070)
	struct FAnimNode_TwoWayBlend                       AnimGraphNode_TwoWayBlend_736042B54C164CD62B768D85C709AB9B;// 0xAFA0(0x0120)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_E05DA50D41F92DC0CA4EE991528E547C;// 0xB0C0(0x00B0)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_91AE2AAF4753A73ABDD783B4D61FB54A;// 0xB170(0x00B0)
	struct FAnimNode_SequenceEvaluator                 AnimGraphNode_SequenceEvaluator_BE1FFFD04063214935B694B5D003C60E;// 0xB220(0x0070)
	struct FAnimNode_TwoWayBlend                       AnimGraphNode_TwoWayBlend_36136B9F4AFE69173E5D7D9663485094;// 0xB290(0x0120)
	struct FAnimNode_SequenceEvaluator                 AnimGraphNode_SequenceEvaluator_4239456C4F154383E0EAA49D54F86EF9;// 0xB3B0(0x0070)
	struct FAnimNode_TwoWayBlend                       AnimGraphNode_TwoWayBlend_89B5BE124FF672B91B170384C3FA877F;// 0xB420(0x0120)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_28D29C01444EF58C9C780BAE9960F115;// 0xB540(0x00B0)
	struct FAnimNode_SequenceEvaluator                 AnimGraphNode_SequenceEvaluator_A01AE8D0402533CCC2D1E28C6147D69E;// 0xB5F0(0x0070)
	struct FAnimNode_TwoWayBlend                       AnimGraphNode_TwoWayBlend_9777CE794589C65648A6EF9AC2C5AF74;// 0xB660(0x0120)
	struct FAnimNode_TwoWayBlend                       AnimGraphNode_TwoWayBlend_19751AD04FEC6030DBE51DBFDE698B80;// 0xB780(0x0120)
	struct FAnimNode_SequenceEvaluator                 AnimGraphNode_SequenceEvaluator_4538F6FC44F18A8501ABD881113EB9B4;// 0xB8A0(0x0070)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_45C1A2CB4AF4DEA53B6EA7B2F28BAAAD;// 0xB910(0x00B0)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_AE7013CE44A08C408857B2977BBAA5E2;// 0xB9C0(0x00B0)
	struct FAnimNode_BlendSpacePlayer                  AnimGraphNode_BlendSpacePlayer_D3E14E5C48B517FE2A69EF830903C65C;// 0xBA70(0x0128)
	struct FAnimNode_TwoWayBlend                       AnimGraphNode_TwoWayBlend_1B77C1554F00FA6AA0B604B6261581FC;// 0xBB98(0x0120)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_1995AEE6405E24BB634D27BEF2AF6ABD;// 0xBCB8(0x00B0)
	struct FAnimNode_BlendSpacePlayer                  AnimGraphNode_BlendSpacePlayer_D82A84B04E985746022E8C88AD031020;// 0xBD68(0x0128)
	struct FAnimNode_TwoWayBlend                       AnimGraphNode_TwoWayBlend_B1C753374569B0C7C906B687660378C6;// 0xBE90(0x0120)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_F28EAE0841F00DCD9065BB83E7D13F69;// 0xBFB0(0x00B0)
	struct FAnimNode_TwoWayBlend                       AnimGraphNode_TwoWayBlend_95E1C1244D6CA6A328A9E6AB27CBFCBA;// 0xC060(0x0120)
	struct FAnimNode_BlendSpacePlayer                  AnimGraphNode_BlendSpacePlayer_647BB0FA4069DD3187495A9CA3E6D87D;// 0xC180(0x0128)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_5CEC17F9412462C50D56D98D47BEA900;// 0xC2A8(0x00B0)
	struct FAnimNode_TwoWayBlend                       AnimGraphNode_TwoWayBlend_B38CCCC94809907F50065A82646B5E51;// 0xC358(0x0120)
	struct FAnimNode_BlendSpacePlayer                  AnimGraphNode_BlendSpacePlayer_ED3671964B12724D60FAB081ABAA50AA;// 0xC478(0x0128)
	struct FAnimNode_TwoWayBlend                       AnimGraphNode_TwoWayBlend_C12460A74A252615D4D771BD2340C913;// 0xC5A0(0x0120)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_23C058854583D125562B20B8C008BC50;// 0xC6C0(0x00B0)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_87DFD70A4929078C36A6749D787B9F49;// 0xC770(0x00B0)
	struct FAnimNode_TwoWayBlend                       AnimGraphNode_TwoWayBlend_A3E8EA3D4B613571BB62A09AD7CF7D6B;// 0xC820(0x0120)
	struct FAnimNode_BlendSpacePlayer                  AnimGraphNode_BlendSpacePlayer_46ED49AF4B064B2DE42606BE830EB429;// 0xC940(0x0128)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_0E303FF7496532240F58A8BC436CBE6E;// 0xCA68(0x00B0)
	struct FAnimNode_BlendSpacePlayer                  AnimGraphNode_BlendSpacePlayer_BDFB0A294D805E7CBF0C6CB6E8343C83;// 0xCB18(0x0128)
	struct FAnimNode_TwoWayBlend                       AnimGraphNode_TwoWayBlend_6874A4104ED66E6003A0C49F09F29809;// 0xCC40(0x0120)
	struct FAnimNode_Root                              AnimGraphNode_StateResult_49C9E62849764CBCD3A7AEB2E50B93C4;// 0xCD60(0x0048)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_1D15B60D49E02C6FCA89CA85167BD7A5;// 0xCDA8(0x00B0)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_F3F79E0449EABC24A05999918B3E51B8;// 0xCE58(0x00B0)
	struct FAnimNode_LayeredBoneBlend                  AnimGraphNode_LayeredBoneBlend_090F5CBA42C02F7B41A5DC9E39A1B1DD;// 0xCF08(0x00E0)
	struct FAnimNode_BlendListByBool                   AnimGraphNode_BlendListByBool_42BB08774E4403BEDA7D79B6850D4AD3;// 0xCFE8(0x00D0)
	struct FAnimNode_SequenceEvaluator                 AnimGraphNode_SequenceEvaluator_78FD9B7941CD2AA026D3FFB101CCC975;// 0xD0B8(0x0070)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_B31240E44BFC913CD1AAACBEB1626186;// 0xD128(0x00B0)
	struct FAnimNode_BlendListByEnum                   AnimGraphNode_BlendListByEnum_24166CE34966243A9EE5379F179A89F5;// 0xD1D8(0x00E0)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_8EF7B3654EDFFCC2EE6D4EB0E7759DF6;// 0xD2B8(0x00B0)
	struct FAnimNode_BlendListByBool                   AnimGraphNode_BlendListByBool_9CB2E2B941B7BCBBA0309498C65293EB;// 0xD368(0x00D0)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_85AD357441C233689334F586BF77EFF6;// 0xD438(0x00B0)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_2948DE004EFCA37075E1EAACAEAD6B62;// 0xD4E8(0x00B0)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_AC0F5E09494AA110C06F1AB274C256AD;// 0xD598(0x00B0)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_F0BD718841CF6CC44C0388ACB6A79223;// 0xD648(0x00B0)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_BBF61786417D1D14B836FDA38A863D99;// 0xD6F8(0x00B0)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_95372D9D40A622860920B3B010146442;// 0xD7A8(0x00B0)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_1817F28C4A5A122EB5CF0C9F09B3F53D;// 0xD858(0x00B0)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_0214CB374AB958525D3C1E9A2C22EFC6;// 0xD908(0x00B0)
	struct FAnimNode_RandomPlayer                      AnimGraphNode_RandomPlayer_CF1B805D4BF74221DF04F4B41B77F8BA;// 0xD9B8(0x0090)
	struct FAnimNode_RandomPlayer                      AnimGraphNode_RandomPlayer_5ADD4BC84AC694A1D804F19686899C69;// 0xDA48(0x0090)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_B2CC9607486CC7E44D687A8AE2AEDBEC;// 0xDAD8(0x00B0)
	struct FAnimNode_Root                              AnimGraphNode_StateResult_6E99F03E457586DB3E6828BA04C04481;// 0xDB88(0x0048)
	struct FAnimNode_StateMachine                      AnimGraphNode_StateMachine_B719B127411201A1A95AD08B389599AF;// 0xDBD0(0x00E0)
	struct FAnimNode_Root                              AnimGraphNode_StateResult_AD05AE0F4C34C89F88AE49B356ECFDAE;// 0xDCB0(0x0048)
	struct FAnimNode_StateMachine                      AnimGraphNode_StateMachine_615E755E4261BD12A5AD13AC20DDFC4F;// 0xDCF8(0x00E0)
	struct FAnimNode_ConvertLocalToComponentSpace      AnimGraphNode_LocalToComponentSpace_0CF8555244085B2D4901C6AAC7B27DF9;// 0xDDD8(0x0048)
	struct FAnimNode_TwoBoneIK                         AnimGraphNode_TwoBoneIK_CB2B612644702D31391D369891535852; // 0xDE20(0x0270)
	struct FAnimNode_Slot                              AnimGraphNode_Slot_B0C4631C43FC5354F954B4892AD87873;      // 0xE090(0x0070)
	struct FAnimNode_RotateRootBone                    AnimGraphNode_RotateRootBone_3B6C1F9545FAA9349FAC63B07B323E65;// 0xE100(0x00E0)
	struct FAnimNode_RotateRootBone                    AnimGraphNode_RotateRootBone_B10527FA4E79758B0AD662BFC79B5399;// 0xE1E0(0x00E0)
	struct FAnimNode_LayeredBoneBlend                  AnimGraphNode_LayeredBoneBlend_20AE03E841B764DA688DBC800E0E173B;// 0xE2C0(0x00E0)
	struct FAnimNode_UseCachedPose                     AnimGraphNode_UseCachedPose_1ADE49214B802D035A72B186C98E9BE5;// 0xE3A0(0x0050)
	struct FAnimNode_ModifyBone                        AnimGraphNode_ModifyBone_AF73FB33489796357D883FA0F7CDAACB;// 0xE3F0(0x0160)
	struct FAnimNode_ConvertLocalToComponentSpace      AnimGraphNode_LocalToComponentSpace_596765604E98902DBCE429B4FCCC2251;// 0xE550(0x0048)
	struct FAnimNode_ConvertComponentToLocalSpace      AnimGraphNode_ComponentToLocalSpace_4336EE314C5FF29C3AD41B9204AE9A28;// 0xE598(0x0048)
	struct FAnimNode_SaveCachedPose                    AnimGraphNode_SaveCachedPose_F95E3A7042EA478114E25196CE759CE4;// 0xE5E0(0x00E0)
	struct FAnimNode_UseCachedPose                     AnimGraphNode_UseCachedPose_480E0C0B4B1E8FD58772D393DEECB7FB;// 0xE6C0(0x0050)
	struct FAnimNode_UseCachedPose                     AnimGraphNode_UseCachedPose_A713AD1E4A7021921E8444B5058BD5CC;// 0xE710(0x0050)
	struct FAnimNode_BlendListByBool                   AnimGraphNode_BlendListByBool_B69A70CA460C6239D2E83781D7305302;// 0xE760(0x00D0)
	struct FAnimNode_ModifyBone                        AnimGraphNode_ModifyBone_DB43FBD541FCA6487986C0B5A4E24AF7;// 0xE830(0x0160)
	struct FAnimNode_ConvertLocalToComponentSpace      AnimGraphNode_LocalToComponentSpace_C5242A304FC02BBC1919B8998A6686B0;// 0xE990(0x0048)
	struct FAnimNode_ConvertComponentToLocalSpace      AnimGraphNode_ComponentToLocalSpace_A0520A1F49D79A2F4EB0579F3F40EAFB;// 0xE9D8(0x0048)
	struct FAnimNode_BlendListByBool                   AnimGraphNode_BlendListByBool_19313FA84A6353DA22CE23AB6CC9FED6;// 0xEA20(0x00D0)
	struct FAnimNode_UseCachedPose                     AnimGraphNode_UseCachedPose_ADFA862244E0B3BDF75A99ADCA4B2B69;// 0xEAF0(0x0050)
	struct FAnimNode_ModifyBone                        AnimGraphNode_ModifyBone_22E3DA9A4B34965C23A4A1A949D72DA9;// 0xEB40(0x0160)
	struct FAnimNode_ConvertLocalToComponentSpace      AnimGraphNode_LocalToComponentSpace_C94DC43D487A8B943D92A68654EB8696;// 0xECA0(0x0048)
	struct FAnimNode_ConvertComponentToLocalSpace      AnimGraphNode_ComponentToLocalSpace_935A58004094A05772E90E93A378A31A;// 0xECE8(0x0048)
	struct FAnimNode_RotationOffsetBlendSpace          AnimGraphNode_RotationOffsetBlendSpace_2E1677EF4A478528E3E1D4ACCD15357F;// 0xED30(0x0200)
	struct FAnimNode_SaveCachedPose                    AnimGraphNode_SaveCachedPose_0FFFCB2941AC292487D2DDB428C829A5;// 0xEF30(0x00E0)
	struct FAnimNode_UseCachedPose                     AnimGraphNode_UseCachedPose_396CD3444F449F3C0294CEB5C5B9723D;// 0xF010(0x0050)
	struct FAnimNode_UseCachedPose                     AnimGraphNode_UseCachedPose_CBF84E5748FD1E9355FA0EA1F89E5C7C;// 0xF060(0x0050)
	struct FAnimNode_RotationOffsetBlendSpace          AnimGraphNode_RotationOffsetBlendSpace_A0F96F9F430476DE4227E894FE84C362;// 0xF0B0(0x0200)
	struct FAnimNode_UseCachedPose                     AnimGraphNode_UseCachedPose_38B1002F44F325CCD9873BA04F2C6FA4;// 0xF2B0(0x0050)
	struct FAnimNode_BlendListByBool                   AnimGraphNode_BlendListByBool_810D95F34E3305277FB36FB489D2E7BB;// 0xF300(0x00D0)
	struct FAnimNode_UseCachedPose                     AnimGraphNode_UseCachedPose_7093652E43AD9EB549F24DA856209B0F;// 0xF3D0(0x0050)
	struct FAnimNode_RotationOffsetBlendSpace          AnimGraphNode_RotationOffsetBlendSpace_63CD46E0404D303FABCAD8A3E2DC70BE;// 0xF420(0x0200)
	struct FAnimNode_UseCachedPose                     AnimGraphNode_UseCachedPose_6F5E695949CC7BFAA08F1BA26699BEC0;// 0xF620(0x0050)
	struct FAnimNode_BlendListByBool                   AnimGraphNode_BlendListByBool_4F4D47F44434EBD5B7276EAEC38E4DAF;// 0xF670(0x00D0)
	struct FAnimNode_ModifyBone                        AnimGraphNode_ModifyBone_DF50F8E44024C35D6532658082CE8B82;// 0xF740(0x0160)
	struct FAnimNode_ConvertComponentToLocalSpace      AnimGraphNode_ComponentToLocalSpace_32415A7946EBE770095DB69A016CD80C;// 0xF8A0(0x0048)
	struct FAnimNode_ConvertLocalToComponentSpace      AnimGraphNode_LocalToComponentSpace_A11652F84A7EFCF1997E68B9AE044F26;// 0xF8E8(0x0048)
	struct FAnimNode_UseCachedPose                     AnimGraphNode_UseCachedPose_ABDFB42F4907610C132DE789785B5B3A;// 0xF930(0x0050)
	struct FAnimNode_UseCachedPose                     AnimGraphNode_UseCachedPose_166AF49C431F8DA6AD2AF08C763B8DAA;// 0xF980(0x0050)
	struct FAnimNode_BlendListByBool                   AnimGraphNode_BlendListByBool_9EB2D081453F8CBD09F253AE65D59507;// 0xF9D0(0x00D0)
	struct FAnimNode_ConvertComponentToLocalSpace      AnimGraphNode_ComponentToLocalSpace_C4F0A7B74431A18FF535AA9B06306886;// 0xFAA0(0x0048)
	struct FAnimNode_SaveCachedPose                    AnimGraphNode_SaveCachedPose_B1FD48304B3A6F37B85D5BBDDD8EA492;// 0xFAE8(0x00E0)
	unsigned char                                      UnknownData00[0x8];                                       // 0xFBC8(0x0008) MISSED OFFSET
	struct FAnimNode_TwoBoneIK                         AnimGraphNode_TwoBoneIK_D4A82C634C328915A22DC6B4CFEEF962; // 0xFBD0(0x0270)
	struct FAnimNode_UseCachedPose                     AnimGraphNode_UseCachedPose_693D69EE416DEF2C2AC4A6905EDAD6BC;// 0xFE40(0x0050)
	struct FAnimNode_Slot                              AnimGraphNode_Slot_10C4469B4BB88A57AA7319820EDA1C52;      // 0xFE90(0x0070)
	struct FAnimNode_LayeredBoneBlend                  AnimGraphNode_LayeredBoneBlend_2D3F2882439C6D0B1AF3249DDD0782CB;// 0xFF00(0x00E0)
	struct FAnimNode_UseCachedPose                     AnimGraphNode_UseCachedPose_22C714314075880F26769E8475B8A62E;// 0xFFE0(0x0050)
	struct FAnimNode_RotationOffsetBlendSpace          AnimGraphNode_RotationOffsetBlendSpace_B47EEA42455A1085849AF8AEDDBFCEFA;// 0x10030(0x0200)
	struct FAnimNode_UseCachedPose                     AnimGraphNode_UseCachedPose_330D3619416CEAE55A4BC8B82A3F56D9;// 0x10230(0x0050)
	struct FAnimNode_UseCachedPose                     AnimGraphNode_UseCachedPose_A3B43656403E56D7486798986D0CE703;// 0x10280(0x0050)
	struct FAnimNode_UseCachedPose                     AnimGraphNode_UseCachedPose_30E0A1474C6911530E0277A5FDE5F501;// 0x102D0(0x0050)
	struct FAnimNode_RotationOffsetBlendSpace          AnimGraphNode_RotationOffsetBlendSpace_3A339BD04071E908CF80FEA47B77FE46;// 0x10320(0x0200)
	struct FAnimNode_RotationOffsetBlendSpace          AnimGraphNode_RotationOffsetBlendSpace_3F54C6DE44F1276530BC48BDE6DD5942;// 0x10520(0x0200)
	struct FAnimNode_UseCachedPose                     AnimGraphNode_UseCachedPose_8D396F944DF76A328C2621ACDBA0194B;// 0x10720(0x0050)
	struct FAnimNode_RotationOffsetBlendSpace          AnimGraphNode_RotationOffsetBlendSpace_21224E3247DC5261459B5E93D18EB8EB;// 0x10770(0x0200)
	struct FAnimNode_UseCachedPose                     AnimGraphNode_UseCachedPose_42F95B1845B0E453345F2F84DD39B630;// 0x10970(0x0050)
	struct FAnimNode_UseCachedPose                     AnimGraphNode_UseCachedPose_B31C0A1549B675A8E01DCDA62367C6C5;// 0x109C0(0x0050)
	struct FAnimNode_UseCachedPose                     AnimGraphNode_UseCachedPose_9E0ACA10433524CD3D8DF68ECA2A98D8;// 0x10A10(0x0050)
	struct FAnimNode_UseCachedPose                     AnimGraphNode_UseCachedPose_2F1B07D746594D7705F636913738D1CB;// 0x10A60(0x0050)
	struct FAnimNode_SaveCachedPose                    AnimGraphNode_SaveCachedPose_B7B9423D4956B6DF8660B1806FF168C7;// 0x10AB0(0x00E0)
	struct FAnimNode_UseCachedPose                     AnimGraphNode_UseCachedPose_F9DAE33F4F9ECB624C5F49898F92A457;// 0x10B90(0x0050)
	struct FAnimNode_Slot                              AnimGraphNode_Slot_76C2F3AC4AE22CBED3845BB7DD9766CB;      // 0x10BE0(0x0070)
	struct FAnimNode_LayeredBoneBlend                  AnimGraphNode_LayeredBoneBlend_24AF42644209742880B3CFBD708713CD;// 0x10C50(0x00E0)
	struct FAnimNode_SaveCachedPose                    AnimGraphNode_SaveCachedPose_2666DD0E45489279511A868F3ABF62E7;// 0x10D30(0x00E0)
	struct FAnimNode_ConvertComponentToLocalSpace      AnimGraphNode_ComponentToLocalSpace_9B528DEA4017EA21A743C6B0D62FF143;// 0x10E10(0x0048)
	struct FAnimNode_SaveCachedPose                    AnimGraphNode_SaveCachedPose_787D8C1F47A2AB2DECED10805786560F;// 0x10E58(0x00E0)
	struct FAnimNode_UseCachedPose                     AnimGraphNode_UseCachedPose_FC2BE49047297400F1F1F4B8175A7B45;// 0x10F38(0x0050)
	struct FAnimNode_BlendListByBool                   AnimGraphNode_BlendListByBool_1FF507C748AE39C53F6D28BB57CA995A;// 0x10F88(0x00D0)
	struct FAnimNode_ConvertLocalToComponentSpace      AnimGraphNode_LocalToComponentSpace_5B7C3C654A803D93CC1CDA9DF35DF5B2;// 0x11058(0x0048)
	struct FAnimNode_SaveCachedPose                    AnimGraphNode_SaveCachedPose_9B62A7874946A0E1F956A89E98514E2A;// 0x110A0(0x00E0)
	struct FAnimNode_RotationOffsetBlendSpace          AnimGraphNode_RotationOffsetBlendSpace_CB1BEA5944FD0F587E6F7EB7A174794F;// 0x11180(0x0200)
	struct FAnimNode_SaveCachedPose                    AnimGraphNode_SaveCachedPose_D2BA08674354C88081D13293F80F0564;// 0x11380(0x00E0)
	struct FAnimNode_UseCachedPose                     AnimGraphNode_UseCachedPose_FF8617E34188BFB8810B3DA7FCC4C061;// 0x11460(0x0050)
	struct FAnimNode_UseCachedPose                     AnimGraphNode_UseCachedPose_5C9CBAF94E73494EA9463BB20D2A3C8F;// 0x114B0(0x0050)
	struct FAnimNode_UseCachedPose                     AnimGraphNode_UseCachedPose_B4D8517C42B2AE43B93FF19D341A7AFE;// 0x11500(0x0050)
	struct FAnimNode_RotationOffsetBlendSpace          AnimGraphNode_RotationOffsetBlendSpace_D730273C49278AEC8DB95CB2A1B5FE55;// 0x11550(0x0200)
	struct FAnimNode_UseCachedPose                     AnimGraphNode_UseCachedPose_B805FF104A34FF973493CAB595443318;// 0x11750(0x0050)
	struct FAnimNode_UseCachedPose                     AnimGraphNode_UseCachedPose_D1E649E747E131F1963BB9B495C9D81A;// 0x117A0(0x0050)
	struct FAnimNode_RotationOffsetBlendSpace          AnimGraphNode_RotationOffsetBlendSpace_B2D703424DFF3D4AF88A66877C782F21;// 0x117F0(0x0200)
	struct FAnimNode_RotationOffsetBlendSpace          AnimGraphNode_RotationOffsetBlendSpace_605676AF4E4EEED78F58CAA3CAAA34AB;// 0x119F0(0x0200)
	struct FAnimNode_UseCachedPose                     AnimGraphNode_UseCachedPose_16A8ECF4484530D2C4C7A1BCED5A58BE;// 0x11BF0(0x0050)
	struct FAnimNode_TwoBoneIK                         AnimGraphNode_TwoBoneIK_E9A238054F40EA57F693B8AD8AD92D19; // 0x11C40(0x0270)
	struct FAnimNode_ModifyBone                        AnimGraphNode_ModifyBone_C256A5814C448444FE086BA7CFD03903;// 0x11EB0(0x0160)
	struct FAnimNode_TwoBoneIK                         AnimGraphNode_TwoBoneIK_C3DEA9394314270B9CFF0D9BCDE8CF49; // 0x12010(0x0270)
	struct FAnimNode_ModifyBone                        AnimGraphNode_ModifyBone_57ADFEF348DD5367D1503FAFE6CE41C4;// 0x12280(0x0160)
	struct FAnimNode_ModifyBone                        AnimGraphNode_ModifyBone_4529F8C0436819B43F6F93AF264EF4FF;// 0x123E0(0x0160)
	struct FAnimNode_SaveCachedPose                    AnimGraphNode_SaveCachedPose_ED5FBC9243DB9BB43E2CBA81D6AF5100;// 0x12540(0x00E0)
	struct FAnimNode_TransitionResult                  AnimGraphNode_TransitionResult_C49A00BD42F2AFE65134C2BC953B43B4;// 0x12620(0x0048)
	struct FAnimNode_TransitionResult                  AnimGraphNode_TransitionResult_6B013E22419121B7B92D03B33BEC63A1;// 0x12668(0x0048)
	struct FAnimNode_TransitionResult                  AnimGraphNode_TransitionResult_D5FAA275488FCE05ACB61D88091EEBF9;// 0x126B0(0x0048)
	struct FAnimNode_TransitionResult                  AnimGraphNode_TransitionResult_116069884AD09F30082899AC7D4DF193;// 0x126F8(0x0048)
	struct FAnimNode_TransitionResult                  AnimGraphNode_TransitionResult_6CFECEE9497F1324C33EFAA7702DBBA0;// 0x12740(0x0048)
	struct FAnimNode_TransitionResult                  AnimGraphNode_TransitionResult_62F55133423E9C2053CAA09A7CE81877;// 0x12788(0x0048)
	struct FAnimNode_TransitionResult                  AnimGraphNode_TransitionResult_42C436BA4CFDA7B67B21D0A7F0F0CCFB;// 0x127D0(0x0048)
	struct FAnimNode_TransitionResult                  AnimGraphNode_TransitionResult_C906738944C90C1E5FD2959E58B0A530;// 0x12818(0x0048)
	struct FAnimNode_TransitionResult                  AnimGraphNode_TransitionResult_37DAD723484CAF4506B71380789C3064;// 0x12860(0x0048)
	struct FAnimNode_TransitionResult                  AnimGraphNode_TransitionResult_9BFC5583466CED101024CDAD248900FA;// 0x128A8(0x0048)
	struct FAnimNode_TransitionResult                  AnimGraphNode_TransitionResult_7BA637554FB2B960A3CDE19E0AAE05E1;// 0x128F0(0x0048)
	struct FAnimNode_TransitionResult                  AnimGraphNode_TransitionResult_E5FB76784DA620876149CE8BFA1A7B36;// 0x12938(0x0048)
	struct FAnimNode_TransitionResult                  AnimGraphNode_TransitionResult_1EC4EF954D80087025DF33A329AE49F2;// 0x12980(0x0048)
	struct FAnimNode_TransitionResult                  AnimGraphNode_TransitionResult_BBC7FAF64E7C454AFFF375B21E97BADB;// 0x129C8(0x0048)
	struct FAnimNode_BlendSpacePlayer                  AnimGraphNode_BlendSpacePlayer_4A417BFA448F22ED84C83AA2F711A085;// 0x12A10(0x0128)
	struct FAnimNode_Root                              AnimGraphNode_StateResult_4DF5DDC249CAACE1F5F734816DD2FD77;// 0x12B38(0x0048)
	struct FAnimNode_StateMachine                      AnimGraphNode_StateMachine_6F8588454DD5507335676CB5D161798A;// 0x12B80(0x00E0)
	struct FAnimNode_Root                              AnimGraphNode_StateResult_278E05F0479D098B747729AFA6F583FB;// 0x12C60(0x0048)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_9B523C0A4C23B435427CCDA0C69FB032;// 0x12CA8(0x00B0)
	struct FAnimNode_Root                              AnimGraphNode_StateResult_262A41684AF826E783061192A9F5C394;// 0x12D58(0x0048)
	struct FAnimNode_BlendSpacePlayer                  AnimGraphNode_BlendSpacePlayer_657EABC84EDCD166D8A1438F3D7DB38D;// 0x12DA0(0x0128)
	struct FAnimNode_Root                              AnimGraphNode_StateResult_A62D0F97438AB0DAF2D5579625CD401B;// 0x12EC8(0x0048)
	struct FAnimNode_TransitionResult                  AnimGraphNode_TransitionResult_FDFA632149E7323D13B5FD9428A42C48;// 0x12F10(0x0048)
	struct FAnimNode_TransitionResult                  AnimGraphNode_TransitionResult_1C15078A4F88F2D846A04384785AE1B3;// 0x12F58(0x0048)
	struct FAnimNode_TransitionResult                  AnimGraphNode_TransitionResult_B2B5A0194E74CA635743C0ABE2045F99;// 0x12FA0(0x0048)
	struct FAnimNode_TransitionResult                  AnimGraphNode_TransitionResult_98B8AE694AE7EA26766CF69F398ECDE3;// 0x12FE8(0x0048)
	struct FAnimNode_TransitionResult                  AnimGraphNode_TransitionResult_9BC95D0C4A5CA7DAF9AF0882E07F2160;// 0x13030(0x0048)
	struct FAnimNode_TransitionResult                  AnimGraphNode_TransitionResult_A7C8155F4FFB3540B7AE689ED422E068;// 0x13078(0x0048)
	struct FAnimNode_RefPose                           AnimGraphNode_IdentityPose_29CF57364EB186A985A941A00C0E2666;// 0x130C0(0x0038)
	struct FAnimNode_Root                              AnimGraphNode_StateResult_A779425E43A7037E28ECF1B465F3D963;// 0x130F8(0x0048)
	struct FAnimNode_BlendSpacePlayer                  AnimGraphNode_BlendSpacePlayer_A79BE23A4D3B4C0DB90334A07B8F8DAB;// 0x13140(0x0128)
	struct FAnimNode_Root                              AnimGraphNode_StateResult_BBF47D9F440E53D1EBD93F9B95086583;// 0x13268(0x0048)
	struct FAnimNode_BlendListByBool                   AnimGraphNode_BlendListByBool_B821324E4507C9C2A78A1487232C7309;// 0x132B0(0x00D0)
	struct FAnimNode_BlendSpacePlayer                  AnimGraphNode_BlendSpacePlayer_EDB04D304DF3B489E14964BD6ADC91BF;// 0x13380(0x0128)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_8889090543F820AC9BBE9D95671373D3;// 0x134A8(0x00B0)
	struct FAnimNode_Root                              AnimGraphNode_StateResult_6B48D67846BE0B8993D118BF0401B8F9;// 0x13558(0x0048)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_30C71C90437C5593CB5BC29E693E8BB7;// 0x135A0(0x00B0)
	struct FAnimNode_Root                              AnimGraphNode_StateResult_3F39D35E464C0ACDDE7086957C24C214;// 0x13650(0x0048)
	struct FAnimNode_StateMachine                      AnimGraphNode_StateMachine_BD29B1EB47540437C70B5A872461D821;// 0x13698(0x00E0)
	struct FAnimNode_Root                              AnimGraphNode_StateResult_3A43BB584C7FD6DCFA9959AF4E8C0D21;// 0x13778(0x0048)
	struct FAnimNode_TransitionResult                  AnimGraphNode_TransitionResult_8DEF606645F5E76704FE0FB8E1088958;// 0x137C0(0x0048)
	struct FAnimNode_TransitionResult                  AnimGraphNode_TransitionResult_C461689A434A1644DC1A988268CBF2A3;// 0x13808(0x0048)
	struct FAnimNode_TransitionResult                  AnimGraphNode_TransitionResult_176DE7604F47F97A838AC2B8BDE8AC97;// 0x13850(0x0048)
	struct FAnimNode_TransitionResult                  AnimGraphNode_TransitionResult_19A26A544E49089A80A5AC81361C4DDF;// 0x13898(0x0048)
	struct FAnimNode_TransitionResult                  AnimGraphNode_TransitionResult_3D64047842128D0EDF12BE80DFCC9048;// 0x138E0(0x0048)
	struct FAnimNode_BlendSpacePlayer                  AnimGraphNode_BlendSpacePlayer_FB7E70FF474FE748C71BE99A7293D5C1;// 0x13928(0x0128)
	struct FAnimNode_Root                              AnimGraphNode_StateResult_7F62657D44BB0AE0FB00C4BF43B976B2;// 0x13A50(0x0048)
	struct FAnimNode_RefPose                           AnimGraphNode_IdentityPose_E31D11D348C730A0031C20B209F7B907;// 0x13A98(0x0038)
	struct FAnimNode_Root                              AnimGraphNode_StateResult_7D37BCE24773CCDE0ABFC4A4488F06C9;// 0x13AD0(0x0048)
	struct FAnimNode_BlendSpacePlayer                  AnimGraphNode_BlendSpacePlayer_422433EC40ED29F1A1F6C7835638527B;// 0x13B18(0x0128)
	struct FAnimNode_BlendSpacePlayer                  AnimGraphNode_BlendSpacePlayer_EB11EFDE448F168B3EC3A39C956278C0;// 0x13C40(0x0128)
	struct FAnimNode_BlendListByBool                   AnimGraphNode_BlendListByBool_DE52E98545163D8FF4E12F8A5682E592;// 0x13D68(0x00D0)
	struct FAnimNode_Root                              AnimGraphNode_StateResult_9CC4EA14464E1CC9FDD7C6AC128DEDD7;// 0x13E38(0x0048)
	struct FAnimNode_BlendSpacePlayer                  AnimGraphNode_BlendSpacePlayer_D6830A8E46BE1D01011CC7A8BCF47605;// 0x13E80(0x0128)
	struct FAnimNode_Root                              AnimGraphNode_StateResult_700F2BE343B9663B08F8BDA6B52A27E4;// 0x13FA8(0x0048)
	struct FAnimNode_StateMachine                      AnimGraphNode_StateMachine_CA8F9C344AEA53162615419E0729935F;// 0x13FF0(0x00E0)
	struct FAnimNode_Root                              AnimGraphNode_StateResult_36E321B941E8B322B1E4ABA54622D04D;// 0x140D0(0x0048)
	struct FAnimNode_TransitionResult                  AnimGraphNode_TransitionResult_D504744E430AD7819348F0A7307A920C;// 0x14118(0x0048)
	struct FAnimNode_TransitionResult                  AnimGraphNode_TransitionResult_6007C8A3477EC17F8054B18DEFCF1196;// 0x14160(0x0048)
	struct FAnimNode_TransitionResult                  AnimGraphNode_TransitionResult_224EDCBE4C8998791BE2C285DC94AFDE;// 0x141A8(0x0048)
	struct FAnimNode_TransitionResult                  AnimGraphNode_TransitionResult_ACF2A9F84C93C954DBACEDA418CBAC7F;// 0x141F0(0x0048)
	struct FAnimNode_TransitionResult                  AnimGraphNode_TransitionResult_C84C850646FEDBCD98421C9E68133AFE;// 0x14238(0x0048)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_FC9577E8447D3726214D42847ABB7CF3;// 0x14280(0x00B0)
	struct FAnimNode_BlendListByBool                   AnimGraphNode_BlendListByBool_16539DAA4FD0EF3FECC2B0BF8831ECA9;// 0x14330(0x00D0)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_D415854F4AF84A67FD65C182D282A65D;// 0x14400(0x00B0)
	struct FAnimNode_Root                              AnimGraphNode_StateResult_A3FA371B4247FD5E8E4FDDA3786546AE;// 0x144B0(0x0048)
	struct FAnimNode_BlendSpacePlayer                  AnimGraphNode_BlendSpacePlayer_8E492C1640B23718A2108AB2A2415A7E;// 0x144F8(0x0128)
	struct FAnimNode_Root                              AnimGraphNode_StateResult_6537646E46B7E28C6A3BFEAA876BB8C6;// 0x14620(0x0048)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_CB93C11B46DC8822DA179FA294A830EB;// 0x14668(0x00B0)
	struct FAnimNode_BlendSpacePlayer                  AnimGraphNode_BlendSpacePlayer_09DFFEA5415165F92D40D6AF93972440;// 0x14718(0x0128)
	struct FAnimNode_TwoWayBlend                       AnimGraphNode_TwoWayBlend_CC359708439409A6754B3F9EBAB736E1;// 0x14840(0x0120)
	struct FAnimNode_Root                              AnimGraphNode_StateResult_F9859A2E42D0EFF60ED210B79C8F83DC;// 0x14960(0x0048)
	struct FAnimNode_SequencePlayer                    AnimGraphNode_SequencePlayer_E01EF50146A17815788368AF721A9906;// 0x149A8(0x00B0)
	struct FAnimNode_Root                              AnimGraphNode_StateResult_E537A04A437315727C0074AAEA5F73D1;// 0x14A58(0x0048)
	struct FAnimNode_StateMachine                      AnimGraphNode_StateMachine_FAB3AE3C41A6ECB607CE708F27A2EA24;// 0x14AA0(0x00E0)
	struct FAnimNode_Root                              AnimGraphNode_StateResult_C58FEEC94016E7D6950C9FBD7BF8EA67;// 0x14B80(0x0048)
	struct FAnimNode_StateMachine                      AnimGraphNode_StateMachine_4C40A39F441484AE359C659BFDD0A987;// 0x14BC8(0x00E0)
	struct FAnimNode_Root                              AnimGraphNode_Root_83792EF84031E4A00BEC78A3C8736BC8;      // 0x14CA8(0x0048)
	struct FAnimNode_Slot                              AnimGraphNode_Slot_693E6C64438454C16564D6B996FBF8D5;      // 0x14CF0(0x0070)
	struct FAnimNode_LayeredBoneBlend                  AnimGraphNode_LayeredBoneBlend_840FD7304DB3D2DDD9F5198A6222E00E;// 0x14D60(0x00E0)
	struct FAnimNode_Slot                              AnimGraphNode_Slot_521559F64D302D20B73302BE1DF8751C;      // 0x14E40(0x0070)
	struct FAnimNode_LayeredBoneBlend                  AnimGraphNode_LayeredBoneBlend_30E6A3A34BDCC7AC720219B29ECD405B;// 0x14EB0(0x00E0)
	struct FAnimNode_SaveCachedPose                    AnimGraphNode_SaveCachedPose_1C01D76B47B0A82E5B9986AA2763FCD8;// 0x14F90(0x00E0)
	struct FAnimNode_UseCachedPose                     AnimGraphNode_UseCachedPose_364DF7254A8E080812E89894807AEF5F;// 0x15070(0x0050)
	struct FAnimNode_UseCachedPose                     AnimGraphNode_UseCachedPose_8244B0FF4E1E06F5B1EF98BE7D916BA9;// 0x150C0(0x0050)
	struct FAnimNode_BlendListByEnum                   AnimGraphNode_BlendListByEnum_0EC62AB644A4DBFD3B333AB4B468EF1D;// 0x15110(0x00E0)
	struct FAnimNode_UseCachedPose                     AnimGraphNode_UseCachedPose_F13283AB4597150DF73D1995375BCFD4;// 0x151F0(0x0050)
	struct FAnimNode_BlendListByBool                   AnimGraphNode_BlendListByBool_BF454E4349A73784CC5A13B75AD5B8E8;// 0x15240(0x00D0)
	struct FAnimNode_RotationOffsetBlendSpace          AnimGraphNode_RotationOffsetBlendSpace_FC95377946F2126C81199194A72E0A85;// 0x15310(0x0200)
	struct FAnimNode_UseCachedPose                     AnimGraphNode_UseCachedPose_B6FE23DF402D11CBF1B75E94CD0558F5;// 0x15510(0x0050)
	struct FAnimNode_RotationOffsetBlendSpace          AnimGraphNode_RotationOffsetBlendSpace_20FB08DB4BB7B80DF8CE4596D45BCD3B;// 0x15560(0x0200)
	class UCharacterMovementComponent*                 mCharacterMovementComponent;                              // 0x15760(0x0008) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, InstancedReference, IsPlainOldData)
	struct FVector                                     mActorLocation;                                           // 0x15768(0x000C) (Edit, BlueprintVisible, DisableEditOnInstance, IsPlainOldData)
	TEnumAsByte<EMovementMode>                         mMovementMode;                                            // 0x15774(0x0001) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char                                      UnknownData01[0x3];                                       // 0x15775(0x0003) MISSED OFFSET
	float                                              mDeltaTime;                                               // 0x15778(0x0004) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	bool                                               mIsLanding;                                               // 0x1577C(0x0001) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	bool                                               mIsFallingLastTick;                                       // 0x1577D(0x0001) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	bool                                               mStandingStill;                                           // 0x1577E(0x0001) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char                                      UnknownData02[0x1];                                       // 0x1577F(0x0001) MISSED OFFSET
	float                                              mDesiredDirection;                                        // 0x15780(0x0004) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	struct FVector                                     mVelocityLocalNormalizedLastTick;                         // 0x15784(0x000C) (Edit, BlueprintVisible, DisableEditOnInstance, IsPlainOldData)
	float                                              mChangeDirectionAngle;                                    // 0x15790(0x0004) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	float                                              mStopDirection;                                           // 0x15794(0x0004) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	bool                                               mLeanAsDirectionChange;                                   // 0x15798(0x0001) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	bool                                               mPlayDirectionChange;                                     // 0x15799(0x0001) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	bool                                               mPlayStop;                                                // 0x1579A(0x0001) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char                                      UnknownData03[0x1];                                       // 0x1579B(0x0001) MISSED OFFSET
	struct FVector                                     mStandingStillLocation;                                   // 0x1579C(0x000C) (Edit, BlueprintVisible, DisableEditOnInstance, IsPlainOldData)
	float                                              mStandingStillLeanDirection;                              // 0x157A8(0x0004) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	float                                              mStandingStillLeanDistance;                               // 0x157AC(0x0004) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	bool                                               mStandingStillLastTick;                                   // 0x157B0(0x0001) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	bool                                               mPlayStopLean;                                            // 0x157B1(0x0001) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char                                      UnknownData04[0x2];                                       // 0x157B2(0x0002) MISSED OFFSET
	float                                              mStandingStillStopDirection;                              // 0x157B4(0x0004) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	struct FRotator                                    mRunLeanRotation;                                         // 0x157B8(0x000C) (Edit, BlueprintVisible, DisableEditOnInstance, IsPlainOldData)
	unsigned char                                      UnknownData05[0x4];                                       // 0x157C4(0x0004) MISSED OFFSET
	class USkeletalMeshComponent*                      mSkeletalmeshComponent;                                   // 0x157C8(0x0008) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, InstancedReference, IsPlainOldData)
	struct FTransform                                  mRootTransform;                                           // 0x157D0(0x0030) (Edit, BlueprintVisible, DisableEditOnInstance, IsPlainOldData)
	struct FVector                                     mRootLocation;                                            // 0x15800(0x000C) (Edit, BlueprintVisible, DisableEditOnInstance, IsPlainOldData)
	struct FVector                                     mIKFootLLocation;                                         // 0x1580C(0x000C) (Edit, BlueprintVisible, DisableEditOnInstance, IsPlainOldData)
	struct FVector                                     mIKFootRLocation;                                         // 0x15818(0x000C) (Edit, BlueprintVisible, DisableEditOnInstance, IsPlainOldData)
	struct FVector                                     mIKFootRootLocation;                                      // 0x15824(0x000C) (Edit, BlueprintVisible, DisableEditOnInstance, IsPlainOldData)
	float                                              mIKFootLOffset;                                           // 0x15830(0x0004) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	struct FRotator                                    mIKFootLRotationOffset;                                   // 0x15834(0x000C) (Edit, BlueprintVisible, DisableEditOnInstance, IsPlainOldData)
	float                                              mIKFootROffset;                                           // 0x15840(0x0004) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	struct FRotator                                    mIKFootRRotationOffset;                                   // 0x15844(0x000C) (Edit, BlueprintVisible, DisableEditOnInstance, IsPlainOldData)
	struct FRotator                                    mRootRotationOffset;                                      // 0x15850(0x000C) (Edit, BlueprintVisible, DisableEditOnInstance, IsPlainOldData)
	float                                              mSpeedLastTick;                                           // 0x1585C(0x0004) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	float                                              mDesiredActorRotationYawDirection;                        // 0x15860(0x0004) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	float                                              mFallingTime;                                             // 0x15864(0x0004) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	bool                                               mIsTumbling;                                              // 0x15868(0x0001) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	bool                                               mIsMontagePlaying;                                        // 0x15869(0x0001) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char                                      mCustomMovementMode;                                      // 0x1586A(0x0001) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char                                      UnknownData06[0x1];                                       // 0x1586B(0x0001) MISSED OFFSET
	float                                              mAimPitchLag;                                             // 0x1586C(0x0004) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	float                                              mAimYawLag;                                               // 0x15870(0x0004) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	struct FRotator                                    mAimRotation;                                             // 0x15874(0x000C) (Edit, BlueprintVisible, DisableEditOnInstance, IsPlainOldData)
	struct FRotator                                    mAimRotationLastTick;                                     // 0x15880(0x000C) (Edit, BlueprintVisible, DisableEditOnInstance, IsPlainOldData)
	struct FRotator                                    mAimRotationDelta;                                        // 0x1588C(0x000C) (Edit, BlueprintVisible, DisableEditOnInstance, IsPlainOldData)
	bool                                               mChainsawHasFuel;                                         // 0x15898(0x0001) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char                                      UnknownData07[0x3];                                       // 0x15899(0x0003) MISSED OFFSET
	float                                              mAG_StandingStillLeanDistanceAlpha;                       // 0x1589C(0x0004) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	bool                                               mAG_HasPositiveVectorLength;                              // 0x158A0(0x0001) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	bool                                               mAG_IsWalking;                                            // 0x158A1(0x0001) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char                                      UnknownData08[0x2];                                       // 0x158A2(0x0002) MISSED OFFSET
	float                                              mAG_InvertedAimPitch;                                     // 0x158A4(0x0004) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	bool                                               mAG_LeanStopToIdleTransition;                             // 0x158A8(0x0001) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	bool                                               mAG_HasNoAcceleration;                                    // 0x158A9(0x0001) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	bool                                               mAG_RunToSprintTransition;                                // 0x158AA(0x0001) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	bool                                               mAG_RunToChangeDirectionTransition;                       // 0x158AB(0x0001) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	bool                                               mAG_SprintToRunTransition;                                // 0x158AC(0x0001) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	bool                                               mAG_IsJumping;                                            // 0x158AD(0x0001) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	bool                                               mAG_IsFalling;                                            // 0x158AE(0x0001) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	bool                                               mAG_IdleToRunTransition;                                  // 0x158AF(0x0001) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	bool                                               mAG_IsSwimming;                                           // 0x158B0(0x0001) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char                                      UnknownData09[0x3];                                       // 0x158B1(0x0003) MISSED OFFSET
	struct FVector                                     mAG_MinIkFootOffsetVector;                                // 0x158B4(0x000C) (Edit, BlueprintVisible, DisableEditOnInstance, IsPlainOldData)
	struct FVector                                     mAG_IkFootLOffsetVector;                                  // 0x158C0(0x000C) (Edit, BlueprintVisible, DisableEditOnInstance, IsPlainOldData)
	struct FVector                                     mAG_IkFootROffsetVector;                                  // 0x158CC(0x000C) (Edit, BlueprintVisible, DisableEditOnInstance, IsPlainOldData)
	bool                                               mAG_TurnInPlaceArms;                                      // 0x158D8(0x0001) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	bool                                               mAG_JumpLoopToFallingTransition;                          // 0x158D9(0x0001) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	bool                                               mAG_FallingToJumpLoopTransition;                          // 0x158DA(0x0001) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char                                      UnknownData10[0x1];                                       // 0x158DB(0x0001) MISSED OFFSET
	struct FRotator                                    mAG_InvertedAimPitchRotator;                              // 0x158DC(0x000C) (Edit, BlueprintVisible, DisableEditOnInstance, IsPlainOldData)
	struct FRotator                                    mAG_AimPitchRotatorSprintClamped;                         // 0x158E8(0x000C) (Edit, BlueprintVisible, DisableEditOnInstance, IsPlainOldData)
	bool                                               mAG_UseArmBaseRotation;                                   // 0x158F4(0x0001) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char                                      UnknownData11[0x3];                                       // 0x158F5(0x0003) MISSED OFFSET
	struct FRotator                                    mAG_AimPitchRotatorSwimClamped;                           // 0x158F8(0x000C) (Edit, BlueprintVisible, DisableEditOnInstance, IsPlainOldData)
	bool                                               mAG_UseFootIK;                                            // 0x15904(0x0001) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	bool                                               AG_UseHandIK;                                             // 0x15905(0x0001) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char                                      UnknownData12[0x2];                                       // 0x15906(0x0002) MISSED OFFSET
	struct FRotator                                    mAG_InvertedAimYawRotator;                                // 0x15908(0x000C) (Edit, BlueprintVisible, DisableEditOnInstance, IsPlainOldData)
	bool                                               mAG_NothingEquipped;                                      // 0x15914(0x0001) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	bool                                               mIsJetpackThrusting;                                      // 0x15915(0x0001) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	bool                                               mHasNobeliskAmmo;                                         // 0x15916(0x0001) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("AnimBlueprintGeneratedClass Anim_1p.Anim_1p_C");
		return ptr;
	}


	void CalculateAnimGraphValues();
	void GetPlayerController(class AFGPlayerController** OutPlayerController);
	void IsEquipmentEquipped(class UClass* EquipmentClass, bool* IsEquiped);
	void EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_1p_AnimGraphNode_TransitionResult_EA87E8294D8EABDC183F65BF5E749D1E();
	void EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_1p_AnimGraphNode_BlendListByEnum_CC1A2B1945E10B7B29887BAF4DD28125();
	void EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_1p_AnimGraphNode_TransitionResult_3FEC73CD415CE6EA644F3A86A8396318();
	void EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_1p_AnimGraphNode_TransitionResult_8DA8A992420A431E9924B2ADBE3EEC11();
	void EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_1p_AnimGraphNode_BlendListByBool_04BE55DE4BDAF8E4297155B3FAD4912B();
	void EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_1p_AnimGraphNode_BlendListByBool_E4EE153048B41B2C8299A9A723F4A7CE();
	void EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_1p_AnimGraphNode_TransitionResult_C290BA2642DAC287EAEB10B8358EC88C();
	void EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_1p_AnimGraphNode_BlendListByBool_D725CE99432C6CF2E288D9B8906BBEBC();
	void EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_1p_AnimGraphNode_BlendListByBool_C446F2544F525016F2A25A90AB8B1637();
	void EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_1p_AnimGraphNode_BlendListByEnum_7215F8D6436EE5EA4DC3DF831ECDB30A();
	void EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_1p_AnimGraphNode_BlendSpacePlayer_8C59E95B4687323C83CCFE860D76B660();
	void EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_1p_AnimGraphNode_TransitionResult_1B7A325746C172AE5C0B46B794AE5F3B();
	void EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_1p_AnimGraphNode_BlendListByEnum_F3F23A7D4725B4CD568ADF9A00250B44();
	void EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_1p_AnimGraphNode_BlendSpacePlayer_4BB10171424F09F42F994A9CB73B009B();
	void EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_1p_AnimGraphNode_TransitionResult_3F088D9849F7BB96258384A8FA66C903();
	void EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_1p_AnimGraphNode_BlendListByEnum_682EE13E4C162D8A18D84D87844B36A8();
	void EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_1p_AnimGraphNode_BlendListByBool_ECCC88264F9300DED167ACB9070AFF57();
	void EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_1p_AnimGraphNode_TransitionResult_9EAA692B4875136C0123118C321CE9BC();
	void EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_1p_AnimGraphNode_TwoWayBlend_9DC4A06D4B5CC99B884D9FA724AC2A07();
	void EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_1p_AnimGraphNode_BlendListByBool_84CFC89C431486EA92B4C19A9C8F9A38();
	void EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_1p_AnimGraphNode_BlendListByEnum_8A89B11646C0EABB4DB11C99E7E7A5CE();
	void EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_1p_AnimGraphNode_TwoWayBlend_736042B54C164CD62B768D85C709AB9B();
	void EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_1p_AnimGraphNode_TwoWayBlend_36136B9F4AFE69173E5D7D9663485094();
	void EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_1p_AnimGraphNode_TwoWayBlend_89B5BE124FF672B91B170384C3FA877F();
	void EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_1p_AnimGraphNode_TwoWayBlend_9777CE794589C65648A6EF9AC2C5AF74();
	void EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_1p_AnimGraphNode_TwoWayBlend_19751AD04FEC6030DBE51DBFDE698B80();
	void EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_1p_AnimGraphNode_BlendSpacePlayer_D3E14E5C48B517FE2A69EF830903C65C();
	void EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_1p_AnimGraphNode_TwoWayBlend_1B77C1554F00FA6AA0B604B6261581FC();
	void EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_1p_AnimGraphNode_BlendSpacePlayer_D82A84B04E985746022E8C88AD031020();
	void EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_1p_AnimGraphNode_TwoWayBlend_B1C753374569B0C7C906B687660378C6();
	void EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_1p_AnimGraphNode_TwoWayBlend_95E1C1244D6CA6A328A9E6AB27CBFCBA();
	void EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_1p_AnimGraphNode_BlendSpacePlayer_647BB0FA4069DD3187495A9CA3E6D87D();
	void EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_1p_AnimGraphNode_TwoWayBlend_B38CCCC94809907F50065A82646B5E51();
	void EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_1p_AnimGraphNode_BlendSpacePlayer_ED3671964B12724D60FAB081ABAA50AA();
	void EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_1p_AnimGraphNode_TwoWayBlend_C12460A74A252615D4D771BD2340C913();
	void EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_1p_AnimGraphNode_TwoWayBlend_A3E8EA3D4B613571BB62A09AD7CF7D6B();
	void EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_1p_AnimGraphNode_BlendSpacePlayer_46ED49AF4B064B2DE42606BE830EB429();
	void EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_1p_AnimGraphNode_BlendSpacePlayer_BDFB0A294D805E7CBF0C6CB6E8343C83();
	void EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_1p_AnimGraphNode_TwoWayBlend_6874A4104ED66E6003A0C49F09F29809();
	void EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_1p_AnimGraphNode_TransitionResult_40E3382B4B538B1FC5BACDB687986EDB();
	void EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_1p_AnimGraphNode_TransitionResult_2025F2404EA061FA9D9697A9B542D25B();
	void EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_1p_AnimGraphNode_TransitionResult_8741F1A4423A331D860F629FE6A60CB3();
	void EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_1p_AnimGraphNode_TransitionResult_10B1324041E8974CD639CB91EA071499();
	void EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_1p_AnimGraphNode_TransitionResult_7F63D8814D03208D6BBAA29EF891D7F8();
	void EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_1p_AnimGraphNode_BlendListByEnum_A72EFCEB4FB0E6C451891FA9AE2361BE();
	void EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_1p_AnimGraphNode_BlendListByBool_68F2D8E4434D8ED200EBC4A512C84709();
	void EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_1p_AnimGraphNode_BlendSpacePlayer_D6C0685E408BBFC5EDB85DB32257F453();
	void EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_1p_AnimGraphNode_BlendListByBool_42BB08774E4403BEDA7D79B6850D4AD3();
	void EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_1p_AnimGraphNode_BlendListByEnum_24166CE34966243A9EE5379F179A89F5();
	void EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_1p_AnimGraphNode_BlendListByBool_9CB2E2B941B7BCBBA0309498C65293EB();
	void EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_1p_AnimGraphNode_BlendListByBool_599A6FCE45A0F124DEF114A3E45F195A();
	void EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_1p_AnimGraphNode_BlendSpacePlayer_088B7D584B0B84B4EB98978859751C5B();
	void EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_1p_AnimGraphNode_TransitionResult_B22AF35D4BCF08D326922D9EED21F2CB();
	void EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_1p_AnimGraphNode_TransitionResult_51B03D77497B352DA91F9280A6878691();
	void EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_1p_AnimGraphNode_RotateRootBone_3B6C1F9545FAA9349FAC63B07B323E65();
	void EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_1p_AnimGraphNode_RotateRootBone_B10527FA4E79758B0AD662BFC79B5399();
	void EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_1p_AnimGraphNode_ModifyBone_AF73FB33489796357D883FA0F7CDAACB();
	void EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_1p_AnimGraphNode_BlendListByBool_B69A70CA460C6239D2E83781D7305302();
	void EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_1p_AnimGraphNode_ModifyBone_DB43FBD541FCA6487986C0B5A4E24AF7();
	void EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_1p_AnimGraphNode_BlendListByBool_19313FA84A6353DA22CE23AB6CC9FED6();
	void EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_1p_AnimGraphNode_ModifyBone_22E3DA9A4B34965C23A4A1A949D72DA9();
	void EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_1p_AnimGraphNode_RotationOffsetBlendSpace_2E1677EF4A478528E3E1D4ACCD15357F();
	void EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_1p_AnimGraphNode_RotationOffsetBlendSpace_A0F96F9F430476DE4227E894FE84C362();
	void EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_1p_AnimGraphNode_BlendListByBool_810D95F34E3305277FB36FB489D2E7BB();
	void EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_1p_AnimGraphNode_RotationOffsetBlendSpace_63CD46E0404D303FABCAD8A3E2DC70BE();
	void EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_1p_AnimGraphNode_BlendListByBool_4F4D47F44434EBD5B7276EAEC38E4DAF();
	void EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_1p_AnimGraphNode_ModifyBone_DF50F8E44024C35D6532658082CE8B82();
	void EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_1p_AnimGraphNode_BlendListByBool_9EB2D081453F8CBD09F253AE65D59507();
	void EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_1p_AnimGraphNode_RotationOffsetBlendSpace_B47EEA42455A1085849AF8AEDDBFCEFA();
	void EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_1p_AnimGraphNode_RotationOffsetBlendSpace_3A339BD04071E908CF80FEA47B77FE46();
	void EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_1p_AnimGraphNode_RotationOffsetBlendSpace_3F54C6DE44F1276530BC48BDE6DD5942();
	void EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_1p_AnimGraphNode_RotationOffsetBlendSpace_21224E3247DC5261459B5E93D18EB8EB();
	void EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_1p_AnimGraphNode_BlendListByBool_1FF507C748AE39C53F6D28BB57CA995A();
	void EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_1p_AnimGraphNode_RotationOffsetBlendSpace_CB1BEA5944FD0F587E6F7EB7A174794F();
	void EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_1p_AnimGraphNode_RotationOffsetBlendSpace_D730273C49278AEC8DB95CB2A1B5FE55();
	void EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_1p_AnimGraphNode_RotationOffsetBlendSpace_B2D703424DFF3D4AF88A66877C782F21();
	void EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_1p_AnimGraphNode_RotationOffsetBlendSpace_605676AF4E4EEED78F58CAA3CAAA34AB();
	void EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_1p_AnimGraphNode_ModifyBone_C256A5814C448444FE086BA7CFD03903();
	void EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_1p_AnimGraphNode_ModifyBone_57ADFEF348DD5367D1503FAFE6CE41C4();
	void EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_1p_AnimGraphNode_ModifyBone_4529F8C0436819B43F6F93AF264EF4FF();
	void EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_1p_AnimGraphNode_TransitionResult_C49A00BD42F2AFE65134C2BC953B43B4();
	void EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_1p_AnimGraphNode_BlendListByBool_6E244A9D44FC15B17498D9BB01211FE4();
	void EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_1p_AnimGraphNode_TransitionResult_6B013E22419121B7B92D03B33BEC63A1();
	void EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_1p_AnimGraphNode_TransitionResult_D5FAA275488FCE05ACB61D88091EEBF9();
	void EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_1p_AnimGraphNode_BlendListByEnum_1A59E2DB4793058EFF6EF6B6E652AE42();
	void EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_1p_AnimGraphNode_TransitionResult_116069884AD09F30082899AC7D4DF193();
	void EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_1p_AnimGraphNode_TransitionResult_6CFECEE9497F1324C33EFAA7702DBBA0();
	void EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_1p_AnimGraphNode_TransitionResult_F948AAE7488B4C18BC7BD3995671074F();
	void EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_1p_AnimGraphNode_TransitionResult_62F55133423E9C2053CAA09A7CE81877();
	void EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_1p_AnimGraphNode_TransitionResult_42C436BA4CFDA7B67B21D0A7F0F0CCFB();
	void EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_1p_AnimGraphNode_TransitionResult_C906738944C90C1E5FD2959E58B0A530();
	void EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_1p_AnimGraphNode_TransitionResult_37DAD723484CAF4506B71380789C3064();
	void EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_1p_AnimGraphNode_TransitionResult_9BFC5583466CED101024CDAD248900FA();
	void EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_1p_AnimGraphNode_TransitionResult_B17FCA464B6FA53AE37EC1921486EDD1();
	void EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_1p_AnimGraphNode_TransitionResult_7BA637554FB2B960A3CDE19E0AAE05E1();
	void EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_1p_AnimGraphNode_TransitionResult_E5FB76784DA620876149CE8BFA1A7B36();
	void EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_1p_AnimGraphNode_TransitionResult_1EC4EF954D80087025DF33A329AE49F2();
	void EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_1p_AnimGraphNode_TransitionResult_BBC7FAF64E7C454AFFF375B21E97BADB();
	void EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_1p_AnimGraphNode_BlendListByBool_A77B04554A25FEF5BCD27ABCAEA3D9DB();
	void EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_1p_AnimGraphNode_BlendListByEnum_C8A0CDDE449DD5FE7DE5ADAE8672235E();
	void EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_1p_AnimGraphNode_BlendSpacePlayer_4A417BFA448F22ED84C83AA2F711A085();
	void EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_1p_AnimGraphNode_TransitionResult_3AB9574D497C4152E7E0B29DC8D7EDCA();
	void EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_1p_AnimGraphNode_BlendSpacePlayer_657EABC84EDCD166D8A1438F3D7DB38D();
	void EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_1p_AnimGraphNode_TransitionResult_FDFA632149E7323D13B5FD9428A42C48();
	void EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_1p_AnimGraphNode_TransitionResult_1C15078A4F88F2D846A04384785AE1B3();
	void EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_1p_AnimGraphNode_TransitionResult_B2B5A0194E74CA635743C0ABE2045F99();
	void EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_1p_AnimGraphNode_TransitionResult_E06F5E1B412E03A618C8DA9390B5A2D4();
	void EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_1p_AnimGraphNode_TransitionResult_9BC95D0C4A5CA7DAF9AF0882E07F2160();
	void EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_1p_AnimGraphNode_TransitionResult_CAFC295140982C1AE6B3448C333C7A68();
	void EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_1p_AnimGraphNode_TransitionResult_A7C8155F4FFB3540B7AE689ED422E068();
	void EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_1p_AnimGraphNode_TransitionResult_DD0BD6BD41CB1D9FFCE1D9BA49984BE9();
	void EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_1p_AnimGraphNode_BlendSpacePlayer_A79BE23A4D3B4C0DB90334A07B8F8DAB();
	void EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_1p_AnimGraphNode_TransitionResult_29E470814ED65B9558A8DEA14BC39066();
	void EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_1p_AnimGraphNode_BlendListByBool_B821324E4507C9C2A78A1487232C7309();
	void EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_1p_AnimGraphNode_BlendSpacePlayer_EDB04D304DF3B489E14964BD6ADC91BF();
	void EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_1p_AnimGraphNode_TransitionResult_8110100E44167500A9386FBBC4AF4756();
	void EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_1p_AnimGraphNode_TransitionResult_8DEF606645F5E76704FE0FB8E1088958();
	void EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_1p_AnimGraphNode_TransitionResult_718AF9734FAD904546F3D9AD33140564();
	void EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_1p_AnimGraphNode_TransitionResult_C461689A434A1644DC1A988268CBF2A3();
	void EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_1p_AnimGraphNode_TransitionResult_650862FA4B1F7229923D688CA2759DEF();
	void EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_1p_AnimGraphNode_TransitionResult_176DE7604F47F97A838AC2B8BDE8AC97();
	void EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_1p_AnimGraphNode_TransitionResult_19A26A544E49089A80A5AC81361C4DDF();
	void EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_1p_AnimGraphNode_TransitionResult_AACAA52D49A3AA8F307990A1AAAEE275();
	void EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_1p_AnimGraphNode_TransitionResult_3D64047842128D0EDF12BE80DFCC9048();
	void EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_1p_AnimGraphNode_BlendListByBool_9A29840E4DF86CAED998D79665BE7144();
	void EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_1p_AnimGraphNode_BlendSpacePlayer_BA77F76D4423368082F3EF89AEBC8A4A();
	void EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_1p_AnimGraphNode_BlendSpacePlayer_FB7E70FF474FE748C71BE99A7293D5C1();
	void EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_1p_AnimGraphNode_TransitionResult_FE2D69DD4977FC45382F1EA75A0059DA();
	void EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_1p_AnimGraphNode_BlendSpacePlayer_422433EC40ED29F1A1F6C7835638527B();
	void EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_1p_AnimGraphNode_BlendSpacePlayer_EB11EFDE448F168B3EC3A39C956278C0();
	void EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_1p_AnimGraphNode_BlendListByBool_DE52E98545163D8FF4E12F8A5682E592();
	void EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_1p_AnimGraphNode_BlendSpacePlayer_D6830A8E46BE1D01011CC7A8BCF47605();
	void EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_1p_AnimGraphNode_TransitionResult_5039F38743640F2D676C48BFB75282A9();
	void EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_1p_AnimGraphNode_TransitionResult_D504744E430AD7819348F0A7307A920C();
	void EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_1p_AnimGraphNode_BlendSpacePlayer_1C506563437EE93E4A008BAB7C81CAB1();
	void EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_1p_AnimGraphNode_BlendListByBool_12CA6B404969F07201205EBE48FCBC18();
	void EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_1p_AnimGraphNode_TransitionResult_224EDCBE4C8998791BE2C285DC94AFDE();
	void EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_1p_AnimGraphNode_BlendSpacePlayer_C4302A564DD4DC47986961B310548E0E();
	void EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_1p_AnimGraphNode_TransitionResult_ACF2A9F84C93C954DBACEDA418CBAC7F();
	void EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_1p_AnimGraphNode_TransitionResult_72A79E6D45404B548CB614A287C4B26C();
	void EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_1p_AnimGraphNode_BlendListByBool_8552BC1A4363A53DF9BBD3A5AAD1CE87();
	void EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_1p_AnimGraphNode_TransitionResult_C84C850646FEDBCD98421C9E68133AFE();
	void EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_1p_AnimGraphNode_BlendListByBool_16539DAA4FD0EF3FECC2B0BF8831ECA9();
	void EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_1p_AnimGraphNode_TransitionResult_41486603465DA2EE45A05285737B6F37();
	void EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_1p_AnimGraphNode_BlendSpacePlayer_8E492C1640B23718A2108AB2A2415A7E();
	void EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_1p_AnimGraphNode_BlendSpacePlayer_09DFFEA5415165F92D40D6AF93972440();
	void EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_1p_AnimGraphNode_TwoWayBlend_CC359708439409A6754B3F9EBAB736E1();
	void EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_1p_AnimGraphNode_BlendListByBool_C48152554428A444E554BE997E9B090C();
	void EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_1p_AnimGraphNode_BlendListByBool_B63E2CE845CF551F8769E7B1288F9250();
	void EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_1p_AnimGraphNode_TransitionResult_98FBC23F4C9A713C0FB93D9AD6EEE9B4();
	void EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_1p_AnimGraphNode_BlendListByEnum_0EC62AB644A4DBFD3B333AB4B468EF1D();
	void EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_1p_AnimGraphNode_BlendListByBool_BF454E4349A73784CC5A13B75AD5B8E8();
	void EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_1p_AnimGraphNode_RotationOffsetBlendSpace_FC95377946F2126C81199194A72E0A85();
	void EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_1p_AnimGraphNode_RotationOffsetBlendSpace_20FB08DB4BB7B80DF8CE4596D45BCD3B();
	void EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_1p_AnimGraphNode_BlendListByBool_44C598054328748E388D148494B2F738();
	void EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_1p_AnimGraphNode_BlendListByBool_6672D63C40D1E6EC3F204D883C306029();
	void EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_1p_AnimGraphNode_BlendListByBool_C201C89F4FF362F861C1FA9AAB9DE7CE();
	void EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_1p_AnimGraphNode_BlendListByBool_E0BF1B2D4E14E08A237EC58F05ABF90C();
	void EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_1p_AnimGraphNode_BlendListByBool_FC15D9B94278E36EDE1BCF8479C9F89C();
	void EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_1p_AnimGraphNode_BlendListByBool_5E3E088D4DBD66AF0E79CD93C53E2344();
	void EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_1p_AnimGraphNode_BlendListByBool_6B8959F1411EE629F76D929645BA68FA();
	void EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_1p_AnimGraphNode_BlendListByEnum_7A8BB8044DC0F9EC9F33CA8DF7803845();
	void EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_1p_AnimGraphNode_BlendListByBool_D301098B4B194CD46BD65389D483A3B5();
	void EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_1p_AnimGraphNode_BlendListByBool_E8691C96472C595D84958892D3697CE1();
	void EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_1p_AnimGraphNode_BlendListByBool_16E8534945D938CACF56D39E39C0FD2F();
	void EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_1p_AnimGraphNode_TransitionResult_200748904D648F095E8D7081C7D7E311();
	void EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_1p_AnimGraphNode_BlendListByEnum_575B095A4B4AFEE0DB448BB769CAF7D6();
	void EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_1p_AnimGraphNode_BlendSpacePlayer_08A98FC84D862A3ED8E484B15DB79D14();
	void EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_1p_AnimGraphNode_BlendListByBool_D6090B114FF238CF6B662DB165E64ED7();
	void EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_1p_AnimGraphNode_TransitionResult_F1D0BC5E40C38AB7A05E3D8D185A67C8();
	void BlueprintUpdateAnimation(float* DeltaTimeX);
	void EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_1p_AnimGraphNode_TransitionResult_1C430D2D45AFC02D733E23A8FB7B20E2();
	void EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_1p_AnimGraphNode_TransitionResult_485ACC644FE59DD1953D1C949B574894();
	void AnimNotify_EnteredIdleState();
	void AnimNotify_FootPrintLeft();
	void AnimNotify_FootPrintRight();
	void EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_1p_AnimGraphNode_TransitionResult_D2070F6E4CA79E0B77A729B8056DBF50();
	void AnimNotify_LeaveChangeDirection();
	void AnimNotify_EnterChangeDirection();
	void AnimNotify_LandImpact();
	void AnimNotify_StartSprint();
	void AnimNotify_StopSprint();
	void ExecuteUbergraph_Anim_1p(int EntryPoint);
};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
