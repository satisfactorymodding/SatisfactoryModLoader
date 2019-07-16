#pragma once
#include <Lib.h>
#include <vector>
#include <Windows.h>

namespace SML {
	namespace Mod {
		namespace Functions {
			/**
			* Reads a vector of bytes from a memory location with a specified offset.
			*/
			SML_API std::vector<BYTE> readMemoryBytes(void* location, int locationOffset, int sizeToRead);

			/**
			* Reads a vector of bytes from a memory location.
			*/
			SML_API std::vector<BYTE> readMemoryBytes(void* location, int sizeToRead);

			/**
			* Writes a vector of bytes to the given location with a specified offset.
			*/
			SML_API void writeMemoryBytes(void* location, int locationOffset, int sizeToWrite, std::vector<BYTE> newBytes);

			/**
			* Writes a vector of bytes to the given location.
			*/
			SML_API void writeMemoryBytes(void* location, int sizeToWrite, std::vector<BYTE> newBytes);

			/**
			* Converts a byte vector to a char vector.
			*/

			SML_API std::vector<char> convertBytesToChars(std::vector<BYTE> bytes);

			/**
			* Converts a char vector to a byte vector.
			*/
			SML_API std::vector<BYTE> convertCharsToBytes(std::vector<char> chars);
		}
	}
}