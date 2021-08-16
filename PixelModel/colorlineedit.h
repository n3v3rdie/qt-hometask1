#ifndef COLORLINEEDIT_H
#define COLORLINEEDIT_H

#include <QObject>
#include <QLineEdit>
#include <QValidator>


class ColorValidator: public QValidator{
    Q_OBJECT
public:
    ColorValidator(QObject* parent);
    void setValid(bool value);
    virtual State validate(QString &text, int &) const override;
private:
    bool isValid = true;
    char padding[3];
};


class ColorLineEdit : public QLineEdit
{
    Q_OBJECT
public:
    ColorLineEdit(QWidget* parent = nullptr);
    const QColor color();
    void setColor(const QColor color);

    // QWidget interface
protected:
    void paintEvent(QPaintEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;

private:
    QColor m_color;
    ColorValidator* validator;
    const QCursor defaultCursor;
    void restoreCursor();
    const QRect getColorRect();

private Q_SLOTS:
    void onTextChanged(const QString &text);

};

#endif // COLORLINEEDIT_H
