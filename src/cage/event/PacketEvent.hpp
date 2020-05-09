#ifndef CAGE_EVENT_XTEVENT
#define CAGE_EVENT_XTEVENT

#include <cage/event/BaseEvent.hpp>
#include <cage/event/XTPacketEvent.hpp>
#include <cage/event/XMLPacketEvent.hpp>

#include <eventpp/eventqueue.h>
#include <eventpp/utilities/scopedremover.h>
#include <eventpp/utilities/eventutil.h>

#include <cage/client/Penguin.hpp>
#include <cage/server/BaseServer.hpp>

#include <functional>

namespace cage {
namespace client{
    class Penguin;
}
namespace event {

    struct XTEventPolicies {

        static std::string getEvent(const XTPacketEvent& e) {
            return get_type(e.xt_type) + ":" + e.category + e.handler;
        }

        static std::string  get_type(const XTPacketType& type) {
            if (type == XTPacketType::GAME) {
                return "game";
            } else
            if (type == XTPacketType::LOGIN) {
                return "login";
            } else
            if (type == XTPacketType::PLAY) {
                return "play";
            } 

            return "";
        }
    };

    struct XTRoomEventPolicies {

        static std::string getEvent(const XTPacketEvent& e) {
            if (e.roomId == -1) {
                throw exceptions::NotImplementedError("Event specific XT Room handler cannot listen to roomid=-1");
            }

            return std::to_string(e.roomId) + "(" + XTEventPolicies::get_type(e.xt_type) + ":" + e.category + e.handler + ")";
        }
    };

    struct XMLEventPolicies {

        static std::string getEvent(const XMLPacketEvent& e) {
            return e.action;
        }
    };

    eventpp::EventQueue<std::string, void(XTPacketEvent&), XTEventPolicies> XTEvent; // XT packet listens on all room id and roomid=-1
    eventpp::EventQueue<std::string, void(XTPacketEvent&), XTRoomEventPolicies> XTRoomEvent; // XT packet listens on specific room id (roomid != -1). Room specific packet will remove the same listener from XTEvent

    eventpp::EventQueue<std::string, void(XMLPacketEvent&), XMLEventPolicies> XMLEvent; // use xml only got login :shrug:

    // Scoped-remover which auto removes any function as soon as it gets out of scope :)
    eventpp::ScopedRemover<eventpp::EventQueue<std::string, void(XTPacketEvent&), XTEventPolicies>> _XTEvent(XTEvent);
    eventpp::ScopedRemover<eventpp::EventQueue<std::string, void(XTPacketEvent&), XTRoomEventPolicies>> _XTRoomEvent(XTRoomEvent);
    eventpp::ScopedRemover<eventpp::EventQueue<std::string, void(XMLPacketEvent&), XMLEventPolicies>> _XMLEvent(XMLEvent);

    void AddXTListener(std::function<void(XTPacketEvent&)> func, const XTPacketType& type, 
        const std::string& category, const std::string& handler, int room=-1) {
            std::string event = XTEventPolicies::get_type(type) + ":" + category + handler;
            if (room != -1) {
                _XTEvent.appendListener(event, func);
            } else {
                event = std::to_string(room) + "(" + event + " )";
                _XTRoomEvent.appendListener(event, func);
            }
    }

    void AddXMLListener(std::function<void(XTPacketEvent&)> func, const std::string& action) {
        _XMLEvent.appendListener(action, func);
    }
}
}

#endif