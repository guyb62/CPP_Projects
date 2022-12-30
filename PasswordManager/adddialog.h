// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

#ifndef ADDDIALOG_H
#define ADDDIALOG_H

#include <QDialog>

QT_BEGIN_NAMESPACE
class QLabel;
class QPushButton;
class QTextEdit;
class QLineEdit;
QT_END_NAMESPACE

//! [0]
class AddDialog : public QDialog
{
    Q_OBJECT

public:
    AddDialog(QWidget *parent = nullptr);

    QString username() const;
    QString password() const;
    QString date() const;
    QString description() const;
    void editEntry(const QString &description, const QString &uname,
                         const QString &pword, const QString &date);

private:
    QLineEdit *usernameText;
    QLineEdit *pwordText;
    QLineEdit *dateText;
    QTextEdit *descriptionText;
};
//! [0]

#endif // ADDDIALOG_H
