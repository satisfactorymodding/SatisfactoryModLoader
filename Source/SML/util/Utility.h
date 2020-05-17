#pragma once
#include <sstream>
#include "Json.h"
#include "SatisfactoryModLoader.h"
#include "GenericPlatform/GenericPlatformFile.h"

#define CALL_VARARG_HANDLER(FunctionName, UserType, args) \
	__processVararg_##FunctionName(UserType, std::forward<Args>(args)...);

#define DEFINE_VARARG_HANDLER(FunctionName, UserType, Body) \
	template<typename First, typename ...Args> \
	void __processVararg_##FunctionName(UserType& Result, First& FirstArg, Args &&...args) { \
		Body; \
		__processVararg_##FunctionName(Result, std::forward<Args>(args)...); \
	} \
	template <typename ResultParamType> \
	void __processVararg_##FunctionName(ResultParamType& Result) {}

namespace SML {

	inline TCHAR* GetMenuSceneMapNamePrefix() {
		return TEXT("/Game/FactoryGame/Map/MenuScenes/MenuScene_");
	}

	inline bool IsMenuMapName(const FString& MapName) {
		return MapName.StartsWith(GetMenuSceneMapNamePrefix());
	}

	FString GetModConfigFilePath(const FString& ModId);

	/**
	 * Parses given json string into a valid json object
	 * Strips json syntax extensions like commentaries prior to parsing
	 */
	SML_API TSharedPtr<FJsonObject> ParseJsonLenient(const FString& Input);

	/**
	 * Parses mod configuration file and returns json object
	 * returns json.null() if config file is missing, unreadable or corrupted
	 * It also supports comments in mod configs
	 */
	SML_API TSharedRef<FJsonObject> ReadModConfig(const FString& ModId, const TSharedRef<FJsonObject>& DefaultValues);

	/*
	 * Dumps the given mod configuration json to the mod config file with the given modid.
	 * Completely overwrites the file with the given json.
	 *
	 * @param[in]	modid	the id of the mod you want to save the config from
	 * @param[in]	config	the coniguration you want to overwrite the file with
	 */
	SML_API void WriteModConfig(const FString& ModId, const TSharedRef<FJsonObject>& Config);
	
	bool SetDefaultValues(const TSharedPtr<FJsonObject>& Obj, const TSharedPtr<FJsonObject>& DefaultValues);

	DEFINE_VARARG_HANDLER(formatStr, std::wostringstream, { Result << FirstArg; });
	template<typename ...Args>
	FString formatStr(Args &&...args) {
		std::wostringstream stream;
		CALL_VARARG_HANDLER(formatStr, stream, args);
		return FString(stream.str().c_str());
	}

	DEFINE_VARARG_HANDLER(ArrayOf, TArray<First>, { Result.Add(FirstArg); });
	
	/**
	 * Constructs TArray and fills it with given arguments
	 */
	template <typename First, typename ...Args>
	TArray<First> ArrayOf(Args&& ...VarArgs) {
		TArray<First> ResultArray;
		CALL_VARARG_HANDLER(ArrayOf, ResultArray, VarArgs);
		return ResultArray;
	}

	DEFINE_VARARG_HANDLER(ArrayOfNullable, TArray<First>, { if (FirstArg != nullptr) Result.Add(FirstArg); });
	
	/**
	 * Constructs TArray and fills it with given arguments
	 * Only non-nullptr values will be added into the array
	 * Arguments are expected to be pointers
	 */
	template <typename First, typename ...Args>
	TArray<First> ArrayOfNullable(Args&& ...VarArgs) {
		TArray<First> ResultArray;
		CALL_VARARG_HANDLER(ArrayOfNullable, ResultArray, VarArgs);
		return ResultArray;
	}
	
	template<typename In, typename FunctorType, typename Out = std::result_of_t<FunctorType(const In&)>>
	FORCEINLINE TArray<Out> Map(const TArray<In>& Input, FunctorType Functor) {
		TArray<Out> ResultArray;
		for (const In& Element : Input) {
			ResultArray.Add(Functor(Element));
		}
		return ResultArray;
	}
	
	template <class FuncType>
	class FuncDirectoryVisitor : public IPlatformFile::FDirectoryVisitor
	{
	public:
		bool Visit(const TCHAR* FilenameOrDirectory, bool bIsDirectory) override
		{
			return Functor(FilenameOrDirectory, bIsDirectory);
		}

		FuncDirectoryVisitor(FuncType&& FunctorInstance)
			: Functor(MoveTemp(FunctorInstance))
		{
		}

	private:
		/** User-provided functor */
		FuncType Functor;
	};

	template <class Functor>
	FuncDirectoryVisitor<Functor> MakeDirectoryVisitor(Functor&& FunctorInstance)
	{
		return FuncDirectoryVisitor<Functor>(MoveTemp(FunctorInstance));
	}
};