#include "SessionSettings/SessionSetting.h"

USMLSessionSetting::USMLSessionSetting() {
	UserSetting = CreateDefaultSubobject<UFGUserSetting>(TEXT("UserSetting"));
	bCanEditAfterSessionCreation = true;
}

#if WITH_EDITOR

void USMLSessionSetting::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) {
	Super::PostEditChangeProperty(PropertyChangedEvent);

	//Carry over changes to the ApplyType property of the user setting
	if (PropertyChangedEvent.MemberProperty->GetFName() == GET_MEMBER_NAME_CHECKED(ThisClass, ApplyType)) {
		UserSetting->ApplyType = ApplyType;
	}
}

#endif
