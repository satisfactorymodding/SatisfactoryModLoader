#pragma once

#include <HookLoader.h>
#include <util/FString.h>

#pragma warning (push)
#pragma warning (disable: 4667)

namespace Classes {
	class UFGItemDescriptor {
	public:
		static void Constructor(UFGItemDescriptor *thiz);

		UFGItemDescriptor() {
			call<&UFGItemDescriptor::Constructor>(this);
		}
	};
}

DEFINE_CONSTRUCTOR(Classes::UFGItemDescriptor, Constructor);

namespace Classes {
	template <typename TElement, typename TAllocator>
	struct TArray;
}

namespace Classes {
	class AActor {
	public:
		template <typename TComponent, typename TAllocator>
		void GetComponents(TArray<TComponent*, TAllocator>* OutComponents, bool bIncludeFromChildActors);
	};
}
namespace Classes {
	class UFGInventoryComponent;
	class FDefaultAllocator;
}
namespace Classes {
	template <>
	struct HookName<&AActor::GetComponents<UFGInventoryComponent, FDefaultAllocator>> {
		static const constexpr char Name[] = "??$GetComponents@VUFGInventoryComponent@@VFDefaultAllocator@@@AActor@@QEAAXPEAU?$TArray@PEAVUFGInventoryComponent@@VFDefaultAllocator@@@@_N@Z";
	};
}

EXPORT_METHOD(Classes::AActor::GetComponents<Classes::UFGInventoryComponent, Classes::FDefaultAllocator>);

#pragma warning (pop)