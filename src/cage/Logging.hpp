#ifndef CAGE_LOGGING
#define CAGE_LOGGING

#include <spdlog/async.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/daily_file_sink.h>

namespace cage {

    auto log_c = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
    auto log_f = std::make_shared<spdlog::sinks::daily_file_sink_mt>("logs/cage.log", 23, 59);
    std::vector<spdlog::sink_ptr> _sinks {log_c, log_f};
    std::shared_ptr<spdlog::async_logger> log;

    namespace database {
        auto log_f = std::make_shared<spdlog::sinks::daily_file_sink_mt>("logs/database.log", 23, 59);
        std::vector<spdlog::sink_ptr> _sinks {log_c, log_f};
        std::shared_ptr<spdlog::async_logger> log;
    }
}

#endif