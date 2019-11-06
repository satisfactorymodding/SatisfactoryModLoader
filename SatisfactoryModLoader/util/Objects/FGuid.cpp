#include <stdafx.h>
#include "FGuid.h"

#include <sstream>

int hexStrToI(const std::string& str) {
	unsigned int x;
	std::stringstream ss;
	ss << std::hex << str;
	ss >> x;
	return static_cast<int>(x);
}

std::string hexToStr(std::uint32_t h) {
	std::stringstream s;
	s << std::hex << h;
	std::string str;
	s >> str;
	while (str.size() < sizeof(std::uint32_t) * 2) str = std::string("0") + str;
	return str;
}

namespace SML {
	namespace Objects {
		FGuid::FGuid(std::uint32_t a, std::uint32_t b, std::uint32_t c, std::uint32_t d) : a(a), b(b), c(c), d(d) {}

		FGuid::FGuid(const SDK::FGuid& o) : a(o.A), b(o.B), c(o.C), d(o.D) {}

		SML::Objects::FGuid::FGuid(std::string str) {
			a = hexStrToI(str.substr(0, 8));
			b = hexStrToI(str.substr(8, 8));
			c = hexStrToI(str.substr(16, 8));
			d = hexStrToI(str.substr(24, 8));
		}

		FGuid::operator SDK::FGuid() const {
			return SDK::FGuid{(int)a,(int)b,(int)c,(int)d};
		}

		bool FGuid::operator==(const FGuid& g) const {
			return a == g.a && b == g.b && c == g.c && d == g.d;
		}

		std::string FGuid::toStr() const {
			return hexToStr(a) + hexToStr(b) + hexToStr(c) + hexToStr(d);
		}
	}
}