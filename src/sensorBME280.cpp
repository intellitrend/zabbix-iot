/*
 MIT License

Copyright (c) 2018 IntelliTrend GmbH, http://www.intellitrend.de

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
 */



/*
Connecting the BME280 Sensor:
Sensor              ->  Board
-----------------------------
Vin (Voltage In)    ->  3.3V
Gnd (Ground)        ->  GND
SDA (Serial Data)   ->  GPIO21
SCK (Serial Clock)  ->  GPIO22
 */

#include <BME280I2C.h>
#include <Wire.h>
#include "sensorBME280.h"

BME280I2C bme;    // Default : forced mode, standby time = 1000 ms
                  // Oversampling = pressure ×1, temperature ×1, humidity ×1, filter off,

using namespace std;

SensorBME280::SensorBME280() {
}

SensorBME280::SensorBME280(const SensorBME280& orig) {
}

SensorBME280::~SensorBME280() {
}


bool SensorBME280::begin() { 
    this->hashum = false;
    // I2C init
    Wire.begin();
    bool bmeStatus = bme.begin();
    if (!bmeStatus) {
        Serial.println("FAILURE - BME280 sensor not found.");
    } else {
        switch(bme.chipModel()) {
            case BME280::ChipModel_BME280:
                Serial.println("Found BME280 sensor! Success.");
                this->hashum = true;
                break;
            case BME280::ChipModel_BMP280:
                Serial.println("Found BMP280 sensor! No Humidity available.");
                break;
            default:
                Serial.println("Found UNKNOWN sensor! Error!");
        } 
    }
  
    return bmeStatus;
}


BMESensorData_t SensorBME280::getData() {
    BMESensorData_t sd;
    BME280::TempUnit tempUnit(BME280::TempUnit_Celsius);
    BME280::PresUnit presUnit(BME280::PresUnit_Pa);

    bme.read(sd.press, sd.temp, sd.hum, tempUnit, presUnit);
    sd.hashum = this->hashum;
    return sd;
}

