#ifndef CAGE_EXCEPTIONS_STANDARD_EXCEPTIONS

#include <stdexcept>

namespace cage {
    namespace exceptions {
        class NotImplementedError : public std::exception {
            std::string subject;
        public:
            NotImplementedError (std::string subject) : subject(subject) { }

            const char* what()
            {
                return ("NotImplementedError: " + subject).c_str();
            }
        };
    }
}

#endif