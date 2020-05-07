#ifndef CAGE_EVENT_BASE_EVENT
#define CAGE_EVENT_BASE_EVENT

#include <string>

namespace cage {
namespace event {

    /**
     * @brief Generic Basic Event template.
     * 
     * @tparam T type of event. eg: int
     * @tparam D type of the data event holds. eg: string
     */
    template <class T, class D>
    struct BaseEvent {
        T type;
        D data;
    };

    /**
     * @brief Describes event policies for BasicEvent class, required by evetpp
     * 
     */
    struct BaseEventPolicies {

        template <class T, class D>
        static T getEvent(const BaseEvent<T, D>& e) {
            return e.type;
        }
    }; 
}    
}

#endif