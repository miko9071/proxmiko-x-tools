#pragma once
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QSystemTrayIcon>
#include <QMenu>
#include <QAction>


class SwitchWidget;

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

private:
    SwitchWidget *toggle;

    void updateLed(bool enabled);
    void saveState(bool enabled);
    bool loadState();
    QSystemTrayIcon *tray;
    QMenu *trayMenu;
    QAction *actionToggle;
    QAction *actionShow;
    QAction *actionQuit;
    QPixmap background;

protected:
    void closeEvent(QCloseEvent *event) override;


protected:
    void paintEvent(QPaintEvent *event) override;
};

#endif // MAINWINDOW_H
