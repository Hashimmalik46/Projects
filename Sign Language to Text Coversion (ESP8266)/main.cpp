#define BLYNK_TEMPLATE_ID "TMPL3t2CsvMT1"
#define BLYNK_TEMPLATE_NAME "Gesture to text converter"
#define BLYNK_AUTH_TOKEN "D_5LQMGgfCWdvt9CCnzhWV5OsUWxRQyb"
#include <Wire.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1  // Reset pin not used for I2C
#define SCREEN_ADDRESS 0x3C  // OLED I2C address

char auth[] = "D_5LQMGgfCWdvt9CCnzhWV5OsUWxRQyb";
char ssid[] = "Hashim";
char pass[] = "hashimmalik123";

Adafruit_MPU6050 mpu;
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setup() {
    Serial.begin(115200);
    Wire.begin();

    // Connect to WiFi
    WiFi.begin(ssid, pass);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("\nWiFi Connected");
    
    // Connect to Blynk
    Blynk.begin(auth, ssid, pass);

    // Initialize OLED
    if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
        Serial.println("SSD1306 allocation failed");
        for (;;);
    }
    display.clearDisplay();
    display.setTextSize(2);
    display.setTextColor(WHITE);
    display.setCursor(0, 10);
    display.println("Loading...");
    display.display();
    delay(2000);

    // Initialize MPU6050
    if (!mpu.begin()) {
        Serial.println("MPU6050 connection failed!");
        while (1);
    }

    mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
    mpu.setGyroRange(MPU6050_RANGE_500_DEG);
    mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);

    Serial.println("MPU6050 Initialized!");
    displayMessage("Ready");
}

void loop() {
    Blynk.run();
    sensors_event_t a, g, temp;
    mpu.getEvent(&a, &g, &temp);

    String message = detectGesture(g.gyro.x, g.gyro.y, g.gyro.z);
    
    if (message != "") {
        Serial.println("Gesture: " + message);
        displayMessage(message);
        delay(1000); 
    }

    delay(200);
}

// Function to detect gestures based on gyroscope values
String detectGesture(float gx, float gy, float gz) {
    if (gx > 2) { 
        Blynk.logEvent("alert1"); 
        return "Hello!";
    }
    if (gx < -2) { 
        Blynk.logEvent("alert2"); 
        return "Goodbye!";
    }
    if (gy > 2) { 
        Blynk.logEvent("alert3"); 
        return "How are you?";
    }
    if (gy < -2) { 
        Blynk.logEvent("alert4"); 
        return "I'm fine!";
    }
    if (gz > 2) { 
        Blynk.logEvent("alert5"); 
        return "Yes";
    }
    if (gz < -2) { 
        Blynk.logEvent("alert6"); 
        return "No";
    }

    return 0;  
}


// Function to display messages on OLED
void displayMessage(String msg) {
    display.clearDisplay();
    display.setTextSize(2);
    display.setTextColor(WHITE);
    display.setCursor(10, 20);
    display.println(msg);
    display.display();
}