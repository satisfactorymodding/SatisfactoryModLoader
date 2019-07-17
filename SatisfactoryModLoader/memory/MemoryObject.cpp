#include <stdafx.h>
#include "MemoryObject.h"
#include <util/Utility.h>
#include <string>

namespace SML {
	MemoryObject::MemoryObject(SDK::UObject* obj) {
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

	std::vector<BYTE> MemoryObject::returnBytes() {
		return this->bytes;
	}

	std::vector<char> MemoryObject::returnBytesAsChars() {
		return std::vector<char>(this->bytes.begin(), this->bytes.end());
	}

	int MemoryObject::getSize() {
		return this->size;
	}

	void MemoryObject::replaceMemory(std::vector<BYTE> newBytes) {
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

	MemoryObject::~MemoryObject() {

	}
}