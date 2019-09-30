#ifndef JGRIDBOX_H
#define JGRIDBOX_H

#include "../global.h"
#include "JGroupBox.h"
#include <QGridLayout>

class JGridBoxPrivate;

class JWT_EXPORT JGridBox : public JGroupBox
{
    Q_OBJECT
    Q_PROPERTY(Qt::Orientation flow READ flow WRITE setFlow)
    Q_PROPERTY(int columnSpacing READ columnSpacing WRITE setColumnSpacing)
    Q_PROPERTY(int rowSpacing READ rowSpacing WRITE setRowSpacing)
    Q_PROPERTY(int columns READ columns WRITE setColumns)
    Q_PROPERTY(int rows READ rows WRITE setRows)
public:
    explicit JGridBox(QWidget *parent = nullptr);
    explicit JGridBox(const QString &title, QWidget *parent = nullptr);
    ~JGridBox() J_OVERRIDE;

    Qt::Orientation flow() const;
    int columnSpacing() const;
    int rowSpacing() const;
    int columns() const;
    int rows() const;

    QGridLayout *mainLayout() const;

    void appendWidget(QWidget *widget, int rowSpan = 1, int columnSpan = 1);

Q_SIGNALS:

public Q_SLOTS:
    void setFlow(Qt::Orientation orientation);
    void setColumnSpacing(int spacing);
    void setRowSpacing(int spacing);
    void setColumns(int count);
    void setRows(int count);

private:
    Q_DISABLE_COPY(JGridBox)
    J_DECLARE_PRIVATE(JGridBox)
};

#endif // JGRIDBOX_H
