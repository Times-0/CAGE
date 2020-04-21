#ifndef CAGE_EXCEPTIONS_XML_EXCEPTIONS
#define CAGE_EXCEPTIONS_XML_EXCEPTIONS

#include <stdexcept>

namespace cage {
    namespace exceptions {

        class MalformedXMLError : public std::exception {
        public:
            MalformedXMLError () { }

            const char* what() const noexcept override {
                return "MalformedXMLError";
            }
        };

        class XMLParseError : public std::exception {
            std::string msg;
        public:
            XMLParseError (std::string m) : msg(m) { }

            const char* what() const noexcept override {
                return ("XMLParseError: " + msg).c_str();
            }
        };

    }
}

#endif