#ifndef JUTRALEDIT_H
#define JUTRALEDIT_H

#include <QScrollArea>
#include "../global.h"

class JUtralEditPrivate;

class JWT_EXPORT JUtralEdit : public QScrollArea
{
    Q_OBJECT
    Q_PROPERTY(QString title READ title WRITE setTitle NOTIFY titleChanged)
    Q_PROPERTY(bool asciiVisible READ isAsciiVisible WRITE setAsciiVisible NOTIFY asciiVisibleChanged)
    Q_PROPERTY(int columnCount READ columnCount WRITE setColumnCount NOTIFY columnCountChanged)
    Q_PROPERTY(int showType READ showType WRITE setShowType NOTIFY showTypeChanged)
    Q_PROPERTY(bool showTypeVisible READ showTypeVisible WRITE setShowTypeVisible NOTIFY showTypeVisibleChanged)
    Q_PROPERTY(bool editable READ editable WRITE setEditable NOTIFY editableChanged)
    Q_PROPERTY(QString text READ text WRITE setText NOTIFY textChanged)
    Q_PROPERTY(int maximumBlockCount READ maximumBlockCount WRITE setMaximumBlockCount NOTIFY maximumBlockCountChanged)
    Q_PROPERTY(QColor dataColor READ dataColor WRITE setDataColor NOTIFY dataColorChanged)
public:
    enum ShowType {
        ShowAsHexData,    // default
        ShowAsString
    };
    Q_ENUM(ShowType)

    explicit JUtralEdit(bool menuVisible = false, QWidget *parent = nullptr);
    ~JUtralEdit() J_OVERRIDE;

    QString title() const;
    bool isAsciiVisible() const;
    int columnCount() const;
    int showType() const;
    bool showTypeVisible() const;
    bool editable() const;

    QString text() const;       // from string-type
    QByteArray hexData() const;    // from hex-type

    int maximumBlockCount() const;

    QColor dataColor() const;

    void updateUi();
    void updateUi(const QByteArray &data);
    void updateUi(const void *data, int size, int offset = 0);

    QByteArray buffer();
    const QByteArray &buffer() const;
    int bufferOffset() const;

Q_SIGNALS:
    void titleChanged(const QString &text);
    void asciiVisibleChanged(bool checked);
    void columnCountChanged(int count);
    void showTypeChanged(int showType);
    void showTypeVisibleChanged(bool visible);
    void editableChanged(bool enabled);
    void textChanged();
    void maximumBlockCountChanged(int count);
    void dataColorChanged(const QColor &color);
    void triggledClose();

public Q_SLOTS:
    void setTitle(const QString &text);
    void setAsciiVisible(bool visible);
    void setColumnCount(int count);
    void setShowType(int showType);
    void setShowTypeVisible(bool visible);
    void setEditable(bool enabled);
    void setText(const QString &text);
    void setMaximumBlockCount(int count);
    void setDataColor(const QColor &color);

private:
    Q_DISABLE_COPY(JUtralEdit)
    J_DECLARE_PRIVATE(JUtralEdit)
};

#endif // JUTRALEDIT_H
