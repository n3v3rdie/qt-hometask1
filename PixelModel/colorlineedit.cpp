#include "colorlineedit.h"
#include <QColor>
#include <QPainter>
#include <QValidator>
#include <QPaintEvent>
#include <QMouseEvent>
#include <QColorDialog>

#define PADDING 4

ColorValidator::ColorValidator(QObject *parent): QValidator(parent){
    Q_UNUSED(padding)
}

void ColorValidator::setValid(bool value){
    isValid = value;
}

QValidator::State ColorValidator::validate(QString &text, int &) const {
    if (isValid && (QColor::isValidColor(text)))
        return Acceptable;
    return Intermediate;
}
//ColorValidator class end


ColorLineEdit::ColorLineEdit(QWidget *parent)
    :QLineEdit(parent)
    ,validator(new ColorValidator(this))
    ,defaultCursor(this->cursor())
{
    this->setInputMask("\\#HHHHHH");
    this->setColor(Qt::white);
    this->setValidator(validator);
    connect(this, &ColorLineEdit::textChanged, this, &ColorLineEdit::onTextChanged);
}

const QColor ColorLineEdit::color()
{
    return m_color;
}

const QRect ColorLineEdit::getColorRect()
{
    QRect rect = this->rect();
    const int height = this->rect().height() - PADDING*2 - 1;
    QRect colorRect = QRect(rect.right() - height - PADDING, rect.top() + PADDING, height, height);
    return colorRect;
}

void ColorLineEdit::onTextChanged(const QString &text)
{
    if ((text.length() > 6)&&(QColor::isValidColor(text))){
        setColor(QColor(text));
    }
}

void ColorLineEdit::restoreCursor()
{
    this->setCursor(defaultCursor);
}

void ColorLineEdit::setColor(const QColor color)
{
    m_color = color;
    this->setText(color.name());
}

void ColorLineEdit::paintEvent(QPaintEvent *event)
{
    QLineEdit::paintEvent(event);

    QColor color = m_color;
    QPainter painter(this);
    QRect colorRect = getColorRect();
    painter.setBrush(color);
    painter.drawRect(colorRect);
}

void ColorLineEdit::mouseMoveEvent(QMouseEvent *event)
{
    QRect colorPreview = getColorRect();
    if (colorPreview.contains(event->pos()))
        this->setCursor(Qt::PointingHandCursor);
    else
        restoreCursor();
    QLineEdit::mouseMoveEvent(event);
}

void ColorLineEdit::mousePressEvent(QMouseEvent *event)
{
    QRect colorPreview = getColorRect();
    if (colorPreview.contains(event->pos())){
        validator->setValid(false);
        QColor color = QColorDialog::getColor(m_color, this, tr("Select color"));
        if (color.isValid())
            setColor(color);
        validator->setValid(true);
    }else{
        return QLineEdit::mousePressEvent(event);
    }
}
