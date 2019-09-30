#ifndef JMESSAGEBOX_H
#define JMESSAGEBOX_H

#include "../global.h"
#include "../style/JShadowDialog.h"
#include <QMessageBox>

// class JMessageBoxDetailsText

#if QT_CONFIG(textedit)
#include <QTextEdit>
class JWT_EXPORT JMessageBoxDetailsText : public QWidget
{
    Q_OBJECT
public:
    class TextEdit : public QTextEdit
    {
    public:
        TextEdit(QWidget *parent = nullptr) : QTextEdit(parent) { }
#ifndef QT_NO_CONTEXTMENU
        void contextMenuEvent(QContextMenuEvent * e) Q_DECL_OVERRIDE;
#endif // QT_NO_CONTEXTMENU
    };

    JMessageBoxDetailsText(QWidget *parent = nullptr);
    void setText(const QString &text);
    QString text() const;

    bool copy();
    void selectAll();

private Q_SLOTS:
    void textCopyAvailable(bool available);

private:
    bool copyAvailable;
    TextEdit *textEdit;
};
#endif // QT_CONFIG(textedit)

// class JMessageBox

class JMessageBoxPrivate;
class QLabel;
class QAbstractButton;
class QCheckBox;

class JWT_EXPORT JMessageBox : public JShadowDialog
{
    Q_OBJECT
    Q_PROPERTY(QString text READ text WRITE setText)
    Q_PROPERTY(QMessageBox::Icon icon READ icon WRITE setIcon)
    Q_PROPERTY(QPixmap iconPixmap READ iconPixmap WRITE setIconPixmap)
    Q_PROPERTY(Qt::TextFormat textFormat READ textFormat WRITE setTextFormat)
    Q_PROPERTY(QMessageBox::StandardButtons standardButtons READ standardButtons WRITE setStandardButtons)
#if QT_CONFIG(textedit)
    Q_PROPERTY(QString detailedText READ detailedText WRITE setDetailedText)
#endif
    Q_PROPERTY(QString informativeText READ informativeText WRITE setInformativeText)
    Q_PROPERTY(Qt::TextInteractionFlags textInteractionFlags READ textInteractionFlags WRITE setTextInteractionFlags)
public:
    explicit JMessageBox(QWidget *parent = nullptr);
    JMessageBox(QMessageBox::Icon icon, const QString &title, const QString &text,
                QMessageBox::StandardButtons buttons = QMessageBox::NoButton,
                QWidget *parent = nullptr);
    ~JMessageBox() J_OVERRIDE;


    void addButton(QAbstractButton *button, QMessageBox::ButtonRole role);
    QPushButton *addButton(const QString &text, QMessageBox::ButtonRole role);
    QPushButton *addButton(QMessageBox::StandardButton button);
    void removeButton(QAbstractButton *button);

    using QDialog::open;
    void open(QObject *receiver, const char *member);

    QList<QAbstractButton *> buttons() const;
    QMessageBox::ButtonRole buttonRole(QAbstractButton *button) const;

    void setStandardButtons(QMessageBox::StandardButtons buttons);
    QMessageBox::StandardButtons standardButtons() const;
    QMessageBox::StandardButton standardButton(QAbstractButton *button) const;
    QAbstractButton *button(QMessageBox::StandardButton which) const;

    QPushButton *defaultButton() const;
    void setDefaultButton(QPushButton *button);
    void setDefaultButton(QMessageBox::StandardButton button);

    QAbstractButton *escapeButton() const;
    void setEscapeButton(QAbstractButton *button);
    void setEscapeButton(QMessageBox::StandardButton button);

    QAbstractButton *clickedButton() const;

    QString text() const;
    void setText(const QString &text);

    QMessageBox::Icon icon() const;
    void setIcon(QMessageBox::Icon);

    QPixmap iconPixmap() const;
    void setIconPixmap(const QPixmap &pixmap);

    Qt::TextFormat textFormat() const;
    void setTextFormat(Qt::TextFormat format);

    void setTextInteractionFlags(Qt::TextInteractionFlags flags);
    Qt::TextInteractionFlags textInteractionFlags() const;

    void setCheckBox(QCheckBox *cb);
    QCheckBox* checkBox() const;

    static QMessageBox::StandardButton information(QWidget *parent, const QString &title,
                                                   const QString &text, QMessageBox::StandardButtons buttons = QMessageBox::Ok,
                                                   QMessageBox::StandardButton defaultButton = QMessageBox::NoButton);
    static QMessageBox::StandardButton question(QWidget *parent, const QString &title,
                                                const QString &text, QMessageBox::StandardButtons buttons =
            QMessageBox::StandardButtons(QMessageBox::Yes | QMessageBox::No),
                                                QMessageBox::StandardButton defaultButton = QMessageBox::NoButton);
    static QMessageBox::StandardButton warning(QWidget *parent, const QString &title,
                                               const QString &text, QMessageBox::StandardButtons buttons = QMessageBox::Ok,
                                               QMessageBox::StandardButton defaultButton = QMessageBox::NoButton);
    static QMessageBox::StandardButton critical(QWidget *parent, const QString &title,
                                                const QString &text, QMessageBox::StandardButtons buttons = QMessageBox::Ok,
                                                QMessageBox::StandardButton defaultButton = QMessageBox::NoButton);
    static void about(QWidget *parent, const QString &title, const QString &text);
    static void aboutQt(QWidget *parent, const QString &title = QString());

    // the following functions are obsolete:

    JMessageBox(const QString &title, const QString &text, QMessageBox::Icon icon,
                int button0, int button1, int button2,
                QWidget *parent = nullptr,
                Qt::WindowFlags f = Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);

    static int information(QWidget *parent, const QString &title,
                           const QString& text,
                           int button0, int button1 = 0, int button2 = 0);
    static int information(QWidget *parent, const QString &title,
                           const QString& text,
                           const QString& button0Text,
                           const QString& button1Text = QString(),
                           const QString& button2Text = QString(),
                           int defaultButtonNumber = 0,
                           int escapeButtonNumber = -1);
    inline static QMessageBox::StandardButton
    information(QWidget *parent, const QString &title,
                const QString& text,
                QMessageBox::StandardButton button0,
                QMessageBox::StandardButton button1 = QMessageBox::NoButton)
    { return information(parent, title, text, QMessageBox::StandardButtons(button0), button1); }

    static int question(QWidget *parent, const QString &title,
                        const QString& text,
                        int button0, int button1 = 0, int button2 = 0);
    static int question(QWidget *parent, const QString &title,
                        const QString& text,
                        const QString& button0Text,
                        const QString& button1Text = QString(),
                        const QString& button2Text = QString(),
                        int defaultButtonNumber = 0,
                        int escapeButtonNumber = -1);
    inline static int question(QWidget *parent, const QString &title,
                               const QString& text,
                               QMessageBox::StandardButton button0, QMessageBox::StandardButton button1)
    { return question(parent, title, text, QMessageBox::StandardButtons(button0), button1); }

    static int warning(QWidget *parent, const QString &title,
                       const QString& text,
                       int button0, int button1, int button2 = 0);
    static int warning(QWidget *parent, const QString &title,
                       const QString& text,
                       const QString& button0Text,
                       const QString& button1Text = QString(),
                       const QString& button2Text = QString(),
                       int defaultButtonNumber = 0,
                       int escapeButtonNumber = -1);
    inline static int warning(QWidget *parent, const QString &title,
                              const QString& text,
                              QMessageBox::StandardButton button0, QMessageBox::StandardButton button1)
    { return warning(parent, title, text, QMessageBox::StandardButtons(button0), button1); }

    static int critical(QWidget *parent, const QString &title,
                        const QString& text,
                        int button0, int button1, int button2 = 0);
    static int critical(QWidget *parent, const QString &title,
                        const QString& text,
                        const QString& button0Text,
                        const QString& button1Text = QString(),
                        const QString& button2Text = QString(),
                        int defaultButtonNumber = 0,
                        int escapeButtonNumber = -1);
    inline static int critical(QWidget *parent, const QString &title,
                               const QString& text,
                               QMessageBox::StandardButton button0, QMessageBox::StandardButton button1)
    { return critical(parent, title, text, QMessageBox::StandardButtons(button0), button1); }

    QString buttonText(int button) const;
    void setButtonText(int button, const QString &text);

    QString informativeText() const;
    void setInformativeText(const QString &text);

#if QT_CONFIG(textedit)
    QString detailedText() const;
    void setDetailedText(const QString &text);
#endif

    void setWindowTitle(const QString &title);
    void setWindowModality(Qt::WindowModality windowModality);

    static QPixmap standardIcon(QMessageBox::Icon icon);

Q_SIGNALS:
    void buttonClicked(QAbstractButton *button);

#ifdef Q_QDOC
public slots:
    int exec();
#endif

protected:
    bool event(QEvent *e) Q_DECL_OVERRIDE;
    void resizeEvent(QResizeEvent *event) Q_DECL_OVERRIDE;
    void showEvent(QShowEvent *event) Q_DECL_OVERRIDE;
    void closeEvent(QCloseEvent *event) Q_DECL_OVERRIDE;
    void keyPressEvent(QKeyEvent *event) Q_DECL_OVERRIDE;
    void changeEvent(QEvent *event) Q_DECL_OVERRIDE;

private Q_SLOTS:
    void _q_buttonClicked(QAbstractButton *button);

private:
    Q_DISABLE_COPY(JMessageBox)
    J_DECLARE_PRIVATE(JMessageBox)
};

#endif // JMESSAGEBOX_H
