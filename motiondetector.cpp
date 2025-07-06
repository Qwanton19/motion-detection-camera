#include "motiondetector.h"
#include <QDebug>

MotionDetector::MotionDetector(QObject *parent)
    : QObject(parent),
    m_enabled(true),
    m_threshold(20),
    m_sensitivity(50)
{
}

void MotionDetector::setEnabled(bool enabled)
{
    m_enabled = enabled;
    if (!m_enabled) {
        m_previousFrame = QImage();
    }
}

void MotionDetector::setThreshold(int threshold)
{
    m_threshold = threshold;
}

void MotionDetector::setSensitivity(int sensitivity)
{
    m_sensitivity = sensitivity;
}

QVector<QRect> MotionDetector::detect(const QImage &QtImage)
{
    QVector<QRect> motionRectangles;

    if (!m_enabled || m_previousFrame.isNull() || m_previousFrame.size() != QtImage.size()) {
        if (m_previousFrame.size() != QtImage.size()) {
            m_previousFrame = QImage(QtImage.size(), QImage::Format_RGB32);
            m_previousFrame.fill(Qt::black);
        } else {
            m_previousFrame = QtImage.copy();
        }
        return motionRectangles; // return empty vector
    }

    QImage grayPrevious = m_previousFrame.convertToFormat(QImage::Format_Grayscale8);
    QImage grayCurrent = QtImage.convertToFormat(QImage::Format_Grayscale8);
    const int blockSize = 16;
    const int width = grayCurrent.width();
    const int height = grayCurrent.height();
    QVector<QPoint> motionBlocks;
    for (int y = 0; y < height; y += blockSize) {
        for (int x = 0; x < width; x += blockSize) {
            int diffSum = 0, pixelCount = 0;
            for (int by = 0; by < blockSize && y + by < height; by++) {
                const uchar *prevLine = grayPrevious.constScanLine(y + by);
                const uchar *currLine = grayCurrent.constScanLine(y + by);
                for (int bx = 0; bx < blockSize && x + bx < width; bx++) {
                    int diff = qAbs(prevLine[x + bx] - currLine[x + bx]);
                    diffSum += diff;
                    pixelCount++;
                }
            }
            float avgChange = pixelCount > 0 ? diffSum / (float)pixelCount : 0;
            if (avgChange > m_threshold) {
                motionBlocks.append(QPoint(x / blockSize, y / blockSize));
            }
        }
    }

    if (!motionBlocks.isEmpty()) {
        QVector<int> labels(motionBlocks.size(), -1);
        int nextLabel = 0;
        for (int i = 0; i < motionBlocks.size(); i++) {
            if (labels[i] >= 0)
                continue;
            QQueue<int> queue;
            queue.enqueue(i);
            labels[i] = nextLabel;
            while (!queue.isEmpty()) {
                int idx = queue.dequeue();
                QPoint current = motionBlocks[idx];
                for (int j = 0; j < motionBlocks.size(); j++) {
                    if (labels[j] >= 0)
                        continue;
                    QPoint neighbor = motionBlocks[j];
                    if (qAbs(neighbor.x() - current.x()) <= 1 && qAbs(neighbor.y() - current.y()) <= 1) {
                        labels[j] = nextLabel;
                        queue.enqueue(j);
                    }
                }
            }
            nextLabel++;
        }

        QVector<QVector<QPoint>> componentBlocks(nextLabel);
        for (int i = 0; i < labels.size(); i++) {
            if (labels[i] >= 0)
                componentBlocks[labels[i]].append(motionBlocks[i]);
        }
        for (const QVector<QPoint> &component : componentBlocks) {
            if (component.size() < m_sensitivity / 3)
                continue;
            int minX = width, minY = height, maxX = 0, maxY = 0;
            for (const QPoint &p : component) {
                minX = qMin(minX, p.x() * blockSize);
                minY = qMin(minY, p.y() * blockSize);
                maxX = qMax(maxX, (p.x() + 1) * blockSize);
                maxY = qMax(maxY, (p.y() + 1) * blockSize);
            }
            QRect rect(qMax(0, minX), qMax(0, minY), qMin(width, maxX) - minX, qMin(height, maxY) - minY);
            if (rect.width() > blockSize * 2 && rect.height() > blockSize * 2)
                motionRectangles.append(rect);
        }
    }
    m_previousFrame = QtImage.copy();

    return motionRectangles;
}
