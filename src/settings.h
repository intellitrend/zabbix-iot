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

// ***** Zabbix related settings *****
// zabbix server or proxy - either IP or FQDN
const char * server = "zabbix.mydomain.loc";
// zabbix trapper port
const uint16_t port = 10051;
// hostname of host in zabbix
const char * hostname = "mysensorhost";

// ***** WiFi related settings *****
// WiFi SSID to connect to (case sensitive)
const char * ssid = "myssid";
// WiFi key
const char * wifiKey = "mysecretwifikey";

// ***** Sensor related settings *****
// send  data intervall in sec after connection and sending data 
const int sendDataIntervallSec = 60;


// ***** Application related settings *****
// Number of wifi connect cyles before going to deepsleep
int maxWifiConnectcycles = 20;
// max connection timeout in ms after wifi connection and waiting for connection to zabbix-server
const int maxConnectionTimeout = 5 * 1000;
// max transmission timeout in ms after connection to zabbix-server and start sending data
const int maxTransmissionTimeout = 5 * 1000;

// ***** LEDs *****
// on Errors
int RED_LED = 16;
// on while waiting for wlan and sending data
int GREEN_LED = 17;

