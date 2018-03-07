#include "DTH22.h"


DTH22::DTH22(char pin, int tempo): pin(pin)
{
    if(tempo < 2000){
        this->tempo = std::chrono::milliseconds(2000);
    } else{
        this->tempo = std::chrono::milliseconds(tempo);
    }

    updateData();
}

void DTH22::updateData(){

    std::cout << "update Data" << std::endl;

    int data[5] = { 0, 0, 0, 0, 0 };
    uint8_t laststate	= HIGH;
	uint8_t counter		= 0;
	uint8_t j			= 0, i;
 
	data[0] = data[1] = data[2] = data[3] = data[4] = 0;
 
	/* pull pin down for 18 milliseconds */
	pinMode( this->pin, OUTPUT );
	digitalWrite( this->pin, LOW );
	delay( 18 );
 
	/* prepare to read the pin */
	pinMode( this->pin, INPUT );
 
	/* detect change and read data */
	for ( i = 0; i < MAX_TIMINGS; i++ )
	{
		counter = 0;
		while ( digitalRead( this->pin ) == laststate )
		{
			counter++;
			delayMicroseconds( 1 );
			if ( counter == 255 )
			{
				break;
			}
		}
		laststate = digitalRead( this->pin );
 
		if ( counter == 255 )
			break;
 
		/* ignore first 3 transitions */
		if ( (i >= 4) && (i % 2 == 0) )
		{
			/* shove each bit into the storage bytes */
			data[j / 8] <<= 1;
			if ( counter > 16 )
				data[j / 8] |= 1;
			j++;
		}
	}
 
	/*
	 * check we read 40 bits (8bit x 5 ) + verify checksum in the last byte
	 * print it out if data is good
	 */
	if ( (j >= 40) &&
	     (data[4] == ( (data[0] + data[1] + data[2] + data[3]) & 0xFF) ) )
	{
		this->humidity = (float)((data[0] << 8) + data[1]) / 10;
		this->temperature = (float)(((data[2] & 0x7F) << 8) + data[3]) / 10;
		if ( data[2] & 0x80 )
		{
			this->temperature = -this->temperature;
		}
    }else  {
		//updateData();
	}

    this->last_mesure = std::chrono::system_clock::now();
}

char DTH22::getHumidity(){
    if( (std::chrono::system_clock::now() - this->last_mesure) > this->tempo){
        updateData();
    }

    return this->humidity;
}

char DTH22::getTemperature(){
    if( (std::chrono::system_clock::now() - this->last_mesure) > this->tempo){
        updateData();
    }

    return this->temperature;
}