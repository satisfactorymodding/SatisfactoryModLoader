#pragma once

#include <stdexcept>
#include <Lib.h>
#include "FMemory.h"

namespace SML {
	namespace Objects {
		template<class T>
		class TArray {
		protected:
			T* data;
			int count;
			int max;

		public:
			inline TArray() {
				data = nullptr;
				count = max = 0;
			};

			inline TArray(const TArray<T>& other) {
				if (other.max) {
					data = (T*)FMemory::malloc(other.max * sizeof(T));
					data = (T*)std::memcpy(data, other.data, other.count * sizeof(T));
					max = other.max;
					count = other.count;
				} else {
					data = nullptr;
					count = max = 0;
				}
			}

			inline TArray(TArray<T>&& other) {
				if (other.max) {
					data = other.data;
					other.data = nullptr;
					max = other.max;
					count = other.count;
					other.max = other.count = 0;
				} else {
					data = nullptr;
					count = max = 0;
				}
			}

			inline ~TArray() {
				if (max) FMemory::free(data);
			}

			inline TArray<T>& operator=(const TArray<T>& other) {
				if (max) {
					if (other.max) {
						data = (T*)FMemory::realloc(data, other.max * sizeof(T));
						data = (T*)std::memcpy(data, other.data, other.count * sizeof(T));
						count = other.count;
						max = other.max;
					} else {
						FMemory::free(data);
						data = nullptr;
						count = max = 0;
					}
				} else {
					if (other.max) {
						data = (T*)FMemory::malloc(other.max * sizeof(T));
						data = (T*)std::memcpy(data, other.data, other.count * sizeof(T));
						count = other.count;
						max = other.max;
					} else {
						data = nullptr;
						max = count = 0;
					}
				}

				return *this;
			}

			inline TArray<T>& operator=(TArray<T>&& other) {
				if (data) FMemory::free(data);
				data = nullptr;
				count = max = 0;
				if (other.Max) {
					data = other.data;
					other.data = nullptr;
					max = other.max;
					count = other.count;
					other.max = other.count = 0;
				}

				return *this;
			}

			inline int num() const {
				return count;
			};

			inline T& operator[](int i) {
				if (i < 0 || i >= count) throw std::out_of_range(std::string("TArray out of range exception for index ").append(std::to_string(i)));
				return data[i];
			};

			inline const T& operator[](int i) const {
				if (i >= count || i < 0) throw std::out_of_range(std::string("TArray out of range exception for index ").append(std::to_string(i)));
				return data[i];
			};

			inline bool isValid(int i) const {
				return i < max && i > 0;
			}

			inline void* getData() const {
				return data;
			}

			/* TODO: 
			- Add reallocation on subscript operator access
			- Add insert and erase functions
			*/
		};
	}
}