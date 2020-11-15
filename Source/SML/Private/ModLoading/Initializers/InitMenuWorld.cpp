#include "InitMenuWorld.h"

void AInitMenuWorld::InitNative() {
}

void AInitMenuWorld::DispatchLifecyclePhase(ELifecyclePhase LifecyclePhase) {
    switch (LifecyclePhase) {
        case ELifecyclePhase::POST_INITIALIZATION: {
            InitNative();
            Init();
            break;
        }
        default: break;
    }
}
