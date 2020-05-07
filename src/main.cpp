#define PUGIXML_HEADER_ONLY
#define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_TRACE

#include <iostream>
#include <fstream>
#include <string>

#include <eventpp/eventqueue.h>
#include <pugixml/pugixml.hpp>
#include <spdlog/spdlog.h>
#include <spdlog/cfg/env.h>
#include <nlohmann/json.hpp>

#include <cage/event/BaseEvent.hpp>
#include <cage/event/XTPacketEvent.hpp>
#include <cage/event/XMLPacketEvent.hpp>

#include <sqlpp11/sqlpp11.h>
#include <sqlpp11/connection_pool.h>
#include <sqlpp11/postgresql/postgresql.h>

#include <cage/database/User.hpp>

#include <cage/Logging.hpp>
#include <cage/server/LoginServer.hpp>

#include <set>

using namespace eventpp;
using namespace cage::event;
using json = nlohmann::json;

json CONFIGS;

void ConfigureDatabase() {

}

void SetupLogs() {
    spdlog::init_thread_pool(8192, 1);

    cage::log = std::make_shared<spdlog::async_logger>("cage::main", cage::_sinks.begin(), cage::_sinks.end(), spdlog::thread_pool(), spdlog::async_overflow_policy::block);
    cage::database::log = std::make_shared<spdlog::async_logger>("cage::database", cage::database::_sinks.begin(), cage::database::_sinks.end(), spdlog::thread_pool(), spdlog::async_overflow_policy::block);

    spdlog::register_logger(cage::log);
    spdlog::register_logger(cage::database::log);

    spdlog::set_pattern("[%T] [%^%=8l%$] [%n] [%!] %v"); // %n -> %@f for file_name:line_no
    //spdlog::flush_every(std::chrono::seconds(5));
}

int main (int argc, char *argv[]) {
    // configure log (spdlog)
    spdlog::cfg::load_env_levels();
    SetupLogs();
    

    std::cout << std::endl << 
        " ██████╗ █████╗  ██████╗ ███████╗\n"
        "██╔════╝██╔══██╗██╔════╝ ██╔════╝\n"
        "██║     ███████║██║  ███╗█████╗  \n"
        "██║     ██╔══██║██║   ██║██╔══╝  \n"
        "╚██████╗██║  ██║╚██████╔╝███████╗\n"
        " ╚═════╝╚═╝  ╚═╝ ╚═════╝ ╚══════╝\n"
        "                                 \n"
    ;

    spdlog::set_level(spdlog::level::debug);    
    
    evpp::EventLoop loop;

    cage::server::LoginServer server("Server", 1, "127.0.0.1:6112", loop);
    
    loop.Run();

    spdlog::shutdown();

    return 0;
}