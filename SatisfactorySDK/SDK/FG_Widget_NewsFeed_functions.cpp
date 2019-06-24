// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_NewsFeed_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Widget_NewsFeed.Widget_NewsFeed_C.GetNewsHeaderText
// ()
// Parameters:
// struct FText                   ReturnValue                    (Parm, OutParm, ReturnParm)

struct FText UWidget_NewsFeed_C::GetNewsHeaderText()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_NewsFeed.Widget_NewsFeed_C.GetNewsHeaderText");

	UWidget_NewsFeed_C_GetNewsHeaderText_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_NewsFeed.Widget_NewsFeed_C.GetHeaderAndBody
// ()
// Parameters:
// struct FText                   InText                         (BlueprintVisible, BlueprintReadOnly, Parm)
// struct FText                   Header                         (Parm, OutParm)
// struct FText                   Body                           (Parm, OutParm)

void UWidget_NewsFeed_C::GetHeaderAndBody(const struct FText& InText, struct FText* Header, struct FText* Body)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_NewsFeed.Widget_NewsFeed_C.GetHeaderAndBody");

	UWidget_NewsFeed_C_GetHeaderAndBody_Params params;
	params.InText = InText;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	if (Header != nullptr)
		*Header = params.Header;
	if (Body != nullptr)
		*Body = params.Body;
}


// Function Widget_NewsFeed.Widget_NewsFeed_C.GetNewsBodyText
// ()
// Parameters:
// struct FText                   ReturnValue                    (Parm, OutParm, ReturnParm)

struct FText UWidget_NewsFeed_C::GetNewsBodyText()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_NewsFeed.Widget_NewsFeed_C.GetNewsBodyText");

	UWidget_NewsFeed_C_GetNewsBodyText_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_NewsFeed.Widget_NewsFeed_C.OnFail_74A37E23495D65D8B1428F9D6302EA77
// ()
// Parameters:
// class UTexture2DDynamic*       Texture                        (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_NewsFeed_C::OnFail_74A37E23495D65D8B1428F9D6302EA77(class UTexture2DDynamic* Texture)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_NewsFeed.Widget_NewsFeed_C.OnFail_74A37E23495D65D8B1428F9D6302EA77");

	UWidget_NewsFeed_C_OnFail_74A37E23495D65D8B1428F9D6302EA77_Params params;
	params.Texture = Texture;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_NewsFeed.Widget_NewsFeed_C.OnSuccess_74A37E23495D65D8B1428F9D6302EA77
// ()
// Parameters:
// class UTexture2DDynamic*       Texture                        (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_NewsFeed_C::OnSuccess_74A37E23495D65D8B1428F9D6302EA77(class UTexture2DDynamic* Texture)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_NewsFeed.Widget_NewsFeed_C.OnSuccess_74A37E23495D65D8B1428F9D6302EA77");

	UWidget_NewsFeed_C_OnSuccess_74A37E23495D65D8B1428F9D6302EA77_Params params;
	params.Texture = Texture;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_NewsFeed.Widget_NewsFeed_C.Construct
// ()

void UWidget_NewsFeed_C::Construct()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_NewsFeed.Widget_NewsFeed_C.Construct");

	UWidget_NewsFeed_C_Construct_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_NewsFeed.Widget_NewsFeed_C.FindNewsFeedActor
// ()

void UWidget_NewsFeed_C::FindNewsFeedActor()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_NewsFeed.Widget_NewsFeed_C.FindNewsFeedActor");

	UWidget_NewsFeed_C_FindNewsFeedActor_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_NewsFeed.Widget_NewsFeed_C.OnNewsTextReceived
// ()
// Parameters:
// struct FText                   NewsText                       (BlueprintVisible, BlueprintReadOnly, Parm)

void UWidget_NewsFeed_C::OnNewsTextReceived(const struct FText& NewsText)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_NewsFeed.Widget_NewsFeed_C.OnNewsTextReceived");

	UWidget_NewsFeed_C_OnNewsTextReceived_Params params;
	params.NewsText = NewsText;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_NewsFeed.Widget_NewsFeed_C.PreConstruct
// ()
// Parameters:
// bool*                          IsDesignTime                   (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_NewsFeed_C::PreConstruct(bool* IsDesignTime)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_NewsFeed.Widget_NewsFeed_C.PreConstruct");

	UWidget_NewsFeed_C_PreConstruct_Params params;
	params.IsDesignTime = IsDesignTime;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_NewsFeed.Widget_NewsFeed_C.BndEvt__Button_0_K2Node_ComponentBoundEvent_0_OnButtonHoverEvent__DelegateSignature
// ()

void UWidget_NewsFeed_C::BndEvt__Button_0_K2Node_ComponentBoundEvent_0_OnButtonHoverEvent__DelegateSignature()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_NewsFeed.Widget_NewsFeed_C.BndEvt__Button_0_K2Node_ComponentBoundEvent_0_OnButtonHoverEvent__DelegateSignature");

	UWidget_NewsFeed_C_BndEvt__Button_0_K2Node_ComponentBoundEvent_0_OnButtonHoverEvent__DelegateSignature_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_NewsFeed.Widget_NewsFeed_C.BndEvt__mButton_K2Node_ComponentBoundEvent_1_OnButtonHoverEvent__DelegateSignature
// ()

void UWidget_NewsFeed_C::BndEvt__mButton_K2Node_ComponentBoundEvent_1_OnButtonHoverEvent__DelegateSignature()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_NewsFeed.Widget_NewsFeed_C.BndEvt__mButton_K2Node_ComponentBoundEvent_1_OnButtonHoverEvent__DelegateSignature");

	UWidget_NewsFeed_C_BndEvt__mButton_K2Node_ComponentBoundEvent_1_OnButtonHoverEvent__DelegateSignature_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_NewsFeed.Widget_NewsFeed_C.BndEvt__mButton_K2Node_ComponentBoundEvent_2_OnButtonClickedEvent__DelegateSignature
// ()

void UWidget_NewsFeed_C::BndEvt__mButton_K2Node_ComponentBoundEvent_2_OnButtonClickedEvent__DelegateSignature()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_NewsFeed.Widget_NewsFeed_C.BndEvt__mButton_K2Node_ComponentBoundEvent_2_OnButtonClickedEvent__DelegateSignature");

	UWidget_NewsFeed_C_BndEvt__mButton_K2Node_ComponentBoundEvent_2_OnButtonClickedEvent__DelegateSignature_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_NewsFeed.Widget_NewsFeed_C.ParseText
// ()
// Parameters:
// struct FText                   NewsText                       (BlueprintVisible, BlueprintReadOnly, Parm)

void UWidget_NewsFeed_C::ParseText(const struct FText& NewsText)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_NewsFeed.Widget_NewsFeed_C.ParseText");

	UWidget_NewsFeed_C_ParseText_Params params;
	params.NewsText = NewsText;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_NewsFeed.Widget_NewsFeed_C.BndEvt__Widget_FrontEnd_Button_K2Node_ComponentBoundEvent_3_OnClicked__DelegateSignature
// ()

void UWidget_NewsFeed_C::BndEvt__Widget_FrontEnd_Button_K2Node_ComponentBoundEvent_3_OnClicked__DelegateSignature()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_NewsFeed.Widget_NewsFeed_C.BndEvt__Widget_FrontEnd_Button_K2Node_ComponentBoundEvent_3_OnClicked__DelegateSignature");

	UWidget_NewsFeed_C_BndEvt__Widget_FrontEnd_Button_K2Node_ComponentBoundEvent_3_OnClicked__DelegateSignature_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_NewsFeed.Widget_NewsFeed_C.ExecuteUbergraph_Widget_NewsFeed
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_NewsFeed_C::ExecuteUbergraph_Widget_NewsFeed(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_NewsFeed.Widget_NewsFeed_C.ExecuteUbergraph_Widget_NewsFeed");

	UWidget_NewsFeed_C_ExecuteUbergraph_Widget_NewsFeed_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
