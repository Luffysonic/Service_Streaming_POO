#include "str2i-error.h"

#include <sstream> // for ostringstream

str2i_error::str2i_error(string str){
    ostringstream oss;
    oss<< "str2i_error: unable to convert the string : "<<str<<" to an int"<<endl;
    this->str=oss.str();
}

str2i_error::~str2i_error() throw(){

}
const char *str2i_error::what() const throw(){
    return this->str.c_str();
}