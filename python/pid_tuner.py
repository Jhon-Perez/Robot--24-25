# Credit to Veera Sai Joshik Unnam (719S) for the original idea
# of tuning the PID controller for the robot using a CSV file

import os
import matplotlib.pyplot as plt

def graph_pid_values(directory, file_name):
    """Graph PID values from a CSV file located in the specified directory."""
    print("Graphing...")
    
    # Construct the file path
    file_path = os.path.join(directory, file_name)
    
    # Initialize lists to store time and error values
    time_list = []
    error_list = []

    # Open the file and read data
    with open(file_path, 'r') as data_file:
        for row in data_file: 
            print(row.strip())  # Print each row for debugging
            time, error = row.split(',')
            time_list.append(float(time))
            error_list.append(float(error))
    
    # Plot the error over time
    plt.plot(time_list, error_list, label="error", color="black")
    
    # Define labels for the legend
    classes = ['Target', 'Error', 'Actual Right Front']
    
    # Set the labels for the x and y axes
    plt.xlabel("Time (ms)")
    plt.ylabel("Error (deg)")  
    
    # Display the legend
    plt.legend(labels=classes)
    
    # Show the plot
    plt.show()

def main():
    # Get the current working directory and data directories
    cwd = os.getcwd()
    data_dir = os.path.join(cwd, "data")
    
    # Define the directories for angular and linear data
    pid_dirs = {
        "angular": os.path.join(data_dir, "angular"),
        "linear": os.path.join(data_dir, "linear")
    }
    
    # Prompt the user to choose the directory and trial number
    choice = input("Enter the PID model ('linear' or 'angular'): ").strip().lower()
    trial_number = input("Enter the trial number: ").strip()
    
    # Construct the file name based on the user's input
    file_name = f"trial_{trial_number}.csv"
    
    # Graph the PID values based on the user's choice
    if choice in pid_dirs:
        graph_pid_values(pid_dirs[choice], file_name)
    else:
        print("Invalid choice. Please enter 'linear' or 'angular'.")

if __name__ == "__main__":
    main()
