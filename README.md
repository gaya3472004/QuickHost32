# QuickHost32 – ESP32 Local Web Server (No Internet Needed)

**QuickHost32** is an offline-project built using the **ESP32 microcontroller** that creates a **local web server** without the need for an internet connection or external router.

The ESP32 is configured as a **secured Wi-Fi hotspot** (with SSID & password protection), and it hosts a static HTML web page stored directly in its memory. This setup allows nearby devices to connect and access the webpage through the ESP32’s IP address.

---

## 🔧 Features

- 📡 **Secure Wi-Fi Access Point** – Custom SSID and password protection  
- 🌍 **Offline Web Hosting** – No router or internet required  
- 🔗 **HTTP Web Server** – Serves HTML content using HTTP server  
- 🔐 **Device Access Control** – Connection limited to specific number of devices  
- 📁 **Static Web Page** – Embedded HTML/CSS interface  
- 🔄 **Local Communication** – Useful in areas with no internet (disaster zones, rural setups, etc.)

---

## 🛠️ Tools & Technologies

- **ESP32 (Wi-Fi-enabled microcontroller)**  
- **ESP-IDF** (Espressif IoT Development Framework)  
- **HTTP Server Library**  
- **C/C++** for firmware  
- **HTML/CSS** for the frontend web page

---

## 📌 Use Case

This project demonstrates how a **standalone embedded device** can act as a full web server, making it ideal for use cases like:

- Emergency broadcast systems  
- Disaster relief instructions  
- Offline data collection  
- Educational kits with no internet access  
- Local control panels for IoT devices

---

## 🚀 Getting Started

1.**Clone this repository**
   
2.**Navigate to the project directory and build using ESP-IDF**
    ```bash
    idf.py build
3.**Flash the code to your ESP32**


