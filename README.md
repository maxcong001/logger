##logger function

##just include the header file. with 

```
#define __LOGGING_ENABLED
```

## how to set loglevel
```
std::unique_ptr<logger_iface> active_logger(new logger(logger::log_level::debug));
```


## dependancy
C++11
