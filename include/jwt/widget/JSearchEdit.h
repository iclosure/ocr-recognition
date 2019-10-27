#ifndef JSEARCHEDIT_H
#define JSEARCHEDIT_H

#include "../global.h"
#include <QWidget>

class QLineEdit;
class JSearchEditPrivate;

class JWT_EXPORT JSearchEdit : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(QString text READ text WRITE setText NOTIFY textChanged)
public:
    explicit JSearchEdit(QWidget *parent = nullptr);
    ~JSearchEdit() J_OVERRIDE;

    const QPixmap *searchIcon() const;
    void setSearchIcon(const QPixmap &pixmap);

    QString text() const;

    QLineEdit *lineEdit() const;

Q_SIGNALS:
    void textChanged(const QString &text);

public Q_SLOTS:
    void setText(const QString &text);
    void clear();

private:
    Q_DISABLE_COPY(JSearchEdit)
    J_DECLARE_PRIVATE(JSearchEdit)
};

#endif // JSEARCHEDIT_H
