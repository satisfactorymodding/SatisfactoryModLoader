#pragma once
#include "../SatisfactorySDK/SDK.hpp"
#include <vector>
#include <Windows.h>
#include <Lib.h>

namespace SML {
	class SML_API MemoryObject {
	public:
		/**
		* Initialize a representation of an object's memory.
		*/
		MemoryObject(SDK::UObject* obj);

		/**
		* Returns the object's memory as an editable byte array.
		*/
		std::vector<BYTE> returnBytes();

		/**
		* Returns the object's memory as an array of chars.
		*/
		std::vector<char> returnBytesAsChars();

		/**
		* Returns the object's size.
		*/
		int getSize();

		/**
		* Replaces the object's memory with new memory
		* The new memory vector MUST be the same size as the original memory vector, otherwise an error will be thrown.
		* This function is relatively more time consuming than others.
		*/
		void replaceMemory(std::vector<BYTE> newMemory);

		/**
		* Destructor
		*/
		~MemoryObject();
	private:
		SDK::UObject* object;
		std::vector<BYTE> bytes;
		int size;
	};

}