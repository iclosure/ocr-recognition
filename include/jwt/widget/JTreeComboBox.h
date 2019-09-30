#ifndef JTREECOMBOBOX_H
#define JTREECOMBOBOX_H

#include "../global.h"
#include "JComboBox.h"
#include <QTreeWidget>

class JTreeComboBoxPrivate;

class JWT_EXPORT JTreeComboBox : public JComboBox
{
    Q_OBJECT
public:
    explicit JTreeComboBox(QWidget *parent = nullptr);
    ~JTreeComboBox() J_OVERRIDE;

Q_SIGNALS:

public Q_SLOTS:

private:
    Q_DISABLE_COPY(JTreeComboBox)
    J_DECLARE_PRIVATE(JTreeComboBox)
};

#endif // JTREECOMBOBOX_H
