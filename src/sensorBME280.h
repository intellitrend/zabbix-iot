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

#ifndef SENSORBME280_H
#define SENSORBME280_H

typedef struct BMESensorData_t {
  float temp;     // temp
  float hum;      // humidity
  float press;    // pressure
  float dew;      // dew point
  bool hashum;    // has humidity sensor (not BMP280, only BME280/BME680) - (not sending as metric)
} BMESensorData_t;


class SensorBME280 {
public:
    SensorBME280();
    SensorBME280(const SensorBME280& orig);
    virtual ~SensorBME280();
    bool begin();
    BMESensorData_t getData();
private:
    bool hashum;
};

#endif /* SENSORBME280_H */
