/**
 * The MySensors Arduino library handles the wireless radio link and protocol
 * between your home built sensors/actuators and HA controller of choice.
 * The sensors forms a self healing radio network with optional repeaters. Each
 * repeater and gateway builds a routing tables in EEPROM which keeps track of the
 * network topology allowing messages to be routed to nodes.
 *
 * Created by Henrik Ekblad <henrik.ekblad@mysensors.org>
 * Copyright (C) 2013-2015 Sensnology AB
 * Full contributor list: https://github.com/mysensors/Arduino/graphs/contributors
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
 */

//LoRa-Radio-Node-v1.0 (Uses Default MySensors pin config)
#define MY_DEBUG
#define MY_RADIO_RFM95
#define MY_DEBUG_VERBOSE_RFM95
#define MY_RFM95_FREQUENCY (RFM95_868MHZ)
#define MY_RFM95_MODEM_CONFIGRUATION RFM95_BW125CR45SF128


//Enable Signing <Make Sure you Change Password>
//#define MY_SIGNING_SIMPLE_PASSWD "mysecretpassword"

//Enable Encryption This uses less memory, and hides the actual data. <Make Sure you Change Password>
//#define MY_ENCRYPTION_SIMPLE_PASSWD "mysecretpassword"


#define MY_NODE_ID 110


// Enable repeater functionality for this node as relay node will never sleep
#define MY_REPEATER_FEATURE

#include <SPI.h>
#include <MySensors.h>

#define RELAY_1  4          // Arduino Digital I/O pin number for first relay (second on pin+1 etc)
#define NUMBER_OF_RELAYS 4  // Total number of attached relays: 4

// Opto Relay Module I was using Active Low - Low (0):ON, High (1): OFF
#define RELAY_ON 0          // GPIO value to write to turn on attached relay
#define RELAY_OFF 1         // GPIO value to write to turn off attached relay

bool initialValueSent = false;

//Init MyMessage for Each Child ID
MyMessage msg1(1, V_LIGHT);
MyMessage msg2(2, V_LIGHT);
MyMessage msg3(3, V_LIGHT);
MyMessage msg4(4, V_LIGHT);

void before() { 
  for (int sensor=1, pin=RELAY_1; sensor<=NUMBER_OF_RELAYS;sensor++, pin++) {
    // Then set relay pins in output mode
    pinMode(pin, OUTPUT);   
    // Set relay to last known state (using eeprom storage) 
    digitalWrite(pin, loadState(sensor)?RELAY_ON:RELAY_OFF);
  }
}

void setup() {
  
}

void presentation()  
{   
  // Send the sketch version information to the gateway and Controller
  sendSketchInfo("Relay", "1.0");

  for (int sensor=1, pin=RELAY_1; sensor<=NUMBER_OF_RELAYS;sensor++, pin++) {
    // Register all sensors to gw (they will be created as child devices)
    present(sensor, S_LIGHT);
  }
}


void loop() 
{
  if (!initialValueSent) {
    Serial.println("Sending initial value");
    send(msg1.set(loadState(1)?RELAY_OFF:RELAY_ON),true);
    wait(1000);
    send(msg2.set(loadState(2)?RELAY_OFF:RELAY_ON),true);
    wait(1000);
    send(msg3.set(loadState(3)?RELAY_OFF:RELAY_ON),true);
    wait(1000);
    send(msg4.set(loadState(4)?RELAY_OFF:RELAY_ON),true);
    wait(1000);
    Serial.println("Sending initial value: Completed");
    wait(5000);
  }
}

void receive(const MyMessage &message) {
  Serial.println("=============== Receive Start =======================");
  if (message.isAck()) {
     Serial.println(">>>>> ACK <<<<<");
     Serial.println("This is an ack from gateway");
     Serial.println("<<<<<< ACK >>>>>>");
  }
  // We only expect one type of message from controller. But we better check anyway.
  if (message.type==V_LIGHT) {
    Serial.println(">>>>> V_LIGHT <<<<<");
    if (!initialValueSent) {
      Serial.println("Receiving initial value from controller");
      initialValueSent = true;
    }
     // Update relay state to HA
     digitalWrite(message.sensor-1+RELAY_1, message.getBool()?RELAY_ON:RELAY_OFF);
     switch (message.sensor) {
        case 1:
          Serial.print("Incoming change for sensor 1");
          send(msg1.set(message.getBool()?RELAY_OFF:RELAY_ON));
          break;
        case 2:
          Serial.print("Incoming change for sensor 2");
          send(msg2.set(message.getBool()?RELAY_OFF:RELAY_ON));
          break;
        case 3:
          Serial.print("Incoming change for sensor 3");
          send(msg3.set(message.getBool()?RELAY_OFF:RELAY_ON));
          break;
        case 4:
          Serial.print("Incoming change for sensor 4");
          send(msg4.set(message.getBool()?RELAY_OFF:RELAY_ON));
          break;                    
        default: 
          Serial.println("Default Case: Receiving Other Sensor Child ID");
        break;
     }
     // Store state in Arduino eeprom
     saveState(message.sensor, message.getBool());
     Serial.print("Saved State for sensor: ");
     Serial.print( message.sensor);
     Serial.print(", New status: ");
     Serial.println(message.getBool());
     Serial.println("<<<<<< V_LIGHT >>>>>>");
   } 
   Serial.println("=============== Receive END =======================");
}
