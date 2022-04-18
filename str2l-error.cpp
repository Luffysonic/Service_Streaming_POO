#include "str2l-error.h"

#include <sstream> // for ostringstream

str2l_error::str2l_error(string str){
    ostringstream oss;
    oss<< "str2l_error: unable to convert the string : "<<str<<" to a long"<<endl;
    this->str=oss.str();
}

str2l_error::~str2l_error() throw(){

}
const char *str2l_error::what() const throw(){
    return this->str.c_str();
}