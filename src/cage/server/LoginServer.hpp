#ifndef CAGE_SERVER_LOGIN_SERVER
#define CAGE_SERVER_LOGIN_SERVER

#include <cage/event/XMLPacketEvent.hpp>
#include <cage/event/XTPacketEvent.hpp>
#include <cage/server/BaseServer.hpp>
#include <cage/client/Penguin.hpp>
#include <cage/event/PenguinEvent.hpp>
#include <cage/event/PacketEvent.hpp>
#include <cage/exception/StandardExceptions.hpp>

namespace cage {
namespace server {
    class LoginServer : public BaseServer<client::Penguin> {
        using Client = std::shared_ptr<client::Penguin>;

    public:
        LoginServer (const std::string _name, const int id, const std::string conn, evpp::EventLoop& loop, int max_limit = 500, int threads = 2) :
            BaseServer(_name, id, conn, loop, max_limit, threads, ServerType::LOGIN) {
                
        }
    protected:

        void on_client_message(const evpp::TCPConnPtr& conn, evpp::Buffer *msg) override {
            Client client = get_client(conn);
            if (client == nullptr) {
                if (conn->IsConnected())
                    conn->Close();

                return;
            }

            bool buffered = client->buffer_data(msg->NextAllString());
            if (!buffered) {
                return;
            }

            std::string packet;
            while ((packet = client->get_packet()).size()) {
                SPDLOG_LOGGER_DEBUG(log, "[RECV] [{}] {}", client->c_str(), packet);

                if (packet[0] == '<') {
                    // xml login packet
                    event::XMLPacketEvent evnt(packet);
                    try {
                        evnt.parse();
                    } catch (std::exception &e) {
                        SPDLOG_LOGGER_ERROR(log, "Error parsing XML packet: {}", e.what());
                        conn->Close();
                        return;
                    }
                } else 
                if (packet[0] == '%') {
                    // xt packet (type=l for login)
                    event::XTPacketEvent evnt(packet);
                    try {
                        evnt.parse();
                    } catch (std::exception &e) {
                        SPDLOG_LOGGER_ERROR(log, "Error parsing XT packet: {}", e.what());
                        conn->Close();
                        return;
                    }

                    if (evnt.xt_type != event::XTPacketType::LOGIN) {
                        conn->Close();
                        return;
                    }
                } else 
                if (packet[0] == '{') {
                    // JSON. 
                    try{
                        throw cage::exceptions::NotImplementedError("Parse JSON packet [LoginServer]");
                    } catch (std::exception &e) {
                        SPDLOG_LOGGER_ERROR(log, "Error parsing JSON packet: {}", e.what());
                        conn->Close();
                        return;
                    } 
                } else {
                    SPDLOG_LOGGER_WARN(log, "Unrecognized packet type: {}", packet);
                    conn->Close();
                    return;
                }
            }

            SPDLOG_LOGGER_DEBUG(log, "Inside LoginServer hahah!");
        }

        void on_client_connection(const evpp::TCPConnPtr& conn) override {
            BaseServer::on_client_connection(conn);
            Client client = get_client(conn);
            if (!conn->IsConnected()) {
                if (client != nullptr) {
                    if (client->handshakeStage == client::PenguinHandshakeStage::AUTHENTICATED) {
                        auto e = event::PenguinConnectionEvent {event::PenguinEventType::DISCONNECTED, client}; 
                        event::penguin_connection_event.enqueue(e);
                    }

                    _conns.erase(client);
                }
            } else {
                auto e = event::PenguinConnectionEvent {event::PenguinEventType::CONNECTED, client}; 
                event::penguin_connection_event.enqueue(e);
            }

            event::penguin_connection_event.process();
        }
    };
}
}

#endif