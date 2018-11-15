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
    u8g2.clearBuffer();
    u8cursor = u8newline;
  }
  if (newline) {
    u8cursor = u8cursor+u8newline;
    Serial.println(message);
  } else {
    Serial.print(message);
  }
  u8g2.setCursor(0, u8cursor);
  u8g2.print(message);
  u8g2.sendBuffer();
  u8cursor = u8cursor+u8newline;
  if (u8cursor > 60) {
    u8cursor = u8newline;
  }
  return;
}

void start_capture() {
  myCAM.clear_fifo_flag();
  myCAM.start_capture();
}

void serverStream() {
    printMessage("STREAMING");
  if (cameraModelId == 5) {
    myCAM.OV2640_set_JPEG_size(2);
  } else if (cameraModelId == 3) {
    myCAM.OV5642_set_JPEG_size(1);
  }
  WiFiClient client = server.client();

  String response = "HTTP/1.1 200 OK\r\n";
  response += "Content-Type: multipart/x-mixed-replace; boundary=frame\r\n\r\n";
  server.sendContent(response);
  int counter = 0;
  while (true) {
    counter++;
    // Use a handleClient only 1 every 99 times
    if (counter % 99 == 0) {
       server.handleClient();
       Serial.print(String(counter)+" % 99 Matched");
    }
    start_capture();
    while (!myCAM.get_bit(ARDUCHIP_TRIG, CAP_DONE_MASK));
    size_t len = myCAM.read_fifo_length();

    if (len == 0 ) //0 kb
    {
      Serial.println(F("Size is 0."));
      continue;
    }
    myCAM.CS_LOW();
    myCAM.set_fifo_burst();
    if (!client.connected()) {
      client.stop(); is_header = false; break;
    }
    response = "--frame\r\n";
    response += "Content-Type: image/jpeg\r\n\r\n";
    server.sendContent(response);
    
    while ( len-- )
    {
      temp_last = temp;
      temp =  SPI.transfer(0x00);

      //Read JPEG data from FIFO
      if ( (temp == 0xD9) && (temp_last == 0xFF) ) //If find the end ,break while,
      {
        buffer[i++] = temp;  //save the last  0XD9
        //Write the remain bytes in the buffer
        myCAM.CS_HIGH();;
        if (!client.connected()) {
          client.stop(); is_header = false; break;
        }
        client.write(&buffer[0], i);
        is_header = false;
        i = 0;
      }
      if (is_header == true)
      {
        //Write image data to buffer if not full
        if (i < bufferSize)
          buffer[i++] = temp;
        else
        {
          //Write bufferSize bytes image data to file
          myCAM.CS_HIGH();
          if (!client.connected()) {
            client.stop(); is_header = false; break;
          }
          client.write(&buffer[0], bufferSize);
          i = 0;
          buffer[i++] = temp;
          myCAM.CS_LOW();
          myCAM.set_fifo_burst();
        }
      }
      else if ((temp == 0xD8) & (temp_last == 0xFF))
      {
        is_header = true;
        buffer[i++] = temp_last;
        buffer[i++] = temp;
      }
    }
    if (!client.connected()) {
      client.stop(); is_header = false; break;
    }
  }
}

void serverStartTimelapse() {
    digitalWrite(ledStatusTimelapse, HIGH);
    printMessage("TIMELAPSE enabled");
    captureTimeLapse = true;
    lastTimeLapse = millis() + timelapseMillis;
    server.send(200, "text/html", "<div id='m'>Start Timelapse</div>"+ javascriptFadeMessage);
}

void serverStopTimelapse() {
    digitalWrite(ledStatusTimelapse, LOW);
    printMessage("TIMELAPSE disabled");
    captureTimeLapse = false;
    server.send(200, "text/html", "<div id='m'>Stop Timelapse</div>"+ javascriptFadeMessage);
}

void serverStopStream() {
    printMessage("STREAM stopped", true, true);
    server.send(200, "text/html", "<div id='m'>Streaming stoped</div>"+ javascriptFadeMessage);
}

/**
 * Update camera settings (Effects / Exposure only on OV5642)
 */
void serverCameraSettings() {
     String argument  = server.argName(0);
     String setValue = server.arg(0);
     if (argument == "effect") {
       if (cameraModelId == 5) {
         myCAM.OV2640_set_Special_effects(setValue.toInt());
       }
       if (cameraModelId == 3) {
         Serial.print(setValue);Serial.print(" in OV5642 this still does not work: https://github.com/ArduCAM/Arduino/issues/377");
         myCAM.OV5642_set_Special_effects(setValue.toInt());
       }
     }
     if (argument == "exposure" && cameraModelId == 3) {
         myCAM.OV5642_set_Exposure_level(setValue.toInt());
     }
     server.send(200, "text/html", "<div id='m'>"+argument+" updated to value "+setValue+"<br>See it on effect on next photo</div>"+ javascriptFadeMessage);
}

/**
 * Convert the IP to string so we can send the display
 */
String IpAddress2String(const IPAddress& ipAddress)
{
  return String(ipAddress[0]) + String(".") +\
  String(ipAddress[1]) + String(".") +\
  String(ipAddress[2]) + String(".") +\
  String(ipAddress[3])  ;
}
