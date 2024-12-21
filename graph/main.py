import requests
import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation
import time 

# Server URL
URL = "http://192.168.212.93/data"

# Data storage for plotting
timestamps = []
temps = []
ecs = []
phs = []
watts = []

# Function to fetch data from the server
def fetch_data():
    try:
        response = requests.get(URL, timeout=5)  # Timeout after 5 seconds
        if response.status_code == 200:
            data = response.json()
            return {
                "Temp": data.get("Temp"),
                "EC": data.get("EC"),
                "PH": data.get("PH"),
                "Watt": data.get("Watt"),
                "Time": time.strftime("%H:%M:%S")  # Current time as timestamp
            }
        else:
            print(f"Error: Received status code {response.status_code}")
    except requests.exceptions.RequestException as e:
        print(f"Error: {e}")
    return None

# Function to update the graph
def update(frame):
    global timestamps, temps, ecs, phs, watts

    # Fetch new data
    data = fetch_data()
    if data:
        timestamps.append(data["Time"])
        temps.append(data["Temp"])
        ecs.append(data["EC"])
        phs.append(data["PH"])
        watts.append(data["Watt"])

        # Keep only the last N points
        N = 50
        timestamps = timestamps[-N:]
        temps = temps[-N:]
        ecs = ecs[-N:]
        phs = phs[-N:]
        watts = watts[-N:]

        # Clear and update subplots
        ax1.clear()
        ax2.clear()
        ax3.clear()
        ax4.clear()

        # Plot Temperature
        ax1.plot(timestamps, temps, label="Temperature (°C)", color="red", marker="o")
        ax1.set_ylabel("Temperature (°C)")
        ax1.set_xticks([])
        ax1.legend(loc="upper left")

        # Plot EC
        ax2.plot(timestamps, ecs, label="EC (mS/cm)", color="blue", marker="o")
        ax2.set_ylabel("EC (mS/cm)")
        ax2.set_xticks([])
        ax2.legend(loc="upper left")

        # Plot pH
        ax3.plot(timestamps, phs, label="pH", color="green", marker="o")
        ax3.set_ylabel("pH")
        ax3.set_xticks([])
        ax3.legend(loc="upper left")

        # Plot Watt
        ax4.plot(timestamps, watts, label="Watt (W)", color="purple", marker="o")
        ax4.set_ylabel("Watt (W)")
        ax4.set_xlabel("Timestamp")
        ax4.legend(loc="upper left")
        ax4.tick_params(axis='x', rotation=45)

# Setup Matplotlib Figure and Axes
fig, (ax1, ax2, ax3, ax4) = plt.subplots(4, 1, figsize=(10, 8), sharex=True)
fig.suptitle("Live Sensor Data", fontsize=16)

# Animate the graph
ani = FuncAnimation(fig, update, interval=1000)  # Update every 2 seconds

# Show the graph
plt.tight_layout()
plt.show()
