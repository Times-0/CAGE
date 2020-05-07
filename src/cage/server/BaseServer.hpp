#ifndef CAGE_SERVER_BASE_SERVER
#define CAGE_SERVER_BASE_SERVER

#include <set>

#include <evpp/tcp_server.h>
#include <evpp/buffer.h>
#include <evpp/tcp_conn.h>

#include <spdlog/spdlog.h>
#include <cage/Logging.hpp>

#include <cage/exception/StandardExceptions.hpp>

namespace cage {
namespace server {

    enum ServerType {
        LOGIN,
        GAME,
        REDEEMPTION,
        OTHER
    };

    template <class T>
    class BaseServer {
        using Client = std::shared_ptr<T>;

        const std::string listen_addr;
        
        std::unique_ptr<evpp::TCPServer> _server;
        evpp::EventLoop& _loop;

        int max_users, _id;
        int threads;

    protected:
        std::set<Client> _conns;
        std::shared_ptr<spdlog::async_logger> log;

    public:
        const std::string name;
        ServerType _type;

        BaseServer (const std::string _name, const int id, const std::string conn, evpp::EventLoop& loop, int max_limit = 500, int threads = 2,
            ServerType type = ServerType::LOGIN) : 
                name(_name), _id(id), listen_addr(conn), _loop(loop), max_users(max_limit), threads(threads), _type(type) {

            auto &sinks = cage::log->sinks();
            log = std::make_shared<spdlog::async_logger>("cage::"+name, sinks.begin(), sinks.end(), spdlog::thread_pool());
            log->set_level(cage::log->level());

            spdlog::register_logger(log);

            _server.reset(new evpp::TCPServer(&_loop, listen_addr, name, threads));
            SPDLOG_LOGGER_INFO(log, "Server: {0} (listening on {1}) [Max={2}] - {3} threads", name, listen_addr, max_limit, threads);

            _server->SetConnectionCallback(std::bind(&BaseServer::on_client_connection, this, std::placeholders::_1));
            _server->SetMessageCallback(std::bind(&BaseServer::on_client_message, this, std::placeholders::_1, std::placeholders::_2));

            start();
        }
    
    protected:

        virtual void on_client_message(const evpp::TCPConnPtr& conn, evpp::Buffer *msg) {
            Client client = get_client(conn);
            if (client == nullptr) {
                SPDLOG_LOGGER_WARN(log, "Received data from a client, which is not registered. Closing conn if possible.");
                try {
                    conn->Close();
                } catch (std::exception &e) { }
                
                return;
            }

            throw exceptions::NotImplementedError("Handling on_client_message");
        }

        virtual void on_client_connection(const evpp::TCPConnPtr& conn) {
            if (conn->IsConnected()) {
                if (_conns.size() >= max_users) {
                    // reomve client from server, server full
                    conn->Send("%xt%e%-1%211%\x00");
                    conn->Close();
                    return;
                }
                // new client connection
                Client client = std::make_shared<T>(conn, log);
                SPDLOG_LOGGER_INFO(log, "New client connection: {}", client->c_str());
                _conns.insert(client);
            } else {
                Client client = get_client(conn);
                if (client == nullptr) {
                    SPDLOG_LOGGER_WARN(log, "Disconnected client is not registered.");

                    return;
                }
                SPDLOG_LOGGER_INFO(log, "Client disconnected: {}", client->c_str());
            }
        }
    
    public:

        Client get_client(const evpp::TCPConnPtr& conn) {
            for (const Client& i: _conns) {
                if (i->get_connection() == conn) {
                    return i;
                }
            }

            return nullptr;
        }

        Client get_client(const int& id) {
            for (Client& i: _conns) {
                if (i->id() == id) {
                    return i;
                }
            }

            return nullptr;
        }

    private:
        void start() {
            if (_server->IsRunning()) {
                throw exceptions::ServerAlreadyListening(name + "#" + listen_addr);
            }

            bool success = _server->Init() && _server->Start();

            if (!success) {
                throw exceptions::ServerNotListening(name + "#" + listen_addr);
            }
        }
    };
}
}

#endif