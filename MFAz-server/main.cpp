
#include<iostream>
#include<string>
#include<sstream>
#include<fstream>
#include<cppcms/application.h>
#include<cppcms/http_response.h>
#include<cppcms/url_dispatcher.h>
#include<cppcms/http_request.h>
#include<cppcms/service.h>
#include<cppcms/applications_pool.h>
#include<cppcms/json.h>
#include<cppcms/serialization.h>
#include<chrono>
#include <boost/date_time/gregorian/gregorian.hpp>
#include<cppcms/http_file.h>

#include "function.h"

#include "models.cpp"

using namespace std;

GrantedAccess grant;



class MyApp : public cppcms::application {
public:
    MyApp(cppcms::service &srv) : cppcms::application(srv) {
        
        dispatcher().assign("/",&MyApp::Home,this);
        dispatcher().assign("/verify", &MyApp::test, this);
        dispatcher().assign("/authrun",&MyApp::authrun, this);
        dispatcher().assign("/add", &MyApp::add, this);
        dispatcher().assign("/register", &MyApp::signup, this);
        dispatcher().assign("/login", &MyApp::login, this);
        dispatcher().assign("/get_GA", &MyApp::get_list, this);
    }

    void Home()  {
        response().out() << "Hello, CppCMS!";
    }

    void add(){
        string method=request().request_method();
        if(method=="POST"){
            pair<void *,int>  data=request().raw_post_data();
            string s(static_cast<char*>(data.first),data.second);
            stringstream ss(s);
            cppcms::json::value json;
            json.load(ss,true);

            int id = json.get<int>("id");

            string n2 = json.get<string>("granted_access");

            grant.insert_access(id,n2);
        }
    }
    void signup(){
        string method=request().request_method();
        if(method=="POST"){
            pair<void *,int>  data=request().raw_post_data();
            string s(static_cast<char*>(data.first),data.second);
            stringstream ss(s);
            cppcms::json::value json;
            json.load(ss,true);

            string username = json.get<string>("username");
            string password = json.get<string>("password");
            int userid = json.get<int>("user_id");

            string res;

            if(grant.register_user(username,password,userid)){
                res = "Registration Successful";
            }
            else{
                res = "Registration Fail";
            }
            cppcms::json::value response_json;
            response_json["Response"] = res;
            response().content_type("application/json");
            response().out() << response_json;
        }
    }
    void login(){
        string method=request().request_method();
        if(method=="POST"){
            pair<void *,int>  data=request().raw_post_data();
            string s(static_cast<char*>(data.first),data.second);
            stringstream ss(s);
            cppcms::json::value json;
            json.load(ss,true);

            string username = json.get<string>("username");
            string password = json.get<string>("password");
            auto [code,user_id] = grant.login_verification(username,password);
            string res;

            cppcms::json::value response_json;
            if(code && user_id){
                res = "Login Successful";
                int id = user_id.value();
                // cout<<id<<endl;
                string sessionid = session_id_generator(id);

                grant.create_session(id,sessionid);
                response_json["SessionID"] = sessionid;

            }else{
                res = "Login Failed";
            }
           
            response_json["Response"] = res;
            response().content_type("application/json");
            response().out() << response_json;
            

        }
    }
    void get_list(){
        string method=request().request_method();
        if(method=="GET"){
            pair<void *,int>  data=request().raw_post_data();
            string s(static_cast<char*>(data.first),data.second);
            stringstream ss(s);
            cppcms::json::value json;
            json.load(ss,true);

            int id = json.get<int>("id");
            vector<string> res = grant.get_access(id);
            for(const auto x:res){
                cout<<x<<endl;
            }
        }
    }
    void authrun(){
        string method=request().request_method();
        if(method == "GET"){
            
            pair<void *,int>  data=request().raw_post_data();
            string s(static_cast<char*>(data.first),data.second);
            stringstream ss(s);
            cppcms::json::value json;
            json.load(ss,true);

            int id = json.get<int>("id");

            // char r[100];
            // char in[5];
            // snprintf(in,5,"aaaa");
            // hashing(in, 4, r);
            // cout<<r<<endl;
            char result[1000];
            vector<string> Oi,Ri;
            Oi.push_back("read");
            Ri.push_back("res1");
            // int id = 12345;

            strcpy(result,authUserRequest(id,Oi,Ri));
            string res;
            
            
            res = "Access Granted";
            cout<<"GA: "<<result<<endl;
            grant.insert_access(id,result);
            

            
            

            cppcms::json::value response_json;
            response_json["access"] = res;
            response().content_type("application/json");
            response().out() << response_json;
        }
    }
    void test() {
        string method=request().request_method();
        if(method == "GET"){
            
            pair<void *,int>  data=request().raw_post_data();
            string s(static_cast<char*>(data.first),data.second);
            stringstream ss(s);
            cppcms::json::value json;
            json.load(ss,true);

            string sessionid = json.get<string>("session_id");
            int used_id = json.get<int>("used_id");

            // char r[100];
            // char in[5];
            // snprintf(in,5,"aaaa");
            // hashing(in, 4, r);
            // cout<<r<<endl;
            char result[1000];
            vector<string> Oi,Ri;
            Oi.push_back("read");
            Ri.push_back("res1");
            // int id = 12345;
            vector<string> gai;
            
            int id = grant.get_id_from_sessionid(sessionid);

            //assume used_id is the ga here! because we are fetching ga based on id 
            if(used_id != 0) gai = grant.get_access(used_id);
            else gai = grant.get_access(id);

            char sga[1000];
            
            strcpy(sga,gai[gai.size()-1].c_str()); //take the last ga from database
            cout<<sga<<endl;
            strcpy(result,userRequest(id,Oi,Ri,sga));
            
            string res;
            
            if(!strcmp(result,"Access Denied")){
                res = result;
            }
            else{
                res = "Access Granted";
                cout<<"GA: "<<result<<endl;
                grant.insert_access(id,result);
            }

            
            

            cppcms::json::value response_json;
            response_json["access"] = res;
            response().content_type("application/json");
            response().out() << response_json;
        }
    }
};

int main(int argc,char *argv[]){
    try{

        cppcms::service service(argc,argv);
        service.applications_pool().mount(cppcms::applications_factory<MyApp>());
        string ip=service.settings().get<string>("service.ip");
        int port=service.settings().get<int>("service.port");
        cout<<endl<<"Server started on "<<ip<<":"<<port<<endl;
        service.run();
    }catch(const exception &e){
        cout<<endl<<e.what()<<endl;
    }
    return 0;
}

