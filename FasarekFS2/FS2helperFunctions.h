typedef unsigned char byte;

template <class T> int EEPROM_writeAnything(int ee, const T& value)
{
    const byte* p = (const byte*)(const void*)&value;
    int i;
    for (i = 0; i < sizeof(value); i++)
    EEPROM.put(ee++, *p++);
    EEPROM.commit();
    return i;
}

template <class T> int EEPROM_readAnything(int ee, T& value)
{
    byte* p = (byte*)(void*)&value;
    int i;
    for (i = 0; i < sizeof(value); i++)
    *p++ = EEPROM.read(ee++);
    return i;
}

String getContentType(String filename) {
  if (server.hasArg("download")) {
    return "application/octet-stream";
  }
  if (filename.endsWith(".json")) {
    return "application/json";
  } else if (filename.endsWith(".html")) {
    return "text/html";
  } else if (filename.endsWith(".css")) {
    return "text/css";
  } else if (filename.endsWith(".js")) {
    return "application/javascript";
  } 
  return "text/plain";
}

/**
 * Generic message printer. Modify this if you want to send this messages elsewhere (Display)
 */
void printMessage(String message, bool newline = true, bool displayClear = false) {
  //u8g2.setDrawColor(1);
  if (displayClear) {
    // Clear buffer and reset cursor to first line
    // u8g2.clearBuffer();
    u8cursor = u8newline;
  }
  if (newline) {
    //u8cursor = u8cursor+u8newline;
    Serial.println(message);
  } else {
    Serial.print(message);
  }
  //u8g2.setCursor(0, u8cursor);
  //u8g2.print(message);
  //u8g2.sendBuffer();
  u8cursor = u8cursor+u8newline;
  if (u8cursor > 60) {
    u8cursor = u8newline;
  }
  return;
}

