#include <pugixml.hpp>/* for xml parse file */
#include <iostream> /*for cout cerr in cin*/
#include <cstring> /*for all string comparaison*/
#include <cstdlib>
#include <cstdio>
#include <climits>
#include <cfloat>
using namespace pugi;
using namespace std;


//include our file
#include "anime.h"
#include "film.h"
#include "media.h"
#include "series.h"
#include "streaming-service.h"
#include "str2f-error.h"
#include "str2i-error.h"
#include "str2l-error.h"


////// if it's a single character ///////////////
void char_Command(char c,streaming_service_t streaming_service){
    switch (c){
        case 'h':
            cout<<"h: prints this help"<<endl;
            cout<<"i: prints information about the streaming service"<<endl;
            cout<<"m: prints the streaming service medias"<<endl;
            cout<<"mn NAME: prints the streaming service medias with the name containing NAME"<<endl;
            cout<<"my YEAR: prints the streaming service medias with the year equal to YEAR"<<endl;
            cout<<"myge YEAR: prints the streaming service with the year greater than or equal to YEAR"<<endl;
            cout<<"mygt YEAR: prints the streaming service with the year greater than YEAR"<<endl;
            cout<<"myle YEAR: prints the streaming service with the year less than or equal to YEAR"<<endl;
            cout<<"mylt YEAR: prints the streaming service with the year less than YEAR"<<endl;
            cout<<"n: prints the streaming service name"<<endl;
            cout<<"q: quits SSP"<<endl;
            cout<<"v: prints the SSP version"<<endl;
            cout<<"w: prints the streaming service web address"<<endl;
            break;
        
        case 'i':
            streaming_service.handle_i();
            break;
    
        case 'm':
            streaming_service.handle_m();
            break;
        
        case 'n':
            streaming_service.handle_n();
            break;
        
        case 'v':
        cout<<"SSP (Streaming Service Program) 20210301"<<endl;
        cout<<endl<<"Copyright (C) 2021 Khao Ricky and Duprat Noé."<<endl;
        cout<<"Written by Khao Ricky <rkhao@univ-pau.fr> and Duprat Noé <nduprat002@univ-pau.fr>"<<endl;
            break;
        
        case 'w':
            streaming_service.handle_w();
            break;
        
        default :
            cerr<<"./ssp.out Invalid command"<<endl;

    }
    
}

//////if the command is a word so his length is more than 1 and arugment2 represents the second argument for example my 2003 argument2 = 2003 ////////////
void word_Command(char w[2],char *argument2,streaming_service_t streaming_service){
    int year;
    string name;
    if(strcmp(w,"mn")==0){
        if(argument2==NULL){
            cout<<"./ssp.out invalid parameter for the mn command"<<endl;
        }
        else{
            if(strlen(argument2)>=16){
            cout<<"./ssp.out too many arguments"<<endl;
            while(getchar()!='\n');

            }
            else{
            name=argument2;
            streaming_service.handle_mn(name);
            }
        }
        
    }
    if(strcmp(w,"my")==0){
        if(argument2==NULL){
            cout<<"./ssp.out missing parameter for the my command"<<endl;
        }
        else{
            if(strlen(argument2)>=16){
                cout<<"./ssp.out too many arguments"<<endl;
                while(getchar()!='\n');
                
            }
            else{
                year=strtof(argument2,NULL);
                if((year<=0)){
                    cout<<"./ssp.out Invalid parameter for the my command"<<endl;
                }
                else{
                    streaming_service.handle_my(year);
                }
            
            }
        }
        
    }
    if(strcmp(w,"myge")==0){
        if(argument2==NULL){
            cout<<"./ssp.out missing parameter for the my command"<<endl;
        }
        if(strlen(argument2)>=16){
            cout<<"./ssp.out too many arguments"<<endl;
            while(getchar()!='\n');

        }
        else{
            year=strtof(argument2,NULL);
            if((year<=0)){
                cout<<"./ssp.out Invalid parameter for the my command"<<endl;
            }
            else{
                streaming_service.handle_myge(year);
            }
            
        }
       
    }
    if(strcmp(w,"mygt")==0){
        if(argument2==NULL){
            cout<<"./ssp.out missing parameter for the my command"<<endl;
        }
        if(strlen(argument2)>=16){
            cout<<"./ssp.out too many arguments"<<endl;
            while(getchar()!='\n');
        }
        
        else{
            year=strtof(argument2,NULL);
            if((year<=0)){
                cout<<"./ssp.out Invalid parameter for the my command"<<endl;
            }
            else{
                streaming_service.handle_mygt(year);
            }
        }
    }
    if(strcmp(w,"myle")==0){
        if(argument2==NULL){
            cout<<"./ssp.out missing parameter for the my command"<<endl;
        }
        if(strlen(argument2)>=16){
            cout<<"./ssp.out too many arguments"<<endl;
        }

        else{
            year=strtof(argument2,NULL);
            if((year<=0)){
                cout<<"./ssp.out Invalid parameter for the my command"<<endl;
            }
            else{
                streaming_service.handle_myle(year);
            }
        }
        
        
    }

    if(strcmp(w,"mylt")==0){
        if(argument2==NULL){
            cout<<"./ssp.out missing parameter for the my command"<<endl;
        }
        if(strlen(argument2)>=16){
            cout<<"./ssp.out too many arguments"<<endl;
            while(getchar()!='\n');
        }

        else{
        year=strtof(argument2,NULL);
            if((year<=0)){
                cout<<"./ssp.out Invalid parameter for the my command"<<endl;
            }
            else{
                streaming_service.handle_mylt(year);
            }
        }
        

    }

    if((strcmp(w,"mn")!=0) && (strcmp(w,"my")!=0) && (strcmp(w,"myge")!=0)  && (strcmp(w,"mygt")!=0) && (strcmp(w,"myle")!=0) && (strcmp(w,"mylt")!=0) ){
        cerr<<"./ssp.out Invalid command"<<endl;
    }
    
}




int main(int argc, char const *argv[]) {
    xml_document doc;
    xml_parse_result result;
    xml_node node;
    xml_node subnode;
    streaming_service_t streaming_service;



    //if number of argument is more or less than 2
    if(argc != 2){
    cerr << "invalid number of arguments" << endl;
    return 1;
    }
    result = doc.load_file(argv[1]);
    //if we can't load the file
    if(result==false){
        cerr<<"Unable to parse the document"<<endl;
        return 1;
    }

    //Now we're able to parse the document

    node=doc.first_child();
    if(strcmp(node.name(),"streaming-service")==0){
        streaming_service.set_name(node.first_attribute().value());
    }
    for(node = node.first_child(); node; node = node.next_sibling()){
        if((strcmp(node.name(),"medias")==0)){
            for(subnode=node.first_child();subnode;subnode=subnode.next_sibling()){

                //if the node type is anime
                if((strcmp(subnode.name(),"media")==0) and (strcmp(subnode.last_attribute().value(),"anime")==0)){
                    anime_t anime;
                    anime.set_name(subnode.first_attribute().value());
                    for(xml_node qualities=(subnode.child("qualities")).first_child();qualities;qualities=qualities.next_sibling()){
                        if (strcmp(qualities.child_value(),static_cast<const char*>("low"))==0){
                            anime.qualities_push_back(low);
                        }
                        if (strcmp(qualities.child_value(),static_cast<const char*>("medium"))==0){
                            anime.qualities_push_back(medium);
                        }
                        if (strcmp(qualities.child_value(),static_cast<const char*>("high"))==0){
                            anime.qualities_push_back(high);
                        }
                    }
                    try{
                        float b=strtof(subnode.child("rating").child_value(),NULL);
                        if(b<=0.0){
                            string str=subnode.child("rating").child_value();
                            throw(str);
                        }

                    }
                    catch(string str){
                        str2f_error error(str);
                        cerr<<error.what();
                        return 1;
                    }
                    anime.set_rating(strtof(subnode.child("rating").child_value(),NULL));

                    try{
                        long int b=strtol(subnode.child("year").child_value(),NULL,10);
                        if(b<=0 or b>=LONG_MAX or b<=LONG_MIN){
                            string str=subnode.child("year").child_value();
                            throw(str);
                            
                        }
                    }
                    catch(string str){
                        str2l_error error(str);
                        cerr<<error.what();
                        return 1;
                    }

                    try{
                        int b=strtol(subnode.child("year").child_value(),NULL,10);
                        if(b<=0 or (b>INT_MAX and b<LONG_MAX) or b<INT_MIN){
                            string str=subnode.child("year").child_value();
                            throw(str);
                           
                        }
                    }
                    catch(string str){
                        str2i_error error(str);
                        cerr<<error.what();
                        return 1;
                    }
                    
                    anime.set_year(strtol(subnode.child("year").child_value(),NULL,10));

                   try{
                       streaming_service.medias_push_back(anime);
                   }
                   catch (bad_alloc &e){
                       cerr << "an exception occurred: " << e.what()<< endl;
                        return 1;
                   }


                }

                //if the node type is film
                if((strcmp(subnode.name(),"media")==0) and (strcmp(subnode.last_attribute().value(),"film")==0)){
                    film_t film;
                    film.set_name(subnode.first_attribute().value());
                    for(xml_node qualities=(subnode.child("qualities")).first_child();qualities;qualities=qualities.next_sibling()){
                        if (strcmp(qualities.child_value(),static_cast<const char*>("low"))==0){
                            film.qualities_push_back(low);
                        }
                        if (strcmp(qualities.child_value(),static_cast<const char*>("medium"))==0){
                            film.qualities_push_back(medium);
                        }
                        if (strcmp(qualities.child_value(),static_cast<const char*>("high"))==0){
                            film.qualities_push_back(high);
                        }
                    }
                    try{
                        float b=strtof(subnode.child("rating").child_value(),NULL);
                        if(b==0.0){
                            string str=subnode.child("rating").child_value();
                            throw(str);
                        }

                    }
                    catch(string str){
                        str2f_error error(str);
                        cerr<<error.what();
                        return 1;
                    }

                    film.set_rating(strtof(subnode.child("rating").child_value(),NULL));

                    try{
                        long int b=strtol(subnode.child("year").child_value(),NULL,10);
                        if(b<=0 or b>=LONG_MAX or b<=LONG_MIN){
                            string str=subnode.child("year").child_value();
                            throw(str);
                            
                        }
                    }
                    catch(string str){
                        str2l_error error(str);
                        cerr<<error.what();
                        return 1;
                    }

                    try{
                        int b=strtol(subnode.child("year").child_value(),NULL,10);
                        if(b<=0 or (b>INT_MAX and b<LONG_MAX) or b<INT_MIN){
                            string str=subnode.child("year").child_value();
                            throw(str);
                           
                        }
                    }
                    catch(string str){
                        str2i_error error(str);
                        cerr<<error.what();
                        return 1;
                    }
                    film.set_year(strtol(subnode.child("year").child_value(),NULL,10));
                   
                    try{
                       streaming_service.medias_push_back(film);
                   }
                   catch (bad_alloc &e){
                       cerr << "an exception occurred: " << e.what()<< endl;
                        return 1;
                   }

                }

                //if the node type is series
                if((strcmp(subnode.name(),"media")==0) and (strcmp(subnode.last_attribute().value(),"series")==0)){
                    series_t series;
                    series.set_name(subnode.first_attribute().value());
                    for(xml_node qualities=(subnode.child("qualities")).first_child();qualities;qualities=qualities.next_sibling()){
                        if (strcmp(qualities.child_value(),static_cast<const char*>("low"))==0){
                            series.qualities_push_back(low);
                        }
                        if (strcmp(qualities.child_value(),static_cast<const char*>("medium"))==0){
                            series.qualities_push_back(medium);
                        }
                        if (strcmp(qualities.child_value(),static_cast<const char*>("high"))==0){
                            series.qualities_push_back(high);
                        }
                    }

                    try{
                        float b=strtof(subnode.child("rating").child_value(),NULL);
                        if(b==0.0){
                            string str=subnode.child("rating").child_value();
                            throw(str);
                        }

                    }
                    catch(string str){
                        str2f_error error(str);
                        cerr<<error.what();
                        return 1;
                    }
                    
                    series.set_rating(strtof(subnode.child("rating").child_value(),NULL));

                    try{
                        long int b=strtol(subnode.child("year").child_value(),NULL,10);
                        if(b<=0 or b>=LONG_MAX or b<=LONG_MIN){
                            string str=subnode.child("year").child_value();
                            throw(str);
                            
                        }
                    }
                    catch(string str){
                        str2l_error error(str);
                        cerr<<error.what();
                        return 1;
                    }

                    try{
                        int b=strtol(subnode.child("year").child_value(),NULL,10);
                        if(b<=0 or (b>INT_MAX and b<LONG_MAX) or b<INT_MIN){
                            string str=subnode.child("year").child_value();
                            throw(str);
                           
                        }
                    }
                    catch(string str){
                        str2i_error error(str);
                        cerr<<error.what();
                        return 1;
                    }
                    series.set_year(strtol(subnode.child("year").child_value(),NULL,10));

                   
                    try{
                       streaming_service.medias_push_back(series);
                   }
                   catch (bad_alloc &e){
                       cerr << "an exception occurred: " << e.what()<< endl;
                        return 1;
                   }

                }

               
                
            }
        }
        if((strcmp(node.name(),static_cast<const char*>("web"))==0)){
            streaming_service.set_web(node.child_value());
        }
    }


    ////////// main ////////////////////////////
    /*The user_data of the user */
    char user_data[18],*user_data2,*user_data3;

    user_data2=new char;
    user_data3=new char;
    while(strcmp(user_data,"q")!=0){
        cout<<"SSP> ";
        user_data[0]='\0';
        
        fgets(user_data,20,stdin);
        

        if(strlen(user_data)<=0){
            cout<<"./ssp.out: Too few characters for the command"<<endl;
        }
        if(strlen(user_data)>18){
            cout<<"./ssp.out: Too many characters for the command"<<endl;
            while(getchar()!='\n');


        }
        else{
            /*searching \n in l'user_data*/
            user_data2=strstr(user_data,"\n");
            if(user_data2!=NULL){
            /*if we find \n we replace it by \0*/
                *user_data2='\0';
            /*Initialise user_data3 */
                user_data3=NULL;
            }
            /*We search the " " for example the command my 2500*/
            user_data2=strstr(user_data," ");
            if(user_data2!=NULL){
            /*we go 1 forward to erase the character " " and the second is in user_data3*/
                user_data3=user_data2+1;
                *user_data2='\0';
            }
            if( (strlen(user_data)==1) && (strcmp(user_data,"q")!=0) ){
                char_Command(user_data[0],streaming_service);
                
            }
            if(strlen(user_data)>1){
                word_Command(user_data,user_data3,streaming_service);
                 

            }
          
        }
        
    }


    cout<<"Goodbye !"<<endl;
    delete user_data2;
    delete user_data3;


}