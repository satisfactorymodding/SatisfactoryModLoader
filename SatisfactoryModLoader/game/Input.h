#pragma once

#include <HookLoader.h>
#include <util/Objects/FString.h>
#include <util/FKey.h>

#pragma warning (push)
#pragma warning (disable: 4667)

namespace SML {
	namespace Objects {
		enum class InputEvent {
			Pressed = 0,
			Released = 1,
			Repeat = 2,
			DoubleClick = 3,
			Axis = 4,
			MAX = 5,
		};

		class PlayerInput {
		public:
			bool InputKey(SML::Objects::FKey Key, InputEvent Event, float AmountDepressed, bool bGamepad);
		};

		DEFINE_METHOD_PRE("U", PlayerInput::InputKey);
	}
}

#pragma warning (pop)