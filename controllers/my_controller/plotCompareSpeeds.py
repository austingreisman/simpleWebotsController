import pandas as pd
import matplotlib.pyplot as plt
from matplotlib.ticker import MaxNLocator
import os

# Load the CSV data
filename = "SpeedVsGPSTS_32.csv"
file_path = os.path.dirname(os.path.abspath(__file__)) + "/" + filename
print(file_path)

# Read the CSV file directly into a DataFrame
data = pd.read_csv(file_path)

# Print column names to verify
print("Columns in the CSV:", data.columns)

# Drop rows with NaN values
data_clean = data.dropna()

# Add a time column safely using .loc
data_clean = data_clean.copy()  # Ensure it's a full copy
data_clean.loc[:, 'Time'] = range(len(data_clean))

# Verify the presence of 'CommandedSpeed' in the data
if 'CommandedSpeed' not in data_clean.columns:
    raise KeyError("The 'CommandedSpeed' column is missing from the CSV file. Please verify its name.")

# Modify CommandedSpeed for a step input starting at 0
time_with_step = [0] + data_clean['Time'].tolist()
commanded_speed_with_step = [0] + data_clean['CommandedSpeed'].tolist()

# Plot the data
plt.figure(figsize=(10, 6))
plt.plot(data_clean['Time'], data_clean['WheelSpeed'], label="WheelSpeed")
plt.plot(data_clean['Time'], data_clean['GPSSpeed'], label="GPSSpeed")
plt.plot(time_with_step, commanded_speed_with_step, label="CommandedSpeed (Step)")

# Add labels, title, and legend
ax = plt.gca()  # Get current axes
ax.yaxis.set_major_locator(MaxNLocator(nbins=5))  # Limit to 5 major ticks
plt.xlabel("Time")
plt.ylabel("Speed (m/s)")
plt.title("Speed Comparison <- " + filename)
plt.legend()

# Show the plot
plt.grid()
plt.show()
