#include "SIM900.h"
#include "gprs.h"
#include <SoftwareSerial.h>
#include "sms.h"
#include "inetGSM.h"
//SoftwareSerial gsmGPRS(2, 3);
InetGSM inet;
SMSGSM sms;
gprs gprs;

int numdata;
boolean started = false; //trạng thái modul sim
char smstext[160];// nội dung tin nhắn
char number[20]; // số điện thoại format theo định dạng quốc tế
int flg = 0;
void setup() {
  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);
  Serial.begin(9600);
  //Serial.println("Gui va nhan tin nhan");
  if (gsm.begin(2400)) {
    //Serial.println("\nstatus=READY");
    started = true;
  }
  gprs.setupGPRS();
  //Serial.println("\nstatus=IDLE");
  //    setupGPRS();
}

void recept() {
  if (started) {
    int pos; //địa chỉ bộ nhớ sim (sim luu tối đa 40 sms nên max pos = 40)
    pos = sms.IsSMSPresent(SMS_UNREAD); // kiểm tra tin nhắn chưa đọc trong bộ nhớ
    //hàm này sẽ trả về giá trị trong khoảng từ 0-40
    if (pos) { //nêu có tin nhắn chưa đọc
      if (sms.GetSMS(pos, number, smstext, 160)) {
        Serial.print("So dien thoại: ");
        Serial.println(number);
        Serial.print("Noi dung tin nhan: ");
        Serial.println(smstext);
        sms.SendSMS(number, "Da doc tin");
        if (strcmp(smstext, "a") == 0) {
          while (1) {
            digitalWrite(13, HIGH);
            delay(1000);
            digitalWrite(13, LOW);
            delay(1000);
          }
        }
      }
    }
    delay(1000);
  } else Serial.println("Offline");
}

void sendMSG() {
  if (started) {
//    sms.SendSMS("+841646403891", "Hello");   //đổi lại số của bạn nhé :D
  }
}

void sendLogsData(char* times, int total_time,int humidity) {
  char msg[100];
  sprintf(msg, "/embedded_2017/receive_data_sim900a?id_tree=1&time=%s&total=%d&humi=%d", times, total_time,  humidity);
  Serial.println(msg);
  gprs.sendData(msg);
}

void sendHumiTenMin(int humidity){
  char msg[100];
  sprintd(msg, "/embedded_2017/receive_data_humi_often_ten_min?id_tree=1&humi=%d", humidity);
  Serial.println(msg);
  gprs.sendData(msg);
}
  
void loop() {
  //  sendMSG();
  //    recept();
  char msg[100] = "hello1";
  sendLogsData("2017-12-12", 12, 50); // send data to server
  sendHumiTenMin(95);
  delay(1000);
}

