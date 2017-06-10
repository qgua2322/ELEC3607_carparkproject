/*
 *   This is a Car Parking Embedded System by using Arduino Due. This system is able to 
 *   communicate with customer by Bluetooth(2.0 or 4.0). In our design, customers can open their own's Apps
 *   to check how many spaces are still available/reserve a parking space/ how long did they parked
 *   in/Pay the bill. So this embedded system need to be able to response customer's command, and manage 
 *   this car park automatically. For example, when a customer is reserve a space, this system need to 
 *   update the number of spaces is remain on LCD and customer's phone, and open the gate of that parking space, 
 *   and the gate will not close until the customer's car park in.
 *   
 *   System design:  
 *   This system is using a Finite state machine(FSM) as the control mechanism.  
 *   Input: Bluetooth and IR sensor;
 *   Output: IR LED, servo motor,bluetooth, LCD display.
 *   
 *   Using different version of Bluetooth:
 *   First,Bluetooth's RX connects to Serial2 TX, Bluetooth's TX connects to Serial2 RX. (For any version)           
 *   Second, if choose Bluetooth 4.0, uncommand setupBlueToothConnection4(), command setupBlueToothConnection()
 *           if choose Bluetooth 2.0, uncommand setupBlueToothConnection(), command setupBlueToothConnection4().
 *           
 *   
 *   Created 10/06/2017 by QISHEN GUAN
 */



//Include Arduino library
#include <TFT.h>  
#include <SPI.h>
#include <Servo.h>

// pin definition for the LCD
#define cs   10
#define dc   9
#define rst  8

//Bluetooth definition
#define blueToothSerial Serial2

//timer counter defintion 
#define XTC TC1
#define XCHAN 1
#define XID ID_TC4

//IR LED signal definition
#define  XTC1    TC0       // TC number
#define  XCHAN1  0         // TC channel
#define  XID1    ID_TC0    // Instance ID
#define  PINCHAN  25      // Digital pin 2 which is on PIOB channel 25

//Create Servo and TFT object
Servo myservo;
TFT TFTscreen = TFT(cs, dc, rst);



/*  FSM States */
typedef enum
{
  IDLE = 0U,
  RESERVESend,
  RESERVECheck,
  RESERVEClose,
  TIMECounting,
  LEAVE,
  PAY,
  PAYCHECK,
  PAYCLOSE,
} ParkingSystem_State_t;


/* FSM variables */
ParkingSystem_State_t txState = IDLE; // State register
int statusreg = 0;  //FSM intrreput  signal

int freespace = 1;
char spaceN[7];
String spacebuff ="";

int timeL = 0 ;
String timebuff = "";
char timeLC[7];

int payment  = 0;
String paybuff = "";
char payA[10];

int detection  = 0 ;


/*  We choose FSM as control mechanism of this system, because in FSM we dont need to 
 *  worry about customer mispress some wrong button(Except "Disconnect"),then the system 
 *  get into a unkown situation. Nothing will happen when customer press "pay" before "leave".
 *  Thing only procese in a sequence that we wanted.
 */
void ParkingSystem_state_machine(){
  switch(txState){
    
    case RESERVESend:
        blueToothSerial.print("    Freespace:");
        blueToothSerial.print(freespace);
        blueToothSerial.println("  Counter time after u park in ");
        opendoor();
        txState = RESERVECheck;
        break;
        
     case RESERVECheck:
        detection = digitalRead(4);
        txState = detection !=1 ? RESERVECheck : RESERVEClose; //Goto next state when car parks in
        break;
        
    case RESERVEClose:
        closedoor();
        REG_TC1_CCR1 = 1<<2; //Reset counter register
        TC_Start(XTC,XCHAN); //Begin counting 
        txState = TIMECounting;
        break;
       
    case TIMECounting:
        timeL = double(TC_ReadCV(XTC,XCHAN))/VARIANT_MCK*128;     //Read time from timer counter register
        timebuff ="";
        timebuff += timeL;
        timebuff.toCharArray(timeLC,7);    //Cast it into LCD form.
        
        TFTscreen.text("Time:", 0, 40); //Write on LCD 
        TFTscreen.text(timeLC, 100, 40);
        blueToothSerial.print("    Time:"); //Write on Customer's App
        blueToothSerial.print(timeL);
        blueToothSerial.println("  ");
        
        txState = statusreg != 2 ? TIMECounting : LEAVE; //Goto next state when customer press "leave"
        break;
        
    case LEAVE:
        
        payment = 10*timeL;
        paybuff ="  $";
        paybuff += payment;
        paybuff.toCharArray(payA,10);
        
        TFTscreen.text("payment:", 0, 40);
        TFTscreen.text(payA, 50, 60);
        blueToothSerial.print("    Payment:"); 
        blueToothSerial.println(payA);
        txState =statusreg != 3 ? LEAVE : PAY;
        break;
  
    case PAY:
        
        blueToothSerial.print("       ");
        blueToothSerial.println("Payment procesing");
        blueToothSerial.print("       ");
        blueToothSerial.println("Payment comfired. Good to go.");
        opendoor();
        TFTscreen.text("Thank for.", 0, 40);
        TFTscreen.text("coming.", 60, 60);
        txState = PAYCHECK;
      
        break;
      
    case PAYCHECK: 
        detection = digitalRead(4);
        txState = detection != 0 ? PAYCHECK : PAYCLOSE; 
        break;
        
    case PAYCLOSE:
         blueToothSerial.print("   ");
         blueToothSerial.println("Thank for coming");
         closedoor();
         txState = IDLE;  
         break;
         
    case IDLE:
        blueToothSerial.print("    Freespace: ");
        blueToothSerial.print(freespace);
        blueToothSerial.println("  ");  
        
        Serial.println("IDLE");
        txState = statusreg != 1 ? IDLE : RESERVESend;
        break;
      
    default:
        break;
  }
}


  


void setup()
{
    Serial.begin(9600);

    pmc_set_writeprotect(false);
     
    setupBlueToothConnection(); //Bluetooth 2.0
    //setupBlueToothConnection4(); //Bluetooth 4.0
    
    TFTscreen.begin();
    TFTscreen.background(0, 0, 0);   // clear the screen with a black background
    TFTscreen.stroke(255, 255, 255); // set the font color to white    
    TFTscreen.setTextSize(2);        // set the font size
  
    //Set up timer counter to counte how long does customer parked in.
    pmc_enable_periph_clk(XID);
    TC_Configure(XTC,XCHAN,TC_CMR_WAVE | TC_CMR_WAVSEL_UP_RC | TC_CMR_TCCLKS_TIMER_CLOCK4);

    //Connect digital pin2 to another timer counter to generate a square wave 
    unsigned int chanmask = (1 << PINCHAN);
    REG_PIOB_PDR = chanmask;
    REG_PIOB_ABSR = chanmask;
    REG_PIOB_MDDR = chanmask;
    squarewave(36000);

    //Setup for IR sensor
    pinMode(4,INPUT);
}

void loop()
{
    String recvStr;
    String sendStr;
    
    
    while(1){
        if(blueToothSerial.available()){
          //check if there's any data sent from the remote bluetooth shield
            recvStr = blueToothSerial.readStringUntil(',');
            Serial.println(recvStr);
            //Change the interrput signal  when customer press a button 
            if(recvStr =="reserve"){
              freespace -= 1;
              statusreg =1;
            }
            
            if(recvStr == "leave"){
              statusreg = 2;
            }
            
            if(recvStr == "pay"){
              freespace += 1;
              statusreg = 3 ;
            }
            
            
        }
        if(Serial.available()){ //For admin to send some message to customer
          sendStr = Serial.readString();
          blueToothSerial.print("");
          blueToothSerial.println(sendStr);
        }

        TFTscreen.stroke(255, 255, 255);
        
        spacebuff ="";                     
        spacebuff += freespace;
        spacebuff.toCharArray(spaceN,7);
        TFTscreen.text("Freespace:", 0, 20);  //keep on showing free spaces on LCD
        TFTscreen.text(spaceN, 120, 20);

        ParkingSystem_state_machine(); //Call the FSM
        delay(1000);
       
        TFTscreen.background(0,0,0);
        // erase the text you just wrote
        TFTscreen.stroke(0, 0, 0);
    }
}

/*
 * Bluetooth 2.0 setup  
 */
void setupBlueToothConnection(){
    blueToothSerial.begin(38400);                           // Set BluetoothBee BaudRate to default baud rate 38400
    blueToothSerial.print("\r\n+STWMOD=0\r\n");             // set the bluetooth work in slave mode
    blueToothSerial.print("\r\n+STNA=ProjectDemo\r\n");    // set the bluetooth name as "SeeedBTSlave"
    blueToothSerial.print("\r\n+STOAUT=1\r\n");             // Permit Paired device to connect me
    blueToothSerial.print("\r\n+STAUTO=0\r\n");             // Auto-connection should be forbidden here
    delay(2000);                                            // This delay is required.
    blueToothSerial.print("\r\n+INQ=1\r\n");                // make the slave bluetooth inquirable
    Serial.println("The slave bluetooth is inquirable!");
    delay(2000);                                            // This delay is required.
    blueToothSerial.flush();
}


/*
 * Bluetooth 4.0 setup (AT mode)
 */
void setupBlueToothConnection4(){
    blueToothSerial.begin(38400);                           // Set BluetoothBee BaudRate to default baud rate 38400
    blueToothSerial.print("AT+ROLE=0");                     //slave mode
    blueToothSerial.print("AT+BAUD8");
    blueToothSerial.print("AT+PIN1234");                    //set pin 1234
    blueToothSerial.print("AT+NAMEBT4");                     // set the bluetooth name as "BT4"
    delay(2000);                                            // This delay is required.
    blueToothSerial.flush();
  
}


/*This function is control servo motor turn backward by half second to open the gate.
 * 
 */
void opendoor(){   
  myservo.attach(12);  //Motor is connected with digital pin 12
  myservo.write(120);  //Turn backward
  delay(500);
  myservo.write(90);  //Stop the motor
}

/*This function is control servo motor turn forward by half second to open the gate.
 * 
 */
void closedoor(){
  myservo.attach(12);
  myservo.write(30);  
  delay(500);
  myservo.write(90);
}

/* This function is to generate a certain frequency squarewave signal by using timer counter.
 *     _ _ _ _         _ _ _ _
 *    |       |       |       |
 * ___|       |_______|       |__
 *    
 *    |<tcclk>|                      tcclk = Time frequency/desired frequency
 *                                   Beacuase CLOCK1 = MCK/2, and square wave only on for half cycle.
 *                                   tcclk = (MCK/2)/freq/2
 *                                   
 *                                   TC_CMR_WAVE: waveform mode on 
 *                                   TC_CMR_WAVSEL_UP_RC: UP mode with automatic trigger on RC Compare
 *                                   TC_CMR_TCCLKS_TIMER_CLOCK1: Time frequency = MCK/2
 *                                   TC_CMR_ACPC_TOGGLE: RC compare effect on TIO
 */
void squarewave(unsigned int freq) {
  pmc_enable_periph_clk(XID1);
  unsigned int  tcclk = VARIANT_MCK / freq / 4;     
  TC_Configure(XTC1, XCHAN1, TC_CMR_WAVE | TC_CMR_WAVSEL_UP_RC | TC_CMR_TCCLKS_TIMER_CLOCK1 | TC_CMR_ACPC_TOGGLE);
  TC_SetRC(XTC1, XCHAN1, tcclk);
  TC_Start(XTC1, XCHAN1);
}

