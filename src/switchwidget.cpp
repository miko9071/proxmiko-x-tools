#include "switchwidget.h"

#include <QPainter>
#include <QMouseEvent>
#include <QPropertyAnimation>

SwitchWidget::SwitchWidget(QWidget *parent)
    : QWidget(parent)
{
    setFixedSize(60, 30);

    animation = new QPropertyAnimation(this, "offset", this);
    animation->setDuration(150);
    animation->setEasingCurve(QEasingCurve::OutCubic);
}

bool SwitchWidget::isChecked() const
{
    return m_checked;
}

void SwitchWidget::setChecked(bool checked)
{
    if (m_checked == checked)
        return;

    m_checked = checked;

    animation->stop();
    animation->setStartValue(m_offset);
    animation->setEndValue(checked ? width() - 28 : 2);
    animation->start();

    emit toggled(checked);
    update();
}

void SwitchWidget::mousePressEvent(QMouseEvent *)
{
    setChecked(!m_checked);
}

void SwitchWidget::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing);

    // 🔵 Цвета
    QColor onColor(0, 191, 255);   // DeepSkyBlue
    QColor offColor(90, 90, 90);   // аккуратный серый

    // ── Фон ──
    p.setBrush(m_checked ? onColor : offColor);
    p.setPen(Qt::NoPen);
    p.drawRoundedRect(rect(), 15, 15);

    // ── Ползунок ──
    p.setBrush(Qt::white);
    p.drawEllipse(QRect(m_offset, 2, 26, 26));
}

int SwitchWidget::offset() const
{
    return m_offset;
}

void SwitchWidget::setOffset(int value)
{
    m_offset = value;
    update();
}
