#define blueToothSerial Serial2



void setup()
{
    Serial.begin(9600);
      
    setupBlueToothConnection();

}

void loop()
{
    char recvChar;
    String recvStr;
    String sendStr;
    while(1)
    {
        if(blueToothSerial.available())
        {//check if there's any data sent from the remote bluetooth shield
            //recvChar = blueToothSerial.read();
            recvStr = blueToothSerial.readStringUntil(',');
            Serial.print(recvStr);
            Serial.print("\n");
        }
        if(Serial.available()){
          sendStr = Serial.readString();

          blueToothSerial.println("Send back");
          blueToothSerial.println(sendStr);
        }
    }
}

void setupBlueToothConnection()
{
    blueToothSerial.begin(38400);                           // Set BluetoothBee BaudRate to default baud rate 38400
    blueToothSerial.print("\r\n+STWMOD=0\r\n");             // set the bluetooth work in slave mode
    blueToothSerial.print("\r\n+STNA=GUANSlave\r\n");    // set the bluetooth name as "SeeedBTSlave"
    blueToothSerial.print("\r\n+STOAUT=1\r\n");             // Permit Paired device to connect me
    blueToothSerial.print("\r\n+STAUTO=0\r\n");             // Auto-connection should be forbidden here
    delay(2000);                                            // This delay is required.
    blueToothSerial.print("\r\n+INQ=1\r\n");                // make the slave bluetooth inquirable
    Serial.println("The slave bluetooth is inquirable!");
    delay(2000);                                            // This delay is required.
    blueToothSerial.flush();
}
