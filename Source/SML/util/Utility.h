#pragma once
#include <string>
#include <sstream>
#include "Json.h"
#include "SatisfactoryModLoader.h"
#include "GenericPlatform/GenericPlatformFile.h"

namespace SML {

	inline TCHAR* GetMenuSceneMapNamePrefix() {
		return TEXT("/Game/FactoryGame/Map/MenuScenes/MenuScene_");
	}

	inline bool IsMenuMapName(const FString& MapName) {
		return MapName.StartsWith(GetMenuSceneMapNamePrefix());
	}

	FString getModConfigFilePath(FString modid);

	/**
	 * Parses given json string into a valid json object
	 * Strips json syntax extensions like commentaries prior to parsing
	 */
	SML_API TSharedPtr<FJsonObject> parseJsonLenient(const FString& input);

	/**
	 * Parses mod configuration file and returns json object
	 * returns json.null() if config file is missing, unreadable or corrupted
	 * It also supports comments in mod configs
	 */
	SML_API TSharedRef<FJsonObject> readModConfig(FString modid, const TSharedRef<FJsonObject>& defaultValues);

	/*
	 * Dumps the given mod configuration json to the mod config file with the given modid.
	 * Completely overwrites the file with the given json.
	 *
	 * @param[in]	modid	the id of the mod you want to save the config from
	 * @param[in]	config	the coniguration you want to overwrite the file with
	 */
	SML_API void writeModConfig(FString modid, const TSharedRef<FJsonObject>& config);
	
	bool setDefaultValues(const TSharedPtr<FJsonObject>& j, const TSharedPtr<FJsonObject>& defaultValues);
	
	template<typename First, typename ...Args>
	FString formatStr(First &&arg0, Args &&...args) {
		std::wostringstream stream;
		formatInternal(stream, arg0, args...);
		return FString(stream.str().c_str());
	}

	inline void formatInternal(std::wostringstream& str) {}

	template<typename First, typename ...Args>
	void formatInternal(std::wostringstream& stream, First &&arg0, Args &&...args) {
		stream << arg0;
		formatInternal(stream, std::forward<Args>(args)...);
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