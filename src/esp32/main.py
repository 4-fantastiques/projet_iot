import ujson as json
import time
import hashlib
import hmac
from machine import UART, Pin

# Product data configuration
APIKEY = "lry0mgtwjvqb537xoysw84hvaqwielif2lncab6notts4s8x1787doiylklpabpo"
DEVICE_DEVELOPER_ID = "7ef4fe2a-8a9c-4361-87d9-45f08bd1cca4"
DEVICE_CHECKSUM = "sN4bUPj71AYvHCT1b033Lga5+mMpmr+IeTlkmuSG1Rc="
DATA_VERSION = "S1"
protocol_version = "v3"

# Configure UART
uart = UART(2, baudrate=9600, tx=17, rx=16)  # Use GPIO 17 as TX and GPIO 16 as RX

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
        "checksum": "",
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

# Function to calculate the checksum
def calculate_checksum(payload_data, timestamp):
    # Extract the "data" part of the payload_data
    data_part = payload_data['data']

    # Convert the "data" part to a JSON string
    payload_json = json.dumps(data_part)
    print("\nDATA : ", payload_json)
    
    # Concatenate the 'at' and 'data' fields
    at_data_concatenated = str(timestamp) + payload_json
    print("\nCONCATENATION : ", at_data_concatenated, "\n")
    
    # Convert DEVICE_CHECKSUM to bytes
    device_checksum_bytes = DEVICE_CHECKSUM.encode('utf-8')
    
    # Calculate the HMAC SHA-1
    stream_bytes = at_data_concatenated.encode('utf-8')
    hmac_sha1 = hmac.new(device_checksum_bytes, stream_bytes, hashlib.sha1)
    
    # Get the HMAC SHA-1 value in hexadecimal
    checksum = hmac_sha1.hexdigest()
    print("Checksum:", checksum)
    return checksum

# Function to read data from UART
def read_uart():
    if uart.any():
        data = uart.readline()
        if data:
            print(data.decode('utf-8').strip())

# Main function to prepare JSON
def main():
    # List of data to send
    data_values = [
        ("variableId1", 10),
        ("variableId2", 10),
        ("variableId3", 40)
    ]

    # Create the data object
    timestamp = int(time.time())
    payload_data = create_data_object(data_values, timestamp)
    # Calculate the checksum
    calculated_checksum = calculate_checksum(payload_data, timestamp)
    
    # Assign the calculated checksum to the data object
    payload_data['checksum'] = calculated_checksum
    
    # Convert the final payload data to JSON string
    payload_json = json.dumps(payload_data)
    print("Prepared JSON payload:\n", payload_json)
    return payload_json

# Entry point of the program
if __name__ == "__main__":
    # Run the UART read in a loop
    while True:
        read_uart()
        time.sleep(0.1)
        
        # Prepare JSON periodically or based on some condition
        prepared_json = main()  # Prepare the JSON payload
