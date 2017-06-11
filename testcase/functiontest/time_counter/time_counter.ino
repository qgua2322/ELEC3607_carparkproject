#define  XTC    TC1       // TC number
#define  XCHAN  1         // TC channel
#define  XID    ID_TC4    // Instance ID
double timeL = 0;
void setup(){
   Serial.begin(9600);
    pmc_set_writeprotect(false);
    pmc_enable_periph_clk(XID);
    TC_Configure(XTC, XCHAN, TC_CMR_WAVE | TC_CMR_WAVSEL_UP_RC | TC_CMR_TCCLKS_TIMER_CLOCK4);
    TC_Start(XTC, XCHAN);
  }
  void loop(){
       TC_Start(XTC, XCHAN);
       REG_TC1_CCR1 = 1<<2 ; 
       sprint("HELLO\n");
       timeL = double(TC_ReadCV(XTC, XCHAN))/VARIANT_MCK*128*1000000;
       Serial.println(timeL,DEC);
       TC_Start(XTC, XCHAN);
       REG_TC1_CCR1 = 1<<2 ;
       fprint(1.2);
       timeL = double(TC_ReadCV(XTC, XCHAN))/VARIANT_MCK*128*1000000;
       Serial.println(timeL,DEC);
       
  }

  void sprint(char *s) {
      Serial.print(s);
    }
    
    void fprint(double f) {
      Serial.println(f);
    }
