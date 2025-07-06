#ifndef MOTIONDETECTOR_H
#define MOTIONDETECTOR_H

#include <QObject>
#include <QImage>
#include <QVector>
#include <QRect>
#include <QQueue>

class MotionDetector : public QObject
{
    Q_OBJECT
public:
    explicit MotionDetector(QObject *parent = nullptr);

    QVector<QRect> detect(const QImage &QtImage);

    void setEnabled(bool enabled);
    void setThreshold(int threshold);
    void setSensitivity(int sensitivity);

private:
    bool m_enabled;
    int m_threshold;
    int m_sensitivity;
    QImage m_previousFrame;
};

#endif // MOTIONDETECTOR_H
