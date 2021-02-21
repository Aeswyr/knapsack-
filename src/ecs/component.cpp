#include "knapsack/component.h"

#include <vector>

#include <knapsack/internal/entity.h>
#include <knapsack/entity.h>

unsigned int CID_MAX = 0;

std::vector<WrapperBase*> MasterComponentList;

void removeComponentByID(unsigned int CID, unsigned short int index) {
    MasterComponentList[CID]->remove(index);
}

void registerComponentWrapper(WrapperBase* ptr) {
    MasterComponentList.push_back(ptr);
}

template <typename T> void ComponentVectorWrapper<T>::remove(unsigned short int index) {
    if (index < list.size()) {
        std::swap(list[index], list[list.size() - 1]);
        list.pop_back();
        if (list.size() > 0)
            ecs::entity::get(list[index].ownerID).componentPos[INTERNAL_ONLY_COMPONENT::getCID<T>()] = index;
    }
}