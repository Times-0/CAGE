#ifndef CAGE_EVENT_PACKET_EVENT

#include <iostream>
#include <string>
#include <eventpp/eventqueue.h>
#include <cage/exception/StandardExceptions.hpp>

namespace cage {
    namespace event {

        enum struct PacketType {
            XML, 
            XT, 
            JSON
        };

        class PacketEvent {
            std::string raw_data;

        public:

            PacketEvent (const std::string& data) : raw_data(data) {
                
            }

            std::string data() const {
                return raw_data;
            }

            virtual void parse() {
                throw exceptions::NotImplementedError("PacketEvent::parse()");
            }
        };

        
        class XTPacketEvent : public PacketEvent{
            static const PacketType type = PacketType::XT;

        public:

            void parse() override {
                std::cout << "XTPacket parse...";
            }
        };

        class XMLPacketEvent : PacketEvent{
            static const PacketType type = PacketType::XML;

            void parse() override {
                std::cout << "XMLPacket parse...";
            }
        };

        class JSONPacketEvent : PacketEvent{
            static const PacketType type = PacketType::JSON;

            void parse() override {
                std::cout << "JSONPacket parse...";

                throw exceptions::NotImplementedError("JSONParseEvent::parse()");
            }
        };
    }    
}

#endif