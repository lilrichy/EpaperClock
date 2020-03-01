/*
 Name:		EpaperClock.ino
 Created:	2/29/2020 7:24:48 PM
 Author:	richa
*/

#include <gfxfont.h>
#include <Adafruit_GFX.h>
#include <Fonts/FreeSansBold24pt7b.h>
#include <GxEPD2_GFX.h>
#include <GxEPD2_BW.h>
#include <ESP8266WiFi.h> 
#include <time.h>

GxEPD2_BW < GxEPD2_750_T7, GxEPD2_750_T7::HEIGHT / 2 > display(GxEPD2_750_T7(/*CS=15*/ 15, /*DC=4*/ 4, /*RST=5*/ 5, /*BUSY=16*/ 16)); // GDEW075T7 800x480

const char* ssid = "LiLRichyNetz";
const char* password = "Monster1984";

void setup() {
	Serial.begin(115200);

	//Screen Init
	Serial.println("Starting screen...");
	display.init(115200);
	display.setRotation(4);
	display.setFont(&FreeSansBold24pt7b);
	display.setTextColor(GxEPD_BLACK);
	display.firstPage();
	do {
		display.fillScreen(GxEPD_WHITE);
		display.setCursor(225, 200);
		display.print("E-Paper Clock");
		display.setCursor(225, 300);
		display.print("By LiLRichy");
		display.drawRect(180, 130, 400, 200, GxEPD_BLACK);
	} while (display.nextPage());
	delay(5000);

	//WiFi Init
	StartWiFi();

	//Time Init
	configTime(0, 0, "pool.ntp.org", "time.nist.gov");
	// See https://github.com/nayarsystems/posix_tz_db/blob/master/zones.csv for Timezone codes for your region
	setenv("TZ", "EST5EDT,M3.2.0,M11.1.0", 1);

	Serial.println(F("Updating Times..."));
	while (get_date() == "Thu  01/01/1970") {
		delay(1000);
		Serial.println(F("."));
	}
}

void loop() {
	//Serial.println(get_time());
	//Serial.println(get_date());
	display.firstPage();
	do {
		display.fillScreen(GxEPD_WHITE);
		display.setCursor(260, 200);
		display.print(get_time());
		display.setCursor(220, 300);
		display.print(get_date());
	} while (display.nextPage());

	delay(60000);
}

void StartWiFi() {
	WiFi.mode(WIFI_STA);
	Serial.println(F("\r\nConnecting to: ")); 
	Serial.println(String(ssid));
	WiFi.begin(ssid, password);
	while (WiFi.status() != WL_CONNECTED) {
		delay(500);
		Serial.println(F("."));
	}
	Serial.println F("WiFi connected to address:");
	Serial.println(IPAddress(WiFi.localIP()));
}

String get_time() {
	time_t now;
	time(&now);
	char time_output[30];

	// See http://www.cplusplus.com/reference/ctime/strftime/ for strftime functions
	strftime(time_output, 30, "%I:%M %p", localtime(&now));
	return String(time_output); // returns 12:31pmchar time_output[30];
}
String get_date() {
	time_t now;
	time(&now);
	char date_output[30];

	// See http://www.cplusplus.com/reference/ctime/strftime/ for strftime functions
	strftime(date_output, 30, "%a  %m/%d/%Y", localtime(&now));
	return String(date_output); // returns Sat Apr/20/19 date_output[30];
}