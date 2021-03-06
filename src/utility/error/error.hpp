#ifndef ESCAPE_ERROR_HPP
#define ESCAPE_ERROR_HPP

#include <optional>
#include <string>
#include <exception>
#include <string_view>
#include <ray.hpp>
#include <source_location>

/// Custom assert function
#define ASSERT(expression, message)\
{\
    auto _sl = std::source_location::current();\
    if (!(expression)) {\
        TraceLog(LOG_FATAL, "ASSERT(%s) failed: %s\nat %s in %s", #expression, message, _sl.function_name(), _sl.file_name());\
        exit(1);\
    }\
}

/**
 * @brief Similar to Rust's ? operator.
 * If function returns Error and calls another function that can return error this macro automatically propagates the error out of the outer function.
 * If the inner function also can return some value this value is returned (and can be assigned to variable).
 */
#define TRY(expression)\
({\
    auto _expression_result = (expression);\
    if (_expression_result.isError())\
        return std::move(_expression_result.getError());\
    _expression_result.getValue();\
})


/**
 * @brief Similar to TRY macro but fails program if error was returned.
 * If function calls another function that can return error this macro HARD checks if return values is an error (crashes the program).
 * If the return values is not error, than its actual value is returned.
 */
#define MUST(expression)\
({\
    auto _expression_result = (expression);\
    ASSERT(!_expression_result.isError(), "MUST check failed.");\
    _expression_result.getValue();\
})

namespace esc {

    /// Simple error struct
    struct [[nodiscard]] Error {
        /// Default contructor - that initializes Error to not contain error value.
        Error(): errorNumber(0), message("") { }
        /// Main constructor, that assigns error value to this struct
        Error(const int errNo, const std::string_view mess): errorNumber(errNo), message(mess) { }
        /// Default copy constructor
        Error(const Error&) = default;
        
        /// Checks if value is actual error.
        constexpr bool isError() const noexcept {
            return errorNumber != 0 && message.size() > 0;
        }

        /// Checks if object is not an error.
        constexpr bool isOK() const noexcept {
            return errorNumber == 0 && message.size() == 0;
        }
        constexpr int getErrorNumber() const noexcept {
            return errorNumber;
        }
        /// Nullop function that is used if function returns only Error - needed for TRY and MUST to work.
        constexpr void getValue() const { }
        const std::string_view getErrorMessage() const noexcept {
            return message;
        }

        /// Returns itself - needed for TRY to work
        const Error& getError() const {
            return *this;
        }
    protected:
        /// Error number - if is 0, that this value shouldn't be considered as error.
        const int errorNumber;

        /// Error message
        const std::string message;
    };


    /**
     * @brief Specialized type, that should be used when user needs to return value or error from function.
     * 
     * @tparam ResultType Type of result returned from function if error is not returned. ResultType should never be void.
     */
    template<typename ResultType>
    struct [[nodiscard]] ErrorOr {
        static_assert(!std::is_same_v<ResultType, void>, "Return type can't be void. Please use Error instead");

        /// Implicit constructor, that moves result from the function.
        ErrorOr(ResultType && result): data(result), error() { }
        /// Implicit constructor, that moves error result from the function.
        ErrorOr(Error&& otherError): data(std::nullopt), error(otherError) { }
        /// Specific proxy constructor, that constructs error value.
        ErrorOr(const int errNo, const std::string_view message): data(std::nullopt), error(errNo, message) { }

        /// Deleted copy constructor (value should be moved)
        ErrorOr(const ErrorOr<ResultType>& other) = delete;
        /// Deleted assign operator (value should be moved)
        void operator=(const ErrorOr<ResultType>& other) = delete;

        /// Check if value is actual error.
        constexpr bool isError() const {
            return !data.has_value() && error.isError();
        }

        /// Implicit conversion to bool if value contains actual value.
        constexpr operator bool() const noexcept {
            return data.has_value() && error.isOK();
        }

        /// Returns error number
        constexpr int getErrorNumber() const {
            return error.getErrorNumber();
        }

        /// Returns error message
        inline const std::string_view getErrorMessage() const {
            return error.getErrorMessage();
        }

        /// Returns the actual value
        inline const ResultType& getValue() const {
            return *data;
        }

        /// Returns the error object - Mainly for TRY macro to pass the Error value;
        inline const Error& getError() const {
            return error;
        }
    protected:
        /// The optional value that can contain the actual function ResultType value
        const std::optional<ResultType> data;
        /// The error value.
        const Error error;
    };
}

#endif//ESCAPE_ERROR_HPP