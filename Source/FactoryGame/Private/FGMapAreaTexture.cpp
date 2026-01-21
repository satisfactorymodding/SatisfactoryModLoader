// This file has been manually implemented by Th3Fanbus

#include "FGMapAreaTexture.h"

#if WITH_EDITOR
#include "Framework/Notifications/NotificationManager.h"
#include "Widgets/Notifications/SNotificationList.h"
#include "UObject/ObjectSaveContext.h"

DEFINE_LOG_CATEGORY_STATIC(LogMapAreaTexture, Log, All);

static bool GetTexturePixels(UTexture2D* Texture, TFunction<void(const FColor*, const int32, const int32)> Func)
{
	bool bSuccess = false;

	/* We assume Mip 0 always exists */
	FTexture2DMipMap* Mip = &Texture->GetPlatformData()->Mips[0];
	const uint32 OldBulkDataFlags = Mip->BulkData.GetBulkDataFlags();

	/* Ensure the texture is fully loaded. Necessary in game, unsure if also needed in the editor */
	Texture->SetForceMipLevelsToBeResident(3600, 0);
	Texture->WaitForStreaming(true, false);

	/* Do not allow bulk data to be discarded, useful when unlocking/locking very often */
	Mip->BulkData.ClearBulkDataFlags(BULKDATA_AlwaysAllowDiscard | BULKDATA_SingleUse);

	/* Access the bulk data; if successful, process it */
	if (const FColor* Ptr = reinterpret_cast<const FColor*>(Mip->BulkData.LockReadOnly())) {
		Invoke(Func, Ptr, Mip->SizeX, Mip->SizeY);
		bSuccess = true;
	}
	Mip->BulkData.Unlock();

	/* Clean up texture force loading */
	Mip->BulkData.ResetBulkDataFlags(OldBulkDataFlags);
	Texture->SetForceMipLevelsToBeResident(0, 0);

	return bSuccess;
}

static FORCEINLINE FColorMapAreaPair AreaFromColor(FColor Color)
{
	FColorMapAreaPair Area;
	Area.PaletteColor = Color;
	return Area;
}

static void ShowPostEditNotification(const FText& NotificationText, SNotificationItem::ECompletionState State)
{
	FNotificationInfo Info(NotificationText);
	Info.ExpireDuration = 5.0f;
	Info.bUseLargeFont = false;
	TSharedPtr<SNotificationItem> Notification = FSlateNotificationManager::Get().AddNotification(Info);
	if (Notification.IsValid()) {
		Notification->SetCompletionState(State);
	}
}

void UFGMapAreaTexture::PostEditChangeProperty(FPropertyChangedEvent& propertyChangedEvent)
{
	Super::PostEditChangeProperty(propertyChangedEvent);

	if (not propertyChangedEvent.Property) {
		return;
	}
	FName PropertyName = propertyChangedEvent.Property->GetFName();
	UE_LOG(LogMapAreaTexture, Verbose, TEXT("PostEdit property '%s' on %s"), *PropertyName.ToString(), *GetPathName());
	if (PropertyName == GET_MEMBER_NAME_CHECKED(UFGMapAreaTexture, mAreaTexture)) {
		if (not mAreaTexture) {
			const FString Msg = FString::Printf(TEXT("Unset texture, but kept the rest of parameters unchanged"));
			ShowPostEditNotification(FText::FromString(Msg), SNotificationItem::CS_Success);
			return;
		}
		if (mAreaTexture->GetSizeX() != mAreaTexture->GetSizeY()) {
			const FString Msg = FString::Printf(TEXT("%s size %d x %d is not square"), *mAreaTexture->GetName(), mAreaTexture->GetSizeX(), mAreaTexture->GetSizeY());
			ShowPostEditNotification(FText::FromString(Msg), SNotificationItem::CS_Fail);
			return;
		}
		const EPixelFormat Format = mAreaTexture->GetPixelFormat();
		if (Format != EPixelFormat::PF_B8G8R8A8) {
			const FString Msg = FString::Printf(TEXT("Unsupported pixel format %s"), GetPixelFormatString(Format));
			ShowPostEditNotification(FText::FromString(Msg), SNotificationItem::CS_Fail);
			return;
		}
		const bool Success = GetTexturePixels(mAreaTexture, [this](const FColor* Ptr, const int32 SizeX, const int32 SizeY) {
			TMap<FColor, uint8> ColorMap;
			TArray<FColor> OldPalette = mColorPalette;
			TArray<FColorMapAreaPair> OldColorToArea = mColorToArea;
			mColorPalette.Empty();
			mColorToArea.Empty();
			mAreaData.SetNum(SizeX * SizeY);
			mDataWidth = SizeX;
			for (int32 Y = 0; Y < SizeY; Y++) {
				for (int32 X = 0; X < SizeX; X++) {
					const int32 Offset = Y * SizeX + X;
					const FColor Color = Ptr[Offset];
					const uint8 Len = ColorMap.Num();
					const uint8 Idx = ColorMap.FindOrAdd(Color, Len);
					mAreaData[Offset] = Idx;
					if (Idx == Len) {
						const int32 OldIdx = OldPalette.Find(Color);
						if (OldIdx == INDEX_NONE) {
							UE_LOG(LogMapAreaTexture, Log, TEXT("New colour %s at (%d, %d) with idx %d"), *Color.ToHex(), X, Y, Idx);
							mColorPalette.Add(Color);
							mColorToArea.Add(AreaFromColor(Color));
						} else {
							UE_LOG(LogMapAreaTexture, Log, TEXT("Remapping colour %s at (%d, %d) from idx %d to idx %d"), *Color.ToHex(), X, Y, OldIdx, Idx);
							mColorPalette.Add(OldPalette[OldIdx]);
							mColorToArea.Add(OldColorToArea[OldIdx]);
						}
					}
					FColorMapAreaPair& Area = mColorToArea[Idx];
					Area.MinX = FMath::Min(Area.MinX, X);
					Area.MinY = FMath::Min(Area.MinY, Y);
					Area.MaxX = FMath::Max(Area.MaxX, X);
					Area.MaxY = FMath::Max(Area.MaxY, Y);
				}
			}
		});
		if (Success) {
			const FString Msg = FString::Printf(TEXT("Done parsing %s, found %d colours"), *mAreaTexture->GetName(), mColorPalette.Num());
			ShowPostEditNotification(FText::FromString(Msg), SNotificationItem::CS_Success);

			this->MarkPackageDirty();
			/* TODO: Do we need to do this? */
			UClass* Class = this->GetClass();
			Class->MarkPackageDirty();
			Class->GetDefaultObject()->MarkPackageDirty();
		} else {
			const FString Msg = FString::Printf(TEXT("Could not process %s"), *mAreaTexture->GetName());
			ShowPostEditNotification(FText::FromString(Msg), SNotificationItem::CS_Fail);
		}
	}
}

void UFGMapAreaTexture::GenerateAreaData(bool reopenAssetEditor, TArray<UPackage*>& out_modifiedAddedPackages) {}

#endif
void UFGMapAreaTexture::InitMapAreaTexture(AFGMinimapCaptureActor* inCaptureActor) {}
TSubclassOf< UFGMapArea > UFGMapAreaTexture::GetMapAreaForWorldLocation(FVector worldLocation) { return TSubclassOf<UFGMapArea>(); }
void UFGMapAreaTexture::InitFogOfWarTexture(UObject* worldContext) {}
UTexture2D* UFGMapAreaTexture::GetFogOfWarTexture() const {	return mFogOfWarTexture; }
void UFGMapAreaTexture::GetAllMapAreas(TArray< TSubclassOf< UFGMapArea > > out_MapAreas) const
{
	for (FColorMapAreaPair Pair : mColorToArea) {
		out_MapAreas.Add(Pair.MapArea);
	}
}
void UFGMapAreaTexture::OnNewMapAreaVisisted(TSubclassOf< UFGMapArea > newMapArea) {}
void UFGMapAreaTexture::UpdateFogOfWarTexture(TSubclassOf< UFGMapArea > newMapArea) {}
