#include "observable.h"

Observable::Observable(CheckTime Time)
    : time(Time) {
}

bool Observable::check(CheckTime currentTime) {
    return (time & currentTime) == currentTime;
}

