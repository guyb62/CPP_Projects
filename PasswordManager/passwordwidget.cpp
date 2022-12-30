// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

#include "passwordwidget.h"
#include "adddialog.h"

#include <QtWidgets>

//! [0]
PasswordWidget::PasswordWidget(QWidget *parent)
    : QTabWidget(parent),
      table(new TableModel(this)),
      newEntryTab(new NewEntryTab(this))
{
    connect(newEntryTab, &NewEntryTab::sendDetails,
        this, &PasswordWidget::addEntry);

    addTab(newEntryTab, tr("Password manager"));

    setupTabs();
}
//! [0]

//! [2]
void PasswordWidget::showAddEntryDialog()
{
    AddDialog aDialog;

    if (aDialog.exec())
        addEntry(aDialog.username(), aDialog.password(),
                 aDialog.date(), aDialog.description());
}
//! [2]

//! [3]
void PasswordWidget::addEntry(const QString &username, const QString &password,
                              const QString &date, const QString &description)
{
    if (!table->getEntries().contains({ username, password, date, description })) {
        table->insertRows(0, 1, QModelIndex());

        QModelIndex index = table->index(0, 0, QModelIndex());
        table->setData(index, username, Qt::EditRole);
        index = table->index(0, 1, QModelIndex());
        table->setData(index, password, Qt::EditRole);
        index = table->index(0, 2, QModelIndex());
        table->setData(index, date, Qt::EditRole);
        index = table->index(0, 3, QModelIndex());
        table->setData(index, description, Qt::EditRole);
        removeTab(indexOf(newEntryTab));
    } else {
        QMessageBox::information(this, tr("Duplicate Name"),
            tr("The name \"%1\" already exists.").arg(username));
    }
}
//! [3]

//! [4a]
void PasswordWidget::editEntry()
{
    QTableView *temp = static_cast<QTableView*>(currentWidget());
    QSortFilterProxyModel *proxy = static_cast<QSortFilterProxyModel*>(temp->model());
    QItemSelectionModel *selectionModel = temp->selectionModel();

    const QModelIndexList indexes = selectionModel->selectedRows();
    QString username;
    QString password;
    QString date;
    QString description;
    int row = -1;

    for (const QModelIndex &index : indexes) {
        row = proxy->mapToSource(index).row();
        QModelIndex usernameIndex = table->index(row, 0, QModelIndex());
        QVariant varName = table->data(usernameIndex, Qt::DisplayRole);
        username = varName.toString();

        QModelIndex passwordIndex = table->index(row, 1, QModelIndex());
        QVariant varPword = table->data(passwordIndex, Qt::DisplayRole);
        password = varPword.toString();

        QModelIndex dateIndex = table->index(row, 1, QModelIndex());
        QVariant varDate = table->data(dateIndex, Qt::DisplayRole);
        date = varDate.toString();

        QModelIndex descriptionIndex = table->index(row, 1, QModelIndex());
        QVariant varDesc = table->data(descriptionIndex, Qt::DisplayRole);
        password = varDesc.toString();
    }
//! [4a]

//! [4b]
    AddDialog aDialog;
    aDialog.setWindowTitle(tr("Edit a Entry"));
    aDialog.editEntry(username, password, date, description);

    if (aDialog.exec()) {
        const QString newDescription = aDialog.description();
        if (newDescription != description) {
            const QModelIndex index = table->index(row, 1, QModelIndex());
            table->setData(index, newDescription, Qt::EditRole);
        }
    }
}
//! [4b]

//! [5]
void PasswordWidget::removeEntry()
{
    QTableView *temp = static_cast<QTableView*>(currentWidget());
    QSortFilterProxyModel *proxy = static_cast<QSortFilterProxyModel*>(temp->model());
    QItemSelectionModel *selectionModel = temp->selectionModel();

    const QModelIndexList indexes = selectionModel->selectedRows();

    for (QModelIndex index : indexes) {
        int row = proxy->mapToSource(index).row();
        table->removeRows(row, 1, QModelIndex());
    }

    if (table->rowCount(QModelIndex()) == 0)
        insertTab(0, newEntryTab, tr("Password manager"));
}
//! [5]

//! [1]
void PasswordWidget::setupTabs()
{
    using namespace Qt::StringLiterals;
    const auto groups = { "ABC"_L1, "DEF"_L1, "GHI"_L1, "JKL"_L1, "MNO"_L1, "PQR"_L1,
                          "STU"_L1, "VW"_L1, "XYZ"_L1 };

    for (QLatin1StringView str : groups) {
        const auto regExp = QRegularExpression(QLatin1StringView("^[%1].*").arg(str),
                                               QRegularExpression::CaseInsensitiveOption);

        auto proxyModel = new QSortFilterProxyModel(this);
        proxyModel->setSourceModel(table);
        proxyModel->setFilterRegularExpression(regExp);
        proxyModel->setFilterKeyColumn(0);

        QTableView *tableView = new QTableView;
        tableView->setModel(proxyModel);
        tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
        tableView->horizontalHeader()->setStretchLastSection(true);
        tableView->verticalHeader()->hide();
        tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
        tableView->setSelectionMode(QAbstractItemView::SingleSelection);
        tableView->setSortingEnabled(true);

        connect(tableView->selectionModel(), &QItemSelectionModel::selectionChanged,
                this, &PasswordWidget::selectionChanged);

        connect(this, &QTabWidget::currentChanged, this, [this, tableView](int tabIndex) {
            if (widget(tabIndex) == tableView)
                emit selectionChanged(tableView->selectionModel()->selection());
        });

        addTab(tableView, str);
    }
}
//! [1]

//! [7]
void PasswordWidget::readFromFile(const QString &fileName)
{
    QFile file(fileName);

    if (!file.open(QIODevice::ReadOnly)) {
        QMessageBox::information(this, tr("Unable to open file"),
            file.errorString());
        return;
    }

    QList<PasswordEntry> entries;
    QDataStream in(&file);
    in >> entries;

    if (entries.isEmpty()) {
        QMessageBox::information(this, tr("No entries in file"),
                                 tr("The file you are attempting to open contains no contacts."));
    } else {
        for (const auto &entry: qAsConst(entries))
            addEntry(entry.username, entry.password,
                     entry.date, entry.description);
    }
}
//! [7]

//! [6]
void PasswordWidget::writeToFile(const QString &fileName)
{
    QFile file(fileName);

    if (!file.open(QIODevice::WriteOnly)) {
        QMessageBox::information(this, tr("Unable to open file"), file.errorString());
        return;
    }

    QDataStream out(&file);
    out << table->getEntries();
}
//! [6]
