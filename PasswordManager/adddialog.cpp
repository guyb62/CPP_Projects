// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

#include "adddialog.h"

#include <QtWidgets>

//! [0]
AddDialog::AddDialog(QWidget *parent)
    : QDialog(parent),
      usernameText(new QLineEdit),
      pwordText(new QLineEdit),
      dateText(new QLineEdit),
      descriptionText(new QTextEdit)
{
    auto usernameLabel = new QLabel(tr("Username"));
    auto pwordLabel = new QLabel(tr("Password"));
    auto dateLabel = new QLabel(tr("Date"));
    auto descriptionLabel = new QLabel(tr("Website URL/Description"));

    auto okButton = new QPushButton(tr("OK"));
    auto cancelButton = new QPushButton(tr("Cancel"));

    auto gLayout = new QGridLayout;
    gLayout->setColumnStretch(1, 4);
    gLayout->addWidget(usernameLabel, 0, 0);
    gLayout->addWidget(usernameText, 0, 1);

    gLayout->addWidget(pwordLabel, 1, 0);
    gLayout->addWidget(pwordText, 1, 1);

    gLayout->addWidget(dateLabel, 2, 0);
    gLayout->addWidget(dateText, 2, 1);

    gLayout->addWidget(descriptionLabel, 3, 0, Qt::AlignLeft|Qt::AlignTop);
    gLayout->addWidget(descriptionText, 3, 1, Qt::AlignLeft);

    auto buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(okButton);
    buttonLayout->addWidget(cancelButton);

    gLayout->addLayout(buttonLayout, 4, 1, Qt::AlignRight);

    auto mainLayout = new QVBoxLayout;
    mainLayout->addLayout(gLayout);
    setLayout(mainLayout);

    connect(okButton, &QAbstractButton::clicked, this, &QDialog::accept);
    connect(cancelButton, &QAbstractButton::clicked, this, &QDialog::reject);

    setWindowTitle(tr("Add a Password"));
}

QString AddDialog::username() const
{
    return usernameText->text();
}

QString AddDialog::password() const
{
    return pwordText->text();
}

QString AddDialog::date() const
{
    return dateText->text();
}

QString AddDialog::description() const
{
    return descriptionText->toPlainText();
}

void AddDialog::editEntry(const QString &uname, const QString &pword,
                          const QString &date, const QString &description)
{
    descriptionText->setReadOnly(true);
    descriptionText->setText(description);
    usernameText->setText(uname);
    dateText->setText(date);
    pwordText->setText(pword);
}
//! [0]
