#ifndef OCRMGR_H
#define OCRMGR_H

#include "global.h"
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/types_c.h>

class OCRMgrPrivate;

class OCRMgr : public QObject
{
    Q_OBJECT
public:
    bool init();

    static void qImageToCvMat(const QImage &image, cv::OutputArray &matOut);
    static QImage cvMatToQImage(const cv::Mat &inMat);
    static QPixmap cvMatToQPixmap(const cv::Mat &inMat);

    QStringList test(const cv::Mat &imBinary,
                     const std::vector<std::vector<cv::Point> > &contours,
                     const QSize &size);
    QStringList test(cv::Mat imSource, const QSize &size,
                     QPixmap *pmSource, QPixmap *pmBinary);
    QStringList test(const QString &filePath, const QSize &size,
                     QPixmap *pmSource = nullptr, QPixmap *pmBinary = nullptr);
    QStringList test(const QImage &image, const QSize &size,
                     QPixmap *pmSource = nullptr, QPixmap *pmBinary = nullptr);

Q_SIGNALS:

public Q_SLOTS:

private:
    explicit OCRMgr(QObject *parent = nullptr);
    ~OCRMgr() J_OVERRIDE;

private:
    Q_DISABLE_COPY(OCRMgr)
    J_DECLARE_PRIVATE(OCRMgr)
    J_DECLARE_SINGLE_INSTANCE(OCRMgr)
};

#endif // LOGGING_H
