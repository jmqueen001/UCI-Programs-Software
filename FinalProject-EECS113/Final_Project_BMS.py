import RPi.GPIO as GPIO
import Adafruit_LCD1602 as LCD
from PCF8574 import PCF8574_GPIO
import Freenove_DHT as DHT
import time
print("hello world")

# Pin configuration
DHT_PIN = 11       # GPIO pin connected to DHT11 sensor
PIR_Sensor = 13      # GPIO pin connected to PIR sensor
GREEN_LED = 40       # GPIO pin connected to green LED
RED_LED = 12      # GPIO pin connected to red LED
BLUE_LED = 16     # GPIO pin connected to blue LED
DOOR_WINDOW_PIN = 18   # GPIO pin connected to door/window sensor
LCD_PIN = 3          # GPIO pin connected to LCD

# Humidity and Temperature Sensor setup
Temp_sensor = DHT.DHT(DHT_PIN)

# HVAC settings
desired_temperature = 70
hvac_status = "OFF"

# Energy consumption settings
ac_consumption = 18000
heater_consumption = 36000
kwh_rate = 0.50
total_energy_consumption = 0

# Door/Window status
door_window_status = "Closed"

# GPIO setup
GPIO.setmode(GPIO.BOARD)
GPIO.setup(PIR_Sensor, GPIO.IN)
GPIO.setup(DHT_PIN, GPIO.IN)
GPIO.setup(GREEN_LED, GPIO.OUT)
GPIO.setup(RED_LED, GPIO.OUT)
GPIO.setup(BLUE_LED, GPIO.OUT)
GPIO.setup(DOOR_WINDOW_PIN, GPIO.IN, pull_up_down=GPIO.PUD_UP)
GPIO.setup(LCD_PIN, GPIO.OUT)

# Function to control LCD display


def display_on_lcd(message):
    # Write code to display message on the LCD
    LCD.setCursor(0, 0)  # set cursor position
    LCD.message(message)  # display
    time.sleep(1)

# Function to turn on HVAC


def turn_on_hvac():
    global hvac_status
    GPIO.output(BLUE_LED, GPIO.HIGH)
    GPIO.output(RED_LED, GPIO.LOW)
    hvac_status = "AC"
    display_on_lcd("AC is on")
    time.sleep(3)
    display_on_lcd("")

# Function to turn on HVAC


def turn_on_heater():
    global hvac_status
    GPIO.output(BLUE_LED, GPIO.LOW)
    GPIO.output(RED_LED, GPIO.HIGH)
    hvac_status = "Heater"
    display_on_lcd("Heater is on")
    time.sleep(3)
    display_on_lcd("")

# Function to turn off HVAC


def turn_off_hvac():
    global hvac_status
    GPIO.output(BLUE_LED, GPIO.LOW)
    GPIO.output(RED_LED, GPIO.LOW)
    hvac_status = "OFF"

# Function to calculate energy consumption and cost


def calculate_energy_cost(consumption):
    global total_energy_consumption
    kwh = consumption / 1000
    total_energy_consumption += kwh
    cost = total_energy_consumption * kwh_rate
    display_on_lcd("Energy: {:.2f} KWh, Cost: ${:.2f}".format(
        total_energy_consumption, cost))


try:
    while True:
        # Read motion detection from PIR sensor
        motion_detected = GPIO.input(PIR_Sensor)

        if motion_detected:
            GPIO.output(GREEN_LED, GPIO.HIGH)  # Turn on green LED
            # Calculate energy consumption
            calculate_energy_cost(ac_consumption)
            time.sleep(10)  # Keep lights on for 10 seconds
        else:
            GPIO.output(GREEN_LED, GPIO.LOW)   # Turn off green LED

        door_window_button_status = GPIO.input(DOOR_WINDOW_PIN)
        if door_window_button_status == GPIO.LOW:
            door_window_status = "Open"
            turn_off_hvac()  # Turn off HVAC when door/window is open
            display_on_lcd("Door/Window open!")
            time.sleep(3)
            display_on_lcd("")
        else:
            door_window_status = "Closed"
            display_on_lcd("Door/Window closed")

        humidity, temperature = DHT.read_retry(Temp_sensor, 4)
        if humidity is not None and temperature is not None:
            # Read temperature and humidity from DHT11 sensor
            temperature = round(temperature)
            humidity = round(humidity)

            # Fetch humidity data from CIMIS
            # Calculate weather index
            weather_index = temperature + 0.05 * humidity
            weather_index = round(weather_index)

            if weather_index > 95:
                # Fire alarm condition
                display_on_lcd("Emergency: Fire Alarm!")
                GPIO.output(RED_LED, GPIO.HIGH)  # Flash red LED
                turn_off_hvac()
            else:
                # Check HVAC status based on temperature and weather index
                if hvac_status == "OFF":
                    if weather_index >= desired_temperature + 3:
                        turn_on_hvac()
                    elif weather_index <= desired_temperature - 3:
                        turn_on_heater()
                elif hvac_status == "AC":
                    if weather_index < desired_temperature:
                        turn_off_hvac()
                elif hvac_status == "Heater":
                    if weather_index > desired_temperature:
                        turn_off_hvac()

            # Update LCD with temperature, humidity, weather index, and HVAC status
            display_on_lcd("Temp: {}C, Humidity: {}%, Weather Index: {}".format(
                temperature, humidity, weather_index))
        else:
            display_on_lcd("Failed to retrieve data from DHT11 sensor.")

        time.sleep(1)  # Pause for 1 second

except KeyboardInterrupt:
    GPIO.cleanup()  # Clean up GPIO on program exit
    LCD.clear()

####################################
