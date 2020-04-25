#ifndef CAGE_DATABASE_LOG
#define CAGE_DATABASE_LOG

#include <memory>
#include <spdlog/spdlog.h>
#include <spdlog/sinks/daily_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>

namespace cage {
namespace database {
    auto console_log = std::make_shared<spdlog::stdout_color_mt>("cage::database::console");
    auto file_log = std::make_shared<spdlog::daily_logger_mt>("cage::database::file", "logs/database.log", 23, 59);

    auto log = spdlog::logger("cage::database", {console_log, file_log});
}
}

#endif