#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "motiondetector.h"
#include "cameramanager.h"
#include <QMainWindow>
#include <QVideoFrame>

class QPushButton;
class QLabel;
class QSlider;
class QCheckBox;
class QLineEdit;
class QGraphicsView;
class QGraphicsScene;
class QGraphicsPixmapItem;
class QTimer;
class QResizeEvent;
class QStackedWidget;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void resizeEvent(QResizeEvent *event) override;

private slots:
    void captureImage();
    void applyGrayscaleEffect(int value);
    void onFrameAvailable(const QVideoFrame &frame);
    void toggleTimestamp(Qt::CheckState state);
    void onImageCaptured(int id, const QImage &image);
    void processNextFrame();
    void toggleMotionDetection(Qt::CheckState state);
    void setMotionThreshold(int value);
    void setMotionSensitivity(int value);
    void toggleRecording();
    void updateRecordTime();
    void onRecorderError(const QString &errorString);
    void onCameraReady(bool ready);
    void toggleAutoSaveMotionImages(Qt::CheckState state);
    void handleAutoSaveMotionImage();
    void validateAndSetAutoSaveInterval();

private:
    void processFrame(const QVideoFrame &frame);

    Ui::MainWindow *ui;
    MotionDetector *m_motionDetector;
    CameraManager *m_cameraManager;
    QStackedWidget *m_viewStack;

    QGraphicsView *videoView;
    QGraphicsScene *videoScene;
    QGraphicsPixmapItem *videoItem;
    QPushButton *captureButton;
    QPushButton *recordButton;
    QLabel *noCameraLabel;
    QLabel *recordingTimeLabel;

    QSlider *grayscaleSlider;
    QLabel *sliderLabel;
    QCheckBox *timestampCheckbox;
    QCheckBox *motionDetectionCheckbox;
    QCheckBox *autoSaveImageCheckbox;
    QSlider *thresholdSlider;
    QSlider *sensitivitySlider;
    QLineEdit *autoSaveIntervalEdit;
    QLabel *autoSaveIntervalLabel;
    QLabel *currentIntervalLabel;

    QTimer *frameUpdateTimer;
    QTimer *recordingTimer;
    QTimer *autoSaveTimer;

    int grayscaleValue;
    bool showTimestamp;
    QImage lastProcessedImage;
    QVideoFrame currentFrame;
    bool processingFrame;
    bool updatePending;
    int recordingSeconds;

    bool autoSaveEnabled;
    bool autoSavePending;
    int autoSaveInterval;

};

#endif // MAINWINDOW_H
