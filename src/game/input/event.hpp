#ifndef ESCAPE_INPUT_EVENT_HPP
#define ESCAPE_INPUT_EVENT_HPP

#include "ray.hpp"
#include "error/error.hpp"
#include <variant>
#include <queue>

/**
 * \page EscapeGameEvents Game Events
 * \tableofcontents
 * This game uses custom game events system.
 * 
 * The input controller (currently based on raylib) generates game relative events, that are then processed by the game engine.
 * The events are designed to be serializable so the user input can be recorded and replayed at any time.
 * Recorded events can also be used in tests, where they can be used to replay problematic (buggy) scenarios and thus prevent for them happen again.
 */

namespace esc::input {
    /// Error number when no more events are stored
    static constexpr int NO_MORE_EVENTS = -1;

    /// Event that represents mouse movement
    struct MouseMovedEvent {
        Vector2 position;
        Vector2 delta;
    };

    /// Event that is caused by quiting the game
    struct ExitButtonPressedEvent {};
    using Event = std::variant<MouseMovedEvent, ExitButtonPressedEvent>;

    /// Queue of all the events in current frame
    static std::queue<Event> events{};

    /// Pushes event to current frame queue
    void pushEvent(const Event& event) noexcept;

    /// Polls event from current frame pool
    ErrorOr<Event> pollEvent() noexcept;
}

#endif//ESCAPE_INPUT_EVENT_HPP