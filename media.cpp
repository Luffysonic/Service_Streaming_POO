#include "media.h"
#include <iostream>
#include <cstring> /*for all string comparaison*/


 char quality[3][10]={"low","medium","high"};

media_t::media_t(){
    this->name="undefined";
    this->announcement="undefined";
    this->rating=-1;
    this->year=-1;
}
string media_t::get_announcement() const{
    return this->announcement;
}
string media_t::get_name() const{
    return this->name;
}
float media_t::get_rating() const{
    return this->rating;
}

int media_t::get_year() const{
    return this->year;
}

void media_t::set_name(string name) {
    this->name=name;
}
void media_t::set_rating(float rating){
    this->rating=rating;
}
void media_t::set_year(int year){
    this->year=year;
}

void media_t::handle_m() const{
    cout<<*this<<endl;
}


void media_t::handle_mn(string name) const{
    const char *ret=strstr(this->name.c_str(),name.c_str());
    if (ret!=NULL){
        this->handle_m();
    }
    }

void media_t::handle_my(int year) const{
    if(year==this->get_year()){        
        this->handle_m();
    }
}


void media_t::handle_myge(int year) const{
    if(this->get_year()>=year){
        this->handle_m();

    }
}

void media_t::handle_mygt(int year) const{
    if(this->get_year()>year){
        this->handle_m();

    }
}

void media_t::handle_myle(int year) const{
    if(this->get_year()<=year){
        this->handle_m();
    }
}  
void media_t::handle_mylt(int year) const{
    if(this->get_year()<year){
        this->handle_m();
        

    }
}

quality_t media_t::qualities_at(int index) const{
    return qualities[index];
}
int media_t::qualities_size() const{
    return this->qualities.size();
}
void media_t::qualities_push_back(quality_t quality){
    this->qualities.push_back(quality);
}


ostream &operator<<(ostream &os, const media_t &media){
    os<<"("<<media.get_name() << ", "<<media.get_year()<<", "<<media.get_announcement()<<", "<<media.get_rating()<<", (";
    for(int i=0;i<media.qualities_size();i++){
        i!=(media.qualities_size()-1) ? os<<quality[media.qualities_at(i)]<<", " : os<<quality[media.qualities_at(i)]<<")";

    }
    os<<")";
    return os;
}



