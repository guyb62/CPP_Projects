// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

#include "newentrytab.h"
#include "adddialog.h"

#include <QtWidgets>

//! [0]
NewEntryTab::NewEntryTab(QWidget *parent)
    : QWidget(parent)
{
    auto descriptionLabel = new QLabel(tr("There are currently no contacts in your address book. "
                                          "\nClick Add to add new contacts."));

    auto addButton = new QPushButton(tr("Add"));

    connect(addButton, &QAbstractButton::clicked, this, &NewEntryTab::addEntry);

    auto mainLayout = new QVBoxLayout;
    mainLayout->addWidget(descriptionLabel);
    mainLayout->addWidget(addButton, 0, Qt::AlignCenter);

    setLayout(mainLayout);
}
//! [0]

//! [1]
void NewEntryTab::addEntry()
{
    AddDialog aDialog;

    if (aDialog.exec())
        emit sendDetails(aDialog.username(), aDialog.password(),
                         aDialog.date(), aDialog.description());
}
//! [1]
