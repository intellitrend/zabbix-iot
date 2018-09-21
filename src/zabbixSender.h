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

#ifndef ZABBIXSENDER_H
#define ZABBIXSENDER_H

#include <stdio.h>
#include <string>

#ifndef ZJSONBUFFER_SIZE
#define ZJSONBUFFER_SIZE 1100
#endif

class ZabbixSender {
public:
  ZabbixSender();
  ZabbixSender(const ZabbixSender& orig);
  virtual ~ZabbixSender();
  String createPayload(const char *hostname, float temp, float hum, float press);
  String createMessage(String jsonPayload);
private:
};

#endif /* ZABBIXSENDER_H */
