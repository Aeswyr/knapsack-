#include <vector>

#include <knapsack/internal/entity.h>

namespace ecs {

    class Filter
    {
    private:
        std::vector<unsigned int> inc = std::vector<unsigned int>(CID_MAX);
        std::vector<unsigned int> exc = std::vector<unsigned int>(CID_MAX);
    public:
        /**
         * Sets a filter to only query entities which have the set component
         * 
         * typename T   -   the component to query for
         * returns      -   the filter with an edited inclusion list
         */ 
        template <typename T> Filter& include() {
            inc.push_back(INTERNAL_ONLY_COMPONENT::getCID<T>());
            return *this;
        }

        /**
         * Sets a filter to only query entities which have the set components
         * 
         * typename T   -   the component(s) to query for
         * returns      -   the filter with an edited inclusion list
         */ 
        template <typename T, typename... Types> Filter& include() {
            inc.push_back(INTERNAL_ONLY_COMPONENT::getCID<T>());
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
            exc.push_back(INTERNAL_ONLY_COMPONENT::getCID<T>());
            return *this;
        }

        /**
         * Sets a filter to only query entities which do not have the set components
         * 
         * typename T   -   the component(s) to exclude from the query
         * returns      -   the filter with an edited exclusion list
         */ 
        template <typename T, typename... Types> Filter& exclude() {
            exc.push_back(INTERNAL_ONLY_COMPONENT::getCID<T>());
            exclude<Types ...>();
            return *this;
        }

        /**
         * fetches a list of all entities with components matching the inclusion
         * and exclusion lists
         */ 
        std::vector<EntityID> query();
    };

    Filter filter;
};


