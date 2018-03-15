var mqtt = require('mqtt')

var mqtt_client_options = {
    protocol: 'mqtt',
    port: 4050,
    clientId: 'Mopidy_client',
    username: 'corentin',
    password: 'Massey6277!'
}

var mqtt_client = mqtt.connect('192.168.0.20', mqtt_client_options);

mqtt_client.subscribe('test/test');
mqtt_client.on('message', function(topic, message){
    console.log(topic); 
    console.log(message.toString()); 
});