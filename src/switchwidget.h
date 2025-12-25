#pragma once

#include <QWidget>

class QPropertyAnimation;

class SwitchWidget : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(int offset READ offset WRITE setOffset)

public:
    explicit SwitchWidget(QWidget *parent = nullptr);

    bool isChecked() const;
    void setChecked(bool checked);

signals:
    void toggled(bool checked);

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void paintEvent(QPaintEvent *event) override;

private:
    bool m_checked = false;
    int m_offset = 2;
    QPropertyAnimation *animation;

    int offset() const;
    void setOffset(int value);
};
