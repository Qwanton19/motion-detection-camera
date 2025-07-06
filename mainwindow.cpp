#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPushButton>
#include <QImage>
#include <QFileDialog>
#include <QLabel>
#include <QVBoxLayout>
#include <QVideoFrame>
#include <QPainter>
#include <QDateTime>
#include <QFont>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include <QTimer>
#include <QStandardPaths>
#include <QMessageBox>
#include <QResizeEvent>
#include <QDebug>
#include <QCheckBox>
#include <QSlider>
#include <QLineEdit>
#include <QDoubleValidator>
#include <QStackedWidget>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::MainWindow),
    grayscaleValue(0),
    showTimestamp(true),
    processingFrame(false),
    updatePending(false),
    recordingSeconds(0),
    autoSaveEnabled(false),
    autoSavePending(false),
    autoSaveInterval(30000) // 30 seconds default
{
    ui->setupUi(this);
    setWindowTitle("Motion Detector Camera");
    setWindowIcon(QIcon(":/images/camera-icon.png"));
    resize(800, 600);

    m_motionDetector = new MotionDetector(this);
    m_cameraManager = new CameraManager(this);

    videoScene = new QGraphicsScene(this);
    videoView = new QGraphicsView(videoScene, this);
    videoView->setAlignment(Qt::AlignCenter);
    videoView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    videoView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    videoView->setViewportUpdateMode(QGraphicsView::MinimalViewportUpdate);
    videoView->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
    videoView->setCacheMode(QGraphicsView::CacheBackground);
    videoView->setOptimizationFlags(QGraphicsView::DontAdjustForAntialiasing |
                                    QGraphicsView::DontSavePainterState);

    videoItem = new QGraphicsPixmapItem();
    videoScene->addItem(videoItem);

    noCameraLabel = new QLabel("Searching for camera...", this);
    noCameraLabel->setAlignment(Qt::AlignCenter);
    noCameraLabel->setStyleSheet("color: gray; font-size: 16px;");

    m_viewStack = new QStackedWidget(this);
    m_viewStack->addWidget(videoView);
    m_viewStack->addWidget(noCameraLabel);
    m_viewStack->setCurrentWidget(noCameraLabel);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(m_viewStack);

    timestampCheckbox = new QCheckBox("Show Timestamp", this);
    timestampCheckbox->setChecked(true);
    connect(timestampCheckbox, &QCheckBox::checkStateChanged, this, &MainWindow::toggleTimestamp);

    motionDetectionCheckbox = new QCheckBox("Motion Detection", this);
    motionDetectionCheckbox->setChecked(true);
    connect(motionDetectionCheckbox, &QCheckBox::checkStateChanged, this, &MainWindow::toggleMotionDetection);

    autoSaveImageCheckbox = new QCheckBox("Auto-Save Motion", this);
    autoSaveImageCheckbox->setChecked(false);
    connect(autoSaveImageCheckbox, &QCheckBox::checkStateChanged, this, &MainWindow::toggleAutoSaveMotionImages);

    // row 1
    QHBoxLayout *controlsLayout = new QHBoxLayout;
    controlsLayout->setSpacing(30);
    controlsLayout->addStretch();

    captureButton = new QPushButton("Capture", this);
    captureButton->setFixedWidth(100);
    connect(captureButton, &QPushButton::clicked, this, &MainWindow::captureImage);
    controlsLayout->addWidget(captureButton);

    recordButton = new QPushButton("Record", this);
    recordButton->setFixedWidth(100);
    connect(recordButton, &QPushButton::clicked, this, &MainWindow::toggleRecording);
    controlsLayout->addWidget(recordButton);

    recordingTimeLabel = new QLabel("00:00", this);
    recordingTimeLabel->setVisible(false);
    controlsLayout->addWidget(recordingTimeLabel);

    sliderLabel = new QLabel("Grayscale:", this);
    controlsLayout->addWidget(sliderLabel);

    grayscaleSlider = new QSlider(Qt::Horizontal, this);
    grayscaleSlider->setRange(0, 100);
    grayscaleSlider->setValue(0);
    grayscaleSlider->setTickInterval(10);
    grayscaleSlider->setTickPosition(QSlider::TicksBelow);
    grayscaleSlider->setFixedWidth(120);
    connect(grayscaleSlider, &QSlider::valueChanged, this, &MainWindow::applyGrayscaleEffect);
    controlsLayout->addWidget(grayscaleSlider);

    controlsLayout->addWidget(timestampCheckbox);
    controlsLayout->addStretch();
    layout->addLayout(controlsLayout);

    // row 2
    QHBoxLayout *motionControlsLayout = new QHBoxLayout;
    motionControlsLayout->setSpacing(30);
    motionControlsLayout->addStretch();
    motionControlsLayout->addWidget(motionDetectionCheckbox);

    QLabel *thresholdLabel = new QLabel("Threshold:", this);
    motionControlsLayout->addWidget(thresholdLabel);
    thresholdSlider = new QSlider(Qt::Horizontal, this);
    thresholdSlider->setRange(5, 50);
    thresholdSlider->setValue(20);
    thresholdSlider->setTickInterval(10);
    thresholdSlider->setTickPosition(QSlider::TicksBelow);
    thresholdSlider->setMaximumWidth(150);
    connect(thresholdSlider, &QSlider::valueChanged, this, &MainWindow::setMotionThreshold);
    motionControlsLayout->addWidget(thresholdSlider);

    QLabel *sensitivityLabel = new QLabel("Sensitivity:", this);
    motionControlsLayout->addWidget(sensitivityLabel);
    sensitivitySlider = new QSlider(Qt::Horizontal, this);
    sensitivitySlider->setRange(5, 90);
    sensitivitySlider->setValue(50);
    sensitivitySlider->setTickInterval(10);
    sensitivitySlider->setTickPosition(QSlider::TicksBelow);
    sensitivitySlider->setMaximumWidth(150);
    connect(sensitivitySlider, &QSlider::valueChanged, this, &MainWindow::setMotionSensitivity);
    motionControlsLayout->addWidget(sensitivitySlider);
    motionControlsLayout->addStretch();
    layout->addLayout(motionControlsLayout);

    // row 3
    QHBoxLayout *autoSaveControlsLayout = new QHBoxLayout;
    autoSaveControlsLayout->setSpacing(30);
    autoSaveControlsLayout->addStretch();

    autoSaveControlsLayout->addWidget(autoSaveImageCheckbox);

    autoSaveIntervalLabel = new QLabel("Interval (s):", this);
    autoSaveControlsLayout->addWidget(autoSaveIntervalLabel);

    autoSaveIntervalEdit = new QLineEdit(this);
    autoSaveIntervalEdit->setText(QString::number(autoSaveInterval / 1000.0, 'f', 1));
    autoSaveIntervalEdit->setPlaceholderText("1.0 - 500.0");
    autoSaveIntervalEdit->setFixedWidth(80);

    QDoubleValidator *validator = new QDoubleValidator(1.0, 500.0, 2, this);
    validator->setNotation(QDoubleValidator::StandardNotation);
    autoSaveIntervalEdit->setValidator(validator);

    connect(autoSaveIntervalEdit, &QLineEdit::editingFinished, this, &MainWindow::validateAndSetAutoSaveInterval);
    autoSaveControlsLayout->addWidget(autoSaveIntervalEdit);

    currentIntervalLabel = new QLabel(this);
    currentIntervalLabel->setText(QString("(Current: %1s)").arg(QString::number(autoSaveInterval / 1000.0, 'f', 1)));
    autoSaveControlsLayout->addWidget(currentIntervalLabel);

    autoSaveControlsLayout->addStretch();
    layout->addLayout(autoSaveControlsLayout);


    QWidget *centralWidget = new QWidget(this);
    centralWidget->setLayout(layout);
    setCentralWidget(centralWidget);

    frameUpdateTimer = new QTimer(this);
    frameUpdateTimer->setSingleShot(true);
    connect(frameUpdateTimer, &QTimer::timeout, this, &MainWindow::processNextFrame);

    recordingTimer = new QTimer(this);
    connect(recordingTimer, &QTimer::timeout, this, &MainWindow::updateRecordTime);

    autoSaveTimer = new QTimer(this);
    autoSaveTimer->setInterval(autoSaveInterval);
    autoSaveTimer->setSingleShot(true);

    // connect to the camera manager's signals
    connect(m_cameraManager, &CameraManager::frameAvailable, this, &MainWindow::onFrameAvailable);
    connect(m_cameraManager, &CameraManager::imageCaptured, this, &MainWindow::onImageCaptured);
    connect(m_cameraManager, &CameraManager::cameraReady, this, &MainWindow::onCameraReady);
    connect(m_cameraManager, &CameraManager::recorderError, this, &MainWindow::onRecorderError);

    m_cameraManager->start();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onCameraReady(bool ready)
{
    if (ready) {
        m_viewStack->setCurrentWidget(videoView);
    } else {
        noCameraLabel->setText("No camera detected, please plug one in and restart the application.");
        m_viewStack->setCurrentWidget(noCameraLabel);
        captureButton->setEnabled(false);
        recordButton->setEnabled(false);
    }
}

void MainWindow::captureImage()
{
    if (!lastProcessedImage.isNull()) {
        QString filePath = QFileDialog::getSaveFileName(this, "save image", "", "images (*.png *.jpg *.bmp)");
        if (!filePath.isEmpty())
            lastProcessedImage.save(filePath);
    } else {
        m_cameraManager->captureImage();
    }
}

void MainWindow::toggleRecording()
{
    if (!m_cameraManager->isRecording()) {
        QString videoLocation = QStandardPaths::writableLocation(QStandardPaths::MoviesLocation);
        QString fileName = videoLocation + "/camerarecording_" +
                           QDateTime::currentDateTime().toString("yyyyMMdd_hhmmss") + ".mp4";
        fileName = QFileDialog::getSaveFileName(this, tr("save video"), fileName, tr("video files (*.mp4)"));
        if (fileName.isEmpty())
            return;

        m_cameraManager->startRecording(QUrl::fromLocalFile(fileName));

        recordButton->setText("stop");
        recordButton->setStyleSheet("background-color: red; color: white;");
        recordingTimeLabel->setVisible(true);
        recordingSeconds = 0;
        updateRecordTime();
        recordingTimer->start(1000);
        captureButton->setEnabled(false);
    } else {
        m_cameraManager->stopRecording();

        recordButton->setText("record");
        recordButton->setStyleSheet("");
        recordingTimer->stop();
        recordingTimeLabel->setVisible(false);
        captureButton->setEnabled(true);
    }
}

void MainWindow::updateRecordTime()
{
    recordingSeconds++;
    int minutes = recordingSeconds / 60;
    int seconds = recordingSeconds % 60;
    recordingTimeLabel->setText(QString("%1:%2")
                                    .arg(minutes, 2, 10, QChar('0'))
                                    .arg(seconds, 2, 10, QChar('0')));
}

void MainWindow::onRecorderError(const QString &errorString)
{
    if (m_cameraManager->isRecording()) {
        toggleRecording();
    }
    QMessageBox::critical(this, tr("recording error"), errorString);
}

void MainWindow::onImageCaptured(int id, const QImage &image)
{
    Q_UNUSED(id);
    QString filePath = QFileDialog::getSaveFileName(this, "save image", "", "images (*.png *.jpg *.bmp)");
    if (!filePath.isEmpty())
        image.save(filePath);
}

void MainWindow::applyGrayscaleEffect(int value)
{
    grayscaleValue = value;
}

void MainWindow::toggleTimestamp(Qt::CheckState state)
{
    showTimestamp = (state == Qt::Checked);
}

void MainWindow::toggleMotionDetection(Qt::CheckState state)
{
    m_motionDetector->setEnabled(state == Qt::Checked);
}

void MainWindow::setMotionThreshold(int value)
{
    m_motionDetector->setThreshold(value);
}

void MainWindow::setMotionSensitivity(int value)
{
    m_motionDetector->setSensitivity(value);
}

void MainWindow::onFrameAvailable(const QVideoFrame &frame)
{
    currentFrame = frame;
    if (!processingFrame && !frameUpdateTimer->isActive()) {
        frameUpdateTimer->start(33); // schedule or it wont work
        updatePending = true;
    } else {
        updatePending = true;
    }
}

void MainWindow::processNextFrame()
{
    if (!updatePending || !currentFrame.isValid())
        return;

    processingFrame = true;
    updatePending = false;

    processFrame(currentFrame);

    processingFrame = false;

    if (updatePending)
        frameUpdateTimer->start(33);
}

void MainWindow::processFrame(const QVideoFrame &frame)
{
    if (!frame.isValid())
        return;
    QImage image = frame.toImage();
    if (image.isNull())
        return;
    QImage processedImage = image.convertToFormat(QImage::Format_RGB32);

    if (grayscaleValue > 0) {
        float grayscaleFactor = grayscaleValue / 100.0f;
        for (int y = 0; y < processedImage.height(); y++) {
            QRgb *line = reinterpret_cast<QRgb*>(processedImage.scanLine(y));
            for (int x = 0; x < processedImage.width(); x++) {
                QRgb pixel = line[x];
                int r = qRed(pixel), g = qGreen(pixel), b = qBlue(pixel);
                int gray = qRound(0.299 * r + 0.587 * g + 0.114 * b);
                r = qRound(r * (1 - grayscaleFactor) + gray * grayscaleFactor);
                g = qRound(g * (1 - grayscaleFactor) + gray * grayscaleFactor);
                b = qRound(b * (1 - grayscaleFactor) + gray * grayscaleFactor);
                line[x] = qRgb(r, g, b);
            }
        }
    }

    QVector<QRect> motionRectangles = m_motionDetector->detect(processedImage);

    if (!motionRectangles.isEmpty()) {
        QPainter painter(&processedImage);
        painter.setPen(QPen(Qt::red, 3));
        for (const QRect &rect : motionRectangles)
            painter.drawRect(rect);
        painter.end();
    }

    if (showTimestamp) {
        QPainter painter(&processedImage);
        QString timestampText = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
        QFont font = painter.font();
        font.setPointSize(20);
        font.setBold(true);
        painter.setFont(font);
        int margin = 30;
        QRect textRect(margin, margin, processedImage.width() - (margin * 2), 30);
        painter.setPen(Qt::black);
        for (int dx = -1; dx <= 1; dx++) {
            for (int dy = -1; dy <= 1; dy++) {
                if (dx == 0 && dy == 0)
                    continue;
                painter.drawText(textRect.adjusted(dx, dy, dx, dy), Qt::AlignRight, timestampText);
            }
        }
        painter.setPen(Qt::white);
        painter.drawText(textRect, Qt::AlignRight, timestampText);
        painter.end();
    }

    lastProcessedImage = processedImage;
    videoItem->setPixmap(QPixmap::fromImage(processedImage));

    QRectF currentRect = videoScene->sceneRect();
    QRectF itemRect = videoItem->boundingRect();
    if (qAbs(currentRect.width() - itemRect.width()) > 5 ||
        qAbs(currentRect.height() - itemRect.height()) > 5) {
        videoScene->setSceneRect(itemRect);
        videoView->fitInView(videoScene->sceneRect(), Qt::KeepAspectRatio);
    }

    if (autoSaveEnabled && !motionRectangles.isEmpty() && !autoSaveTimer->isActive() && !autoSavePending) {
        autoSavePending = true;
        QTimer::singleShot(1000, this, &MainWindow::handleAutoSaveMotionImage);
    }
}

void MainWindow::toggleAutoSaveMotionImages(Qt::CheckState state)
{
    autoSaveEnabled = (state == Qt::Checked);
    qDebug() << "auto-save motion images toggled:" << autoSaveEnabled;
}

void MainWindow::handleAutoSaveMotionImage()
{
    QString picturesDir = QStandardPaths::writableLocation(QStandardPaths::PicturesLocation);
    QString timestamp = QDateTime::currentDateTime().toString("yyyyMMdd_hhmmss");
    QString fileName = picturesDir + "/motion_" + timestamp + ".png";
    if (lastProcessedImage.save(fileName))
        qDebug() << "motion image auto-saved to:" << fileName;
    else
        qDebug() << "failed to auto-save motion image.";
    autoSavePending = false;
    autoSaveTimer->start();
}

void MainWindow::validateAndSetAutoSaveInterval()
{
    QString text = autoSaveIntervalEdit->text();
    bool ok;
    double value = text.toDouble(&ok);

    if (ok && value >= 1.0 && value <= 500.0) {
        autoSaveInterval = static_cast<int>(value * 1000.0);
        autoSaveTimer->setInterval(autoSaveInterval);
        currentIntervalLabel->setText(QString("(Current: %1s)").arg(QString::number(value, 'f', 1)));
        qDebug() << "Auto-save interval updated to" << value << "seconds.";
    } else {
        qWarning() << "Invalid auto-save interval entered. Reverting to previous value.";
        autoSaveIntervalEdit->setText(QString::number(autoSaveInterval / 1000.0, 'f', 1));
    }
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    QMainWindow::resizeEvent(event);
    if (videoView && !videoScene->sceneRect().isEmpty())
        videoView->fitInView(videoScene->sceneRect(), Qt::KeepAspectRatio);
}
