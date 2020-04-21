#ifndef CAGE_EVENT_XT_PACKET_EVENT
#define CAGE_EVENT_XT_PACKET_EVENT

#include <iostream>
#include <string>

#include <cage/event/PacketEvent.hpp>
#include <cage/exception/XTExceptions.hpp>

namespace cage {
    namespace event {

        enum struct XTPacketType {
            PLAY,
            GAME
        };

        class XTPacketEvent : public PacketEvent{
        public:
            XTPacketType xt_type;
            std::string category, handler;
            int roomId;
            std::string arguments;

            XTPacketEvent (const std::string &data) : PacketEvent(data, PacketType::XT) { }

            void parse() override {
                if(raw_data.find("%xt%", 0) != 0 || raw_data.rfind("%") != raw_data.size()-1) {
                    throw exceptions::MalformedXTError();
                }

                std::string data = raw_data.substr(4, raw_data.size()-5);
                std::string type = data.substr(0, data.find("%"));
                if (type.empty()) {
                    throw exceptions::XTParseError("no type specified");
                }

                if (type == "s") {
                    xt_type = XTPacketType::PLAY;
                } else 
                if (type == "z") {
                    xt_type = XTPacketType::GAME;
                } else {
                    throw exceptions::XTParseError("unknown type");
                }

                data.erase(0, type.size()+1);
                type = data.substr(0, data.find("%"));
                if (type.empty()) {
                    throw exceptions::XTParseError("no category/handler specified");
                }

                category = type.substr(0, type.find("#"));    
                data.erase(0, category.size() + 1);
                handler = data.substr(0, data.find("%"));
                if (handler.empty()) {
                    throw exceptions::XTParseError("no handler specified");
                }

                data.erase(0, handler.size() + 1);
                roomId = std::atoi(data.substr(0, data.find("%")).c_str());
                if (roomId == 0) {
                    throw exceptions::XTParseError("invalid room id specified");
                }

                arguments = data.erase(0, data.find("%")+1);
            }
        };
    }    
}

#endif