#pragma once

extern unsigned int CID_MAX; // defined in component.cpp

struct EntityID {
    long long id = 0;
	int gen = 0;
	EntityID& operator++() {
		id++;
		return *this;
	}

	bool operator==(const EntityID &e) const {
		return id == e.id && gen == e.gen;
	}
};

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