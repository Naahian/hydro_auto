import requests
import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation
import time

# API endpoint for long polling
URL = "http://192.168.4.1/data"  # Replace with your ESP32's IP

# Data lists for plotting
timestamps = []  # Timestamps for the x-axis
temp_values = []  # Temperature values
ec_values = []    # EC values
ph_values = []    # PH values
watt_values = []  # Watt values

# Function to fetch data from the server
def fetch_data():
    try:
        response = requests.get(URL, timeout=60)  # Long polling with a 60-second timeout
        if response.status_code == 200:
            json_data = response.json()  # Parse JSON response
            timestamp = time.time()  # Use UNIX timestamp for better scrolling
            return timestamp, json_data
        else:
            print(f"Error: Received status code {response.status_code}")
    except requests.exceptions.RequestException as e:
        print(f"Error: {e}")
    return None, None

# Function to update the graph
def update(frame):
    global timestamps, temp_values, ec_values, ph_values, watt_values

    # Fetch new data
    timestamp, data = fetch_data()
    if timestamp and data:
        # Update data lists
        timestamps.append(timestamp)
        temp_values.append(data.get("Temp", 0))
        ec_values.append(data.get("EC", 0))
        ph_values.append(data.get("PH", 0))
        watt_values.append(data.get("Watt", 0))

        # Keep only the last N seconds of data
        window_size = 30  # Show the last 30 seconds of data
        while timestamps and (timestamps[-1] - timestamps[0] > window_size):
            timestamps.pop(0)
            temp_values.pop(0)
            ec_values.pop(0)
            ph_values.pop(0)
            watt_values.pop(0)

        # Clear and update the plot
        ax1.clear()
        ax2.clear()
        ax3.clear()
        ax4.clear()

        # Convert timestamps to relative time for the x-axis
        relative_timestamps = [t - timestamps[0] for t in timestamps]

        # Plot temperature
        ax1.plot(relative_timestamps, temp_values, marker='o', linestyle='-', color='r', label="Temp (°C)")
        ax1.set_title("Temperature")
        ax1.set_ylabel("°C")
        ax1.legend()

        # Plot EC
        ax2.plot(relative_timestamps, ec_values, marker='o', linestyle='-', color='b', label="EC (mS/cm)")
        ax2.set_title("EC")
        ax2.set_ylabel("mS/cm")
        ax2.legend()

        # Plot pH
        ax3.plot(relative_timestamps, ph_values, marker='o', linestyle='-', color='g', label="PH")
        ax3.set_title("PH")
        ax3.set_ylabel("PH")
        ax3.legend()

        # Plot Watt
        ax4.plot(relative_timestamps, watt_values, marker='o', linestyle='-', color='m', label="Watt (W)")
        ax4.set_title("Watt")
        ax4.set_ylabel("W")
        ax4.legend()

        # Adjust x-axis limits for scrolling
        ax1.set_xlim(0, window_size)
        ax2.set_xlim(0, window_size)
        ax3.set_xlim(0, window_size)
        ax4.set_xlim(0, window_size)

        plt.tight_layout()

# Setup the plot
fig, ((ax1, ax2), (ax3, ax4)) = plt.subplots(2, 2, figsize=(10, 6))
ani = FuncAnimation(fig, update, interval=1000)  # Update every second

# Show the graph
plt.show()
