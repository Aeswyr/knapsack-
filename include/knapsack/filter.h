#include <vector>

#include <boost/dynamic_bitset.hpp>

#include <knapsack/internal/entity.h>

namespace ecs {

    class Filter
    { 
    private:
        boost::dynamic_bitset<> inc = boost::dynamic_bitset<>(CID_MAX);
        boost::dynamic_bitset<> exc = boost::dynamic_bitset<>(CID_MAX);
    public:
        /**
         * Sets a filter to only query entities which have the set component
         * 
         * typename T   -   the component to query for
         * returns      -   the filter with an edited inclusion list
         */ 
        template <typename T> Filter& include() {
            inc[INTERNAL_ONLY_COMPONENT::getCID<T>()] = 1;
            return *this;
        }

        /**
         * Sets a filter to only query entities which have the set components
         * 
         * typename T   -   the component(s) to query for
         * returns      -   the filter with an edited inclusion list
         */ 
        template <typename T, typename... Types> Filter& include() {
            inc[INTERNAL_ONLY_COMPONENT::getCID<T>()] = 1;
            include<Types ...>();
            return *this;
        }

        /**
         * Sets a filter to only query entities which do not have the set component
         * 
         * typename T   -   the component to exclude from the query
         * returns      -   the filter with an edited exclusion list
         */ 
        template <typename T> Filter& exclude() {
            exc[INTERNAL_ONLY_COMPONENT::getCID<T>()] = 1;
            return *this;
        }

        /**
         * Sets a filter to only query entities which do not have the set components
         * 
         * typename T   -   the component(s) to exclude from the query
         * returns      -   the filter with an edited exclusion list
         */ 
        template <typename T, typename... Types> Filter& exclude() {
            exc[INTERNAL_ONLY_COMPONENT::getCID<T>()] = 1;
            exclude<Types ...>();
            return *this;
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

    Filter filter;
};


