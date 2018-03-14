#include <iostream>

#include "lib_mqtt.h"

Mqtt::Mqtt(std::string host, int port, std::string username, std::string password):
host(host), port(port), username(username), password(password)
{
    mosquitto_lib_init();
    this->mosq = mosquitto_new("c++", false, &this->subscribed_list);
    mosquitto_username_pw_set(this->mosq, this->username.c_str(), this->password.c_str());
    
    mosquitto_message_callback_set(this->mosq, this->message_callback);
    
    if(!mosquitto_connect(this->mosq, this->host.c_str(), this->port, 60)){
        if(!mosquitto_loop_start(this->mosq)){
            std::cout << "created instance of mqtt" << std::endl;
            return;
        }
    }

    std::cout << "error Mqtt initialization" << std::endl;
}

void Mqtt::message_callback(struct mosquitto *mosq, void *obj, const struct mosquitto_message *message){
    std::cout << "in callback" << std::endl;
    function_map * list = static_cast<function_map *>(obj);
    auto topic = list->find(message->topic);
    if(topic != list->end()){
        topic->second(std::string( (char *) message->payload));
    }
}

bool Mqtt::send(std::string topic, std::string message){
    mosquitto_reconnect(this->mosq);
    return mosquitto_publish(this->mosq, NULL, topic.c_str(), message.length(), message.c_str(), 3, false);
}

bool Mqtt::subscribe(std::string topic, std::function<void(std::string)> callback){
    this->subscribed_list[topic] = callback;
    mosquitto_subscribe(this->mosq, NULL, topic.c_str(), 1);
    return true;
}