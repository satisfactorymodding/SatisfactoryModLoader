#pragma once
#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "SMLBlueprintArrayLibrary.generated.h"

UCLASS()
class SML_API USMLBlueprintArrayLibrary : public UBlueprintFunctionLibrary {
	GENERATED_BODY()
public:
	/** 
	 * Sort array elements using the provided comparator function
	 *
	 * @param TargetArray the array to sort
	 * @param Object object on which the sort function is hosted
	 * @param FunctionName name of the comparator function
	*/
	UFUNCTION(BlueprintCallable, CustomThunk, meta = (ArrayParm = "TargetArray", BlueprintInternalUseOnly = "true", BlueprintThreadSafe))
	static void Array_Sort(const TArray<int32>& TargetArray, UObject* Object, FName FunctionName);

	static void GenericArray_Sort(const void* TargetArray, const FArrayProperty* ArrayProp, UObject* Object, FName FunctionName);
	
	DECLARE_FUNCTION(execArray_Sort)
	{
		Stack.MostRecentProperty = nullptr;
		Stack.StepCompiledIn<FArrayProperty>(NULL);
		
		void* ArrayAddress = Stack.MostRecentPropertyAddress;
		const FArrayProperty* ArrayProperty = CastField<FArrayProperty>(Stack.MostRecentProperty);
		if (!ArrayProperty) {
			Stack.bArrayContextFailed = true;
			return;
		}
		P_GET_OBJECT(UObject, Object);
		P_GET_PROPERTY(FNameProperty, FunctionName);

		P_FINISH;
		P_NATIVE_BEGIN;
		GenericArray_Sort(ArrayAddress, ArrayProperty, Object, FunctionName);
		P_NATIVE_END;
	}
};
