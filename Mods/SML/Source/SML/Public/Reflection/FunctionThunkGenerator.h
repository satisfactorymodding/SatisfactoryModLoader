#pragma once

#include "CoreMinimal.h"
#include "UObject/Script.h"
#include "UObject/ScriptMacros.h"
#include "UObject/Stack.h"

#include <tuple>
#include <type_traits>

/**
 * Generates a UFunction thunk (equivalent to what UHT would generate) given a function signature.
 * The thunk is templated on a callback that will be invoked with the parameters from the stack.
 */
template<typename FunctionType>
class TFunctionThunkGenerator;

namespace FunctionThunkGenerator_Detail
{
	/*
	 * ArgTraits
	 * Type-specific details, specialized for each support argument type.
	 */

	template<typename T>
	struct ArgTraitsImpl;

	template<typename T>
	using ArgTraits = ArgTraitsImpl<std::decay_t<T>>;

	// Integers
	template<> struct ArgTraitsImpl<int8> { using PropertyType = FInt8Property; };
	template<> struct ArgTraitsImpl<int16> { using PropertyType = FInt16Property; };
	template<> struct ArgTraitsImpl<int32> { using PropertyType = FIntProperty; };
	template<> struct ArgTraitsImpl<int64> { using PropertyType = FInt64Property; };
	template<> struct ArgTraitsImpl<uint8> { using PropertyType = FByteProperty; };
	template<> struct ArgTraitsImpl<uint16> { using PropertyType = FUInt16Property; };
	template<> struct ArgTraitsImpl<uint32> { using PropertyType = FUInt32Property; };
	template<> struct ArgTraitsImpl<uint64> { using PropertyType = FUInt64Property; };

	// Bool specialized to use (up to) 32-bit values.
	template<>
	struct ArgTraitsImpl<bool>
	{
		using PropertyType = FBoolProperty;

		static FORCEINLINE void OverrideGetValue(bool& Result, FFrame& Stack)
		{
			uint32 Temp = 0;
			Stack.StepCompiledIn<FBoolProperty>(&Temp);
			Result = !!Temp;
		}
	};

	// Structs
	template<typename T> requires (!!TModels<CStaticStructProvider, T>::Value)
	struct ArgTraitsImpl<T>
	{
		using PropertyType = FStructProperty;
	};

	// Objects
	template<typename T> requires (!!TModels<CStaticClassProvider, T>::Value)
	struct ArgTraitsImpl<T*>
	{
		using PropertyType = FObjectPropertyBase;
	};

	// Classes
	template<typename ClassType>
	struct ArgTraitsImpl<TSubclassOf<ClassType>>
	{
		using PropertyType = FObjectProperty;
	};

	// Arrays
	template<typename T>
	struct ArgTraitsImpl<TArray<T>>
	{
		using PropertyType = FArrayProperty;
	};

	// Maps
	template<typename KeyType, typename ValueType>
	struct ArgTraitsImpl<TMap<KeyType, ValueType>>
	{
		using PropertyType = FMapProperty;
	};

	// Sets
	template<typename ElementType>
	struct ArgTraitsImpl<TSet<ElementType>>
	{
		using PropertyType = FSetProperty;
	};

	// Interfaces
	template<typename InterfaceType>
	struct ArgTraitsImpl<TScriptInterface<InterfaceType>>
	{
		using PropertyType = FInterfaceProperty;
	};

	// Weak Object Pointers
	template<typename T>
	struct ArgTraitsImpl<TWeakObjectPtr<T>>
	{
		using PropertyType = FWeakObjectProperty;
	};

	// Soft Object Pointers
	template<typename T>
	struct ArgTraitsImpl<TSoftObjectPtr<T>>
	{
		using PropertyType = FSoftObjectProperty;
	};

	// Soft Class Pointers
	template<typename T>
	struct ArgTraitsImpl<TSoftClassPtr<T>>
	{
		using PropertyType = FSoftClassProperty;
	};

	// Field Paths
	template<typename InPropertyType>
	struct ArgTraitsImpl<TFieldPath<InPropertyType>>
	{
		using PropertyType = FFieldPathProperty;
	};

	// Enums
	template<typename T> requires (!!TIsUEnumClass<T>::Value)
	struct ArgTraitsImpl<T>
	{
		using PropertyType = FEnumProperty;
	};

	/*
	 * ArgReader
	 * Pops a single typed object off the stack and stores it.
	 */

	template<typename T>
	struct ArgReaderImpl
	{
		T Value = {};

		explicit ArgReaderImpl(FFrame& Stack)
		{
			if constexpr (requires { ArgTraits<T>::OverrideGetValue(Value, Stack); })
			{
				ArgTraits<T>::OverrideGetValue(Value, Stack);
			}
			else
			{
				Stack.StepCompiledIn<typename ArgTraits<T>::PropertyType>(&Value);
			}
		}
	};

	template<typename T>
	struct ArgReaderImpl<T&>
	{
		T DefaultValue = {};
		T& Value;

		explicit ArgReaderImpl(FFrame& Stack)
			: Value(Stack.StepCompiledInRef<typename ArgTraits<T>::PropertyType, T>(&DefaultValue))
		{
		}
	};

	// Arguments are all read as non-const, if any of them are const then that will be enforced in the
	// callback function signature.
	template<typename T>
	using ArgReader = ArgReaderImpl<
		std::conditional_t<std::is_reference_v<T>, std::remove_cvref_t<T>&, std::remove_cv_t<T>>>;

	/*
	 * TFunctionThunkGeneratorBase
	 * Base implementation that takes the arguments and return value as separate parameters so that it's
	 * independent of function type.
	 */

	template<
		typename Ret,
		typename OptionalInstanceTuple,
		typename ArgsTuple,
		typename ArgsIndexSequence = std::make_index_sequence<std::tuple_size_v<ArgsTuple>>>
	class TFunctionThunkGeneratorBase;

	template<typename Ret, typename... OptionalInstance, typename... Args, size_t... ArgIndices>
	class TFunctionThunkGeneratorBase<
		Ret,
		std::tuple<OptionalInstance...>,
		std::tuple<Args...>,
		std::index_sequence<ArgIndices...>>
	{
	public:
		template<Ret(*Impl)(OptionalInstance*..., Args...)>
		static void Thunk(UObject* Context, FFrame& Stack, RESULT_DECL)
		{
			std::tuple ArgValues{ArgReader<Args>(Stack)...};
			P_FINISH;
			P_NATIVE_BEGIN;
			if constexpr (!std::is_void_v<Ret>)
			{
				*(Ret*)RESULT_PARAM = InvokeImpl<Impl>(Context, ArgValues);
			}
			else
			{
				InvokeImpl<Impl>(Context, ArgValues);
			}
			P_NATIVE_END;
		}

	private:
		template<auto Impl>
		static FORCEINLINE decltype(auto) InvokeImpl(UObject* Context, auto&& ArgValues)
		{
			return Impl(
				static_cast<OptionalInstance*>(Context)...,
				std::get<ArgIndices>(ArgValues).Value...);
		}
	};
}

// Static function.
template<typename Ret, typename... Args>
class TFunctionThunkGenerator<Ret(*)(Args...)>
	: public FunctionThunkGenerator_Detail::TFunctionThunkGeneratorBase<
		Ret,
		std::tuple<>,
		std::tuple<Args...>> {};

// Non-static member function.
template<typename Ret, typename InstanceType, typename... Args>
class TFunctionThunkGenerator<Ret(InstanceType::*)(Args...)>
	: public FunctionThunkGenerator_Detail::TFunctionThunkGeneratorBase<
		Ret,
		std::tuple<InstanceType>,
		std::tuple<Args...>> {};

// Const non-static member function.
template<typename Ret, typename InstanceType, typename... Args>
class TFunctionThunkGenerator<Ret(InstanceType::*)(Args...) const>
	: public FunctionThunkGenerator_Detail::TFunctionThunkGeneratorBase<
		Ret,
		std::tuple<const InstanceType>,
		std::tuple<Args...>> {};
