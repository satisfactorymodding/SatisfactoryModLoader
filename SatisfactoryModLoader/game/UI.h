#pragma once

#include <HookLoader.h>

#pragma warning (push)
#pragma warning (disable: 4667)

namespace Classes {
	class UButton {
	public:
		bool IsPressed();
		void SlateHandlePressed();
	};
}

DEFINE_METHOD(Classes::UButton::IsPressed);
DEFINE_METHOD(Classes::UButton::SlateHandlePressed);

namespace Classes {
	class UCheckBox {
	public:
		bool IsPressed();
	};
}

DEFINE_METHOD(Classes::UCheckBox::IsPressed);

namespace Classes {
	class SButton {
	public:
		bool IsPressed();
	};
}

DEFINE_METHOD(Classes::SButton::IsPressed);

namespace Classes {
	class UAkCheckBox {
	public:
		bool IsPressed();
	};
}

DEFINE_METHOD(Classes::UAkCheckBox::IsPressed);

#pragma warning (pop)
