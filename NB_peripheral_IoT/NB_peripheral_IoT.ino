#include <ArduinoBLE.h>

const char* deviceServiceUuid = "19b10000-e8f2-537e-4f6c-d104768a1214";
const char* deviceOwnIDCharacteristicUuid = "19b10001-e8f2-537e-4f6c-d104768a1214";
const char* deviceConnectedIDCharacteristicUuid = "19b10001-e8f2-537e-4f6c-d104768a1215";
const char* deviceMatchCharacteristicUuid = "19b10001-e8f2-537e-4f6c-d104768a1216";

int id = 111;
int match = -1;

BLEService matchService(deviceServiceUuid); 
BLEByteCharacteristic ownIDCharacteristic(deviceOwnIDCharacteristicUuid, BLERead | BLEWrite);
BLEByteCharacteristic connectedIDCharacteristic(deviceConnectedIDCharacteristicUuid, BLERead | BLEWrite);
BLEBooleanCharacteristic matchCharacteristic(deviceMatchCharacteristicUuid, BLERead | BLEWrite);


void setup() {
  Serial.begin(9600);
  
  if (!BLE.begin()) {
    Serial.println("- Starting Bluetooth® Low Energy module failed!");
    while (1);
  }

  BLE.setLocalName("Arduino Nano 33 BLE (Peripheral)");
  BLE.setAdvertisedService(matchService);

  matchService.addCharacteristic(ownIDCharacteristic);
  matchService.addCharacteristic(connectedIDCharacteristic);
  matchService.addCharacteristic(matchCharacteristic);
  BLE.addService(matchService);

  ownIDCharacteristic.writeValue(id);
  connectedIDCharacteristic.writeValue(0);
  matchCharacteristic.writeValue(false);

  BLE.advertise();

  Serial.println("Nano 33 BLE (Peripheral Device)");
  Serial.println(" ");
}

void loop() {
  BLEDevice central = BLE.central();

  Serial.println("- Discovering central device...");
  delay(500);

  if (central) {
    Serial.println("* Connected to central device!");
    Serial.print("* Central MAC address: ");
    Serial.println(central.address());
    Serial.print("* Central RSSI: ");
    Serial.println(central.rssi());
    Serial.println(" ");

    Serial.print("ownID: ");
    Serial.print(ownIDCharacteristic.value());
    Serial.println(" ");

    Serial.print("connectedID: ");
    Serial.print(connectedIDCharacteristic.value());
    Serial.println(" ");

    Serial.print("Match: ");
    Serial.print(matchCharacteristic.value());

    while (central.connected()) {
      if (matchCharacteristic.written()) {
         match = matchCharacteristic.value();
        
       }
    }
    
    Serial.println("* Disconnected to central device!");
  }
}