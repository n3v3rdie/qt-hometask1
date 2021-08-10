#include "colordelegate.h"
#include <QColorDialog>

ColorDelegate::ColorDelegate(QObject* parent):
    QStyledItemDelegate(parent)
{
}

QWidget *ColorDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(index)
    Q_UNUSED(option)
    return new QColorDialog(parent);
}

void ColorDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    auto colorEditor = qobject_cast<QColorDialog*>(editor);
    if (colorEditor == nullptr)
        return;
    QColor color = index.data(Qt::EditRole).value<QColor>();
    if (color.isValid()){
        colorEditor->setCurrentColor(color);
    }
}

void ColorDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    auto colorEditor = qobject_cast<QColorDialog*>(editor);
    if (colorEditor == nullptr)
        return;
    model->setData(index, colorEditor->currentColor(), Qt::EditRole);
}
