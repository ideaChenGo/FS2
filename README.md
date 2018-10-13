# FS2
## ESP8266 WiFi powered digital Camera

### The FS2 is a digital Polaroid that uploads the photo instantly to the cloud

This project serves as a base to explore Arducam possibilities in combination with a WiFI "System on a Chip" such as ESP8266 to create a simple WiFi point-and-shoot digital camera.
This is a work in progress and only schematics is provided, but it can work out of the box if you can connect 8 Serial Parallel Interface cables from the camera to a Wemos D1 or similar and upload the Arducam example.

### What is powering this camera
This WiFi instant camera is powered by a 2000mA/hr LiOn battery and Espressif state of the art WiFi "System of a Chip" allowing to be about 15 hours online and take hundreds of pictures.
Press the shooter button and the JPEG will be uploaded to a digital gallery in the next 4 seconds. It’s a pure WiFi camera, without a memory card, so you need to be online to use it. And that’s nowadays very easy, right? You just need to make a mobile hotspot on the phone if you are outside home. And if the camera does not detect a WiFi then creates an Access point called CAM-autoconnect for you to set up a new connection. 

### How to set up the connection
It's done in two easy steps:

    Then you have to connect to it through the phone and browse 162.168.4.1 there will greet you a “WiFi manager”
    Select a WiFi and write the credentials to make a connection
    You are all set, you just need to enable the hotspot and the camera will reset and connect to it automatically.

This is just the base program to enable you to have a fast demo to start with. The idea is that is fully open source DIY Camera where the users can modify and fully control the software that is running it. 

### Schematics

Please check the latest [electronics Schematics](https://fasarek.de/fs2-digital-camera.php) in our website Fasarek.de since it may be updated since it's a work in progress.

![electronics Schematics](https://fasarek.de/assets/fs2/Schematic_FS2-Camera_FS2_201810.png)

### Credits

[tablatronix WiFiManager](https://github.com/tzapu/WiFiManager) The amazing, configurable, extendable WiFiManager library made by tablatronix is the ground basement of this Camera
[Arducam](http://www.arducam.com) This camera has enabled many hobby electronic enthusiasts to make very interesting applications, with this Espressif chips, but also with Raspberry Pi. 
[3D-Print the FS2 Camera](https://www.thingiverse.com/thing:3135141) 
[Fasani](https://fasani.de) Lead programmer of this project

