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

### Requirements to compile this

To compile this on Arduino and upload it to your ESP8266 board you will need the following things to be properly set up:

   WiFiManager library in it's latest version (Check credit links)

   The last ESP8266 Board in Arduino

   [Understanding how SPIFFS work and the library to upload a data folder](http://esp8266.github.io/Arduino/versions/2.0.0/doc/filesystem.html) This is because the Camera configuration is saved in a config.json file using SPI Flash File System 

   *An upload API endpoint* That is referred in the config.json . Please rename the data/config.json.dist to config.json and configure it to fit your system upload endpoint

   [Button2](https://github.com/LennartHennigs/Button2) Arduino Library to simplify working with buttons. It allows you to use callback functions to track single, double, triple and long clicks.

   The camera is a pure WiFi camera so it needs an upload endpoint, made in any language, that takes the POST request and uploads the image, responding with the image full URL. For an example about this please check my repository [repository php-gallery](https://github.com/martinberlin/php-gallery)

### config.json

   {
   "timelapse":    30,
   "upload_host" : "testweb.com",
   "upload_path" : "/upload.php?f=2018",
   "slave_cam_ip": ""
   }

*timelapse*   Seconds in timelapse mode (Enabled doing a long Shutter click of at least 2 seconds)
*upload_host* / path   the host and path to your upload script ( testweb.com/upload.php?f=2018 )
*slave_cam_ip*  BETA A GET ping that is made to another IP or host/capture on the moment of taking a picture. For ex. can be used to trigger IP/capture route of another camera, taking two picture at the same time when you shoot one camera

### Known limitations and bugs

My C++ skills to make a POST request may not work sometimes, WiFi can be not stable, and also the ESP8266 "System on a chip" boards are not meant to upload an Elephant in the internet. So 1 of 20 pictures may fail and will fail.
But well is not so tragic. Just do not expect a super high resolution. And start with Arducam 2MP, before going any further.
Resolution in 2MP can be 1600x1200 jpeg, filesize anywhere between 50 and 100K.
That takes here with fast WiFi about 4 / 5 seconds and connected through a mobile hotspot some seconds more. This resolutions was so far the best in my tests because going higher, you get more resolution, but also a higher fail rate.
For a PHP upload endpoint please check the upload.php sample using my 
[repository php-gallery](https://github.com/martinberlin/php-gallery) (A bootstrap4 very simple PHP gallery)


### Credits

[tablatronix WiFiManager](https://github.com/tzapu/WiFiManager) The amazing, configurable, extendable WiFiManager library made by tablatronix is the ground basement of this Camera

[Arducam](http://www.arducam.com) This camera has enabled many hobby electronic enthusiasts to make very interesting applications, with this Espressif chips, but also with Raspberry Pi

[3D-Print the FS2 Camera](https://www.thingiverse.com/thing:3135141) 

[Fasani](https://fasani.de) Lead programmer of this project

