

#include "logger/simpleLogger.hpp"

#include <chrono>
#include <thread>
int main()
{


	INIT_LOGGER(new simpleLogger());
	SET_LOG_LEVEL(debug);
	__LOG(critical, "hello logger!"
						<< "this is critical log" << (void *)ACTIVE_LOGGER_INSTANCE);
	__LOG(error, "hello logger!"
					 << "this is error log" << (void *)ACTIVE_LOGGER_INSTANCE);
	__LOG(warn, "hello logger!"
					<< "this is warn log" << (void *)ACTIVE_LOGGER_INSTANCE);
	__LOG(info, "hello logger!"
					<< "this is info log" << (void *)ACTIVE_LOGGER_INSTANCE);
	__LOG(debug, "hello logger!"
					 << "this is debug log" << (void *)ACTIVE_LOGGER_INSTANCE);


}
