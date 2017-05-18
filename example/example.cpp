
#include "logger.hpp"

int main()
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
