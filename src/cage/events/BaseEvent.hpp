#ifndef CAGE_EVENT_BASE_EVENT

#include <string>

namespace cage {
    namespace event {

        using CageEventType = std::string;

        enum PacketType {
            XML, 
            XT, 
            JSON
        };

        struct EventType {
            std::string category, handler;
            PacketType packet_type;

            CageEventType event;
        };

        struct BaseEvent {
            EventType type;
        };

        struct EventPolicies {
            template <class T>
            static CageEventType getEvent(const BaseEvent& e, const T& ...) {
                
            }
        }; 
    }    
}

#endif