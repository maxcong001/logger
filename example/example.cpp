
#include "logger.hpp"

int main()
{
    __LOG(error, "hello logger!" << " error log");
    __LOG(warn, "hello logger!" << " warn log");
    __LOG(info, "hello logger!" << " info log");
    __LOG(debug, "hello logger!" << " debug log");
}
