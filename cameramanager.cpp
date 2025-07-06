#include "cameramanager.h"
#include "qaudiodevice.h"
#include <QCamera>
#include <QImageCapture>
#include <QMediaCaptureSession>
#include <QMediaRecorder>
#include <QVideoSink>
#include <QMediaDevices>
#include <QAudioInput>
#include <QCameraDevice>
#include <QMediaFormat>

CameraManager::CameraManager(QObject *parent) : QObject(parent)
{
    m_camera = nullptr;
    m_imageCapture = nullptr;
    m_captureSession = new QMediaCaptureSession(this);
    m_mediaRecorder = nullptr;
    m_videoSink = new QVideoSink(this);

    connect(m_videoSink, &QVideoSink::videoFrameChanged, this, &CameraManager::onVideoFrameChanged);
}

CameraManager::~CameraManager()
{
    if (m_camera) {
        m_camera->stop();
    }
}

void CameraManager::start()
{
    QList<QCameraDevice> cameras = QMediaDevices::videoInputs();
    if (cameras.isEmpty()) {
        emit cameraReady(false);
        return;
    }

    m_camera = new QCamera(cameras.first(), this);

    QCameraFormat bestFormat;
    const QList<QCameraFormat> formats = cameras.first().videoFormats();
    if (!formats.isEmpty()) {
        for (const QCameraFormat &format : formats) {
            if (format.resolution().width() <= 640 && format.resolution().height() <= 480) {
                bestFormat = format;
                break;
            }
        }
        if (!bestFormat.isNull())
            m_camera->setCameraFormat(bestFormat);
    }

    m_imageCapture = new QImageCapture(this);
    connect(m_imageCapture, &QImageCapture::imageCaptured, this, &CameraManager::onImageCaptured);

    m_mediaRecorder = new QMediaRecorder(this);
    connect(m_mediaRecorder, &QMediaRecorder::errorChanged, this, &CameraManager::onRecorderError);

    m_captureSession->setCamera(m_camera);
    m_captureSession->setImageCapture(m_imageCapture);
    m_captureSession->setRecorder(m_mediaRecorder);
    m_captureSession->setVideoSink(m_videoSink);

    m_camera->start();
    emit cameraReady(true);
}

void CameraManager::captureImage()
{
    if (m_imageCapture && m_imageCapture->isReadyForCapture()) {
        m_imageCapture->capture();
    }
}

bool CameraManager::startRecording(const QUrl &outputUrl)
{
    if (!m_mediaRecorder) return false;

    QMediaFormat mediaFormat;
    mediaFormat.setFileFormat(QMediaFormat::FileFormat::MPEG4);
    mediaFormat.setVideoCodec(QMediaFormat::VideoCodec::H264);
    mediaFormat.setAudioCodec(QMediaFormat::AudioCodec::AAC);
    m_mediaRecorder->setMediaFormat(mediaFormat);
    m_mediaRecorder->setQuality(QMediaRecorder::NormalQuality);

    QAudioDevice audioDevice = QMediaDevices::defaultAudioInput();
    if (!audioDevice.isNull()) {
        QAudioInput *audioInput = new QAudioInput(audioDevice, this);
        m_captureSession->setAudioInput(audioInput);
    }

    m_mediaRecorder->setOutputLocation(outputUrl);
    m_mediaRecorder->record();
    return true;
}

void CameraManager::stopRecording()
{
    if (m_mediaRecorder) {
        m_mediaRecorder->stop();
    }
}

bool CameraManager::isRecording() const
{
    return m_mediaRecorder && m_mediaRecorder->recorderState() == QMediaRecorder::RecorderState::RecordingState;
}

void CameraManager::onVideoFrameChanged(const QVideoFrame &frame)
{
    emit frameAvailable(frame);
}

void CameraManager::onImageCaptured(int id, const QImage &preview)
{
    emit imageCaptured(id, preview);
}

void CameraManager::onRecorderError()
{
    emit recorderError(m_mediaRecorder->errorString());
}
