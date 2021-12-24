#ifndef ESCAPE_GAME_HPP
#define ESCAPE_GAME_HPP

#include "game_state/game_state.hpp"
#include "error/error.hpp"
#include "input/event.hpp"
#include <fmt/core.h>
#include <raylib.h>

namespace esc {

    /**
     * @brief Main game object.
     *
     * This is the main game object. It is used to process game events, to store game data and to pass the new game data to renderer.
     * 
     * @tparam InputHandler Template type that should read user input and create game events.
     * @tparam RenderTarget Template type that should create appropriate render context.
     */
    template<typename InputHandler, typename RenderTarget>
    class Game {
    public:
        /// Enum that specifies the current game state.
        enum class State: int {
            /// Game is running and the user mainly controls the player.
            IN_GAME,
            /// Game is paused. User paused the game.
            PAUSED,
            /// Game is currently paused, because the game is loading some assets.
            LOADING
        };

        /// Deleted default copy contructor to make the game not copyable
        Game(const Game&) = delete;
        /// Deleted default copy operator to make the game not copyable
        void operator=(const Game&) = delete;

        /**
         * @brief Construct a new Game object. Only viable constructor to create game object.
         * 
         * @param handler Input handler object, that processes user inputs and creates game events.
         * @param target Render target object, sets current rendering context.
         */
        Game(InputHandler&& handler, RenderTarget&& target): inputHandler(handler), renderTarget(target) {
            current = this;
        }

        /**
         * @brief Returns immutable reference to last created game.
         * 
         * @return const Game& Immutable game object reference
         */
        static const Game* the() {
            return current;
        }

        /**
         * @brief Returns mutable reference to last created game.
         * 
         * @return Game& Mutable game object reference
         */
        static Game* theMutable() {
            return current;
        }

        /// Flag that determines if on next loop the game should quit.
        bool shouldQuit{false};

        Error processEvent(const input::ExitButtonPressedEvent&) noexcept {
            shouldQuit = true;
            return {};
        }

        Error processEvent(const input::Event&) noexcept {
            return {};
        }

        Error processEvents() noexcept {
            // TODO: Move to some kind of SCENE Object -> different controls for different scenes
            while (true) {
                auto eventOrError = input::pollEvent();
                if (eventOrError.isError()) {
                    if (eventOrError.getErrorNumber() == input::NO_MORE_EVENTS) {
                        return {};
                    }
                    return eventOrError.getError();
                }
                TRY(std::visit([this](auto && event) {
                    return processEvent(event);
                }, eventOrError.getValue()));
            }
        }

        /**
         * @brief Starts the main game loop.
         * 
         * Initializes and starts the main game loop.
         * @return Error object if anything bad happens.
         */
        Error run() noexcept {
            TRY(renderTarget.init());
            
            while(!shouldQuit) {
                TRY(inputHandler.readForEvents());
                TRY(renderTarget.startRendering());
                ClearBackground(Color{255, 255, 255, 255});
                TRY(processEvents());
                TRY(renderTarget.stopRendering());
            }

            TRY(renderTarget.deinit());
            return {};
        }
    protected:
        /// Game's current input handler.
        InputHandler inputHandler;
        /// Game's current render target.
        RenderTarget renderTarget;

        /// Reference to current (latest) instance of the game. (Default initializes to nullptr).
        static Game* current;
    };
    template <typename InputHandler, typename RenderTarget> 
    Game<InputHandler, RenderTarget>* Game<InputHandler, RenderTarget>::current = nullptr;
}

#endif//ESCAPE_GAME_HPP