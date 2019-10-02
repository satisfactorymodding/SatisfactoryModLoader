#pragma once

#include <HookLoader.h>
#include <util/Objects/FString.h>

#pragma warning (push)
#pragma warning (disable: 4667)

namespace SML {
	namespace Objects {
		class UFGItemDescriptor {
		public:
			static void Constructor(UFGItemDescriptor *thiz);

			UFGItemDescriptor() {
				call<&UFGItemDescriptor::Constructor>(this);
			}
		};

		DEFINE_CONSTRUCTOR(UFGItemDescriptor, Constructor);

		class AActor {
		public:
			template <typename TComponent, typename TAllocator>
			void GetComponents(TArray<TComponent*>* OutComponents, bool bIncludeFromChildActors);
			bool Destroy(bool bNetForce, bool bShouldModifyLevel);
			void BeginPlay();
		};

		DEFINE_METHOD(AActor::Destroy);
		DEFINE_METHOD(AActor::BeginPlay);

		class UFGInventoryComponent;
		class FDefaultAllocator;

		EXPORT_METHOD(AActor::GetComponents<SML::Objects::UFGInventoryComponent, SML::Objects::FDefaultAllocator>);

		template <>
		struct HookName<&AActor::GetComponents<UFGInventoryComponent, FDefaultAllocator>> {
			static const constexpr char Name[] = "??$GetComponents@VUFGInventoryComponent@@VFDefaultAllocator@@@AActor@@QEAAXPEAU?$TArray@PEAVUFGInventoryComponent@@VFDefaultAllocator@@@@_N@Z";
		};
	}
}

#pragma warning (pop)