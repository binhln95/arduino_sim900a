#include "gprs.h"
SoftwareSerial gsmGPRS(2, 3);
char c, d;
unsigned char buffers[64];
int count = 0;
int varloop = 1000;
void gprs::setupGPRS(){
 	pinMode(2, INPUT);
 	pinMode(3, OUTPUT);
 	gsmGPRS.begin(2400);
 	gsmGPRS.println("AT+SAPBR=3,1,\"Contype\",\"GPRS\"");
 	delay(varloop);
 	while (gsmGPRS.available()) {
  		d = gsmGPRS.read();
   	Serial.print(d);
 	}
 	gsmGPRS.println("AT+CIPCSGP=1,\"m-wap\",\"mms\",\"mms\"");
 	delay(varloop);
 	while (gsmGPRS.available()) {
   	d = gsmGPRS.read();
   	Serial.print(d);
 	}
 	gsmGPRS.println("AT+SAPBR =1,1");
 	delay(varloop);
 	while (gsmGPRS.available()) {
   	d = gsmGPRS.read();
   	Serial.print(d);
 	}
 	gsmGPRS.println("AT+SAPBR =2,1");
 	delay(varloop);
 	while (gsmGPRS.available()) {
   	d = gsmGPRS.read();
   	Serial.print(d);
 	}

 	gsmGPRS.println("AT+CMEE=2");
 	delay(varloop);
 	while (gsmGPRS.available()) {
   	d = gsmGPRS.read();
   	Serial.print(d);
 	}
 	delay(varloop);
 	gsmGPRS.println("AT+HTTPINIT");
 	delay(varloop);
 	while (gsmGPRS.available()) {
   	d = gsmGPRS.read();
   	Serial.print(d);
 	}

 	gsmGPRS.println("AT+HTTPPARA=\"CID\",1");
 	delay(varloop);
 	while (gsmGPRS.available()) {
   	d = gsmGPRS.read();
   	Serial.print(d);
 	}
}

void gprs::sendData(char* url){
	Serial.println("------------------------start send-------------------------");
    int varloop = 1000;
    char d;
    gsmGPRS.println("AT+CIPSHUT");
    while (gsmGPRS.available()) {
        d = gsmGPRS.read();
        Serial.print(d);
    }
    char* BASE_URL = "117.0.172.40:3000";
    // char* BASE_URL = "47.74.176.246:3000";

    delay(varloop);
    char cmd[100] = "AT+HTTPPARA=\"URL\",\"";
    char req_url[100] = "";
    strcat(req_url, BASE_URL);
    strcat(req_url, url);
    strcat(cmd, req_url);
    strcat(cmd, "\"");
    Serial.println(cmd);
    gsmGPRS.println(cmd);
    while (gsmGPRS.available()) {
        d = gsmGPRS.read();
        Serial.print(d);
    }
    delay(varloop);
    gsmGPRS.println("AT+HTTPACTION=0");
    while (gsmGPRS.available()) {
        d = gsmGPRS.read();
        Serial.print(d);
    }
    delay(varloop);
    gsmGPRS.println("AT+HTTPREAD");
    while (gsmGPRS.available()) {
        d = gsmGPRS.read();
        Serial.print(d);
    }
    delay(varloop);
    while (1) {
        while (gsmGPRS.available()) {
            d = gsmGPRS.read();
            Serial.print(d);
        }
        if (d == '\n' && !gsmGPRS.available() ){
            break;
        }
        delay(2000);
    }
    delay(varloop);
    return 1;
}

void setting(char *url){
  Serial.println("------------------------start send-------------------------");
    int varloop = 1000;
    char d;
    gsmGPRS.println("AT+CIPSHUT");
    while (gsmGPRS.available()) {
        d = gsmGPRS.read();
        Serial.print(d);
    }
    char* BASE_URL = "117.0.172.40:3000";
    // char* BASE_URL = "47.74.176.246:3000";

    delay(varloop);
    char cmd[100] = "AT+HTTPPARA=\"URL\",\"";
    char req_url[100] = "";
    strcat(req_url, BASE_URL);
    strcat(req_url, url);
    strcat(cmd, req_url);
    strcat(cmd, "\"");
    Serial.println(cmd);
    gsmGPRS.println(cmd);
    while (gsmGPRS.available()) {
        d = gsmGPRS.read();
        Serial.print(d);
    }
    delay(varloop);
    gsmGPRS.println("AT+HTTPACTION=0");
    while (gsmGPRS.available()) {
        d = gsmGPRS.read();
        Serial.print(d);
    }
    delay(varloop);
    gsmGPRS.println("AT+HTTPREAD");
    while (gsmGPRS.available()) {
        d = gsmGPRS.read();
        Serial.print(d);
    }
    delay(varloop);
    while (1) {
        while (gsmGPRS.available()) {
            d = gsmGPRS.read();
            Serial.print(d);
        }
        if (d == '\n' && !gsmGPRS.available() ){
            break;
        }
        delay(2000);
    }
    delay(varloop);
}