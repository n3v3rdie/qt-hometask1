#ifndef PIXELMODEL_H
#define PIXELMODEL_H

#include <QObject>
#include <QAbstractItemModel>

class PixelModelPrivate;

class PixelModel : public QAbstractItemModel
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(PixelModel)
public:
    PixelModel(QObject* parent = nullptr);
    virtual ~PixelModel() override;
    void setImage(const QImage &img);
    QImage image() const;
    // QAbstractItemModel interface
public:
    QModelIndex index(int row, int column, const QModelIndex &parent) const override;
    QModelIndex parent(const QModelIndex &child) const override;
    int rowCount(const QModelIndex &parent) const override;
    int columnCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role) override;
private:
    PixelModelPrivate* d_ptr;
};

#endif // PIXELMODEL_H
