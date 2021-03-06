#include "str2f-error.h"

#include <sstream> // for ostringstream

str2f_error::str2f_error(string str){
    ostringstream oss;
    oss<< "str2f_error: unable to convert the string : "<<str<<" to a float"<<endl;
    this->str=oss.str();
}

str2f_error::~str2f_error() throw(){}
const char *str2f_error::what() const throw(){
    return this->str.c_str();
}