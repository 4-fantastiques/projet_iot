from machine import UART, Pin
import time

# Configure UART
uart = UART(2, baudrate=9600, tx=17, rx=16)  # Use GPIO 17 as TX and GPIO 16 as RX

# Function to read data from UART
def read_uart():
    if uart.any():
        data = uart.readline()
        if data:
            print(data.decode('utf-8').strip())

# Main loop
while True:
    read_uart()
    time.sleep(0.1)