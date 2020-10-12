#include "BasicModInit.h"

void ABasicModInit::DispatchLifecyclePhase(ELifecyclePhase /*LifecyclePhase*/) {
    checkf(0, TEXT("DispatchLifecyclePhase not implemented for %s"), *GetClass()->GetPathName());
}
