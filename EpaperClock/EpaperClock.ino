/*
 Name:		EpaperClock.ino
 Created:	2/29/2020 7:24:48 PM
 Author:	richa
*/

#include <ESP8266WiFi.h> 
#include <time.h>

const char* ssid = "LiLRichyNetz";
const char* password = "Monster1984";

void setup() {
	Serial.begin(115200);
	
	StartWiFi();

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
	Serial.println(get_time());
	Serial.println(get_date());
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
	strftime(time_output, 30, "%I:%M%p", localtime(&now));
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