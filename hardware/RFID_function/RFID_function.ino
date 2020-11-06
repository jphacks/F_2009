/*
 * File:      RFID_function.ino
 * Function:  RFIDカードを読み取ります。
 * Date:      2020/11/04 Y.Kawakami
 * Author:    Y.Kawakami
 * 
 * Hardware   MCU:  ESP32 (DOIT ESP32 DEVKIT V1 Board)
 *            RFID-RC522
 *
 * Typical pin layout used:
 * -----------------------------------------------------------------------------------------
 *             MFRC522      Arduino       Arduino   Arduino    Arduino          Arduino
 *             Reader/PCD   Uno/101       Mega      Nano v3    Leonardo/Micro   Pro Micro
 * Signal      Pin          Pin           Pin       Pin        Pin              Pin
 * -----------------------------------------------------------------------------------------
 * RST/Reset   RST          9             5         D9         RESET/ICSP-5     RST
 * SPI SS      SDA(SS)      10            53        D10        10               10
 * SPI MOSI    MOSI         11 / ICSP-4   51        D11        ICSP-4           16
 * SPI MISO    MISO         12 / ICSP-1   50        D12        ICSP-1           14
 * SPI SCK     SCK          13 / ICSP-3   52        D13        ICSP-3           15
 */
// libraries
// RFID
#include <SPI.h>
#include <MFRC522.h>

// defines
// RFID(ESP32)
#define SS_PIN 5
#define RST_PIN 26

// class
// RFID
MFRC522 rfid(SS_PIN, RST_PIN); // Instance of the class

// variables

// functions
// RFID
/* Byte data -> String */
void array_to_string(byte array[], unsigned int len, char buffer[]) 
{ 
  for (unsigned int i = 0; i < len; i++) { 
    byte nib1 = (array[i] >> 4) & 0x0F; 
    byte nib2 = (array[i] >> 0) & 0x0F; 
    buffer[i*2+0] = nib1 < 0xA ? '0' + nib1 : 'A' + (nib1 - 0xA); 
    buffer[i*2+1] = nib2 < 0xA ? '0' + nib2 : 'A' + (nib2 - 0xA); 
  } 
  buffer[len*2] = '\0'; 
}


/* Helper routine to dump a byte array as hex values to Serial. */
String printHex(byte *buffer, byte bufferSize) {
  char str[32] = ""; 
  array_to_string(buffer, bufferSize, str); 
  // Serial.print(str);
  return str;
}


/* RFIDタグの読み取り */
String readRfid(){
  /* カードが新しいかと、カードが読み取れるかを確認 */
  // Reset the loop if no new card present on the sensor/reader. This saves the entire process when idle.
  if (!rfid.PICC_IsNewCardPresent())  // PICC_IsNewCardPresent() -> 「New Cardが現れた」
    return "ERROR";
  // Verify if the NUID has been readed
  if (!rfid.PICC_ReadCardSerial())  // PICC_ReadCardSerial() -> 「カードが読み取れるか確認」
    return "ERROR";

  /* PICタイプの取得 */
  MFRC522::PICC_Type piccType = rfid.PICC_GetType(rfid.uid.sak);

  // Check is the PICC of Classic MIFARE type
  if (piccType != MFRC522::PICC_TYPE_MIFARE_MINI &&  
      piccType != MFRC522::PICC_TYPE_MIFARE_1K &&
      piccType != MFRC522::PICC_TYPE_MIFARE_4K) {
    Serial.println(F("Your tag is not of type MIFARE Classic."));
    return "ERROR";
  }
  
  String nuid = printHex(rfid.uid.uidByte, rfid.uid.size);

  // Halt PICC
  rfid.PICC_HaltA();
  // Stop encryption on PCD
  rfid.PCD_StopCrypto1();

  return nuid;
}


void setup() {
  // Serial connection speed
  Serial.begin(115200);

  // initiate
  // RFID
  SPI.begin(); // Init SPI bus
  rfid.PCD_Init(); // Init MFRC522 
}
 
void loop() {
  // 読み取りと判断の例
  String nuid = readRfid();
  if(!nuid.equals("ERROR")){
    if(nuid.equals("DADC3186")){
      // tag1 proceccing
    }else if(nuid.equals("EA850485")){
      // tag2 proceccing
    }else if(nuid.equals("0A1AF384")){
      // tag3 proceccing
    }else{
      // ERROR proceccing
    }
  }
  else{
    // ERROR proceccing
  }
  
  delay(1000);
}
