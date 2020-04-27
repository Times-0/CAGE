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

    template <class T>
    class BaseServer {
        using Client = std::shared_ptr<T>;

        const std::string listen_addr;
        
        std::unique_ptr<evpp::TCPServer> _server;
        std::set<Client> _conns;
        evpp::EventLoop& _loop;

        int max_users, _id;

    protected:
        std::shared_ptr<spdlog::async_logger> log;

    public:
        int threads;
        const std::string name;

        BaseServer (const std::string _name, const int& id, const std::string& conn, evpp::EventLoop& loop, int max_limit = 500, int threads = 2) :
                name(_name), _id(id), listen_addr(conn), _loop(loop), max_users(max_limit), threads(threads) {
            
            auto &sinks = cage::log->sinks();
            log = std::make_shared<spdlog::async_logger>("cage::"+name, sinks.begin(), sinks.end(), spdlog::thread_pool());
            log->set_level(cage::log->level());

            spdlog::register_logger(log);

            _server.reset(new evpp::TCPServer(&_loop, listen_addr, name, threads));
            log->info("Server: {0}. [Max={1}]", name, max_limit);

            _server->SetConnectionCallback(std::bind(&BaseServer::on_client_connection, this, std::placeholders::_1));
            _server->SetMessageCallback(std::bind(&BaseServer::on_client_message, this, std::placeholders::_1, std::placeholders::_2));

            start();
        }

        void on_client_message(const evpp::TCPConnPtr& conn, evpp::Buffer *msg) {
            log->debug("Client message: {}", msg->NextAllString());
        }

        void on_client_connection(const evpp::TCPConnPtr& conn) {
            if (conn->IsConnected()) {
                if (_conns.size() >= max_users) {
                    // reomve client from server, server full
                    conn->Send("%xt%e%-1%211%\x00");
                    conn->Close();
                    return;
                }
                // new client connection
                Client client = Client(new T(conn));
                log->info("New client connection from {}", conn->remote_addr());
            } else {

            }
        }

        Client& get_client(const evpp::TCPConnPtr& conn) {
            for (Client& i: _conns) {
                if (i->get_connection() == conn) {
                    return i;
                }
            }

            return nullptr;
        }

        Client& get_client(const int& id) {
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