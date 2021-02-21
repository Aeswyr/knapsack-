#pragma once

#include <vector>

template <typename T> struct ComponentDataPair {
    T component;
    unsigned int ownerID;
};

class WrapperBase {
public:
    virtual void remove(unsigned short int index) = 0;

};

template <typename T> class ComponentVectorWrapper : WrapperBase {
public:    
    std::vector<ComponentDataPair<T>> list;
    ComponentVectorWrapper() {}

    void remove(unsigned short int index);
};

void registerComponentWrapper(WrapperBase* ptr);
void removeComponentByID(unsigned int CID, unsigned short int index);