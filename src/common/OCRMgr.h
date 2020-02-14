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

    static bool boundRectImage(std::vector<std::vector<cv::Point> > &contours,
                               cv::Mat &imSource, cv::Mat &imBinary, int threshold,
                               const QSize &anchorOpenClose, const QSize &anchorErode,
                               QPixmap *pmSource = nullptr, QPixmap *pmBinary = nullptr);
    static bool boundRectImage(std::vector<std::vector<cv::Point> > &contours,
                               const QImage &image, cv::Mat &imSource, cv::Mat &imBinary, int threshold,
                               const QSize &anchorOpenClose, const QSize &anchorErode,
                               QPixmap *pmSource = nullptr, QPixmap *pmBinary = nullptr);
    static bool boundRectImage(std::vector<std::vector<cv::Point> > &contours,
                               const QString &filePath, cv::Mat &imSource, cv::Mat &imBinary,
                               int threshold, const QSize &anchorOpenClose, const QSize &anchorErode,
                               QPixmap *pmSource = nullptr, QPixmap *pmBinary = nullptr);

    QStringList test(const cv::Mat &imBinary,
                     const std::vector<std::vector<cv::Point> > &contours,
                     const QSize &erodeSize);
    QStringList test(cv::Mat imSource,  int threshold, const QSize &anchorOpenClose,
                     const QSize &erodeSize, QPixmap *pmSource, QPixmap *pmBinary);
    QStringList test(const QString &filePath, int threshold, const QSize &anchorOpenClose,
                     const QSize &erodeSize, QPixmap *pmSource = nullptr,
                     QPixmap *pmBinary = nullptr);
    QStringList test(const QImage &image, int threshold, const QSize &anchorOpenClose,
                     const QSize &erodeSize, QPixmap *pmSource = nullptr, QPixmap *pmBinary = nullptr);

    static bool removeInvalidLine(cv::Mat &imBinary);

    static const char *tessVariableValue();

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
