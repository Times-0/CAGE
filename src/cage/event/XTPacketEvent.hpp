#ifndef CAGE_EVENT_XT_PACKET_EVENT
#define CAGE_EVENT_XT_PACKET_EVENT

#include <iostream>
#include <string>

#include <cage/event/PacketEvent.hpp>
#include <cage/exception/StandardExceptions.hpp>

namespace cage {
    namespace event {

        class XTPacketEvent : public PacketEvent{
            static const PacketType type = PacketType::XT;

        public:

            XTPacketEvent (const std::string &data) : PacketEvent(data) { }

            void parse() override {
                std::cout << "XTPacket parse...";
            }
        };
    }    
}

#endif