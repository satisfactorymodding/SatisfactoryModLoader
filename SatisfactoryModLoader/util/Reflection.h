#pragma once

namespace SML {
	namespace Utility {
		static const char* gameModule = "FactoryGame-Win64-Shipping.exe";

		void* get_field_value(void* module, const char* procName);

		// gets a field's value
		template <typename O>
		bool get_field_value(void* module, const char* procName, O& value) {
			void* proc = get_field_value(module, procName);
			if (proc == nullptr) {
				return false;
			}

			value = *(O*)proc;
			return true;
		}
	}
}