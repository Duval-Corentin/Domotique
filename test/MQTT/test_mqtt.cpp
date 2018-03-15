#include <iostream>
#include <string>
#include <stdio.h>

#include "mqtt_lib/lib_mqtt.h"


int main(){
    std::string host("192.168.0.20");
    int port = 4050;
    std::string username("corentin");
    std::string password("Massey6277!");
    std::string topic("test/test");


    Mqtt mqtt_client(host, port, username, password, "coco l'asticot", 2);
    mqtt_client.subscribe(topic, [](std::string message){
        std::cout << "message recu : " << message << std::endl;
    });

    mqtt_client.subscribe("test/test2", [](std::string message){
        std::cout << "message 2 : " << message << std::endl;
    });

    getchar();

    mqtt_client.unsubscribe(topic);
    getchar();
}