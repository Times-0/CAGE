#ifndef CAGE_EVENT_PENGUINEVENT
#define CAGE_EVENT_PENGUINEVENT

#include <memory>

#include <cage/event/BaseEvent.hpp>
#include <eventpp/eventqueue.h>
#include <cage/client/Penguin.hpp>

namespace cage {
namespace client {
    class Penguin;
}
namespace event {
    enum struct PenguinEventType {
        CONNECTED,
        DISCONNECTED,
        CONNECTED_TO_LOGIN,
        CONNECTED_TO_WORLD
    };

    using PenguinConnectionEvent = BaseEvent<PenguinEventType, std::shared_ptr<client::Penguin>>;

    eventpp::EventQueue<PenguinEventType, void (PenguinConnectionEvent&), BaseEventPolicies> penguin_connection_event;
}
}


#endif