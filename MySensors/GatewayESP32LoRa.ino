/*
 * The MySensors Arduino library handles the wireless radio link and protocol
 * between your home built sensors/actuators and HA controller of choice.
 * The sensors forms a self healing radio network with optional repeaters. Each
 * repeater and gateway builds a routing tables in EEPROM which keeps track of the
 * network topology allowing messages to be routed to nodes.
 *
 * Created by Henrik Ekblad <henrik.ekblad@mysensors.org>
 * Copyright (C) 2013-2018 Sensnology AB
 * Full contributor list: https://github.com/mysensors/MySensors/graphs/contributors
 *
 * Documentation: http://www.mysensors.org
 * Support Forum: http://forum.mysensors.org
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * version 2 as published by the Free Software Foundation.
 *
 *******************************
 *
 * REVISION HISTORY
 * Version 1.0 - tekka
 *
 * DESCRIPTION
 * The ESP32 gateway sends data received from sensors to the WiFi link.
 * The gateway also accepts input on ethernet interface, which is then sent out to the radio network.
 *
 * Make sure to fill in your ssid and WiFi password below.
 */

// Enable debug prints to serial monitor
#define MY_DEBUG

// Radio settings for Heltec ESP32 Lora node V2
#define MY_RADIO_RFM95
#define MY_DEBUG_VERBOSE_RFM95
#define MY_RFM95_RST_PIN 14
#define MY_RFM95_CS_PIN 18
#define MY_RFM95_IRQ_PIN 26
#define MY_RFM95_IRQ_NUM MY_RFM95_IRQ_PIN
#define MY_SOFT_SPI_MOSI_PIN 27
#define MY_SOFT_SPI_SCK_PIN 5
#define MY_RFM95_MODEM_CONFIGRUATION RFM95_BW125CR45SF128
#define MY_RFM95_FREQUENCY (RFM95_868MHZ)




//Enable Signing <Make Sure you Change Password>
//#define MY_SIGNING_SIMPLE_PASSWD "mysecretpassword"

//Enable Encryption This uses less memory, and hides the actual data. <Make Sure you Change Password>
//#define MY_ENCRYPTION_SIMPLE_PASSWD "mysecretpassword"


#define MY_GATEWAY_ESP32
// #define MY_GATEWAY_SERIAL

//Wifi Settings
#define MY_WIFI_SSID "ChangeMe"
#define MY_WIFI_PASSWORD "ChangeMe"

// Set the hostname for the WiFi Client. This is the hostname
// it will pass to the DHCP server if not static.
#define MY_HOSTNAME "Home_GW_LoRa"

// Enable MY_IP_ADDRESS here if you want a static ip address (no DHCP)
#define MY_IP_ADDRESS 192,168,1,203

// If using static ip you can define Gateway and Subnet address as well
#define MY_IP_GATEWAY_ADDRESS 192,168,1,1
#define MY_IP_SUBNET_ADDRESS 255,255,255,0

// The port to keep open on node server mode
#define MY_PORT 5003

// How many clients should be able to connect to this gateway (default 1)
#define MY_GATEWAY_MAX_CLIENTS 2

#include <MySensors.h>
#include "heltec.h"




void setup()
{
	// Setup locally attached sensors
  Heltec.begin(true /*DisplayEnable Enable*/, false /*LoRa Disable*/, true /*Serial Enable*/);
  
  Heltec.display->setContrast(255);

 Heltec.display->clear();
 Heltec.display->setFont(ArialMT_Plain_16);
 Heltec.display->drawString(30, 10, "LoRa Home");
 Heltec.display->setFont(ArialMT_Plain_10);
 Heltec.display->drawString(30, 40, WiFi.localIP().toString());
 Heltec.display->display();

}

void presentation()
{
	// Present locally attached sensors here
}

void loop()
{
	// Send locally attached sensors data here
}
