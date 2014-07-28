#include <SPI.h>
#include <Ethernet.h>

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED }; //physical mac address
byte ip[] = { 192, 168, 2, 177 };         

EthernetServer server(80);
int pinup=2;   
int pinstop=3;   
int pindown=4;    
String readString = String(50);

 

void setup(){
  Ethernet.begin(mac, ip);
  pinMode(pinup, OUTPUT);
  pinMode(pinstop, OUTPUT);
  pinMode(pindown, OUTPUT);
  server.begin();
  Serial.begin(9600);
}
void loop(){

  EthernetClient client = server.available();
  if (client) {
    while (client.connected()) {
   if (client.available()) {
    char c = client.read();
      readString.concat(c);
      //　資料處理區
        Serial.print("f");
            
      if (c == '\n')
            {
                Serial.println(readString.substring(6,11));
            if (readString.substring(6,10) == "pw=0")
               {
                   Serial.println("鐵捲門開");
                 digitalWrite(pinup, HIGH);   
                 digitalWrite(pinstop, LOW);    
                 digitalWrite(pindown, LOW);    
                 delay(2000);
               }
             else if (readString.substring(6,10) == "pw=1")
               {
                   Serial.println("鐵捲門停");
                 digitalWrite(pinstop, HIGH);   
                 digitalWrite(pinup, LOW);    
                 digitalWrite(pindown, LOW);    
                 delay(2000);
               }
           else if (readString.substring(6,10) == "pw=2")
              {
               Serial.println("鐵捲門關");
               digitalWrite(pindown, HIGH);      
               digitalWrite(pinup, LOW);    
               digitalWrite(pinstop, LOW);    
               delay(2000);  
            }
           else
              {
                 Serial.println("等待中全部停止狀態");
                 digitalWrite(pinup, LOW); 
                 digitalWrite(pinstop, LOW);    
                 digitalWrite(pindown, LOW);  
              }
               digitalRead(pinup);
// 　  網頁開始
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
//          client.println("Connection: close");  // the connection will be closed after completion of the response
          client.println();
          client.println("<!DOCTYPE HTML>");
          client.println("<html><meta charset='utf-8' /><link type='text/css' rel='stylesheet' href='http://211.75.72.240/home/home.css' >");
          client.println("<link href='//maxcdn.bootstrapcdn.com/font-awesome/4.1.0/css/font-awesome.min.css' rel='stylesheet'>");
          client.println("<img src='http://211.75.72.240/home/bg.jpg' id='bgImage' style='margin-left: 0px;'>");
          // output the value of each analog input pin
             client.println(readString.substring(6,10));
          client.print("<div id='lights'>                                                             ");
          client.print("    <ul>                                                                      ");
          client.print("      <li><a href='?pw=0'><span class='sw on'>ON</span>電捲門上</a></li>      ");
          client.print("      <li><a href='?pw=1'><span class='sw on'>ON</span>電捲門停</a></li>      ");
          client.print("      <li><a href='?pw=2'><span class='sw off'>OFF</span>電捲門下</a></li>    ");
          client.print("      <li><a href='?pw=3'><span class='sw off'>OFF</span>電腦開機</a></li>    ");
          client.print("      <li><a href='?pw=4'><span class='sw off'>OFF</span>　電燈</a></li>      ");
          client.print("    </ul>                                                                     ");
          client.print("</div>                                                                        ");



                  client.println("</html>");
        readString="";
        client.stop();
        }
        }
      }
    }
    }
