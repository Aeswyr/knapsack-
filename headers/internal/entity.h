#pragma once
extern unsigned int CID_MAX; // defined in component.cpp

namespace INTERNAL_ONLY_COMPONENT {
    using CID = unsigned int;

inline CID getCID() {
	return CID_MAX++;
}

template <typename T> inline CID getCID() noexcept {
	static CID typeID = getCID();
	return typeID;
}
};