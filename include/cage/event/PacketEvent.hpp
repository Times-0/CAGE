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

        /**
         * @brief PacketEvent is fired when a packet of data is received.
         *  It stores raw-data, and parses it, if possible.
         * 
         */
        class PacketEvent {
        protected:
            std::string raw_data;
            PacketType _type = PacketType::ANY;

        public:
            /**
             * @brief Construct a new Packet Event object
             * 
             * @param data the raw-data packets
             * @param type type of packet, eg: XT, XML, JSON
             */
            PacketEvent (const std::string& data, PacketType type = PacketType::ANY) : raw_data(data), _type(type) {
                
            }

            /**
             * @brief returns raw-data packets.
             * 
             * @return std::string 
             */
            std::string data() const {
                return raw_data;
            }

            virtual void parse() {
                throw exceptions::NotImplementedError("PacketEvent::parse()");
            }

            PacketType type() const {
                return _type;
            }
        };

        class PacketEventPolicies {

            static PacketType getEvent(PacketEvent& event) {
                return event.type();
            }
        };

        class JSONPacketEvent : PacketEvent{
        
        public:

            JSONPacketEvent (const std::string &data) : PacketEvent(data, PacketType::JSON) { }

            void parse() override {
                std::cout << "JSONPacket parse...";

                throw exceptions::NotImplementedError("JSONParseEvent::parse()");
            }
        };
    }    
}

#endif