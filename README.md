# Parking_Availability_System
Our project focuses on revolutionizing parking management by implementing a real-time availability system. It utilizes IoT sensors and intuitive screens at parking entrances to provide instant updates on slot availability. This enhances user convenience with displaying color-coded indicators for easy navigation.


Parking Slot Status Monitor

Overview:
This project utilizes an ESP8266 microcontroller to monitor the occupancy status of parking slots using IR sensors. It provides a web-based interface to view the real-time status of each slot.

Features

Real-time Monitoring: Displays whether each parking slot is occupied or free.
Web Interface: Accessible via a web browser to check status remotely.
JSON API: Provides a JSON API endpoint /status to fetch the status programmatically.

Hardware Requirements:
ESP8266 development board (e.g., NodeMCU)
IR sensors (two sensors used in this project)
Jumper wires

Software Requirements:

Arduino IDE with ESP8266 board support
Libraries:
ESP8266WiFi
ESP8266WebServer
ArduinoJson (for handling JSON data)
Installation and Setup

Hardware Setup:

Connect IR sensors to GPIO pins of the ESP8266 board (pins D1 and D6 in this example).

Software Setup:

Install the Arduino IDE.
Install the ESP8266 board package in the Arduino IDE.
Install necessary libraries (ESP8266WiFi, ESP8266WebServer, ArduinoJson).

Configuration:
Update ssid and password variables in the sketch with your WiFi credentials.

Upload Sketch:
Compile and upload the provided Arduino sketch (parking_status_monitor.ino) to your ESP8266 board.

Accessing the Web Interface:
After uploading, open the Serial Monitor in the Arduino IDE to view the IP address assigned to your ESP8266 by the WiFi network.
Open a web browser and enter the IP address to access the parking slot status monitor.
Usage
Open the web interface to view the current status of each parking slot.
The status updates automatically in real-time due to JavaScript fetching JSON data from the /status endpoint.
Contributing
Contributions are welcome! If you'd like to contribute to this project, please fork the repository and submit a pull request.

License
This project is licensed under the MIT License - see the LICENSE file for details.

Acknowledgments
Arduino: For providing the development platform and libraries.
ESP8266 Community: For developing the ESP8266 board package and support libraries.
