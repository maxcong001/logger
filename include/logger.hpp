#pragma once

#include <memory>
#include <mutex>
#include <string>
#include <iostream>

//! logger_iface
//! should be inherited by any class intended to be used for logging
class logger_iface
{
  public:
    //! ctor & dtor
    logger_iface(void) = default;
    virtual ~logger_iface(void) = default;

    //! copy ctor & assignment operator
    logger_iface(const logger_iface &) = default;
    logger_iface &operator=(const logger_iface &) = default;

  public:
    virtual void debug(const std::string &msg, const std::string &file, std::size_t line) = 0;
    virtual void info(const std::string &msg, const std::string &file, std::size_t line) = 0;
    virtual void warn(const std::string &msg, const std::string &file, std::size_t line) = 0;
    virtual void error(const std::string &msg, const std::string &file, std::size_t line) = 0;
};

//! default logger class provided by the library
class logger : public logger_iface
{
  public:
    //! log level
    enum class log_level
    {
        error = 0,
        warn = 1,
        info = 2,
        debug = 3
    };

  public:
    //! ctor & dtor
    logger(log_level level = log_level::info);
    ~logger(void) = default;

    //! copy ctor & assignment operator
    logger(const logger &) = default;
    logger &operator=(const logger &) = default;

  public:
    void debug(const std::string &msg, const std::string &file, std::size_t line);
    void info(const std::string &msg, const std::string &file, std::size_t line);
    void warn(const std::string &msg, const std::string &file, std::size_t line);
    void error(const std::string &msg, const std::string &file, std::size_t line);

  private:
    log_level m_level;
    std::mutex m_mutex;
};

//! variable containing the current logger
//! by default, not set (no logs)

//! convenience functions used internaly to call the logger
void debug(const std::string &msg, const std::string &file, std::size_t line);
void info(const std::string &msg, const std::string &file, std::size_t line);
void warn(const std::string &msg, const std::string &file, std::size_t line);
void error(const std::string &msg, const std::string &file, std::size_t line);

#define __LOGGING_ENABLED
//! convenience macro to log with file and line information
#ifdef __LOGGING_ENABLED
#define __LOG(level, msg) level(msg, __FILE__, __LINE__);
#else
#define __LOG(level, msg)
#endif /* __LOGGING_ENABLED */

std::unique_ptr<logger_iface> active_logger(new logger(logger::log_level::debug)); //nullptr;

static const char black[] = {0x1b, '[', '1', ';', '3', '0', 'm', 0};
static const char red[] = {0x1b, '[', '1', ';', '3', '1', 'm', 0};
static const char yellow[] = {0x1b, '[', '1', ';', '3', '3', 'm', 0};
static const char blue[] = {0x1b, '[', '1', ';', '3', '4', 'm', 0};
static const char normal[] = {0x1b, '[', '0', ';', '3', '9', 'm', 0};

logger::logger(log_level level)
    : m_level(level) {}

void logger::debug(const std::string &msg, const std::string &file, std::size_t line)
{
    if (m_level >= log_level::debug)
    {
        std::lock_guard<std::mutex> lock(m_mutex);
        std::cout << "[" << black << "DEBUG" << normal << "][" << file << ":" << line << "] " << msg << std::endl;
    }
}

void logger::info(const std::string &msg, const std::string &file, std::size_t line)
{
    if (m_level >= log_level::info)
    {
        std::lock_guard<std::mutex> lock(m_mutex);
        std::cout << "[" << blue << "INFO " << normal << "] [" << file << ":" << line << "] " << msg << std::endl;
    }
}

void logger::warn(const std::string &msg, const std::string &file, std::size_t line)
{
    if (m_level >= log_level::warn)
    {
        std::lock_guard<std::mutex> lock(m_mutex);
        std::cout << "[" << yellow << "WARN " << normal << "] [" << file << ":" << line << "] " << msg << std::endl;
    }
}

void logger::error(const std::string &msg, const std::string &file, std::size_t line)
{
    if (m_level >= log_level::error)
    {
        std::lock_guard<std::mutex> lock(m_mutex);
        std::cerr << "[" << red << "ERROR" << normal << "] [" << file << ":" << line << "] " << msg << std::endl;
    }
}

void debug(const std::string &msg, const std::string &file, std::size_t line)
{
    if (active_logger)
        active_logger->debug(msg, file, line);
}

void info(const std::string &msg, const std::string &file, std::size_t line)
{
    //std::cout << "Maxx logger info, active_logger is : " << (void *)(active_logger)<<std::endl;
    if (active_logger)
        active_logger->info(msg, file, line);
}

void warn(const std::string &msg, const std::string &file, std::size_t line)
{
    if (active_logger)
        active_logger->warn(msg, file, line);
}

void error(const std::string &msg, const std::string &file, std::size_t line)
{
    if (active_logger)
        active_logger->error(msg, file, line);
}
