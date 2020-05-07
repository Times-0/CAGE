#pragma once
#ifndef CAGE_CLIENT_PENGUIN
#define CAGE_CLIENT_PANGUIN

#include <spdlog/spdlog.h>
#include <cage/Logging.hpp>
#include <evpp/tcp_conn.h>

#include <cage/event/PenguinEvent.hpp>

namespace cage {
namespace client {

    enum struct PenguinHandshakeStage {
        NONE,
        API_CHECK,
        IN_PROCESS,
        AUTHENTICATED
    };

    class Penguin {
        evpp::TCPConnPtr conn;
        std::string buffer = "";

        bool _skip_until_next_delimiter = false;

    
    protected:
        size_t max_buffer = 2048; // 2mb
        char delimiter = '\x00';

    public:
        std::shared_ptr<spdlog::async_logger> log;
        PenguinHandshakeStage handshakeStage = PenguinHandshakeStage::NONE;

        Penguin (const evpp::TCPConnPtr& conn, std::shared_ptr<spdlog::async_logger> log) : conn(conn), log(log) {
            // mostly don't do anything in penguin class other than parsing data :shrug:
        }

        bool buffer_data(const std::string& data) {
            if (buffer.size() + data.size() > max_buffer) {
                // skip this packet
                buffer.clear();
                _skip_until_next_delimiter = true;

                SPDLOG_LOGGER_INFO(log, "packet is too long, skipping");
                return false;
            }

            buffer.append(data);

            int i = buffer.find(delimiter);
            if (i == std::string::npos) return false;
            else if (_skip_until_next_delimiter) {
                _skip_until_next_delimiter = false;

                buffer.erase(i+1);
                return false;
            }

            return true;
        }

        std::string get_packet() {
            int i = buffer.find(delimiter);
            if (i == std::string::npos) return "";

            std::string t = buffer.substr(0, i);
            buffer.erase(0, i+1);
            return t;
        }

        evpp::TCPConnPtr get_connection() const {
            return conn;
        }

        std::string c_str() const {
            return "Penguin#"+conn->remote_addr();
        }
    };
}
}

#endif