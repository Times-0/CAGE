#ifndef CAGE_EXCEPTIONS_XT_EXCEPTIONS
#define CAGE_EXCEPTIONS_XT_EXCEPTIONS

#include <stdexcept>

namespace cage {
    namespace exceptions {

        class MalformedXTError : public std::exception {
        public:
            MalformedXTError () { }

            const char* what() const noexcept override {
                return "MalformedXTError";
            }
        };

        class XTParseError : public std::exception {
            std::string msg;
        public:
            XTParseError (std::string m) : msg(m) { }

            const char* what() const noexcept override {
                return ("XTParseError: " + msg).c_str();
            }
        };

    }
}

#endif