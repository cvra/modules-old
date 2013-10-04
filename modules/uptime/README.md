Uptime
======
This module is able to provide time since system reset, with a microsecond
resolution. It uses a hardware timer, and therefore, is not altered by heavy
CPU load, which makes it suitable for code profiling applications.

Usage
-----
This module only provides a single function, which retrieves the time :

    int time_since_reset_us = uptime_get();
