#pragma once

#include <vector>
#include <memory>

#include <knapsack/internal/entity.h>


namespace ecs {
    class Filter
    { 
    private:
        std::shared_ptr<void> inc;
        std::shared_ptr<void> exc;

        void setInc(unsigned int CID);
        void setExc(unsigned int CID);
    public:
        Filter();

        /**
         * Sets a filter to only query entities which have the set component
         * 
         * typename T   -   the component to query for
         * returns      -   the filter with an edited inclusion list
         */ 
        template <typename T> Filter& include() {
            setInc(INTERNAL_ONLY_COMPONENT::getCID<T>());
            return *this;
        }

        /**
         * Sets a filter to only query entities which have the set components
         * 
         * typename T   -   the component(s) to query for
         * returns      -   the filter with an edited inclusion list
         */ 
        template <typename T, typename U, typename... Types> Filter& include() {
            setInc(INTERNAL_ONLY_COMPONENT::getCID<T>());
            return include<U, Types ...>();
        }

        /**
         * Sets a filter to only query entities which do not have the set component
         * 
         * typename T   -   the component to exclude from the query
         * returns      -   the filter with an edited exclusion list
         */ 
        template <typename T> Filter& exclude() {
            setExc(INTERNAL_ONLY_COMPONENT::getCID<T>());
            return *this;
        }

        /**
         * Sets a filter to only query entities which do not have the set components
         * 
         * typename T   -   the component(s) to exclude from the query
         * returns      -   the filter with an edited exclusion list
         */ 
        template <typename T, typename U, typename... Types> Filter& exclude() {
            setExc(INTERNAL_ONLY_COMPONENT::getCID<T>());
            return exclude<U, Types ...>();
        }

        /**
         * clears this filter's inclusion and exclusion lists
         */ 
        void reset();

        /**
         * fetches a list of all entities with components matching the inclusion
         * and exclusion lists
         */ 
        std::vector<EntityID> query();
    };
    
    Filter filter();
};


