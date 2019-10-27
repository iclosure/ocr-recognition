#ifndef IMAGELABEL_H
#define IMAGELABEL_H

#include "global.h"
#include <QLabel>

// class ImageLabel

class ImageLabel : public QLabel
{
    Q_OBJECT
public:
    explicit ImageLabel(QWidget *parent = nullptr);
    ~ImageLabel() J_OVERRIDE;

    bool isClickable() const;

    QString filePath() const;

signals:
    void clickableChanged(bool enabled);
    void filePathChanged(const QString &filePath);

public slots:
    void setClickable(bool enabled);

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void enterEvent(QEvent *event) override;
    void leaveEvent(QEvent *event) override;
    void paintEvent(QPaintEvent *) override;

private:
    QString filePath_;
    bool clickable_;
};

#endif // IMAGELABEL_H
