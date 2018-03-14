#ifndef LIB_MQTT_H
#define LIB_MQTT_H

#include <string>
#include <map>
#include <algorithm>
#include <functional>

#include <mosquitto.h>

typedef std::map<std::string, std::function<void(std::string)>> function_map;

class Mqtt{
private:
    std::string host;
    int port;
    std::string username;
    std::string password;

    std::map<std::string, std::function<void(std::string)> > subscribed_list;

    struct mosquitto* mosq;

    static void message_callback(struct mosquitto *mosq, void *obj, const struct mosquitto_message *message);

public: 
    Mqtt(std::string host, int port, std::string username, std::string password);
    bool subscribe(std::string topic, std::function<void(std::string)> callback);
    bool send(std::string topic, std::string message);
};


#endif