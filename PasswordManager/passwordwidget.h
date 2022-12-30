// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

#ifndef PASSWORDWIDGET_H
#define PASSWORDWIDGET_H

#include "newentrytab.h"
#include "tablemodel.h"

#include <QItemSelection>
#include <QTabWidget>

QT_BEGIN_NAMESPACE
class QSortFilterProxyModel;
class QItemSelectionModel;
QT_END_NAMESPACE

//! [0]
class PasswordWidget : public QTabWidget
{
    Q_OBJECT

public:
    PasswordWidget(QWidget *parent = nullptr);
    void readFromFile(const QString &fileName);
    void writeToFile(const QString &fileName);

public slots:
    void showAddEntryDialog();
    void addEntry(const QString &username, const QString &password,
                  const QString &date, const QString &description);
    void editEntry();
    void removeEntry();

signals:
    void selectionChanged (const QItemSelection &selected);

private:
    void setupTabs();

    TableModel *table;
    NewEntryTab *newEntryTab;
};
//! [0]

#endif // ADDRESSWIDGET_H
