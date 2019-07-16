#include <stdafx.h>
#include <memory/MemoryFunctions.h>
#include <util/Utility.h>
#include <string>

namespace SML {
	namespace Mod {
		namespace Functions {
			SML_API std::vector<BYTE> readMemoryBytes(void* location, int locationOffset, int sizeToRead) {
				MEMORY_BASIC_INFORMATION mem;
				HANDLE process = OpenProcess(PROCESS_VM_READ | PROCESS_QUERY_INFORMATION, FALSE, GetCurrentProcessId());
				BYTE* a = new BYTE[sizeToRead];
				void* loc = static_cast<void*>(static_cast<char*>(location) + 1);
				if (VirtualQueryEx(process, loc, &mem, sizeof(mem))) {
					ReadProcessMemory(process, loc, &a, sizeof(a), 0);
				} else {
					Utility::displayCrash("Error reading " + std::to_string(sizeToRead) + " bytes at memory location " + static_cast<char*>(loc) + ".");
				}
				std::vector<BYTE> ret;
				ret.assign(a, a + sizeToRead);
				delete[] a;
				return ret; //i really hope whatever shit i just wrote works
			}

			SML_API std::vector<BYTE> readMemoryBytes(void* location, int sizeToRead) {
				return readMemoryBytes(location, 0, sizeToRead);
			}

			SML_API void writeMemoryBytes(void* location, int locationOffset, int sizeToWrite, std::vector<BYTE> newBytes) {
				MEMORY_BASIC_INFORMATION mem;
				HANDLE process = OpenProcess(PROCESS_VM_WRITE | PROCESS_VM_OPERATION, FALSE, GetCurrentProcessId());
				BYTE* a = new BYTE[sizeToWrite];
				std::copy(newBytes.begin(), newBytes.end(), a);
				void* loc = static_cast<void*>(static_cast<char*>(location) + 1);
				if (VirtualQueryEx(process, loc, &mem, sizeof(mem))) {
					WriteProcessMemory(process, loc, &a, sizeof(a), 0);
				} else {
					Utility::displayCrash("Error writing " + std::to_string(sizeToWrite) + " bytes at memory location " + static_cast<char*>(loc) + ".");
				}
				delete[] a;
			}

			SML_API void writeMemoryBytes(void* location, int sizeToWrite, std::vector<BYTE> newBytes) {
				writeMemoryBytes(location, 0, sizeToWrite, newBytes);
			}

			SML_API std::vector<char> convertBytesToChars(std::vector<BYTE> bytes) {
				return std::vector<char>(bytes.begin(), bytes.end());
			}

			SML_API std::vector<BYTE> convertCharsToBytes(std::vector<char> chars) {
				return std::vector<BYTE>(chars.begin(), chars.end());
			}
		}
	}
}