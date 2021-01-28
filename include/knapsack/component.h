#pragma once

#include <iostream>
#include <vector>

#include <knapsack/internal/entity.h>

/**
 * A base struct all components must extend. Components are collections of
 * raw data which can be composed onto entities to describe specific game
 * objects.
 * 
 * User created components must both extend this struct, as well as implement
 * a default constructor. Best practice would be to manually invoke the base constructor
 * as well eg.
 *      Child_Component() : Component() {}
 */ 
template <typename T> struct Component {
private:
    class ComponentRegister {
    public:
        ComponentRegister(int id) {
            std::cout << "registered component " << typeid(T).name() << " for ID " << id << std::endl;
        }
         static ComponentRegister reg() {
            unsigned int i = INTERNAL_ONLY_COMPONENT::getCID<T>();
            ComponentRegister r(i);
            return r;
        }
    };
protected:
    static ComponentRegister r;
public:
    struct ComponentDataPair {
        T component;
        unsigned short component_index;
    };
    static std::vector<ComponentDataPair> componentList;
    
    Component() {
        (void)r;
    }

    virtual void serialize(void) {}
    virtual void deserialize(void) {}
};

template <typename T> typename Component<T>::ComponentRegister Component<T>::r = ComponentRegister::reg();

template <typename T>  std::vector<typename Component<T>::ComponentDataPair> Component<T>::componentList = std::vector<Component<T>::ComponentDataPair>();

