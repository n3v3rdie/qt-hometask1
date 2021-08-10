#include "pixelmodel.h"
#include <QImage>

class PixelModelPrivate
{
public:
    QImage img;
};

PixelModel::PixelModel(QObject* parent)
    : QAbstractItemModel(parent)
    , d_ptr(new PixelModelPrivate)
{
}

PixelModel::~PixelModel()
{
    delete d_ptr;
}

void PixelModel::setImage(const QImage &img)
{
    beginResetModel();
    d_ptr->img = img;
    endResetModel();
}

QImage PixelModel::image() const
{
    return d_ptr->img;
}

QModelIndex PixelModel::index(int row, int column, const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return createIndex(row, column);
}

QModelIndex PixelModel::parent(const QModelIndex &child) const
{
    Q_UNUSED(child)
    return QModelIndex();
}

int PixelModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return image().height();
}

int PixelModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return image().width();
}

QVariant PixelModel::data(const QModelIndex &index, int role) const
{
    switch (role) {
        case Qt::DisplayRole:
        case Qt::DecorationRole:
        case Qt::EditRole:
            return image().pixelColor(index.column(), index.row());
    }
    return QVariant();
}

Qt::ItemFlags PixelModel::flags(const QModelIndex &index) const
{
    if (index.isValid()){
        return QAbstractItemModel::flags(index) | Qt::ItemIsEditable;
    }
    return QAbstractItemModel::flags(index);
}

bool PixelModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    switch (role) {
        case Qt::EditRole:
            if (value.isValid()){
                d_ptr->img.setPixelColor(index.column(), index.row(), value.value<QColor>());
                return true;
            }else
                return false;
    }
    return QAbstractItemModel::setData(index, value, role);
}
