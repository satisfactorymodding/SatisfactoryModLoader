#include <stdafx.h>
#include "MemoryObject.h"
#include <util/Utility.h>
#include <string>

namespace SML {
	template<class O>
	MemoryObject<O>::MemoryObject(O* obj) {
		this->object = obj;
		this->size = sizeof(*obj);

		MEMORY_BASIC_INFORMATION mem;
		HANDLE process = OpenProcess(PROCESS_VM_READ | PROCESS_QUERY_INFORMATION, FALSE, GetCurrentProcessId());
		BYTE a[sizeof(*obj)];

		if (VirtualQueryEx(process, reinterpret_cast<void*>(obj), &mem, sizeof(mem))) {
			ReadProcessMemory(process, reinterpret_cast<void*>(obj), &a, sizeof(a), 0);
		}
		this->bytes = std::vector<BYTE>(std::begin(a), std::end(a));
	}

	template<class O>
	std::vector<BYTE> MemoryObject<O>::returnBytes() {
		return this->bytes;
	}

	template<class O>
	std::vector<char> MemoryObject<O>::returnBytesAsChars() {
		return std::vector<char>(this->bytes.begin(), this->bytes.end());
	}

	template<class O>
	int MemoryObject<O>::getSize() {
		return this->size;
	}

	template<class O>
	void MemoryObject<O>::replaceMemory(std::vector<BYTE> newBytes) {
		if (newBytes.size() == this->size) {
			this->bytes = newBytes;
			HANDLE process = OpenProcess(PROCESS_VM_WRITE | PROCESS_VM_OPERATION, FALSE, GetCurrentProcessId());
			BYTE newArray[sizeof(this->object)];
			std::copy(newBytes.begin(), newBytes.end(), newArray);
			WriteProcessMemory(process, reinterpret_cast<void*>(this->object), &newArray, this->size, 0);
		}
		else {
			Utility::displayCrash("ObjectMemory::replaceMemory expected a vector size of " + std::to_string(this->size) + "but instead recived a vector size of " + std::to_string(newBytes.size()) + ".");
		}
	}

	template<class O>
	MemoryObject<O>::~MemoryObject() {

	}
}