//----------------------------------------------------------------//
//
// SAIC Biological Communications SP24
// Brett Ian Balogh
//
//
// firefly.ino
//
// Firefly simulation
//
//----------------------------------------------------------------//

// Include libraries for TFT
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7789.h>

#define FIREFLY_PIN 5
#define PHOTOCELL_PIN 18
#define NOISE_PIN 17
#define LED_PIN 13
#define BUFLEN 2

// Create a TFT object
Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_RST);

// 'firefly', 240x135px
const unsigned char epd_bitmap_firefly [] PROGMEM = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x3e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x3e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1e, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1e, 0x00, 0x00, 
	0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0e, 0x00, 0x00, 0x00, 0x03, 
	0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0e, 0x00, 0x00, 0x00, 0x03, 0x80, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00, 0x03, 0xc0, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00, 0x01, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x78, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x01, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf8, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x78, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 
	0x80, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x70, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x80, 0x00, 
	0x00, 0x00, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x80, 0x00, 0x00, 0x00, 
	0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xc0, 0x00, 0x00, 0x00, 0xc0, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3e, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xc0, 0x00, 0x00, 0x00, 0xc0, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3f, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xc0, 0x00, 0x00, 0x06, 0xc0, 0x00, 0x00, 0x10, 0xf8, 0x80, 
	0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x07, 0x80, 0x00, 0x00, 0x3f, 0xc0, 0x00, 0x00, 0x3f, 0xff, 0xf9, 0xc0, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x3c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x0f, 0x80, 0x00, 0x02, 0xff, 0x80, 0x00, 0x00, 0x7f, 0xff, 0xff, 0x80, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 
	0x80, 0x00, 0x3f, 0xff, 0x80, 0x00, 0x03, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x07, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1b, 0x80, 0x00, 
	0x7f, 0xff, 0x00, 0x00, 0x07, 0xe0, 0x3f, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x37, 0x80, 0x00, 0xff, 0xfe, 
	0x00, 0x00, 0x07, 0xe0, 0x03, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x6f, 0x00, 0x01, 0xc0, 0x00, 0x00, 0x00, 
	0x0f, 0xe0, 0x00, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xcf, 0x00, 0x01, 0x80, 0x00, 0x00, 0x00, 0x1f, 0xc0, 
	0x00, 0x3c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1e, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x03, 0x1e, 0x00, 0x03, 0x80, 0x00, 0x00, 0x00, 0x1f, 0xc0, 0x00, 0x0c, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x0e, 0x7c, 0x00, 0x0f, 0x80, 0x00, 0x00, 0x00, 0x3f, 0xc0, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x3f, 0xfc, 0x00, 0x0f, 0xc0, 0x00, 0x00, 0x00, 0x3f, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x01, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xf8, 
	0x00, 0x07, 0xe0, 0x00, 0x00, 0x00, 0x7f, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xe0, 0x00, 0x07, 
	0xe0, 0x00, 0x00, 0x00, 0x3f, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xdc, 0x00, 0x00, 0x00, 0x70, 0x5e, 
	0x07, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0c, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfc, 0x00, 0x00, 0x70, 0x00, 0x00, 0x0c, 0x48, 
	0x80, 0x00, 0x7c, 0x78, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7e, 0x00, 0x06, 0x72, 0x19, 0xf9, 0xfc, 0xff, 0xf0, 0x00, 
	0x01, 0x3c, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x80, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x7f, 0x00, 0x3f, 0x07, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfb, 0xff, 0x59, 
	0xe7, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x6e, 0x00, 0x7f, 0x87, 0xdf, 0x7f, 0xff, 0xff, 0xbe, 0x77, 0xff, 0xff, 0xff, 0xf8, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7f, 
	0x66, 0x00, 0xfe, 0x3f, 0xbf, 0xff, 0xdf, 0xff, 0x27, 0x06, 0xe0, 0xfd, 0xff, 0xf8, 0x18, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x70, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xe1, 0x00, 0x91, 
	0xf4, 0x1f, 0x27, 0xff, 0xff, 0xff, 0xeb, 0x8e, 0xc4, 0xbf, 0xff, 0xff, 0xc0, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x38, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x53, 0xfd, 0x99, 
	0x7f, 0xff, 0xff, 0xff, 0xfe, 0x7f, 0xfc, 0x3b, 0xff, 0xff, 0xfc, 0x60, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x0c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x60, 0x00, 0x00, 0x43, 0xdf, 0xe1, 0xff, 0xff, 
	0xff, 0xfe, 0xff, 0xff, 0xff, 0xfb, 0xff, 0xff, 0xff, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x90, 0x00, 0x00, 0x93, 0xc7, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x80, 
	0x00, 0x00, 0x00, 0x03, 0x20, 0x1e, 0x00, 0x33, 0x87, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xc0, 0x00, 0x00, 
	0x00, 0x34, 0x86, 0xf7, 0x90, 0x23, 0x9f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xdb, 
	0xff, 0xff, 0xff, 0xff, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe4, 0x00, 0x00, 0x00, 0xfd, 
	0x33, 0xf3, 0x1c, 0x67, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x34, 0x00, 0x00, 0x07, 0xff, 0x3f, 0xfd, 
	0xbc, 0x3f, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1e, 0x00, 0x00, 0x0f, 0xb0, 0xcd, 0xa4, 0x1e, 0x3f, 
	0x3f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x80, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x80, 0x00, 0x1f, 0xb0, 0x1a, 0x60, 0x0e, 0x1f, 0x3f, 0xf0, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc0, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x01, 0xe0, 0x00, 0x3f, 0x60, 0x18, 0xc1, 0x0e, 0x1f, 0xbf, 0xe3, 0xdf, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xe0, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0xf0, 0x00, 0x3f, 0xc0, 0x3d, 0x80, 0x06, 0x1d, 0xff, 0xc2, 0xdf, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x3a, 0x00, 0x2f, 0x80, 0x3d, 0xe1, 0x00, 0x09, 0xff, 0x98, 0xff, 0xff, 0xff, 0xff, 0xff, 0xed, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0x00, 
	0x27, 0x07, 0x3f, 0xf0, 0x03, 0x1b, 0xff, 0xcc, 0x37, 0xff, 0xff, 0xe6, 0xff, 0xd9, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xc0, 0x37, 0x1f, 
	0x7f, 0xfc, 0x01, 0x1f, 0x9f, 0x4c, 0x7f, 0xfb, 0xff, 0x4f, 0xff, 0xdf, 0xf3, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xe0, 0x38, 0x3f, 0x7f, 0xff, 
	0x93, 0x1e, 0x9f, 0xe4, 0x07, 0x7e, 0x69, 0xcf, 0xfe, 0x67, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xce, 0x7e, 0x7e, 0xff, 0xff, 0xc3, 0x1c, 
	0xe3, 0xc4, 0x03, 0x9c, 0x11, 0xec, 0x79, 0x37, 0xdf, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x77, 0xf9, 0x3f, 0xb7, 0xff, 0xfe, 0x79, 0xf3, 0x8e, 
	0xf8, 0xdb, 0xc3, 0x77, 0xfb, 0x38, 0xc9, 0x62, 0x73, 0xbf, 0xff, 0xff, 0xff, 0xfc, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x37, 0xf0, 0xbf, 0xef, 0xff, 0xf2, 0x7b, 0xfe, 0x26, 0xe8, 0x7d, 
	0xe3, 0xf3, 0x8c, 0x11, 0x8d, 0xbb, 0x6f, 0xfd, 0xff, 0xff, 0xff, 0xe8, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x03, 0xf0, 0xff, 0xff, 0xfe, 0x39, 0x61, 0xdf, 0xff, 0xff, 0x9f, 0xec, 0xf0, 
	0xc1, 0x80, 0x1e, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0xf1, 0x7f, 0xff, 0xbf, 0x18, 0x61, 0x93, 0xdb, 0xff, 0xff, 0xff, 0x98, 0x23, 0x00, 
	0x11, 0xcc, 0x99, 0x9c, 0xc0, 0x1f, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x71, 0xff, 0xbf, 0xff, 0xfc, 0x77, 0x03, 0xe8, 0x38, 0x58, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 
	0x00, 0x00, 0x00, 0x00, 0x04, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x67, 0xff, 
	0x9f, 0xff, 0xff, 0x33, 0x33, 0xe4, 0x00, 0x01, 0x18, 0x0f, 0xff, 0xff, 0xff, 0xfd, 0xf7, 0x9f, 
	0xff, 0xff, 0xff, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfd, 0xff, 0xcf, 0xfe, 
	0x19, 0x27, 0x07, 0x07, 0xb7, 0xe1, 0xbf, 0xff, 0xf0, 0x00, 0x00, 0x00, 0x1d, 0xdc, 0x18, 0x00, 
	0x0f, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfc, 0xff, 0xef, 0xf8, 0x18, 0x41, 
	0xc3, 0x7f, 0x30, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xf0, 0xff, 0xe7, 0xa0, 0x90, 0x07, 0xf7, 0xfe, 
	0x3f, 0xff, 0xe0, 0x7f, 0x0d, 0x70, 0xe2, 0x6c, 0x23, 0xa7, 0x27, 0xf8, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xb0, 0xff, 0xf7, 0xff, 0x21, 0x3f, 0xff, 0xf0, 0xff, 0x6c, 
	0x62, 0x43, 0x3b, 0x5a, 0x10, 0x79, 0x03, 0x67, 0x1f, 0xff, 0xdf, 0xc0, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0xf7, 0xb0, 0x67, 0xf7, 0xff, 0x03, 0x3f, 0xff, 0xc3, 0x69, 0x45, 0x00, 0x01, 
	0xb3, 0x6e, 0x01, 0xff, 0x1f, 0xf9, 0xd3, 0xff, 0xff, 0xc4, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x04, 0xfc, 0xf2, 0x6f, 0xd3, 0xff, 0x02, 0x3f, 0xff, 0xc0, 0x01, 0x86, 0x90, 0x00, 0x37, 0xff, 
	0xa7, 0xff, 0x7f, 0xff, 0xe7, 0xff, 0xff, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1c, 0xc8, 
	0x3a, 0x73, 0xff, 0xf9, 0x8c, 0x5f, 0xdf, 0x80, 0x01, 0xde, 0xb7, 0xff, 0xff, 0xdf, 0x7b, 0xff, 
	0xff, 0xff, 0xbf, 0xff, 0xff, 0x7f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7c, 0x80, 0x3b, 0x35, 
	0xff, 0xe7, 0x8e, 0x17, 0xdf, 0x80, 0x01, 0xdf, 0xf7, 0x7f, 0xff, 0xff, 0xff, 0xfd, 0xff, 0xff, 
	0x9f, 0xff, 0xff, 0xf2, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x70, 0x00, 0x3f, 0x1f, 0xf3, 0xe7, 
	0xba, 0x3f, 0x8f, 0x00, 0x01, 0xbf, 0xff, 0x7f, 0xff, 0xff, 0xef, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x60, 0x00, 0x3c, 0x9f, 0xf9, 0x01, 0xae, 0x3f, 
	0x8f, 0x80, 0x31, 0xff, 0xff, 0xff, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0x40, 0x00, 0x36, 0x97, 0xf9, 0x80, 0x1e, 0x7d, 0x9f, 0xc0, 
	0x10, 0xbf, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x1c, 0x00, 0x00, 0x16, 0x60, 0xfb, 0xc0, 0x3e, 0x79, 0x3f, 0x87, 0x3f, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x18, 0x00, 0x00, 0x1b, 0x20, 0xfd, 0xf4, 0x7e, 0x79, 0x3f, 0x9f, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xef, 0x78, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 
	0x00, 0x00, 0x03, 0x91, 0xbd, 0xff, 0xfe, 0x7b, 0x3f, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xdf, 0xff, 0xff, 0x70, 0x00, 0x00, 0x00, 0x00, 0x00, 0x60, 0x00, 0x00, 
	0x07, 0xf0, 0x1e, 0x3f, 0xbe, 0x7f, 0x7f, 0x1c, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xf9, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x00, 0x00, 0x01, 0xfc, 
	0x60, 0x1f, 0xfe, 0x7f, 0xde, 0x37, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xf4, 0x97, 0x80, 0x00, 0x00, 0x00, 0x00, 0x01, 0xc0, 0x00, 0x00, 0x00, 0x0e, 0x00, 0x93, 
	0x80, 0x23, 0xfc, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0xff, 0xff, 0xf3, 
	0x4e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x80, 0x00, 0x00, 0x00, 0x03, 0x84, 0x80, 0x00, 0x03, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xdc, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe1, 0xb8, 0x00, 0x01, 0xfe, 0x7f, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xdf, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x0e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3d, 0xff, 0x80, 0x40, 0xfe, 0xff, 0xff, 0xff, 
	0xff, 0xfe, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x0c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0xc0, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x97, 0x80, 0x67, 0xff, 0xfd, 0xfe, 0xed, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x01, 0xfe, 0x00, 0x0c, 0x1f, 0xfd, 0xae, 0x8f, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0x8c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x48, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x02, 0x3e, 0x00, 0x00, 0x40, 0x19, 0x23, 0x13, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xd1, 
	0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 
	0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xff, 0xff, 0xff, 0xff, 0x81, 0x80, 0x13, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xf0, 0x00, 
	0x00, 0x03, 0xc8, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x92, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x01, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x38, 0x00, 0x00, 0x03, 
	0xd8, 0x00, 0x01, 0x3e, 0xc0, 0x19, 0x34, 0x78, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x01, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3e, 0x00, 0x00, 0x03, 0xf0, 0x00, 
	0x00, 0x00, 0x1f, 0xe0, 0xc8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0xc0, 0x00, 0x03, 0xf0, 0x3f, 0xc0, 0x00, 
	0x0f, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xe0, 0x00, 0x03, 0xe1, 0xff, 0xc0, 0x00, 0x0f, 0xf0, 
	0x00, 0x38, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1c, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x03, 0xf8, 0x00, 0x01, 0xc7, 0xff, 0xc0, 0x00, 0x06, 0xf0, 0x00, 0x70, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x38, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x01, 0xfc, 0x00, 0x07, 0xcf, 0xff, 0xe0, 0x00, 0x06, 0x78, 0x01, 0xfc, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x58, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0xfe, 0x00, 0x0a, 0xff, 0xb0, 0x60, 0x00, 0x03, 0x38, 0x07, 0xfe, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3e, 
	0x00, 0x05, 0xff, 0x80, 0x70, 0x00, 0x01, 0xf8, 0x3e, 0xf7, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x03, 0xa0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x5f, 0x00, 0x01, 
	0xff, 0x00, 0x70, 0x00, 0x00, 0xff, 0xf3, 0xe3, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x10, 0x00, 
	0x78, 0x00, 0x00, 0x3f, 0xb1, 0x81, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0e, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0x80, 0x00, 0x00, 0x00, 0x38, 0x00, 
	0x00, 0x00, 0xfc, 0x01, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xec, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x80, 0x00, 0x00, 0x00, 0x3c, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0xfd, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x80, 0x00, 0x00, 0x00, 0x3c, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0xfc, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x03, 0x80, 0x00, 0x00, 0x00, 0x1e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x78, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x38, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 
	0x00, 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3c, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 
	0x00, 0x00, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0c, 0x00, 0x00, 0x00, 0x00, 
	0x1f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 0x00, 0x0f, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x38, 0x00, 0x00, 0x00, 0x00, 0x1f, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x38, 0x00, 0x00, 0x00, 0x00, 0x1e, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x70, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x01, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xf0, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xe0, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xe0, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00
};

// Array of all bitmaps for convenience. (Total bytes used to store images in PROGMEM = 4080)
const int epd_bitmap_allArray_LEN = 1;
const unsigned char* epd_bitmap_allArray[1] = {
	epd_bitmap_firefly
};


int ambientLight = 0;
int buffer = 0;
int filterBuffer[BUFLEN];

int filteredValue = 0;
// How many values for our screen buffer = screen width
int screenBuffer[240];
// The current reading from ADC
int currentReading = 0;

int minValue = 4000;
int maxValue = 8000;
// How much above ambiwntLight is a flash
int detectThreshold = 100;
// Keep our own flash time
double flashAccumulator = 0;
// When flashAccumulator equals this we flash
//int flashThreshold = 100;
// Phase is periodic over 2pi
double flashThreshold = 6.2832;
// How long do we flash for
int flashDuration = 20;
int pastTime = 0;

// flash interval
int interval = 30;
// Are we blind or not
bool blind = false;
// How long are we blind. Should be at least as long as flashDuration
int blindDuration = 40;
// Keeps track of how long we've been blind
int blindPastTime = 0;

// x1, y1, x2, y2 for tft plotting
int dataRect[] = { 0, 10, 240, 125 };

// how much we advance phase when we see a flash. 2 works well
double nudgeAmount = 1.75;

//----{SETUP}-----------------------------------------------------//

void setup() {

  // Start Serial COM
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
  pinMode(FIREFLY_PIN, OUTPUT);
  
  // initialize filter buffer
  for (int i = 0; i < BUFLEN; i++) {
    filterBuffer[i] = 0;
  }

  // initialize screen buffer
  for (int i = 0; i < 240; i++) {
    screenBuffer[i] = 68;
  }

  // turn on backlite
  pinMode(TFT_BACKLITE, OUTPUT);
  digitalWrite(TFT_BACKLITE, HIGH);

  // turn on the TFT / I2C power supply
  pinMode(TFT_I2C_POWER, OUTPUT);
  digitalWrite(TFT_I2C_POWER, HIGH);
  delay(10);

  // initialize TFT
  tft.init(135, 240);  // Init ST7789 240x135
  tft.setRotation(3);
  tft.fillScreen(ST77XX_BLACK);

  // default text size
  tft.setTextSize(2);

  // set text foreground and background colors
  tft.setTextColor(ST77XX_WHITE, ST77XX_BLACK);

  tft.println(F("TFT Initialized"));
  delay(500);
  tft.fillScreen(ST77XX_BLACK);
  tft.setCursor(0, 0);
  tft.println(F("Calibrating"));

  for (int i = 0; i < 10; i++) {
    tft.print(".");
    buffer += analogRead(PHOTOCELL_PIN);
    delay(200);
  }

  ambientLight = buffer / 10;
  tft.fillScreen(ST77XX_BLACK);
  tft.setCursor(0, 0);
  tft.println(F("Done Calibrating"));
  tft.println("");
  tft.print(F("Ambient Light Level is: "));
  tft.println(ambientLight);

  minValue = ambientLight;

  randomSeed(analogRead(NOISE_PIN));
  tft.println("");
  tft.print("Waiting to start...");
  delay(1000);
  delay(random(10000));

  ///tft.fillScreen(ST77XX_BLACK);
  ///tft.drawLine(0, dataRect[1] - 5, 240, dataRect[1] - 5, ST77XX_GREEN);
  ///tft.drawLine(0, dataRect[3] + 5, 240, dataRect[3] + 5, ST77XX_RED);

  tft.drawBitmap(0, 0, epd_bitmap_firefly, 240, 135, 0xc626, ST77XX_BLACK);
}

//----{LOOP}------------------------------------------------------//

void loop() {

  // If not blind, look for flash
  if (blind == false) {

    // Read the photocell
    currentReading = analogRead(PHOTOCELL_PIN);
    // Formatted print for serial plotter
    //Serial.print(0);
    //Serial.print(",");
    //Serial.print(currentReading - ambientLight);
    //Serial.print(",");
    //Serial.println(1000);
    //Serial.println(currentReading-minValue);

    // Decide if we have detected a flash
    // I think I have to change my approach here...
    // Now trying w + Asin(theta)
    if (currentReading > ambientLight + detectThreshold) {
      digitalWrite(LED_PIN, HIGH);
      delay(10);
      digitalWrite(LED_PIN, LOW);
      double flashPower = -nudgeAmount * sin(flashAccumulator);
      flashPower = constrain(flashPower, 0, 1);
      flashAccumulator += flashPower;
    }
  }

  // Add to the flash accumulator
  if (millis() - pastTime > interval) {

    flashAccumulator += 0.1;
    pastTime = millis();

    // Formatted print for serial plotter
    // Serial.print(0);
    // Serial.print(",");
    // Serial.print(flashAccumulator);
    // Serial.print(",");
    // Serial.println(100);
  }

  // Flash if we have accumulated enough power
  if (flashAccumulator >= flashThreshold) {

    blind = true;
    //Serial.println("Blind");
    digitalWrite(FIREFLY_PIN, HIGH);
    delay(flashDuration);
    digitalWrite(FIREFLY_PIN, LOW);
    flashAccumulator = 0;
    blindPastTime = millis();

  } else {

    digitalWrite(FIREFLY_PIN, LOW);
  }

  if (blind == true) {

    if (millis() - blindPastTime > blindDuration) {
      blind = false;
      //Serial.println("Not Blind");
      blindPastTime = millis();
    }
  }

  // Update stuff
  //updateScreenBuffer(flashAccumulator);
  //updateDisplay();
  
}

//----{DISPLAY}------------------------------------------------------//

void updateDisplay() {

  //tft.fillScreen(ST77XX_BLACK);
  tft.fillRect(dataRect[0], dataRect[1], dataRect[2], dataRect[3], ST77XX_BLACK);
  for (int i = 0; i < 239; i++) {
    //tft.drawPixel(i, screenBuffer[i], ST77XX_WHITE);
    tft.drawLine(i, screenBuffer[i], i + 1, screenBuffer[i + 1], ST77XX_WHITE);
  }
}

//----{FILTER BUFFER}------------------------------------------------------//

int updateFilterBuffer(int val) {

  // shift values in the buffer
  for (int i = 0; i < BUFLEN - 1; i++) {
    filterBuffer[i] = filterBuffer[i + 1];
  }

  filterBuffer[BUFLEN - 1] = val;
  int sum = 0;

  for (int i = 0; i < BUFLEN; i++) {
    sum += filterBuffer[i];
  }

  filteredValue = sum / BUFLEN;
  constrain(filteredValue, 0, maxValue);
  return filteredValue;
}

//----{SCREEN BUFFER}------------------------------------------------------//

void updateScreenBuffer(double val) {

  for (int i = 0; i < 239; i++) {
    screenBuffer[i] = screenBuffer[i + 1];
    //tft.drawPixel(i, screenBuffer[i], ST77XX_WHITE);
  }

  //int mappedValue = map(val, minValue, maxValue, 125, 10);
  int mappedValue = map(val*10, 0, 64, dataRect[3], dataRect[1]);

  screenBuffer[239] = mappedValue;
}

//----{END}------------------------------------------------------//