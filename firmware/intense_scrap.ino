/*
 * Intense Scrap — ESP32 firmware starter
 * Hardware: ESP32 + 160x80 ST7735 SPI TFT + PREV/PLAY-NEXT buttons.
 *
 * Required Arduino libraries:
 *   Adafruit GFX Library
 *   Adafruit ST7735 and ST7789 Library
 *
 * Wi-Fi and Spotify credentials are intentionally NOT stored in the repo.
 * Set WIFI_SSID, WIFI_PASSWORD and SPOTIFY_ACCESS_TOKEN locally before use.
 *
 * Pin plan:
 * TFT SCK=18, MOSI=23, CS=5, DC=27, RST=4
 * PREV=32, PLAY=33, NEXT=25
 */

#include <WiFi.h>
#include <HTTPClient.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>

#define TFT_CS   5
#define TFT_DC   27
#define TFT_RST  4
#define TFT_SCLK 18
#define TFT_MOSI 23

#define BTN_PREV 32
#define BTN_PLAY 33
#define BTN_NEXT 25

const char* WIFI_SSID = "YOUR_WIFI_SSID";
const char* WIFI_PASSWORD = "YOUR_WIFI_PASSWORD";
const char* SPOTIFY_ACCESS_TOKEN = "YOUR_SPOTIFY_ACCESS_TOKEN";

Adafruit_ST7735 tft(TFT_CS, TFT_DC, TFT_RST);

bool playing = false;
String trackName = "Intense Scrap";
String artistName = "Spotify controller";

void spotifyRequest(const char* method, const char* path) {
  if (WiFi.status() != WL_CONNECTED) return;
  if (String(SPOTIFY_ACCESS_TOKEN) == "YOUR_SPOTIFY_ACCESS_TOKEN") return;

  HTTPClient http;
  String url = String("https://api.spotify.com/v1/me/player") + path;
  http.begin(url);
  http.addHeader("Authorization", String("Bearer ") + SPOTIFY_ACCESS_TOKEN);

  int code = -1;
  if (strcmp(method, "PUT") == 0) {
    code = http.PUT("");
  } else {
    code = http.POST("");
  }
  http.end();

  Serial.printf("Spotify %s %s -> %d\n", method, path, code);
}

void drawScreen() {
  tft.fillScreen(ST77XX_BLACK);
  tft.setTextColor(ST77XX_WHITE);
  tft.setTextSize(1);

  tft.setCursor(4, 4);
  tft.println("INTENSE SCRAP");

  tft.drawFastHLine(4, 16, 152, ST77XX_WHITE);

  tft.setCursor(4, 28);
  tft.setTextSize(2);
  tft.println(trackName.substring(0, 12));

  tft.setTextSize(1);
  tft.setCursor(4, 52);
  tft.println(artistName.substring(0, 22));

  tft.setCursor(4, 68);
  tft.print("PREV   ");
  tft.print(playing ? "PAUSE" : "PLAY");
  tft.println("   NEXT");
}

void connectWiFi() {
  if (String(WIFI_SSID) == "YOUR_WIFI_SSID") {
    Serial.println("Wi-Fi credentials not configured.");
    return;
  }

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");

  unsigned long start = millis();
  while (WiFi.status() != WL_CONNECTED && millis() - start < 15000) {
    delay(250);
    Serial.print(".");
  }
  Serial.println();

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("Wi-Fi connected.");
  } else {
    Serial.println("Wi-Fi connection failed.");
  }
}

void setup() {
  Serial.begin(115200);

  pinMode(BTN_PREV, INPUT_PULLUP);
  pinMode(BTN_PLAY, INPUT_PULLUP);
  pinMode(BTN_NEXT, INPUT_PULLUP);

  SPI.begin(TFT_SCLK, -1, TFT_MOSI, TFT_CS);
  tft.initR(INITR_MINI160x80);
  tft.setRotation(1);

  drawScreen();
  connectWiFi();
}

void loop() {
  static bool oldPrev = HIGH;
  static bool oldPlay = HIGH;
  static bool oldNext = HIGH;

  bool prev = digitalRead(BTN_PREV);
  bool play = digitalRead(BTN_PLAY);
  bool next = digitalRead(BTN_NEXT);

  if (oldPrev == HIGH && prev == LOW) {
    spotifyRequest("POST", "/previous");
    delay(250);
  }

  if (oldPlay == HIGH && play == LOW) {
    if (playing) {
      spotifyRequest("PUT", "/pause");
    } else {
      spotifyRequest("PUT", "/play");
    }
    playing = !playing;
    drawScreen();
    delay(250);
  }

  if (oldNext == HIGH && next == LOW) {
    spotifyRequest("POST", "/next");
    delay(250);
  }

  oldPrev = prev;
  oldPlay = play;
  oldNext = next;

  delay(10);
}
