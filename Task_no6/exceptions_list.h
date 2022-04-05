#include "exception"
#include "string"

class arg_verification: std::exception
{
    const char* what() {return msg.c_str();} ;
private:
    std::string msg{"wrong input arguments result"};
};