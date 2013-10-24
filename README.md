dprintf
=======

Fast, lock-free, core-dumpable prints (meaning you can see not-yet-flushed prints in core dumps/live processes).

Basically a way to have a binary log buffer for real-time/low-level/kernel-level debugging that you then
view as formatted text messages (instead of some type of struct array or whatever).

100+ LOC, more of example code than a "real" library at this point.

Usage
=====

* **dtest.cpp** shows how to use dprintf - basically **dprintf("i=%d\n", i); dflush();**
* **source test.sh** shows how to convert raw log files to text, and how to extract the last log messages from core dumps
  or live processes (you use a user-defined gdb command **dprintf** and pass it a raw file, or get the last messages in the core/process
  if you don't pass a file).
