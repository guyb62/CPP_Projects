// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

#ifndef NEWENTRYTAB_H
#define NEWENTRYTAB_H

#include <QWidget>

QT_BEGIN_NAMESPACE
class QLabel;
class QPushButton;
class QVBoxLayout;
QT_END_NAMESPACE

//! [0]
class NewEntryTab : public QWidget
{
    Q_OBJECT

public:
    NewEntryTab(QWidget *parent = nullptr);

public slots:
    void addEntry();

signals:
    void sendDetails(const QString &username, const QString &password,
                     const QString &date, const QString &description);
};
//! [0]

#endif
