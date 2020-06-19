This project was done in collaboration with Prathamesh Kale

# Automatic Seed Planter

# Aim of the project:
 The aim of this project was to build a bot which would plough, plant seeds and water the field and then levels it up with voice commands. 
 
# Hardware : 
Arduino Mega was used to run the logic behind all the commands and pass on the control signals to stepper motors/ motors of the bot/ ESP 8266.

Stepper Motors were connected for ploughing and seeding mechanisms and were actuated only during the forward movement. Other than that ultrasonic sensors were connected to ESP8266 directly. 

# Software :
Two files : 

Google_Robot : Takes in command from the Google Assistant and correspondingly conveys to the bot. Along with that, publishes the level of seeds and water on the Adafruit server

Bot_code : Actuates the motor to go forward, left, right, back or stops them upon receiving the commands from ESP 8266. Actuates the stepper motors for the ploughs and seeding mechanisms during the forward motion.
