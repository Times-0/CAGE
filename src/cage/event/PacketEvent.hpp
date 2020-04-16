#ifndef CAGE_EVENT_PACKET_EVENT
#define CAGE_EVENT_PACKET_EVENT

#include <iostream>
#include <string>
#include <cage/exception/StandardExceptions.hpp>

namespace cage {
    namespace event {

        enum struct PacketType {
            ANY = 0,
            XML, 
            XT, 
            JSON
        };

        class PacketEvent {
        protected:
            std::string raw_data;
            PacketType _type = PacketType::ANY;

        public:

            PacketEvent (const std::string& data, PacketType type = PacketType::ANY) : raw_data(data), _type(type) {
                
            }

            std::string data() const {
                return raw_data;
            }

            virtual void parse() {
                throw exceptions::NotImplementedError("PacketEvent::parse()");
            }

            virtual PacketType type() const {
                return _type;
            }
        };

        class PacketEventPolicies {

            static PacketType getEvent(PacketEvent& event) {
                return event.type();
            }
        };

        class JSONPacketEvent : PacketEvent{
            static const PacketType type = PacketType::JSON;
        
        public:

            JSONPacketEvent (const std::string &data) : PacketEvent(data) { }

            void parse() override {
                std::cout << "JSONPacket parse...";

                throw exceptions::NotImplementedError("JSONParseEvent::parse()");
            }
        };
    }    
}

#endif