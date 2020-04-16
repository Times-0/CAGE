#ifndef CAGE_EVENT_XML_PACKET_EVENT
#define CAGE_EVENT_XML_PACKET_EVENT

#include <iostream>
#include <string>

#include <pugixml/pugixml.hpp>

#include <cage/event/PacketEvent.hpp>
#include <cage/exception/StandardExceptions.hpp>

namespace cage {
    namespace event {

        class XMLPacketEvent : PacketEvent{
            static const PacketType type = PacketType::XML;
        
        public:

            XMLPacketEvent (const std::string &data) : PacketEvent(data) { }

            void parse() override {
                std::cout << "XMLPacket parse...";
            }
        };
    }    
}

#endif