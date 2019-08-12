#pragma once
#include "../SatisfactorySDK/SDK.hpp"
#include <vector>
#include <Windows.h>
#include <Lib.h>

namespace SML {
	template<class O>
	class SML_API MemoryObject {
	public:
		/**
		* Initialize a representation of an object's memory.
		*/
		SML_API MemoryObject(O* obj);

		/**
		* Returns the object's memory as an editable byte array.
		*/
		SML_API std::vector<BYTE> returnBytes();

		/**
		* Returns the object's memory as an array of chars.
		*/
		SML_API std::vector<char> returnBytesAsChars();

		/**
		* Returns the object's size.
		*/
		SML_API int getSize();

		/**
		* Replaces the object's memory with new memory
		* The new memory vector MUST be the same size as the original memory vector, otherwise an error will be thrown.
		* This function is relatively more time consuming than others.
		*/
		SML_API void replaceMemory(std::vector<BYTE> newMemory);

		/**
		* Destroy this object safely (aka do nothing and let C++ take care of it)
		*/
		SML_API ~MemoryObject();
	private:
		O* object;
		std::vector<BYTE> bytes;
		int size;
	};

}