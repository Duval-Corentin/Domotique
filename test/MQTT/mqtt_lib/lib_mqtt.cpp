#include <iostream>

#include "lib_mqtt.h"

Mqtt::Mqtt(std::string host, int port, std::string username, std::string password):
host(host), port(port), username(username), password(password)
{
    mosquitto_lib_init();
    this->mosq = mosquitto_new("c++", false, 0);
    mosquitto_username_pw_set(this->mosq, this->username.c_str(), this->password.c_str());
    
    if(mosquitto_connect(this->mosq, this->host.c_str(), this->port, 60)){
        if(mosquitto_loop_start(this->mosq)){
            std::cout << "created instance of mqtt" << std::endl;
            return;
        }
    }

    mosquitto_message_callback_set(this->mosq, this->message_callback);
    std::cout << "error Mqtt initialization" << std::endl);
}

void Mqtt::message_callback(struct mosquitto *mosq, void *obj, const struct mosquitto_message *message){
    std::function<void(std::string)> function = this->subscribed_list.find( std::string(message->topic));
    if(function != this->subscribed_list.end()){
        function(std::string( (char *) message->payload));
    }
}


bool Mqtt::send(std::string topic, std::string message){
    mosquitto_reconnect(this->mosq);
    return mosquitto_publish(this->mosq, NULL, topic.c_str(), message.length(), message, 3, false);
}

bool Mqtt::subscribe(std::string topic, std::function<void(std::string)> callback){
    this->subscribed_list[topic] = callback;
}