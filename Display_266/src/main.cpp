//E-Paper Display for Cooling Device Metrics

// #include <GxEPD2_3C.h> //includes Epaper library

#include <GxEPD2_BW.h> //includes Epaper library
GxEPD2_BW<GxEPD2_266_BN, GxEPD2_266_BN::HEIGHT> display(GxEPD2_266_BN(/*CS=D8*/ 10, /*DC=D3*/ 9, /*RST=D4*/ 8, /*BUSY=D2*/ 7)); // DEPG0213BN 122x250, SSD1680, TTGO T5 V2.4.1, V2.3.1
// GxEPD2_BW<GxEPD2_213_BN, GxEPD2_213_BN::HEIGHT> display(GxEPD2_213_BN(/*CS=D8*/ 10, /*DC=D3*/ 9, /*RST=D4*/ 8, /*BUSY=D2*/ 7)); // DEPG0213BN 122x250, SSD1680, TTGO T5 V2.4.1, V2.3.1

#include <Fonts/FreeMonoBold9pt7b.h> //includes font gfx
#include "imagedata.h" //includes image data
void wifi_connection(const char *signal);
void status(const char *stat);
void light(const char *l);
void mode(const char *m);
void print_device_name(const char *text);
void getInput();



void setup() {
  Serial.begin(115200);
  display.init(115200, true, 2, false);
  display.setRotation(1); //set the rotation of the screen
  wifi_connection("disconnected"); //draw the basic icons
  status("good");
  light("dark");
  mode("eco");
  print_device_name("Ted");
  display.display(); //display the icons
  delay(1000); //1sec wait
}

void loop() {
  if (Serial.available() > 0) {
    getInput(); //get the input data
  }
}

//wifi connection icon: 
//if input was "C: connected" -> wifi icon
//if input was different -> no wifi icon
void wifi_connection(const char *signal) {
  String connected_compare = "connected"; //creating a String "connected" to be able to compare it with the input data (input is a String)
  if (signal == connected_compare) {
    display.fillRoundRect(127, 8, 55.5, 32.6, 10, GxEPD_WHITE); //draw a filled round rectangle
    display.drawBitmap(143, 12, gImage_c_bmp_wifi_c, 25, 25, GxEPD_BLACK); //draw the wifi icon inside
  }
  else {
    display.fillRoundRect(127, 8, 55.5, 32.6, 10, GxEPD_BLACK); //draw a filled round rectangle
    display.drawRoundRect(127, 8, 55.5, 32.6, 10, GxEPD_WHITE); //draw a white border around the rectangle
    display.drawBitmap(143, 12, gImage_c_nowifi, 25, 25, GxEPD_WHITE); //draw the no wifi icon inside
  }
}

//status icon: 
//if input was "S: good" -> like icon
//if input was different -> dislike icon
void status(const char *stat) {
  String good_compare = "good"; //creating a String "good" to be able to compare it with the input data
  if (stat == good_compare) {
    display.fillRoundRect(127, 44.6, 55.5, 32.6, 10, GxEPD_WHITE);
    display.drawBitmap(143, 47.6, gImage_c_like, 25, 25, GxEPD_BLACK); 
  }
  else {
    display.fillRoundRect(127, 44.6, 55.5, 32.6, 10, GxEPD_BLACK);
    display.drawRoundRect(127, 44.6, 55.5, 32.6, 10, GxEPD_WHITE);
    display.drawBitmap(143, 47.6, gImage_c_dislike, 25, 25, GxEPD_WHITE);
  }
}

//light icon: 
//if input was "L: light" -> sun icon
//if input was different -> moon icon
void light(const char *l) {
  String light_compare = "light";
  if (l == light_compare) {
    display.fillRoundRect(186.5, 8, 55.5, 51, 10, GxEPD_WHITE);
    display.drawBitmap(196, 16, gImage_c_light, 35, 35, GxEPD_BLACK); 
  }
  else {
    display.fillRoundRect(186.5, 8, 55.5, 51, 10, GxEPD_BLACK);
    display.drawRoundRect(186.5, 8, 55.5, 51, 10, GxEPD_WHITE);
    display.drawBitmap(196, 16, gImage_c_dark, 35, 35, GxEPD_WHITE);
  }
}

//mode icon: 
//if input was "M: on" -> check icon
//if input was "M: off" -> cross icon
//if input was "M: eco" -> leaves icon
void mode(const char *m) {
  String off_compare = "off";
  String on_compare = "on";
  String eco_compare = "eco";
  if (m == off_compare) {
    display.fillRoundRect(186.5, 63, 55.5, 51, 10, GxEPD_BLACK);
    display.drawRoundRect(186.5, 63, 55.5, 51, 10, GxEPD_WHITE);
    display.drawBitmap(196, 71, gImage_c_off, 35, 35, GxEPD_WHITE); 
  }
  else if (m == on_compare) {
    display.fillRoundRect(186.5, 63, 55.5, 51, 10, GxEPD_WHITE);
    display.drawBitmap(196, 72, gImage_c_on, 35, 35, GxEPD_BLACK);
  }
  else if (m == eco_compare) {
    display.fillRoundRect(186.5, 63, 55.5, 51, 10, GxEPD_WHITE);
    display.drawBitmap(196, 72, gImage_c_eco, 35, 35, GxEPD_BLACK);
  }
}

//drawing text function
void drawtext(int x, int y, const char *text, uint16_t color, const GFXfont *f, int size) {
  display.setCursor(x, y);
  display.setTextColor(color);
  display.setFont(f);
  display.setTextSize(size);
  display.print(text);
}

//show temperature function
void show_temperature(const char *t) {
  display.fillRoundRect(8, 8, 115, 106, 10, GxEPD_WHITE);
  display.drawCircle(90, 20, 4, GxEPD_BLACK);
  drawtext(100, 20, "C", GxEPD_BLACK, NULL, 2);
  drawtext(15, 54, t, GxEPD_BLACK, NULL, 7);
}

//prints name of the device
void print_device_name(const char *text) {
  display.fillRoundRect(127, 81.2, 55.5, 32.6, 10, GxEPD_WHITE);
  drawtext(137, 90, text, GxEPD_BLACK, NULL, 2);
}

//draws three rectangles - isn't used, demonstrates the drawing of rectangles
void draw_3_rectangles() {
  display.fillRoundRect(127, 8, 55.5, 32.6, 10, GxEPD_WHITE);
  display.fillRoundRect(127, 44.6, 55.5, 32.6, 10, GxEPD_BLACK);
  display.drawRoundRect(127, 44.6, 55.5, 32.6, 10, GxEPD_WHITE);
  display.fillRoundRect(127, 81.2, 55.5, 32.6, 10, GxEPD_WHITE);
}

void draw_2_rectangles() {
  display.fillRoundRect(186.5, 8, 55.5, 51, 10, GxEPD_WHITE);
  display.drawRoundRect(186.5, 63, 55.5, 51, 10, GxEPD_WHITE);
}

//high temperature warning message + the temperature is shown in the middle rectangle
void warning(const char *t) {
  display.fillRoundRect(8, 8, 115, 106, 10, GxEPD_BLACK);
  display.drawRoundRect(8, 8, 115, 106, 10, GxEPD_WHITE);
  drawtext(16, 28, "Error:", GxEPD_WHITE, NULL, 2);
  drawtext(16, 48, "High Temperature:", GxEPD_WHITE, NULL, 1);
  drawtext(16, 58, "Check the", GxEPD_WHITE, NULL, 1);
  drawtext(16, 68, "requirements!", GxEPD_WHITE, NULL, 1);
  display.fillRoundRect(127, 44.6, 55.5, 32.6, 10, GxEPD_BLACK);
  display.drawRoundRect(127, 44.6, 55.5, 32.6, 10, GxEPD_WHITE);
  drawtext(137, 54, t, GxEPD_WHITE, NULL, 2);
  display.drawCircle(166, 50, 2, GxEPD_WHITE);
  drawtext(171, 50, "C", GxEPD_WHITE, NULL, 1);
}

//main function, gets input, calls functions for drawing icons based on the input
void getInput() {

  //logic for defining the b character in order to switch between cases
  String a = Serial.readStringUntil('\n');
  char b = a[0];
  a.remove(0, 3);
  int a_len = a.length() + 1; 
  char data[a_len];
  a.toCharArray(data, a_len);

  switch (b) {
  case 'C':
    wifi_connection(data); 
    display.display();  
    break;
  case 'S':
    status(data); 
    display.display();
    break;
  case 'L':
    light(data);
    display.display();
    break;
  case 'M':
    mode(data);
    display.display();
    break;
  case 'T':
    show_temperature(data);
    display.display();
    break;
  case 'W':
    warning(data);
    display.display();
    break;
  case '?':
    Serial.println("Setting Parameters for a Cooling Device on the E-Paper Display");
    Serial.println();
    Serial.println("For temperature setting, use 'T: ' followed by the temperature (with a space between the number and the colon)."); 
    Serial.println("For wifi connection status, use 'C: ' followed by either 'connected' or 'disconnected'."); 
    Serial.println("For general status, use 'S: ' followed by 'good' or 'bad'."); 
    Serial.println("To adjust brightness, use 'L: ' followed by 'light' or 'dark'."); 
    Serial.println("For mode selection, use 'M: ' followed by 'on', 'off', or 'eco'."); 
    Serial.println("To issue HighTemperatureError warning, use 'W: ' followed by the temperature."); 
    break;
  }
}