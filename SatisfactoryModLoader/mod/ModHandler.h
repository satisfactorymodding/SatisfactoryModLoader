#pragma once
#include "Mod.h"
#include "Registry.h"
#include <string>
#include <vector>
#include <memory>

namespace SML {
	namespace Mod {
		// holds important information about the loaded mods. It should never be accessed by mods directly.
		class ModHandler {
		public:
			std::vector<std::unique_ptr<Mod>> mods;

			std::vector<Registry> commandRegistry;
			std::vector<Registry> APIRegistry;

			void load_mods(const char* startingPath);
			void setup_mods();
			void check_dependencies();
			void post_setup_mods();
		private:
			std::vector<std::string> modNameDump;
			void recursive_dependency_load(Mod& mod, int i);
			void get_files(std::string path);
			void find_mods(std::string path);
		};
	}
}