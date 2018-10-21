# FS2
## ESP8266 WiFi powered digital Camera

### The FS2 is a digital Polaroid that uploads the photo instantly to the cloud
This project serves as a base to explore Arducam possibilities in combination with a WiFI "System on a Chip" such as ESP8266 to create a simple WiFi point-and-shoot digital camera.
This is a work in progress, and only schematics is provided, but it can work out of the box if you can connect 8 Serial Parallel Interface cables from the camera to a Wemos D1 or similar and upload this example with the described requirements. Please open an issue if you can't compile it and I will try to help and fill the missing requirements.
This is just the base program to enable you to have a fast demo to start with. The idea is that is fully open source DIY Camera where the users can modify and fully control the software that is running it. 

### What is powering this camera
This WiFi instant camera is powered by a 2000mA/hr LiOn battery and Espressif state of the art WiFi "System of a Chip" allowing to be about 15 hours online and take hundreds of pictures.
Press the shooter button and the JPEG will be uploaded to a digital gallery in the next 4 seconds. It’s a pure WiFi camera, without a memory card, so you need to be online to use it. And that’s nowadays very easy, right? You just need to make a mobile hotspot on the phone if you are outside home. And if the camera does not detect a WiFi then creates an Access point called CAM-autoconnect for you to set up a new connection. 

### How to set up the connection
It's done in two easy steps:

    1 . Turn on the camera and connect to CAM-autoconnect through any device, browse 162.168.4.1 
        and there will greet you the “WiFi manager”
    2 . Select a WiFi and write the credentials to make a connection
        You are all set, you just need to enable the hotspot and the camera will reset and connect
        to it automatically.

### Schematics
Please check the latest [electronics Schematics](https://fasarek.de/fs2-digital-camera.php) in our website Fasarek.de since it may be updated since it's a work in progress. There you will find also the hardware components that are just a few and you will need a 2.54 small PCB board to fit the components (35*56 mm).

![electronics Schematics](https://fasarek.de/assets/fs2/Schematic_FS2-Camera_FS2_201810.png)

### Photos previews in Php-gallery
Please check this small gallery for Photo samples taken with the 2MP Arducam model and this camera:
[FS2 Photo previews](https://fasarek.de/php-gallery/gallery/index.php)

### Requirements to compile this
To compile this on Arduino and upload it to your ESP8266 board you will need the following things to be properly set up:

   WiFiManager library in it's latest version (Check credit links)

   The last ESP8266 Board in Arduino.

   [Understanding how SPIFFS work and the library to upload a data folder](http://esp8266.github.io/Arduino/versions/2.0.0/doc/filesystem.html) This is because the Camera configuration is saved in a config.json file using SPI Flash File System.
   
   Arduino JSON Library. I literally copied WiFi Manager example to build the config.json
   IMPORTANT: Any version > 5.13.3 gives me an error on compiling. I still didn't found exactly why I would be glad if you make me aware, so please downgrade your Arduino Json lib when compiling this.

   *UPDATE the upload API endpoint* in the config.json . Please rename the data/config.json.dist to config.json and configure it to fit your system upload endpoint that will receive the Post request from the camera.

   [Button2](https://github.com/LennartHennigs/Button2) Arduino Library to simplify working with buttons. It allows you to use callback functions to track single, double, triple and long clicks.

   The camera is a pure WiFi camera so it needs an upload endpoint, made in any language, that takes the POST request and uploads the image responding with the image full URL. For an example about this please check the script upload.php in my [repository php-gallery](https://github.com/martinberlin/php-gallery)
   
   LAZY to bring together all this?
   Just ask and I will post somewhere a download link with the compiled binary file!

### config.json

    {
     "timelapse":    30,
     "upload_host" : "testweb.com",
     "upload_path" : "/upload.php?f=2018",
     "slave_cam_ip": ""
    }
    
    on develop branch there is a new property called jpeg_size 

**timelapse**  Seconds in timelapse mode till next picture (Enabled doing a long Shutter click of at least 2 seconds)

**upload_host** / path   the host and path to your upload script ( testweb.com/upload.php?f=2018 )

**slave_cam_ip**  BETA This is GET ping that is made to another IP or host with a fixed path: /capture on the moment of taking a picture. For ex. can be used to trigger IP the capture route of another camera, taking two pictures at the same time when you shoot one of the cameras triggering the other as a 'slave camera'. UPDATING this slightly it could be used to ping any script to trigger an action when taking a photo, like sending an email or giving a signal to another IoT device.

NOTE: The new config is saved as a file in SPIFFS only if the new connection is succesfull ! Take out the boxing gloves before typing your Wifi password ;)

### Latest experimental features are on develop branch
Please pull develop to help us testing new features.

New features currently being tested are:

    - Force start in Wifi Manager mode with the route /wifi/reset
    - Configure Arducam model changing one line
    - jpegSize resolutiom with the 5 bigger settings added as a new parameter and stored in SPIFFS config.json
    - SPIFFS File manager

### Known limitations and bugs
My C++ skills to make a POST are not fail safe, WiFi can be not stable all times, and also the ESP8266 "System on a chip" boards are not meant to upload an Elephant in the internet. So 1 of 20 pictures may fail and will fail.
But well is not so tragic. Just do not expect a super high resolution. And start with Arducam 2 megapixels before going any further.
Max. resolution in Arducam 2MP can be 1600x1200 jpeg and filesize anywhere between 50 and 100K.
That takes here with fast WiFi about 4 / 5 seconds and connected through a mobile hotspot some seconds more. This resolutions was so far the best in my tests because going higher, you get more resolution, but also a higher fail rate. So it's possible to use an Arducam 5MP and take more higher resolution images but I don't really see the point right now, since it's not failsafe. 
To be clear: It just makes a POST push attempt without any checks or whatsoever to a PHP endpoint, that will not upload anything if the image does not arrive entirely, logging a partial upload exception in your server. Other than that it will work allright most of the time being my current fault rate about 1 fail in 20 pictures. 
For a PHP upload endpoint please check the upload.php sample using my 
[repository php-gallery](https://github.com/martinberlin/php-gallery) (A bootstrap4 very simple PHP gallery)

### Get involved and fork this

The main idea to build this was to learn more of C++ and IoT specially when dealing with bigger requests as sending an image through this small boards. Challenges are many if you would like to collaborate:

    1. FAILSAFE UPLOAD detect if the upload went wrong and try to repeat it 2 or 3 times giving
       a signal to the user when succeded
    2. EXTEND THIS to work also taking advantage of Arducam 5Mp and their 8 megas flash memory. 
       That will enable taking pictures offline up to this native storage capacity.
    3. OFFLINE PICTURES adding a flash card reader to this for the Arducam 2MP
       Also would be possible to save the images on SPIFFS but it has a writing limit like any SD Card
    4. SYNC OFFLINE TO ONLINE when camera finds an available WIFI
    
This are only some of the next goals. But is your camera, your software, so make what you want from it and learn in the process.

### Credits

[tablatronix WiFiManager](https://github.com/tzapu/WiFiManager) The amazing, configurable, extendable WiFiManager library made by tablatronix is the ground basement of this Camera

[Arducam](http://www.arducam.com) This camera has enabled many hobby electronic enthusiasts to make very interesting applications, with this Espressif chips, but also with Raspberry Pi

[3D-Print the FS2 Camera](https://www.thingiverse.com/thing:3135141) 

[Fasani](https://fasani.de) Lead programmer of this project

