#pragma once

#include <HookLoader.h>
#include <util/FString.h>

#pragma warning (push)
#pragma warning (disable: 4667)

class UFGItemDescriptor {
public:
	static void Constructor(UFGItemDescriptor *thiz);

	UFGItemDescriptor() {
		call<&UFGItemDescriptor::Constructor>(this);
	}
};

DEFINE_CONSTRUCTOR(UFGItemDescriptor, Constructor);


template <typename TElement, typename TAllocator>
struct TArray;

class AActor {
public:
	template <typename TComponent, typename TAllocator>
	void GetComponents(TArray<TComponent*, TAllocator>* OutComponents, bool bIncludeFromChildActors);
};

class UFGInventoryComponent;
class FDefaultAllocator;

template <>
struct HookName<&AActor::GetComponents<UFGInventoryComponent, FDefaultAllocator>> {
	static const constexpr char Name[] = "??$GetComponents@VUFGInventoryComponent@@VFDefaultAllocator@@@AActor@@QEAAXPEAU?$TArray@PEAVUFGInventoryComponent@@VFDefaultAllocator@@@@_N@Z";
};

EXPORT_METHOD(AActor::GetComponents<UFGInventoryComponent, FDefaultAllocator>);

#pragma warning (pop)