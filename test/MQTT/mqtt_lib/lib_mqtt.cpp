#include <iostream>

#include "lib_mqtt.h"

Mqtt::Mqtt(std::string host, int port, std::string username, std::string password, std::string id, int qos):
host(host), port(port), username(username), password(password), id(id), qos(qos)
{
    mosquitto_lib_init();
    this->mosq = mosquitto_new(this->id.c_str(), false, &this->subscribed_list);
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

Mqtt::~Mqtt(){
    mosquitto_disconnect(this->mosq);
    mosquitto_lib_cleanup();
}


bool Mqtt::send(std::string topic, std::string message){
    mosquitto_reconnect(this->mosq);
    return mosquitto_publish(this->mosq, NULL, topic.c_str(), message.length(), message.c_str(), 3, false);
}

void Mqtt::message_callback(struct mosquitto *mosq, void *obj, const struct mosquitto_message *message){

    function_map * list = static_cast<function_map *>(obj);
    auto topic = list->find(message->topic);
    if(topic != list->end()){
        topic->second(std::string( (char *) message->payload));
    }
}

bool Mqtt::subscribe(std::string topic, std::function<void(std::string)> callback){
    this->subscribed_list[topic] = callback;
    return mosquitto_subscribe(this->mosq, NULL, topic.c_str(), this->qos);
}

bool Mqtt::unsubscribe(std::string topic){

    this->subscribed_list.erase(topic);
    return mosquitto_unsubscribe(this->mosq, NULL, topic.c_str());
}