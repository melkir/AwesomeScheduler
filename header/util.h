#ifndef AWESOMESCHEDULER_UTIL_H
#define AWESOMESCHEDULER_UTIL_H

#include <cstdio>
#include <cstdlib>

static void myAssert(bool condition, const char *message) {
    if (condition) return;
    perror(message);
    exit(1);
}

#endif //AWESOMESCHEDULER_UTIL_H
