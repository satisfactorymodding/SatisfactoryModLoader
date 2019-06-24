#pragma once

#include "../Lib.h"
#include "../SatisfactorySDK/SDK.hpp"
#include <string>
#include <vector>
#include <util/Utility.h>

#define MOD_API extern "C" __declspec(dllexport)

namespace SML {
	namespace Mod {
		class Mod {
		private:
			bool postSetupCalled;

		public:
			struct Info {
				std::string loaderVersion;
				std::string name;
				std::string version;
				std::string description;
				std::string authors;
				std::vector<std::string> dependencies;
			};

			SML_API Mod(const Info& info);

			virtual void SML_API setup();
			virtual void SML_API postSetup();
			virtual SML_API ~Mod();

			// called by mod loader
			void callPostSetup() {
				if (postSetupCalled)
					return;

				postSetupCalled = true;
				postSetup();
			}

			Info info;
		};
	}
}