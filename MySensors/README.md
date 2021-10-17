# Radio Settings for all LoRa Nodes used in this project

//Heltec ESP32 Lora V2<br />
#define MY_RADIO_RFM95<br />
#define MY_DEBUG_VERBOSE_RFM95<br />
#define MY_RFM95_RST_PIN 14<br />
#define MY_RFM95_CS_PIN 18<br />
#define MY_RFM95_IRQ_PIN 26<br />
#define MY_RFM95_IRQ_NUM MY_RFM95_IRQ_PIN<br />
#define MY_SOFT_SPI_MOSI_PIN 27<br />
#define MY_SOFT_SPI_SCK_PIN 5<br />
#define MY_RFM95_MODEM_CONFIGRUATION RFM95_BW125CR45SF128<br />
#define MY_RFM95_FREQUENCY (RFM95_868MHZ)<br />

//LoRa-Radio-Node-v1.0 (Uses Default MySensors pin config)<br />
#define MY_RADIO_RFM95<br />
#define MY_DEBUG_VERBOSE_RFM95<br />
#define MY_RFM95_FREQUENCY (RFM95_868MHZ)<br />
#define MY_RFM95_MODEM_CONFIGRUATION RFM95_BW125CR45SF128<br />

//Adafruit LoRa32u4 II<br />
#define MY_DEBUG<br />
#define MY_RADIO_RFM95<br />
#define MY_DEBUG_VERBOSE_RFM95<br />
#define MY_RFM95_RST_PIN 4<br />
#define MY_RFM95_CS_PIN 8<br />
#define MY_RFM95_IRQ_PIN 7<br />
#define MY_RFM95_IRQ_NUM digitalPinToInterrupt(7)<br />
#define MY_RFM95_MODEM_CONFIGRUATION RFM95_BW125CR45SF128<br />
#define MY_RFM95_FREQUENCY (RFM95_868MHZ)<br />
