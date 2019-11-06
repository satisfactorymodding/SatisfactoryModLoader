#pragma once

#include <stdexcept>
#include <Lib.h>
#include "../SatisfactorySDK/SDK.hpp"
#include "FMemory.h"

namespace SML {
	namespace Objects {
		template<class T>
		class TArray;

		template<class T>
		struct TArrayIterator {
			TArray<T>* arr;
			size_t current;

			inline TArrayIterator(TArray<T>* arr, size_t start = 0) : arr(arr) {
				current = start;
			}

			inline bool operator!=(const TArrayIterator<T>& other) {
				return current != other.current || arr != other.arr;
			}

			inline void operator++() {
				++current;
			}

			inline T& operator*() {
				return (*arr)[current];
			}
		};

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
					max = other.max;
					count = other.count;
					for (int i = 0; i < count; ++i) {
						new (&data[i]) T(other.data[i]);
					}
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

			inline TArray(const SDK::TArray<T>& other) {
				auto o = (TArray<T>*) &other;
				data = o->data;
				max = o->max;
				count = o->count;
			}

			inline ~TArray() {
				for (int i = 0; i < count; ++i) {
					((T&) data[i]).~T();
				}
				if (max) FMemory::free(data);
			}

			inline TArray<T>& operator=(const TArray<T>& other) {
				if (max) {
					if (other.max) {
						data = (T*)FMemory::realloc(data, other.max * sizeof(T));
						data = (T*)std::memset(data, 0, other.count * sizeof(T));
						count = other.count;
						max = other.max;
						for (int i = 0; i < count; ++i) {
							new (&data[i]) T(other.data[i]);
						}
					} else {
						FMemory::free(data);
						data = nullptr;
						count = max = 0;
					}
				} else {
					if (other.max) {
						data = (T*)FMemory::malloc(other.max * sizeof(T));
						count = other.count;
						max = other.max;
						for (int i = 0; i < count; ++i) {
							new (&data[i]) T(other.data[i]);
						}
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
				if (other.max) {
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

			inline void add(const T& item) {
				if (!max) {
					data = (T*) FMemory::malloc(1);
					count = 0;
					max = 1;
				} else if (count + 1 > max) {
					max = count + 1;
					data = (T*) FMemory::realloc(data, max * sizeof(T));
				}
				++count;
				new (&data[count - 1]) T(item);
			}

			inline void remove(int i) {
				if (i < 0 || i >= max) throw std::out_of_range("index is not valid");
				--max;
				--count;
				auto n = (T*) FMemory::malloc(max * sizeof(T));
				memcpy(n, data, i * sizeof(T));
				memcpy((void*)((size_t)n + i*sizeof(T)), (void*)((size_t)data + (i + 1)*sizeof(T)), (max - i) * sizeof(T));
				FMemory::free(data);
				data = n;
			}

			inline void clear() {
				this->~TArray();
				count = max = 0;
				data = nullptr;
			}

			inline TArrayIterator<T> begin() {
				return TArrayIterator<T>(this);
			}

			inline TArrayIterator<T> end() {
				return TArrayIterator<T>(this, count);
			}

			/* TODO: 
			- Add reallocation on subscript operator access
			*/
		};
	}
}