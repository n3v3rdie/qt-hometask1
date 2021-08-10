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
    auto editor = new QColorDialog(parent);
    return editor;
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
    auto parent = colorEditor->parentWidget();
    if (parent){
        auto center = parent->mapToGlobal(parent->rect().center());
        int x = colorEditor->sizeHint().width()/2;
        int y = colorEditor->sizeHint().height()/2;
        colorEditor->move(center - QPoint(x,y));
    }
}

void ColorDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    auto colorEditor = qobject_cast<QColorDialog*>(editor);
    if (colorEditor == nullptr)
        return;
    model->setData(index, colorEditor->currentColor(), Qt::EditRole);
}
