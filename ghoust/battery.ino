

// TODO: tst battery levels with powersupply to find correct values here.

int BATTERYLOW_THRESHOLD =500;


void battery_setup()
{
   
  
  Serial.println("battery_setup()");

  pinMode(A0,INPUT);

  battery_check();

  
}


void battery_check()
{
 int battery_level =0; 



 //TODO!!!
 // analogRead() breaks something so MQTT gets disconnected.
 // this might be a hardware issue due to wrong voltage divider values or something..
 
 battery_level = 501;//analogRead(A0);

  
 //Serial.print("battery: ");
 //Serial.println(battery_level);
 
 if(battery_level<BATTERYLOW_THRESHOLD)
 {


   // stay in here forever
   while(true){
       beep_fail();
         

       for(int i=0;i<5;i++)
       {
         set_led(10,0,0);
         delay(400);
         set_led(0,0,0);
         delay(200);
       }   
    }
 }

  
}

