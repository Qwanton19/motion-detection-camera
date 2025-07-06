#ifndef CAMERAMANAGER_H
#define CAMERAMANAGER_H

#include <QObject>
#include <QVideoFrame>
#include <QImage>

class QCamera;
class QImageCapture;
class QMediaCaptureSession;
class QMediaRecorder;
class QVideoSink;

class CameraManager : public QObject
{
    Q_OBJECT
public:
    explicit CameraManager(QObject *parent = nullptr);
    ~CameraManager();

    void start();
    void captureImage();
    bool startRecording(const QUrl &outputUrl);
    void stopRecording();
    bool isRecording() const;

signals:
    void frameAvailable(const QVideoFrame &frame);
    void imageCaptured(int id, const QImage &preview);
    void cameraReady(bool ready);
    void recorderError(const QString &errorString);

private slots:
    void onVideoFrameChanged(const QVideoFrame &frame);
    void onImageCaptured(int id, const QImage &preview);
    void onRecorderError();

private:
    QCamera *m_camera;
    QImageCapture *m_imageCapture;
    QMediaCaptureSession *m_captureSession;
    QMediaRecorder *m_mediaRecorder;
    QVideoSink *m_videoSink;
};

#endif // CAMERAMANAGER_H
