#ifndef COLORDELEGATE_H
#define COLORDELEGATE_H

#include <QObject>
#include <QStyledItemDelegate>


class ColorDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    ColorDelegate(QObject* parent = nullptr);

    // QAbstractItemDelegate interface
public:
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    void setEditorData(QWidget *editor, const QModelIndex &index) const override;
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const override;
};

#endif // QCOLORDELEGATE_H
