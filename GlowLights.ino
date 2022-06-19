
#include <FastLED.h>
#include <time.h>
#define NUM_LEDS 60 // number of LEDs
#define LED_DT 12   // your data pin (DI)
#define COLOR_ORDER GRB
#define LED_TYPE WS2812
// #define CLOCK_PIN 7  // your clock pin (CI/CLK)
int InBytes;
uint8_t max_bright = 80;
uint8_t paletteIndex = 0;
struct CRGB leds[NUM_LEDS];

//Happy Lights
DEFINE_GRADIENT_PALETTE (Sunset_Real_gp) {
    0,   120,   0,   0,   
   22,   179,  22,   0,   
   51,   255, 104,   0,   
   85,   167,  22,  18,
  135,   100,   0, 103,
  198,    16,   0, 130,
  255,     0,   0, 160  
};
CRGBPalette16 HappyPal = Sunset_Real_gp;

//Sad Lights
CRGBPalette16 SadPal = CRGBPalette16{
    CRGB::DarkViolet,
    CRGB::DarkViolet,
    CRGB::DarkViolet,
    CRGB::DarkViolet,
    
    CRGB::Magenta,
    CRGB::Magenta,
    CRGB::Linen,
    CRGB::Linen,
    
    CRGB::Magenta,
    CRGB::Magenta,
    CRGB::DarkViolet,
    CRGB::DarkViolet,

    CRGB::DarkViolet,
    CRGB::DarkViolet,
    CRGB::Linen,
    CRGB::Linen
};

void setup() 
{
  Serial.begin(9600);
  delay(1000);
  FastLED.addLeds<LED_TYPE, LED_DT, COLOR_ORDER>(leds, NUM_LEDS);
  FastLED.setBrightness(max_bright);
  FastLED.clear();
}

void loop()
{
  long int begin, end;
  if (Serial.available()>0)
  {
    InBytes = Serial.read();
    if (InBytes == '0')
    {
      //Change Lights for Happy Mood
      begin = millis();
      while(1)
      {
        fill_palette(leds, NUM_LEDS, paletteIndex, 255/NUM_LEDS, HappyPal, 255, LINEARBLEND);
        EVERY_N_MILLISECONDS(5)
        {
          paletteIndex++;
        }
        FastLED.show();
        end = millis();
        Serial.print(end);
        
        if (((end-begin)/1000)==100)
        {
          break;
        }
      }
      Serial.write("Happy Done");
    }
    
    if (InBytes == '1')
    {
      begin = millis();
      while(1)
      {
        fill_palette(leds, NUM_LEDS, paletteIndex, 255/NUM_LEDS, SadPal, 255, LINEARBLEND);
        EVERY_N_MILLISECONDS(25)
        {
          paletteIndex++;
        }
        FastLED.show();
        end = millis();
        Serial.print(end);
        
        if (((end-begin)/1000)==100)
        {
          break;
        }
      }
        
      Serial.write("Sad Done");
    }
  }
}
