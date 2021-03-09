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

void setEntityIndex(EntityID ID, unsigned int CID, unsigned short int index) {
    ecs::entity::get(ID).compPos(CID) = index;
}