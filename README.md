# Motion Alert Project

This project is a Qt-based camera application that combines real-time video capture with a variety of multimedia features. It allows users to capture images, record videos, apply live effects (such as adjustable grayscale), overlay timestamps, detect motion, and automatically notify via email or save motion snapshots.

## Features

- **Real-time Video Capture:** Utilizes Qt's multimedia framework to capture video from an available camera.
- **Image Capture & Video Recording:** Users can take snapshots or record videos.
- **Live Image Effects:**
  - **Grayscale Effect:** Adjustable via a slider for a custom look.
  - **Timestamp Overlay:** Displays the current date and time on the captured image.
- **Motion Detection:**
  - Detects motion by comparing successive video frames.
  - Highlights motion regions with red rectangles.
- **Email Notifications:**
  - Sends an email alert with an attached image when motion is detected.
  - Configurable SMTP settings and destination email address.
- **Auto-Save Motion Images:** Optionally auto-save the motion-captured images with timestamped filenames.

## Requirements

- **Qt Framework:** Qt 5 or Qt 6
- **C++ Compiler:** Compatible with C++11 and higher
- **OpenSSL:** For secure email transmission via QSslSocket

## File Structure

- **main.cpp:** Initializes the application and displays the main window.
- **mainwindow.h / mainwindow.cpp:**
  - Implements the main user interface and core functionalities such as camera setup, video processing, and UI controls.
  - Contains logic for image capture, video recording, motion detection, and live effects.
- **emailsender.h / emailsender.cpp:**
  - Handles SMTP email communication.
  - Provides functionality to send an email (with optional attachment) over a secure connection using STARTTLS.

## Build Instructions

1. **Install Qt:** Make sure you have the appropriate Qt version installed.
2. **Configure the Project:**
   - If using **qmake**:
     ```bash
     qmake -project
     qmake
     ```
   - If using **CMake**, create a `CMakeLists.txt` that includes the necessary Qt modules.
3. **Compile the Application:**
   - For qmake:
     ```bash
     make
     ```
   - For CMake:
     ```bash
     cmake --build .
     ```
4. **Run the Application:**
   - Execute the generated binary:
     ```bash
     ./YourAppName
     ```

## Usage

- **Capture/Record:**
  - Use the **Capture** button to take snapshots.
  - Use the **Record** button to start and stop video recording.
- **Grayscale Effect:**
  - Adjust the grayscale slider to change the intensity of the effect.
- **Timestamp & Motion Detection:**
  - Toggle the "Show Timestamp" checkbox to overlay the current time on the video.
  - Toggle the "Motion Detection" checkbox to enable/disable motion detection.

