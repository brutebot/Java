// ==========================================================
// BLYNK + NODEMCU + TCS3200 COLOR SENSOR PROJECT
// Purpose:
// Detect RED, GREEN or BLUE color using TCS3200 sensor
// and display the detected color on Blynk.
// The corresponding Blynk LED will turn ON.
// ==========================================================


// ----------------------------------------------------------
// 1. BLYNK TEMPLATE INFORMATION
// ----------------------------------------------------------

// Template ID identifies your Blynk IoT template.
// It connects this program with the correct Blynk template.
#define BLYNK_TEMPLATE_ID "TMPL67ChRbklj"

// Template name is the name of your Blynk project.
#define BLYNK_TEMPLATE_NAME "COLOR SENSOR"

// Auth token is a unique key used to authenticate
// your NodeMCU with your Blynk account.
#define BLYNK_AUTH_TOKEN "lyzkqNxuhId9mMUNfKzQS7arSpWaGZfe"


// ----------------------------------------------------------
// 2. REQUIRED LIBRARIES
// ----------------------------------------------------------

// ESP8266WiFi library is required to connect
// NodeMCU ESP8266 to Wi-Fi.
#include <ESP8266WiFi.h>

// Blynk library allows NodeMCU to communicate
// with the Blynk IoT application.
#include <BlynkSimpleEsp8266.h>


// ----------------------------------------------------------
// 3. BLYNK VIRTUAL LEDs
// ----------------------------------------------------------

// WidgetLED is used to control an LED widget
// placed in the Blynk application.

// V0 → Red LED
WidgetLED ledR(V0);

// V1 → Green LED
WidgetLED ledG(V1);

// V2 → Blue LED
WidgetLED ledB(V2);


// ----------------------------------------------------------
// 4. BLYNK AUTHENTICATION AND WI-FI DETAILS
// ----------------------------------------------------------

// Store the Blynk authentication token.
char auth[] = BLYNK_AUTH_TOKEN;

// Wi-Fi network name (SSID).
char ssid[] = "Pooja";

// Wi-Fi password.
char pass[] = "pooja123";


// ----------------------------------------------------------
// 5. TCS3200 COLOR SENSOR PIN CONNECTIONS
// ----------------------------------------------------------

// S0 and S1 control the frequency scaling of the sensor.
int S0 = D1;
int S1 = D2;

// S2 and S3 select which color filter is measured.
int S2 = D3;
int S3 = D4;

// sensorOut gives the output frequency from the sensor.
int sensorOut = D5;


// ----------------------------------------------------------
// 6. BLYNK TIMER
// ----------------------------------------------------------

// BlynkTimer is used to execute a function periodically
// without using delay() continuously.
//
// It allows Blynk communication to continue while
// the sensor is being checked.
BlynkTimer timer;


// This flag is used to prevent color detection immediately
// after starting the system.
//
// The sensor gets 3 seconds to stabilize first.
bool sensorReady = false;


// ==========================================================
// 7. FUNCTION: readColor()
// ==========================================================

// This function reads the frequency corresponding
// to a particular color.
//
// s2 and s3 determine which color filter is selected.
int readColor(bool s2, bool s3) {

  // Set S2 according to the selected color.
  digitalWrite(S2, s2);

  // Set S3 according to the selected color.
  digitalWrite(S3, s3);

  // Give the sensor 50 milliseconds to respond
  // after changing the filter selection.
  delay(50);

  // pulseIn() measures the time for which the
  // output signal remains LOW.
  //
  // The measured pulse width is used as the
  // sensor's color value.
  return pulseIn(sensorOut, LOW);
}


// ==========================================================
// 8. FUNCTION: detectColor()
// ==========================================================

// This function measures Red, Green and Blue values
// and determines which color is detected.
String detectColor() {

  // --------------------------------------------------------
  // Read RED
  // --------------------------------------------------------
  //
  // S2 = LOW and S3 = LOW selects the RED filter
  // in the TCS3200 sensor.
  int red = readColor(LOW, LOW);


  // --------------------------------------------------------
  // Read GREEN
  // --------------------------------------------------------
  //
  // S2 = HIGH and S3 = HIGH selects the GREEN filter.
  int green = readColor(HIGH, HIGH);


  // --------------------------------------------------------
  // Read BLUE
  // --------------------------------------------------------
  //
  // S2 = LOW and S3 = HIGH selects the BLUE filter.
  int blue = readColor(LOW, HIGH);


  // --------------------------------------------------------
  // Display sensor values on Serial Monitor
  // --------------------------------------------------------

  // Print the Red value.
  Serial.print("R=");
  Serial.print(red);

  // Print the Green value.
  Serial.print(" G=");
  Serial.print(green);

  // Print the Blue value.
  Serial.print(" B=");
  Serial.println(blue);


  // --------------------------------------------------------
  // COLOR DECISION
  // --------------------------------------------------------

  // If Red has the lowest value and is below 20,
  // consider the detected color as RED.
  if (red < green && red < blue && red < 20)
    return "RED";


  // If Green has the lowest value,
  // consider the detected color as GREEN.
  if (green < red && green < blue)
    return "GREEN";


  // If Blue has the lowest value,
  // consider the detected color as BLUE.
  if (blue < red && blue < green)
    return "BLUE";


  // If none of the above conditions are satisfied,
  // return UNKNOWN.
  return "UNKNOWN";
}


// ==========================================================
// 9. FUNCTION: sendColor()
// ==========================================================

// This function detects the color and sends the result
// to the Blynk application.
void sendColor() {


  // --------------------------------------------------------
  // Check whether sensor is ready
  // --------------------------------------------------------

  // If sensorReady is false, color detection is skipped.
  //
  // This prevents incorrect readings immediately
  // after powering ON the system.
  if (!sensorReady) {

    Serial.println("Waiting for sensor stabilization...");

    // Exit the function without detecting color.
    return;
  }


  // --------------------------------------------------------
  // Detect the color
  // --------------------------------------------------------

  // Call detectColor() and store the detected color.
  String color = detectColor();


  // --------------------------------------------------------
  // Send detected color to Blynk
  // --------------------------------------------------------

  // V3 is used to display the detected color as text
  // in the Blynk application.
  Blynk.virtualWrite(V3, color);


  // --------------------------------------------------------
  // Turn OFF all LEDs first
  // --------------------------------------------------------

  // Red LED OFF
  ledR.off();

  // Green LED OFF
  ledG.off();

  // Blue LED OFF
  ledB.off();


  // --------------------------------------------------------
  // If RED is detected
  // --------------------------------------------------------

  if (color == "RED") {

    // Turn ON Red LED in Blynk.
    ledR.on();

    // Display result in Serial Monitor.
    Serial.println("Detected: RED (Red ON, Green OFF, Blue OFF)");
  }


  // --------------------------------------------------------
  // If GREEN is detected
  // --------------------------------------------------------

  else if (color == "GREEN") {

    // Turn ON Green LED in Blynk.
    ledG.on();

    // Display result in Serial Monitor.
    Serial.println("Detected: GREEN (Green ON, Red OFF, Blue OFF)");
  }


  // --------------------------------------------------------
  // If BLUE is detected
  // --------------------------------------------------------

  else if (color == "BLUE") {

    // Turn ON Blue LED in Blynk.
    ledB.on();

    // Display result in Serial Monitor.
    Serial.println("Detected: BLUE (Blue ON, Red OFF, Green OFF)");
  }


  // --------------------------------------------------------
  // If no valid color is detected
  // --------------------------------------------------------

  else {

    // Display "No Color Detected" in Blynk.
    Blynk.virtualWrite(V3, "No Color Detected");

    // Display message in Serial Monitor.
    Serial.println("No Color Detected → All LEDs OFF");
  }
}


// ==========================================================
// 10. SETUP FUNCTION
// ==========================================================

// setup() runs only ONCE when NodeMCU is powered ON
// or reset.
void setup() {


  // --------------------------------------------------------
  // Turn OFF all Blynk LEDs initially
  // --------------------------------------------------------

  // Red LED OFF at startup.
  ledR.off();

  // Green LED OFF at startup.
  ledG.off();

  // Blue LED OFF at startup.
  ledB.off();


  // --------------------------------------------------------
  // Start Serial Communication
  // --------------------------------------------------------

  // 115200 is the communication speed between
  // NodeMCU and Serial Monitor.
  //
  // It is useful for displaying sensor values
  // and debugging the program.
  Serial.begin(115200);


  // --------------------------------------------------------
  // CONNECT NODEMCU TO WI-FI
  // --------------------------------------------------------

  // Start Wi-Fi connection using SSID and password.
  WiFi.begin(ssid, pass);


  // Continue checking until Wi-Fi is connected.
  while (WiFi.status() != WL_CONNECTED) {

    // Wait 500 milliseconds before checking again.
    delay(500);

    // Print a dot to show that connection is in progress.
    Serial.print(".");
  }


  // Print message after successful Wi-Fi connection.
  Serial.println("\nWiFi Connected!");


  // --------------------------------------------------------
  // CONFIGURE BLYNK
  // --------------------------------------------------------

  // Configure Blynk using the authentication token.
  //
  // Blynk.config() prepares the Blynk connection
  // using the Wi-Fi connection already established.
  Blynk.config(auth);


  // --------------------------------------------------------
  // CONFIGURE SENSOR PINS
  // --------------------------------------------------------

  // S0 is an output because NodeMCU controls it.
  pinMode(S0, OUTPUT);

  // S1 is an output because NodeMCU controls it.
  pinMode(S1, OUTPUT);

  // S2 is an output because NodeMCU selects the color filter.
  pinMode(S2, OUTPUT);

  // S3 is an output because NodeMCU selects the color filter.
  pinMode(S3, OUTPUT);

  // sensorOut is an input because the sensor sends
  // its output signal to NodeMCU.
  pinMode(sensorOut, INPUT);


  // --------------------------------------------------------
  // SET SENSOR FREQUENCY SCALING
  // --------------------------------------------------------

  // S0 = HIGH and S1 = LOW selects 20% frequency scaling.
  //
  // This controls the frequency range generated
  // by the TCS3200 sensor.
  digitalWrite(S0, HIGH);
  digitalWrite(S1, LOW);


  // --------------------------------------------------------
  // DEFAULT BLYNK DISPLAY
  // --------------------------------------------------------

  // Display this message when the system starts.
  Blynk.virtualWrite(V3, "No Color Detected");


  // Display startup message on Serial Monitor.
  Serial.println("System Started → Default State: All LEDs OFF");


  // --------------------------------------------------------
  // RUN COLOR DETECTION EVERY 1 SECOND
  // --------------------------------------------------------

  // sendColor() is called once every 1000 milliseconds.
  //
  // 1000 ms = 1 second.
  timer.setInterval(1000L, sendColor);


  // --------------------------------------------------------
  // SENSOR STABILIZATION DELAY
  // --------------------------------------------------------

  // Wait 3 seconds after startup before detecting colors.
  //
  // This gives the sensor and system time to stabilize.
  timer.setTimeout(3000L, []() {

    // After 3 seconds, allow color detection.
    sensorReady = true;

    // Inform the user through Serial Monitor.
    Serial.println("Sensor Ready → Now detecting colors!");
  });
}


// ==========================================================
// 11. LOOP FUNCTION
// ==========================================================

// loop() runs continuously after setup() is completed.
void loop() {


  // --------------------------------------------------------
  // RUN BLYNK
  // --------------------------------------------------------

  // Maintains communication between NodeMCU and Blynk.
  //
  // It handles data exchange between the hardware
  // and Blynk cloud.
  Blynk.run();


  // --------------------------------------------------------
  // RUN TIMER
  // --------------------------------------------------------

  // Checks whether any timer function needs to run.
  //
  // This allows sendColor() to execute every 1 second
  // and the 3-second stabilization function to execute.
  timer.run();
}
