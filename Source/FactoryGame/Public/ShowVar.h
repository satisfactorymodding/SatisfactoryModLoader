// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/StructOnScope.h"

#ifndef WITH_SHOWVAR
	#define WITH_SHOWVAR !( UE_BUILD_SHIPPING || UE_BUILD_TEST ) || WITH_EDITOR
#endif

// This header should only be used locally to debug code, and it's usages should never be submitted or used outside of development builds
#if WITH_SHOWVAR

#include "UObject/Object.h"
#include "UObject/PropertyPortFlags.h"
#include "UObject/LazyObjectPtr.h"
#include "UObject/SoftObjectPtr.h"
#include "Templates/IsUEnumClass.h"
#include "Stats/Stats.h"
#include "FactoryGame.h"

/*-----------------------------------------------------------------------------
Example usage:
UE_LOG( LogTemp, Log, TEXT( "Logging some variable: %s" ), SHOWVAR( myVariable ) );

If you want to log a large data type (like a map, array or a set with a lot of elements, you can use LOGVAR instead:
LOGVAR( LogTemp, Log, TEXT("Logging a long array: "), myVariable );

If SHOWVAR does not support a specific type you can overload VarToString below like:
FORCEINLINE FString VarToString( MyClass var ){ return FString::Printf( TEXT( "%s" ), MyClass->GetName() ); }
-----------------------------------------------------------------------------*/

#define SHOWVAR( Var ) *FString::Printf( TEXT( "%s = %s" ), TEXT( #Var ), *VarToString( Var ) )
// <FL> [TranN] Fix compile error
// #define LOGVAR( Category, Verbosity, Message, Var, ... ) VarToLog( FString::Printf( Message TEXT( #Var ), ##__VA_ARGS__ ), Var, Category, ELogVerbosity::##Verbosity );
#define LOGVAR( Category, Verbosity, Message, Var, ... ) VarToLog( FString::Printf( Message TEXT( #Var ), ##__VA_ARGS__ ), Var, Category, ELogVerbosity::Verbosity );
// </FL>

// Implementation for the inline array types
template<typename T>
FORCEINLINE FString VarToString( const TArray<T>& Array )
{
	FString Elements;
	for( int32 i = 0; i < Array.Num(); ++i )
	{
		if( Array.Num() > 1 && i > 0 )
		{
			Elements.Append( FString( TEXT( "," ) ) );
		}
		Elements.Append( VarToString( Array[ i ] ) );
	}
	return FString::Printf( TEXT( "[%i]{%s}" ), Array.Num(), *Elements );
}

// Implementation of VarToString for integral types
template<typename InIntegralType>
requires( static_cast<bool>( TIsIntegral<InIntegralType>::Value ) || static_cast<bool>( TIsFloatingPoint<InIntegralType>::Value ) )
FORCEINLINE FString VarToString( InIntegralType InIntegralValue )
{
	return FString::Printf( TFormatSpecifier<InIntegralType>::GetFormatSpecifier(), InIntegralValue );
}

// Implementation of VarToString for boolean values
FORCEINLINE FString VarToString( const bool Value )
{
	return FString( Value ? TEXT( "true" ) : TEXT( "false" ) );
}

// Implementation of VarToString for FString
FORCEINLINE FString VarToString( const FString& Value )
{
	return Value;
}

// Implementation of VarToString for FText
FORCEINLINE FString VarToString( const FText& Text )
{
	return Text.ToString();
}

// Implementation of VarToString for FName
FORCEINLINE FString VarToString( const FName& Name )
{
	return Name.ToString();
}

// Implementation of VarToString for raw UObject pointers
FORCEINLINE FString VarToString( const UObject* Object )
{
	return GetNameSafe( Object );
}

// Implementation of VarToString for new style object pointers
FORCEINLINE FString VarToString( const FObjectPtr& ObjectPtr )
{
	return GetNameSafe( ObjectPtr.Get() );
}

// Implementation of VarToString for new style object pointers
template<typename T>
FORCEINLINE FString VarToString( const TObjectPtr<T>& ObjectPtr )
{
	return GetNameSafe( ObjectPtr.Get() );
}

// Implementation of VarToString for weak object pointers
FORCEINLINE FString VarToString( const FWeakObjectPtr& WeakObjectPtr )
{
	return GetNameSafe( WeakObjectPtr.Get() );
}
// Implementation of VarToString for soft object pointers

FORCEINLINE FString VarToString( const FSoftObjectPtr& SoftObjectPtr )
{
	return SoftObjectPtr.ToString();
}

// Implementation of VarToString for lazy object pointers
FORCEINLINE FString VarToString( const FLazyObjectPtr& LazyObjectPtr )
{
	return GetNameSafe( LazyObjectPtr.Get() );
}

// Used to lower the priority of the UScriptStruct overload
struct FImplicitStructConversionParam
{
	FStructOnScope StructOnScope;

	template<typename StructType>
	FImplicitStructConversionParam( const StructType& StructValue )
	{
		StructOnScope = MakeStructOnScope<StructType>( StructValue );
	}
};

// Implementation for normal UScriptStruct types (e.g. the ones outside of Core)
FORCEINLINE FString VarToString( const FImplicitStructConversionParam& StructValue )
{
	const UScriptStruct* ScriptStruct = CastChecked<UScriptStruct>( StructValue.StructOnScope.GetStruct() );

	FString Result;
	ScriptStruct->ExportText( Result, StructValue.StructOnScope.GetStructMemory(), nullptr, nullptr, PPF_IncludeTransient, nullptr );
	return Result;
}

// Implementation of VarToString for UEnum types
template<typename EnumType>
requires( static_cast<bool>( TIsEnum<EnumType>::Value ) )
FORCEINLINE FString VarToString( EnumType EnumValue )
{
	return EnumToString( EnumValue );
}

// Implementation of VarToString for container types
template<typename ElementType, typename AllocatorType>
FORCEINLINE FString VarToString( const TArray<ElementType, AllocatorType>& Array )
{
	TArray<FString> Elements;
	for ( const ElementType& Element : Array )
	{
		Elements.Add( VarToString( Element ) );
	}
	return FString::Printf( TEXT( "[%i]{%s}" ), Array.Num(), *FString::Join( Elements, TEXT(", ") ) );
}

template<typename KeyType, typename ValueType, typename SetAllocatorType, typename KeyFuncs>
FORCEINLINE FString VarToString( const TMap<KeyType, ValueType, SetAllocatorType, KeyFuncs>& Map )
{
	TArray<FString> Elements;
	for( const TPair<KeyType, ValueType>& Pair : Map )
	{
		Elements.Add( FString::Printf( TEXT("%s = %s"), *VarToString( Pair.Key ), *VarToString( Pair.Value ) ) );
	}
	return FString::Printf( TEXT("{%s}"), *FString::Join( Elements, TEXT(", ") ) );
}

template<typename ElementType, typename SetAllocatorType>
FORCEINLINE FString VarToString( const TSet<ElementType, SetAllocatorType>& Set )
{
	TArray<FString> Elements;
	for( const ElementType& Element : Set )
	{
		Elements.Add( VarToString( Element ) );
	}
	return FString::Printf( TEXT("{%s}"), *FString::Join( Elements, TEXT(", ") ) );
}

// Generic VarToLog implementation that delegates to VarToString

template<typename T>
FORCEINLINE void VarToLog( const FString& Message, const T& Value, const FLogCategoryBase& LogCategory, ELogVerbosity::Type Verbosity )
{
	if ( !LogCategory.IsSuppressed( Verbosity ) )
	{
		FMsg::Logf( __FILE__, __LINE__, LogCategory.GetCategoryName(), Verbosity, TEXT("%s = %s"), *Message, *VarToString( Value ) );
	}
}

// VarToLog implementations for container types that log their values in multiple separate logs to avoid truncation

template<typename ElementType, typename AllocatorType>
FORCEINLINE void VarToLog( const FString& Message, const TArray<ElementType, AllocatorType>& Array, const FLogCategoryBase& LogCategory, ELogVerbosity::Type Verbosity )
{
	if ( !LogCategory.IsSuppressed( Verbosity ) )
	{
		FMsg::Logf( __FILE__, __LINE__, LogCategory.GetCategoryName(), Verbosity, TEXT("%s (%i):"), *Message, Array.Num() );
	
		for( int32 i = 0; i < Array.Num(); ++i )
		{
			FMsg::Logf( __FILE__, __LINE__, LogCategory.GetCategoryName(), Verbosity, TEXT("[%i] %s"), i, *VarToString( Array[ i ] ) );
		}
	}
}

template<typename KeyType, typename ValueType, typename SetAllocatorType, typename KeyFuncs>
FORCEINLINE void VarToLog( const FString& Message, const TMap<KeyType, ValueType, SetAllocatorType, KeyFuncs>& Map, const FLogCategoryBase& LogCategory, ELogVerbosity::Type Verbosity )
{
	if ( !LogCategory.IsSuppressed( Verbosity ) )
	{
		FMsg::Logf( __FILE__, __LINE__, LogCategory.GetCategoryName(), Verbosity, TEXT("%s:"), *Message );
	
		for( const TPair<KeyType, ValueType>& Pair : Map )
		{
			FMsg::Logf( __FILE__, __LINE__, LogCategory.GetCategoryName(), Verbosity, TEXT("%s = %s"), *VarToString( Pair.Key ), *VarToString( Pair.Value ) );
		}
	}
}

template<typename ElementType, typename SetAllocatorType>
FORCEINLINE void VarToLog( const FString& Message, const TSet<ElementType, SetAllocatorType>& Set, const FLogCategoryBase& LogCategory, ELogVerbosity::Type Verbosity )
{
	if ( !LogCategory.IsSuppressed( Verbosity ) )
	{
		FMsg::Logf( __FILE__, __LINE__, LogCategory.GetCategoryName(), Verbosity, TEXT("%s:"), *Message );
	
		for( const ElementType& Element : Set )
		{
			FMsg::Logf( __FILE__, __LINE__, LogCategory.GetCategoryName(), Verbosity, TEXT("%s"), *VarToString( Element ) );
		}
	}
}

#endif
