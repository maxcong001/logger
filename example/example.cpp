
#include "logger/logger.hpp"

int main()
{
    set_log_level(logger_iface::log_level::warn);
    for (int i = 0; i < 100; i++)
    {
        __LOG(error, "hello logger!"
                         << "this is error log");
        __LOG(warn, "hello logger!"
                        << "this is warn log");
        __LOG(info, "hello logger!"
                        << "this is info log");
        __LOG(debug, "hello logger!"
                         << "this is debug log");
    }
    dump_log();
}
