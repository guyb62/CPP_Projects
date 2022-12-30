// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

#include "tablemodel.h"

//! [0]
TableModel::TableModel(QObject *parent)
    : QAbstractTableModel(parent)
{
}

TableModel::TableModel(const QList<PasswordEntry> &entries, QObject *parent)
    : QAbstractTableModel(parent), entries(entries)
{
}
//! [0]

//! [1]
int TableModel::rowCount(const QModelIndex &parent) const
{
    return parent.isValid() ? 0 : entries.size();
}

int TableModel::columnCount(const QModelIndex &parent) const
{
    return parent.isValid() ? 0 : 4;
}
//! [1]

//! [2]
QVariant TableModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (index.row() >= entries.size() || index.row() < 0)
        return QVariant();

    if (role == Qt::DisplayRole) {
        const auto &entry = entries.at(index.row());

        switch (index.column()) {
            case 0:
                return entry.username;
            case 1:
                return entry.password;
            case 2:
                return entry.date;
            case 3:
                return entry.description;
            default:
                break;
        }
    }
    return QVariant();
}
//! [2]

//! [3]
QVariant TableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole)
        return QVariant();

    if (orientation == Qt::Horizontal) {
        switch (section) {
            case 0:
                return tr("Username");
            case 1:
                return tr("Password");
            case 2:
                return tr("Date");
            case 3:
                return tr("Description");
            default:
                break;
        }
    }
    return QVariant();
}
//! [3]

//! [4]
bool TableModel::insertRows(int position, int rows, const QModelIndex &index)
{
    Q_UNUSED(index);
    beginInsertRows(QModelIndex(), position, position + rows - 1);

    for (int row = 0; row < rows; ++row)
        entries.insert(position, { QString(), QString() });

    endInsertRows();
    return true;
}
//! [4]

//! [5]
bool TableModel::removeRows(int position, int rows, const QModelIndex &index)
{
    Q_UNUSED(index);
    beginRemoveRows(QModelIndex(), position, position + rows - 1);

    for (int row = 0; row < rows; ++row)
        entries.removeAt(position);

    endRemoveRows();
    return true;
}
//! [5]

//! [6]
bool TableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (index.isValid() && role == Qt::EditRole) {
        const int row = index.row();
        auto entry = entries.value(row);

        switch (index.column()) {
            case 0:
                entry.username = value.toString();
                break;
            case 1:
                entry.password = value.toString();
                break;
            case 2:
                entry.date = value.toString();
                break;
            case 3:
                entry.description = value.toString();
                break;
            default:
                return false;
        }
        entries.replace(row, entry);
        emit dataChanged(index, index, {Qt::DisplayRole, Qt::EditRole});

        return true;
    }

    return false;
}
//! [6]

//! [7]
Qt::ItemFlags TableModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::ItemIsEnabled;

    return QAbstractTableModel::flags(index) | Qt::ItemIsEditable;
}
//! [7]

//! [8]
const QList<PasswordEntry> &TableModel::getEntries() const
{
    return entries;
}
//! [8]
