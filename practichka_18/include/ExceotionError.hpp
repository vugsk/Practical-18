
#ifndef EXCEPTIONERROR_HPP
#define EXCEPTIONERROR_HPP

#include <exception>
#include <string>

class Error : public std::exception
{
public:
    Error(const std::string& msg_error) : _msg(msg_error) {}
    ~Error() override = default;

    const char* what() const noexcept override
    {
        return _msg.c_str();
    } 
private:
    std::string _msg;
};

#endif
