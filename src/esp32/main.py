from machine import UART, Pin
import network
import time
import ujson as json
import urequests
import ntptime

# Product data configuration
APIKEY = "lry0mgtwjvqb537xoysw84hvaqwielif2lncab6notts4s8x1787doiylklpabpo"
DEVICE_DEVELOPER_ID = "7ef4fe2a-8a9c-4361-87d9-45f08bd1cca4"
DATA_VERSION = "S1"
protocol_version = "v2"  # Using v2 protocol for initial testing

# Configure UART
uart = UART(2, baudrate=9600, tx=17, rx=16)  # Use GPIO 17 as TX and GPIO 16 as RX

# Function to connect to Wi-Fi
def connect_to_wifi():
    sta_if = network.WLAN(network.STA_IF)
    sta_if.active(True)
    sta_if.connect('Coworking', 'C0w0rking!')
    
    while not sta_if.isconnected():
        Pin(2, Pin.OUT).value(1)
        time.sleep(0.2)
        Pin(2, Pin.OUT).value(0)
        time.sleep(0.2)
    
    Pin(2, Pin.OUT).value(1)
    print("Connected to WiFi:", sta_if.ifconfig())

# Function to synchronize time with NTP server
def sync_time():
    try:
        ntptime.settime()
        print("Time synchronized with NTP server")
    except Exception as e:
        print("Failed to synchronize time:", e)

# Function to create the data object
def create_data_object(data_values, timestamp):
    datasets = []

    # Create datasets from provided data values
    for ref, value in data_values:
        datasets.append({"ref": ref, "at": timestamp, "value": value})

    # Create the data object
    data_object = {
        "protocol": protocol_version,
        "device": DEVICE_DEVELOPER_ID,
        "at": timestamp,
        "data": {
            "ver": DATA_VERSION,
            "dataset": [{
                "at": timestamp,
                "columns": ["ref", "value"],
                "values": [[d["ref"], d["value"]] for d in datasets]
            }]
        }
    }
    return data_object

# Function to read data from UART
def read_uart():
    if uart.any():
        data = uart.readline()
        if data:
            return data.decode('utf-8').strip()
    return None

# Function to send the request with the JSON data
def send_request(payload_data):
    url = "https://streams-api.magicbuilder.io/streams/"
    headers = {
        'Content-Type': 'application/json',
        'apikey': APIKEY
    }
   
    # Send the POST request with the JSON data
    try:
        response = urequests.post(url, headers=headers, json=payload_data, timeout=10)
        return response.text
    except Exception as e:
        return str(e)

# Main function to prepare JSON and send data
def main():
    # Initialize the list for storing data values
    data_values = []

    while True:
        uart_data = read_uart()
        if uart_data:
            print(f"Raw UART data: {uart_data}")  # Debug print statement

            try:
                # Extract data from UART and add to data_values list
                if "Temperature:" in uart_data:
                    temperature = float(uart_data.split(":")[1].replace("C", "").strip())
                    data_values.append(("temperature", temperature))
                elif "Humidity:" in uart_data:
                    humidity = float(uart_data.split(":")[1].replace("%", "").strip())
                    data_values.append(("humidity", humidity))
                elif "Light level:" in uart_data:
                    light_level = float(uart_data.split(":")[1].replace("%", "").strip())
                    data_values.append(("light_level", light_level))
                elif "Sound level:" in uart_data:
                    sound_level = float(uart_data.split(":")[1].strip())
                    data_values.append(("sound_level", sound_level))
                elif "redButtonState" in uart_data:
                    red_button_state = int(uart_data.split(":")[1].strip())
                    data_values.append(("red_button_state", red_button_state))
                elif "greenButtonState" in uart_data:
                    green_button_state = int(uart_data.split(":")[1].strip())
                    data_values.append(("green_button_state", green_button_state))
            except ValueError as e:
                print(f"Error parsing UART data: {e}")

        # Once we have collected all necessary data, prepare and send the JSON payload
        if len(data_values) >= 5:  # Assuming we are collecting 5 different values
            # Getting the current timestamp
            ts = time.time()
            ts += 946677600

            print("Timestamp:", ts)
            payload_data = create_data_object(data_values, ts)
            payload_json = json.dumps(payload_data)
            print("Prepared JSON payload:\n", payload_json)
            
            response = send_request(payload_data)
            print("Response from server:\n", response)

            # Clear data_values list for the next round of data collection
            data_values.clear()

        time.sleep(2)

# Entry point of the program
if __name__ == "__main__":
    # Connect to Wi-Fi
    connect_to_wifi()
    
    # Synchronize time with NTP server
    sync_time()
    
    # Run main function
    main()
