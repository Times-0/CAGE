#ifndef CAGE_EVENT_BASE_EVENT

#include <string>

namespace cage {
    namespace event {

        template <class T, class D>
        struct BaseEvent {
            T type;
            D& data;
        };

        struct BaseEventPolicies {

            template <class T, class D>
            static T getEvent(const BaseEvent<T, D>& e) {
                return e.type;
            }
        }; 
    }    
}

#endif