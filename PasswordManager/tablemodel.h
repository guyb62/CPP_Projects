// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

#ifndef TABLEMODEL_H
#define TABLEMODEL_H

#include <QAbstractTableModel>
#include <QList>

//! [0]

struct PasswordEntry
{
    QString username;
    QString password;
    QString date;
    QString description;

    bool operator==(const PasswordEntry &other) const
    {
        return username == other.username && password == other.password
                && date == other.date && description == other.description;
    }
};

inline QDataStream &operator<<(QDataStream &stream, const PasswordEntry &entry)
{
    return stream << entry.username << entry.password << entry.date << entry.description;
}

inline QDataStream &operator>>(QDataStream &stream, PasswordEntry &entry)
{
    return stream >> entry.username >> entry.password >> entry.date >> entry.description;
}

class TableModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    TableModel(QObject *parent = nullptr);
    TableModel(const QList<PasswordEntry> &contacts, QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent) const override;
    int columnCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;
    bool insertRows(int position, int rows, const QModelIndex &index = QModelIndex()) override;
    bool removeRows(int position, int rows, const QModelIndex &index = QModelIndex()) override;
    const QList<PasswordEntry> &getEntries() const;

private:
    QList<PasswordEntry> entries;
};
//! [0]

#endif // TABLEMODEL_H
