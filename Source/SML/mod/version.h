#pragma once
#include <string>

namespace SML {
	namespace Versioning {
		enum EComparisonOp {
			EQUALS,
			GREATER,
			GREATER_EQUALS,
			LESS,
			LESS_EQUALS
		};
		
		class FVersion {
		public:
			uint64_t major;
			uint64_t minor;
			uint64_t patch;
			std::wstring type;
			std::wstring buildInfo;

			FVersion();
			FVersion(const std::wstring& string);
		public:
			std::wstring string() const;

			int compare(const FVersion& other) const;
		};
		class FVersionRange {
		private:
			EComparisonOp op;
			FVersion myVersion;
		public:
			FVersionRange();
			FVersionRange(const std::wstring& string);

			std::wstring string() const;
			bool matches(const FVersion& version) const;
		};
	};
};
		
