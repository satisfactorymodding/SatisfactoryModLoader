#pragma once

#include <HookLoader.h>

#pragma warning (push)
#pragma warning (disable: 4667)

namespace SML {
	namespace Objects {
		class UButton {
		public:
			bool IsPressed();
			void SlateHandlePressed();
		};

		DEFINE_METHOD(UButton::IsPressed);
		DEFINE_METHOD(UButton::SlateHandlePressed);

		class UCheckBox {
		public:
			bool IsPressed();
		};

		DEFINE_METHOD(UCheckBox::IsPressed);

		class SButton {
		public:
			bool IsPressed();
		};

		DEFINE_METHOD(SButton::IsPressed);


		class UAkCheckBox {
		public:
			bool IsPressed();
		};

		DEFINE_METHOD(UAkCheckBox::IsPressed);

	}
}


#pragma warning (pop)
