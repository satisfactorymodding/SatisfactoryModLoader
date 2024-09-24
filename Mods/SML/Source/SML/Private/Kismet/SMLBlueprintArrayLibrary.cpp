#include "Kismet/SMLBlueprintArrayLibrary.h"

#include "EngineLogs.h"

void USMLBlueprintArrayLibrary::Array_Sort(const TArray<int32>& TargetArray, UObject* Object, FName FunctionName) {
	checkf(false, TEXT("Blueprint only function. Use TArray::StableSort instead in C++"));
}

void USMLBlueprintArrayLibrary::GenericArray_Sort(const void* TargetArray, const FArrayProperty* ArrayProp, UObject* Object, FName FunctionName) {
	UFunction* ComparatorFunction = Object ? Object->FindFunction(FunctionName) : NULL;

	if (ComparatorFunction == NULL) {
		UE_LOG(LogBlueprint, Error, TEXT("Array_Sort failed: Failed to find comparator function %s inside of Object %s"),
			*FunctionName.ToString(), *Object->GetClass()->GetPathName());
		return;
	}

	const FProperty* ArrayInnerProperty = ArrayProp->Inner;

	//Initialize the frame for calling the comparator function
	//We do not need to actually initialize or destroy values in the frame,
	//since we do not actually copy them, we steal array value's memory without reclaiming their ownership
	//and pass them to the function, and then repeat the process.
	//Memzero is here just to avoid using uninitialized stack memory if something goes wrong
	void* ComparatorCallFrame = FMemory_Alloca(ComparatorFunction->ParmsSize);
	FMemory::Memzero(ComparatorCallFrame, ComparatorFunction->ParmsSize);
	
	//Should have 3 parameters, including either the return value or the output parameter
	check(ComparatorFunction->NumParms == 3);

	const FProperty* FirstParamProperty = ComparatorFunction->PropertyLink;
	const FProperty* SecondParamProperty = FirstParamProperty->PropertyLinkNext;
	const FBoolProperty* ReturnValueProperty = CastField<FBoolProperty>(SecondParamProperty->PropertyLinkNext);

	//Parameters should have exactly same type as the array inner property
	check(FirstParamProperty->SameType(ArrayInnerProperty));
	check(SecondParamProperty->SameType(ArrayInnerProperty));
	//Return value should be a normal boolean property
	//Should also have either CPF_OutParam and not have CPF_ReferenceParm
	check(ReturnValueProperty);
	check(ReturnValueProperty->HasAnyPropertyFlags(CPF_OutParm) && !ReturnValueProperty->HasAnyPropertyFlags(CPF_ReferenceParm));
	
	FScriptArrayHelper ArrayHelper(ArrayProp, TargetArray);
	
	//Create indices array that we are gonna sort
	TArray<int32> ArrayIndices;
	ArrayIndices.AddZeroed(ArrayHelper.Num());
	for (int32 i = 0; i < ArrayHelper.Num(); i++) {
		ArrayIndices[i] = i;
	}

	//Actually sort array indices
	ArrayIndices.StableSort([&](int32 IndexA, int32 IndexB) {
		const void* ElementAPtr = ArrayHelper.GetRawPtr(IndexA);
		const void* ElementBPtr = ArrayHelper.GetRawPtr(IndexB);

		void* ElementADestPtr = FirstParamProperty->ContainerPtrToValuePtr<void>(ComparatorCallFrame);
		void* ElementBDestPtr = SecondParamProperty->ContainerPtrToValuePtr<void>(ComparatorCallFrame);

		//Steal property values from the array into the comparator call frame
		FMemory::Memcpy(ElementADestPtr, ElementAPtr, ArrayInnerProperty->ElementSize);
		FMemory::Memcpy(ElementBDestPtr, ElementBPtr, ArrayInnerProperty->ElementSize);

		ReturnValueProperty->SetPropertyValue_InContainer(ComparatorCallFrame, false);
		
		Object->ProcessEvent(ComparatorFunction, ComparatorCallFrame);
		return ReturnValueProperty->GetPropertyValue_InContainer(ComparatorCallFrame);
	});

	TArray<int32> TargetPositions;
	TargetPositions.AddZeroed(ArrayIndices.Num());
	for (int32 i = 0; i < ArrayIndices.Num(); i++) {
		TargetPositions[ArrayIndices[i]] = i;
	}
	
	//Swap values in the array to have the correct order
	for (int32 i = 0; i < ArrayHelper.Num(); i++) {
		// Swap until element at i is correct
		// Each step ensures that the current element at i is moved to its correct position
		// Each element will be swapped to its correct position once
		// therefore the execution time of this for loop is still linear
		while(TargetPositions[i] != i) {
			ArrayHelper.SwapValues(i, TargetPositions[i]);
			TargetPositions.Swap(i, TargetPositions[i]);
		}
	}
}
