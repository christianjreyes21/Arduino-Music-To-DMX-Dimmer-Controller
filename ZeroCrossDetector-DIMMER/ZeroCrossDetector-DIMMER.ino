#include <TimerOne.h>

volatile int count;
volatile boolean ZeroCross;
const int ACfrequency = 60;
volatile int dimvalue[5];
volatile int dataupdate[28];
int ch[5]={4,5,6,7,8};

void setup()
{
  
  for(int i=0; i<5; i++)
  {
    pinMode(ch[i],OUTPUT);
    digitalWrite(ch[i],LOW);
  }
  
  Serial1.begin(250000);
  attachInterrupt(0,ZeroCrossDetection,FALLING);
  Timer1.initialize (ACfrequency);
  Timer1.attachInterrupt (Activate,ACfrequency);
}

void ZeroCrossDetection()
{
  ZeroCross = 1;
}

void Activate()
{
  if(ZeroCross == 1)
  {
    
    for(int i=0; i < 5; i++)
    {
      if(count >= dimvalue[i])
      {
        digitalWrite (ch[i] , HIGH);
        
      
      }
    }
      
      count++;
      if(count >= 128)
      {
        
        count = 0;
        ZeroCross = 0;
        for(int x=0; x<5; x++)
        {
          digitalWrite(ch[x],LOW);
        }
        
      }
      
      
    
  }
}

void loop()
{
  if(Serial1.available() >= 28)
  {
    
    for(int i = 0; i < 28; i++)
    {
      dataupdate[i] = Serial1.read();
    }
  
    
    for(int i = 0; i < 5; i++) 
    {
      dimvalue[i] = map(dataupdate[i],0,255,128,0);
    }
}
}    
