#include "arduinoFFT.h"
 
#define SAMPLES 128             //Must be a power of 2
#define SAMPLING_FREQUENCY 2000 //Hz, must be less than 10000 due to ADC
arduinoFFT FFT = arduinoFFT();
 
unsigned int sampling_period_us;
unsigned long microseconds;
int ledPin = 13;
int ledPin2 = 12;
int ledPin3 = 7;  
double vReal[SAMPLES];
double vImag[SAMPLES];
const int a = A0;
void setup() {
    Serial.begin(115200);
 
    sampling_period_us = round(1000000*(1.0/a));
}
 
void loop() {
   
    /*SAMPLING*/
    for(int i=0; i<SAMPLES; i++)
    {
        microseconds = micros();  
       
        vReal[i] = analogRead(0);
        vImag[i] = 0;
     
        while(micros() < (microseconds + sampling_period_us)){
        }
    }
    /*FFT*/
    FFT.Windowing(vReal, SAMPLES, FFT_WIN_TYP_HAMMING, FFT_FORWARD);
    FFT.Compute(vReal, vImag, SAMPLES, FFT_FORWARD);
    FFT.ComplexToMagnitude(vReal, vImag, SAMPLES);
    double peak = FFT.MajorPeak(vReal, SAMPLES, SAMPLING_FREQUENCY);
    /*PRINT RESULTS*/
    Serial.println(peak);   //prints dominant frequency
    delay(1000);  
    if(peak <= 549 && peak >= 551){
      digitalWrite(ledPin, HIGH);
      } else {
        digitalWrite(ledPin, LOW);
        }
     if(peak <=  999 && peak >= 1001){
      digitalWrite(ledPin2, HIGH);
      } else {
        digitalWrite(ledPin2, LOW);
        }
      if(peak <=  699 && peak >= 701){
      digitalWrite(ledPin3, HIGH);
      } else {
        digitalWrite(ledPin3, LOW);
        }
    //while(1);       //Run code once
}
