import os

def remove_files(directory: str):
    """Remove all files in the specified directory."""
    files = os.listdir(directory)
    for file in files:
        file_path = os.path.join(directory, file)
        if os.path.isfile(file_path):
            os.remove(file_path)
            print(f"Removed {file}")

def main():
    # Get current working directory
    cwd = os.getcwd()
    data_dir = os.path.join(cwd, "data")

    # Directories to clean, if you need another model, add it here
    pid_dirs = {
        "angular": os.path.join(data_dir, "angular"),
        "linear": os.path.join(data_dir, "linear")
    }

    # Ask the user which directories to clean
    choice = input("Enter the directory to clean ('linear', 'angular', or 'both'): ").strip().lower()

    match choice:
        case "linear":
            remove_files(pid_dirs["linear"])
        case "angular":
            remove_files(pid_dirs["angular"])
        case "both":
            remove_files(pid_dirs["linear"])
            remove_files(pid_dirs["angular"])
        case _:
            print("Invalid choice. Please enter 'linear', 'angular', or 'both'.")

    print("All specified files removed")

if __name__ == "__main__":
    main()
