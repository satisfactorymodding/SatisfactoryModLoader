#pragma once

#include <cstdint>
#include <util/Objects/FString.h>
#include <HookLoader.h>

#include "Objects/FName.h"

namespace SML {
	namespace Objects {
		struct ITextData {
		public:
			virtual ~ITextData() {
			}

			/**
			 * True if this text data owns its localized string pointer, and allows you to call GetMutableLocalizedString on it
			 */
			virtual bool OwnsLocalizedString() const = 0;

			/**
			 * Get the string to use for display purposes.
			 * This may have come from the localization manager, or may been generated at runtime (eg, via FText::AsNumber).
			 */
			virtual const FString& GetDisplayString() const = 0;

			/**
			 * Get the string pointer that was retrieved from the text localization manager.
			 * Text that was generated at runtime by default will not have one of these, and you must call Persist() to generate one.
			 */
			virtual void* GetLocalizedString() const = 0;

			/**
			 * Get a mutable reference to the localized string associated with this text (used when loading/saving text).
			 */
			virtual void*& GetMutableLocalizedString() = 0;

			/**
			 * Get the history associated with this text.
			 */
			virtual const void*& GetTextHistory() const = 0;

			/**
			 * Get a mutable reference to the history associated with this text (used when loading/saving text).
			 */
			virtual void*& GetMutableTextHistory() = 0;

			/**
			 * Persist this text so that it can be stored in the localization manager.
			 */
			virtual void PersistText() = 0;

			/**
			 * Get the global history revision associated with this text instance.
			 */
			virtual void* GetGlobalHistoryRevision() const = 0;

			/**
			 * Get the local history revision associated with this text instance.
			 */
			virtual void* GetLocalHistoryRevision() const = 0;

			/**
			 * Assign a new history object to this instance.
			 * @note: There is no RTTI on these types, so it is your responsibility to make sure that the history object you're assigning is of the correct type!
			 */
			template <typename THistoryType>
			void SetTextHistory(THistoryType&& InHistory);
		};

		struct FText {
			ITextData* TextData;
			uint16_t flags;

			const FString* ToString();
		};

		DEFINE_METHOD(FText::ToString);

		struct TAttribute {
			FText Value;
			int64_t overflow;
		};

		struct FKeyDetails {
			void* Key;
			void* MenuCategory;
			unsigned char bIsModifierKey : 1;
			unsigned char bIsGamepadKey : 1;
			unsigned char bIsMouseButton : 1;
			unsigned char bIsBindableInBlueprints : 1;
			int64_t AxisType;
			char Padding_1[6];
			TAttribute LongDisplayName;
			TAttribute ShortDisplayName;
		};

		template <typename T>
		struct SharedPtr {
			T* object;

			T* operator->() const { return object; }

		private:
			void* refcount;
		};

		struct FKey {
			FName KeyName;
			SharedPtr<FKeyDetails> KeyDetails;
		};
	}
}