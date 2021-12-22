#include "event.h"
#include "event.hpp"

namespace esc::input {
void pushEvent(const Event& event) noexcept {
    esc::input::events.push(event);
}

ErrorOr<Event> pollEvent() noexcept {
    if (events.size() > 0) {
        auto e = events.front();
        events.pop();
        return e;
    }
    return Error(NO_MORE_EVENTS, "No more events in event queue, try to read for more.");
}
}