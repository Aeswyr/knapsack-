#pragma once

#include <vector>

template <typename T> struct ComponentDataPair {
    T component;
    EntityID ownerID;
};

class WrapperBase {
public:
    virtual void remove(unsigned short int index) = 0;

};

void setEntityIndex(EntityID ID, unsigned int CID, unsigned short int index);

template <typename T> class ComponentVectorWrapper : public WrapperBase {
public:    
    std::vector<ComponentDataPair<T>> list;
    ComponentVectorWrapper() {}

    void remove(unsigned short int index) {
        if (index < list.size()) {
            std::swap(list[index], list[list.size() - 1]);
            list.pop_back();
            if (list.size() > 0)
                setEntityIndex(list[index].ownerID, INTERNAL_ONLY_COMPONENT::getCID<T>(), index);
        }
    }
};

void registerComponentWrapper(WrapperBase* ptr);
void removeComponentByID(unsigned int CID, unsigned short int index);