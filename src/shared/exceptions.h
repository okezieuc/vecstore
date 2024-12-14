#ifndef VECSTORE_VECSTORE_EXCEPTIONS
#define VECSTORE_VECSTORE_EXCEPTIONS
#include <exception>
#include <string>
#include "vecstore_error.h"

class VecStoreExceptions : public std::exception
{
private:
    Error error;
    std::string errorMessage;

public:
    VecStoreExceptions(const Error e)
        : error(e), errorMessage(VecStoreError::Get(error).GetDescription())
    {
    }

    Error getError() const
    {
        return error;
    }

    // Override the what() method to return our message
    const char *what() const throw()
    {
        return errorMessage.c_str();
    }
};

#endif // VECSTORE_VECSTORE_EXCEPTIONS