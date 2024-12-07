#include "include/serial.h"
#include "logger.hpp"
#include "g.hpp"
char* kernel_logbuf = "H\nE\n";

void kernel_log(char* what) {
    serial_write_string(what);
    kernel_logbuf = strconcat(kernel_logbuf, what);
    kernel_logbuf = strconcat(kernel_logbuf, "\n");
}

void kernel_log_init() {

}