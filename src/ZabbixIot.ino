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


/**
 * Very basic demo application to read sensor values from a BME280 
 * and send them to a Zabbix Server/Proxy using the Zabbix Sender protocol through Wi-Fi.
 */

/**
 * Modify settings like zabbix-server, wifi etc. in settings.h
 */

// To work as idf component. Not needed in arduino but does not harm either.
#include "Arduino.h"

#include <WiFi.h>
#include "zabbixSender.h"
#include "sensorBME280.h"
#include "settings.h"


// ****** Functions *******
void goDeepsleep() {    
    WiFi.disconnect(true);
    delay(100);
    esp_sleep_enable_timer_wakeup(sendDataIntervallSec * 1000 * 1000ULL);
    Serial.printf("Deepsleep starts now for %d seconds.\n", sendDataIntervallSec);
    delay(100);
    esp_deep_sleep_start();
}

// ****** Main *******

void setup() {   
    Serial.begin(115200);
    delay(100);    
    Serial.println("=== SETUP Start ===");
    
    pinMode(RED_LED, OUTPUT);
    pinMode(GREEN_LED, OUTPUT);

    Serial.println("Waiting for WiFi... ");   
    // indicate to user
    digitalWrite(GREEN_LED, HIGH);   
    WiFi.begin(ssid, wifiKey);
    // current wifi ap connect cycles
    int wccycles = 0;
    while(WiFi.status() != WL_CONNECTED) {
        Serial.print(".");
        Serial.print((int)WiFi.status());
        wccycles++;
        // try maxWifiConnectcycles than deepsleep
        if (wccycles > maxWifiConnectcycles) {
          Serial.printf("\n[ERROR] WLAN TIMEOUT - Abort\n");
          // indicate to user
          digitalWrite(GREEN_LED, LOW);
          digitalWrite(RED_LED, HIGH);
          delay(1000);
          digitalWrite(RED_LED, LOW);
          goDeepsleep();
        }
        delay(300);
    }
    
    // we are connected, turn off
    digitalWrite(GREEN_LED, LOW);    
    Serial.printf("\nWiFi connected. IP address:");
    Serial.println(WiFi.localIP());
    Serial.println("=== SETUP End ===");
} // setup



void loop() {
    Serial.println("=== START ==="); 
    // init sensor
    SensorBME280 sb;   
    bool sbStatus = sb.begin();
    if (!sbStatus) {      
        Serial.printf("[ERROR] Sensor FAILURE - Abort\n");
        // indicate to user
        digitalWrite(RED_LED, HIGH);
        delay(1000);
        digitalWrite(RED_LED, LOW);
        goDeepsleep();
    }
 
    BMESensorData_t sd = sb.getData();       
    Serial.printf("Collected values. temp:%f, hum:%f, press:%f\n", sd.temp, sd.hum, sd.press);

    ZabbixSender zs;
    String jsonPayload;
    jsonPayload = zs.createPayload(hostname, sd.temp, sd.hum, sd.press);
      // create message in zabbix sender format
    String msg = zs.createMessage(jsonPayload);
    
    // connect and transmit
    Serial.printf("==> Connecting to:%s:%d\n", server, port);
    // connect to server
    WiFiClient client;
    // indicate to user
    digitalWrite(GREEN_LED, HIGH);      
    if (!client.connect(server, port)) {
        Serial.printf("[ERROR] Connection FAILED - Abort\n"); 
        digitalWrite(GREEN_LED, LOW);
        digitalWrite(RED_LED, HIGH);
        delay(1000);
        digitalWrite(RED_LED, LOW);
        goDeepsleep();
    }
    
    Serial.println("Connected. Sending data.");
    client.print(msg);  
    unsigned long startTime = millis();
    while (client.available() == 0) {
        if (millis() - startTime > maxTransmissionTimeout) {
            Serial.printf("[ERROR] Transmission TIMEOUT - Abort\n");
            client.stop();
            // indicate to user
            digitalWrite(GREEN_LED, LOW);
            digitalWrite(RED_LED, HIGH);
            delay(1000);
            digitalWrite(RED_LED, LOW);
            goDeepsleep();
        }
    }
    
    digitalWrite(GREEN_LED, LOW);

    // read reply from zabbix server
    while(client.available()) {
        String line = client.readStringUntil('\r');
        Serial.print(line);
    }    
    Serial.println();

    Serial.printf("Closing connection - Sleeping for %d sec...\n", sendDataIntervallSec);
    client.stop(); 
    goDeepsleep();
}

