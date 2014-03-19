Uptime
======
This module is able to provide time since system reset, with a microsecond
resolution. It uses a hardware timer, and therefore, is not altered by heavy
CPU load, which makes it suitable for code profiling applications.

Usage
-----
This module only provides a single function, which retrieves the time :

    int time_since_reset_us = uptime_get();

Mock usage
----------
When compiling for host platform, this module can be configured to return
any value using the following function :

    void uptime_set(int32_t time);
