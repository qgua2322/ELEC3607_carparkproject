#define  XTC    TC0       // TC number
#define  XCHAN  0         // TC channel
#define  XID    ID_TC0    // Instance ID
#define  PIN    2
#define  PINCHAN  25      // Digital pin 2 which is on PIOB channel 25

void setup() {
  Serial.begin(9600);
  
  unsigned int chanmask = (1 << PINCHAN);
      
  // set PIO to chan A
  REG_PIOB_PDR = chanmask;
  REG_PIOB_ABSR = chanmask;
  REG_PIOB_MDDR = chanmask;
  
  // set up TC
  pmc_set_writeprotect(false);
  pmc_enable_periph_clk(XID);
  squarewave(36000);
 
  pinMode(4,INPUT);

}

void loop() {
  int detection =  digitalRead(4);
  Serial.println(detection);
  delay(10);
}





void pwmwave(unsigned int duty, unsigned int freq) {
  unsigned int tcclk = VARIANT_MCK/freq/2;
  TC_Configure(XTC,XCHAN,TC_CMR_WAVE |TC_CMR_WAVSEL_UP_RC |TC_CMR_TCCLKS_TIMER_CLOCK1|TC_CMR_ACPC_CLEAR| TC_CMR_ACPA_SET);
  TC_SetRC(XTC,XCHAN,tcclk);
  TC_SetRA(XTC,XCHAN,tcclk/100*(100-duty));
  TC_Start(XTC,XCHAN);
}

void squarewave(unsigned int freq) {
  unsigned int  tcclk = VARIANT_MCK / freq / 4;
  
  TC_Configure(XTC, XCHAN, TC_CMR_WAVE | TC_CMR_WAVSEL_UP_RC | TC_CMR_TCCLKS_TIMER_CLOCK1 | TC_CMR_ACPC_TOGGLE);
  TC_SetRC(XTC, XCHAN, tcclk);
  TC_Start(XTC, XCHAN);
}



