#ifndef ABOUTDIALOG_H
#define ABOUTDIALOG_H

#include <QDialog>

class AboutDialog : public QDialog
{
    Q_OBJECT
public:
    explicit AboutDialog(QWidget *parent = nullptr);

private:
};

#endif // ABOUTDIALOG_H