#include <stdafx.h>
#include "Mod.h"

namespace SML {
	namespace Mod {
		Mod::Mod(const Info& info)
			: post_setup_called(false)
			, info(std::move(info)) {}

		void Mod::setup() {}
		void Mod::post_setup() {}
		Mod::~Mod() {}
	}
}