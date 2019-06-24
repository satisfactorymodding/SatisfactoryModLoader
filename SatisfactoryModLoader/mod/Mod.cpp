#include <stdafx.h>
#include "Mod.h"

namespace SML {
	namespace Mod {
		Mod::Mod(const Info& info)
			: postSetupCalled(false)
			, info(std::move(info)) {}

		void Mod::setup() {}
		void Mod::postSetup() {}
		Mod::~Mod() {}
	}
}