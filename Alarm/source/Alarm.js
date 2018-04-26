const Spawn = require("child_process");
const Mopidy = require("mopidy");
const Cron = require("node-cron")

module.exports = class Alarm{
    constructor(default_snooze_time, default_trigger_time){
        this.default_snooze_time = default_snooze_time;
        this.default_trigger_time = default_trigger_time;

        this.mopidy_process = Spawn("mopidy");
        
        var process_out = "";
        this.mopidy_process.stderr.on('data', (data) => {
            process_out += String(data);
            
            if(process_out.includes("Logged in to Spotify in online mode") && process_out.includes("HTTP server running at [::ffff:127.0.0.1]:6680")){
                this.mopidy = new Mopidy({
                    webSocketUrl: "ws://localhost:6680/mopidy/ws/",
                    callingConvention: "by-position-only"
                });
                this.mopidy.on("state:online", function () {
                    this.mopidy_ready = true;
                });
            }
        });


        this.alarms = new Map();
    }

    add(alarm_JSON){
        if(this.mopidy_ready){
            return this.mopidy.playlists.getPlaylists().then( playlists => {
                for(let playlist of playlists){
                    if(playlist.name === alarm_JSON.playlist_name){
                        if( typeof alarm_JSON.name === "string" && typeof alarm_JSON.date.day_of_the_week === "object" && alarm_JSON.date.hour < 24 && alarm_JSON.date.minute < 60){
                            this.alarms.set(alarm_JSON, Cron.schedule(this.dateJSONToCron(alarm_JSON.date), () => {
                                this.play(alarm_JSON);
                            }));
                            return alarm_JSON;
                        }
                    }
                }
            });
        }
        return false;
    }
    
    remove(){
        
    }
    
    play(alarm_JSON){
        
    }
    
    snooze(){
        
    }
    
    pause(){
        
    }
    
    stop(){
        
    }
    
    getAlarmJSONPattern(){
        return {
            "name": "name",
            "playlist_name": "playlist_name",
            "trigger_time": 'minutes',
            "snooze_time": 'minutes',
            "volume": '0-100',
            "repeat": "boolean",
            "date": {
                "day_of_the_week": {
                    "MON": "boolean",
                    "TUE": "boolean",
                    "WED": "boolean",
                    "THU": "boolean",
                    "FRI": "boolean",
                    "SAT": "boolean",
                    "SUN": "boolean",
                },
                "hour": "0-23",
                "minute": "0-59"
            }
        }
    }
    
    dateJSONToCron(date_object){
        var cron = "* " + String(minutes) + " " + String(hour) + " * * ";
        var index = 0;
        for(day of date_object.day_of_the_week){
            index++;
            if(date_object.day_of_the_week[day]){
                cron += index + "-";
            }
        }
        return cron.substr(0, cron.length - 2);
    }

    getAlarmFromName(){

    }

    getVolume(){
        
    }
    
    getState(){

    }

    getPlaylistsNames(){
        
    }

    getMopidyState(){
        return this.mopidy_ready;
    }

    setRandom(){
        
    }
    
    setVolume(){

    }

    setrandom(){

    }
}