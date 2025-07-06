# 📸 Motion Detector Camera

A real-time motion detection application developed for **CS3377**, built with C++ and the Qt Framework.

This project captures live video from a connected camera, processes each frame to detect motion, and provides a range of customizable visual effects and controls.

## 🚀 Features & Controls

The user interface provides a comprehensive set of tools to manage the video feed and detection parameters.

*   **Real-time Video Feed**: Displays a live feed from the default system camera.
*   **Advanced Motion Detection**:
    *   Highlights moving objects with red rectangles in real-time.
    *   Adjust the motion `Threshold` and `Sensitivity` with dedicated sliders to fine-tune detection.
*   **Live Image Effects**:
    *   **Grayscale**: Apply an adjustable grayscale filter using a slider.
    *   **Timestamp**: Overlay the current date and time on the video feed.
*   **Capture & Record**:
    *   `Capture` button saves the current processed frame as an image.
    *   `Record` button saves the live feed as an `.mp4` video file, including audio.
*   **Automated Motion Saving**:
    *   Optionally enable **Auto-Save Motion** to automatically save a snapshot whenever motion is detected.
    *   The cooldown `Interval` between saves can be precisely set in seconds.

## 🛠️ Installation & Compilation

### Prerequisites
*   **Qt Framework:** [Qt 5 or Qt 6](https://www.qt.io/download) (Qt Creator is recommended.
*   **C++ Compiler:** A modern compiler that supports C++17.

1.  Clone the repository to your local machine.
2.  Open **Qt Creator** and use `File > Open File or Project...` to load the `MotionDetection.pro` file.
4.  Click the **Build** button, then the **Run** button.
