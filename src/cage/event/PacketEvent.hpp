#ifndef CAGE_EVENT_XTEVENT
#define CAGE_EVENT_XTEVENT

#include <cage/event/BaseEvent.hpp>
#include <cage/event/XTPacketEvent.hpp>
#include <cage/event/XMLPacketEvent.hpp>
#include <eventpp/eventqueue.h>

#include <cage/client/Penguin.hpp>
#include <cage/server/BaseServer.hpp>

namespace cage {
namespace client{
    class Penguin;
}
namespace event {
    
    struct XTEvent {
        server::ServerType _type;
        XTPacketEvent data;
        XTEvent(server::ServerType server_type, XTPacketEvent data) : _type(server_type), data(data) {

        }
    };

    struct XTEventPolicies {

        static std::string getEvent(const XTEvent& e) {
            std::string event = std::to_string(e._type);
            event += get_type(e.data.xt_type) + e.data.category + e.data.handler;
            
            return event;
        }

        static std::string get_type(const XTPacketType& t) {
            if (t == XTPacketType::GAME) {
                return "game";
            } else
            if (t == XTPacketType::LOGIN) {
                return "login";
            } else
            if (t == XTPacketType::PLAY) {
                return "play";
            } else 
                return "";
        } 
    }; 

    //eventpp::EventQueue<std::string, void(XTEvent&), >
}
}

#endif