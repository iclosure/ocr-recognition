#ifndef HOMEWINDOW_H
#define HOMEWINDOW_H

#include <QLabel>
#include "global.h"

// class LabelImage

class LabelImage : public QLabel
{
    Q_OBJECT
public:
    explicit LabelImage(QWidget *parent = nullptr);
    ~LabelImage() J_OVERRIDE;

    bool isClickable() const;

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

// class HomeWidget

class JSplitter;
class QPlainTextEdit;

class HomeWindow : public QWidget
{
    Q_OBJECT
public:
    explicit HomeWindow(QWidget *parent = nullptr);
    ~HomeWindow() override;

    bool init();

signals:

public slots:

private:
    Q_DISABLE_COPY(HomeWindow)
    JSplitter *splitter_;
    LabelImage *labelImSource_;
    LabelImage *labelImBinary_;
    QPlainTextEdit *editDevInfo_;
};

#endif // HOMEWINDOW_H
