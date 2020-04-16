#ifndef CAGE_EVENT_XML_PACKET_EVENT
#define CAGE_EVENT_XML_PACKET_EVENT

#include <iostream>
#include <string>

#include <pugixml/pugixml.hpp>

#include <cage/event/PacketEvent.hpp>
#include <cage/exception/StandardExceptions.hpp>
#include <cage/exception/XMLExceptions.hpp>

namespace cage {
    namespace event {

        class XMLPacketEvent : PacketEvent{
            static const PacketType PacketEvent::_type = PacketType::XML;
            
        public:
            std::string action;
            pugi::xml_node body;

            XMLPacketEvent (const std::string &data) : PacketEvent(data) { }

            void parse() override {
                pugi::xml_document doc;
                pugi::xml_parse_result result = doc.load_string(data().c_str());

                if (!result) {
                    throw exceptions::MalformedXMLError();
                }

                body = doc.child("msg").child("body");
                if (!body || !body.attribute("action")) {
                    throw exceptions::XMLParseError("element body or (and) attribute action not found.");
                }

                action = body.attribute("action").value();
            }

            PacketType type() const override {
                return _type;
            }
        };
    }    
}

#endif