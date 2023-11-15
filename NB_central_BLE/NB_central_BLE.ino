#include <ArduinoBLE.h>

const char* deviceServiceUuid = "19b10000-e8f2-537e-4f6c-d104768a1214";
const char* deviceIDCharacteristicUuid = "19b10001-e8f2-537e-4f6c-d104768a1214";
const char* inputIDCharacteristicUuid = "19b10001-e8f2-537e-4f6c-d104768a1215";
const char* deviceMatchCharacteristicUuid = "19b10001-e8f2-537e-4f6c-d104768a1216";

int id = 222;

void setup() {
  Serial.begin(9600);
  
  if (!BLE.begin()) {
    Serial.println("* Starting Bluetooth® Low Energy module failed!");
    while (1);
  }
  
  BLE.setLocalName("Nano 33 BLE (Central)"); 
  BLE.advertise();

  Serial.println("Arduino Nano 33 BLE (Central Device)");
  Serial.println(" ");
}

void loop() {
  connectToPeripheral();
  delay(500);
}

void connectToPeripheral(){
  BLEDevice peripheral;
  
  Serial.println("- Discovering peripheral device...");

  do
  {
    BLE.scanForUuid(deviceServiceUuid);
    peripheral = BLE.available();
  } while (!peripheral);
  
  if (peripheral) {
    Serial.println("* Peripheral device found!");
    Serial.print("* Device MAC address: ");
    Serial.println(peripheral.address());
    Serial.print("* Device name: ");
    Serial.println(peripheral.localName());
    Serial.print("* Advertised service UUID: ");
    Serial.println(peripheral.advertisedServiceUuid());
    Serial.println(" ");
    BLE.stopScan();
    controlPeripheral(peripheral);
  }
}

void controlPeripheral(BLEDevice peripheral) {
  Serial.println("- Connecting to peripheral device...");

  if (peripheral.connect()) {
    Serial.println("* Connected to peripheral device!");
    Serial.println(" ");
  } else {
    Serial.println("* Connection to peripheral device failed!");
    Serial.println(" ");
    return;
  }

  Serial.println("- Discovering peripheral device attributes...");
  if (peripheral.discoverAttributes()) {
    Serial.println("* Peripheral device attributes discovered!");
    Serial.print("RSSI: ");
    Serial.println(peripheral.rssi());
    Serial.println(" ");
  } else {
    Serial.println("* Peripheral device attributes discovery failed!");
    Serial.println(" ");
    peripheral.disconnect();
    return;
  }

  BLEService service = peripheral.service(deviceServiceUuid);

  // Read IDCharacteristic value
  BLECharacteristic IDCharacteristic = service.characteristic(deviceIDCharacteristicUuid);
  IDCharacteristic.read();
  int peripheralID = readData(IDCharacteristic.value(), IDCharacteristic.valueLength());

  // Write inputIDCharacteristic value
  BLECharacteristic inputIDCharacteristic = service.characteristic(inputIDCharacteristicUuid);
  inputIDCharacteristic.writeValue((byte)id);
  IDCharacteristic.read();
  int inputID = readData(inputIDCharacteristic.value(), inputIDCharacteristic.valueLength());

  // Read matchCharacteristic value
  BLECharacteristic matchCharacteristic = service.characteristic(deviceMatchCharacteristicUuid);
  matchCharacteristic.read();
  int matching = readData(matchCharacteristic.value(), matchCharacteristic.valueLength());

  Serial.print("Peripheral ID: ");
  Serial.println(peripheralID);
  Serial.print("This ID: ");
  Serial.println(inputID);
  Serial.print("Matching: ");
  Serial.println(matching);

  Serial.println("- Peripheral device disconnected!");
}



int readData(const unsigned char data[], int length) {
  for (int i = 0; i < length; i++) {
    unsigned char b = data[i];

    if (b < 16) {
      Serial.print("0");
    }

    return (int)b;
  }
}
  
