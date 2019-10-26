#pragma once
#include "Mod.h"
#include <../SatisfactorySDK/SDK.hpp>
#include "Registry.h"
#include <string>
#include <vector>
#include <map>
#include <memory>
#include <ttvfs.h>
#include <ttvfs_zip.h>

namespace SML {
	namespace Mod {
		class ZipHandler {
		public:
			std::vector<std::string> cleanupPaths;

			/**
			* Extract zip files before the engine has started
			* DO NOT ADD ANY EXTRA LOGIC HERE!!!
			*/
			void extractZips();

			/**
			* Cleanup and destroy
			*/
			void destroy();
		private:

			/**
			* Load mod DLL from memory
			*/
			void loadMemoryDLL(void *data, size_t size, std::string file, ModHandler modHandler);

			/**
			* Extract file from archive
			*/
			void extractFile(ttvfs::Dir* modArchive, std::string objPath, std::string outFilePath, std::string archive, bool cleanup);
		};
	}
}