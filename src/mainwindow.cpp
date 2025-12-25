#include "mainwindow.h"
#include "switchwidget.h"

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QProcess>
#include <QSettings>
#include <QPainter>
#include <QPixmap>
#include <QApplication>

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{
    // 🏷️ Название окна
    setWindowTitle("PROXMIKO x tools v1.0.0");

    // 🎨 Прозрачный фон (фон рисуем сами)
    setAutoFillBackground(false);

    // ─────────────────────────────
    // 📦 ГЛАВНЫЙ LAYOUT (ВЕСЬ UI)
    // ─────────────────────────────
    auto *mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(32, 24, 32, 24);
    mainLayout->setSpacing(20);
    mainLayout->setAlignment(Qt::AlignTop);

    // ─────────────────────────────
    // 🧩 СТРОКА: Подсветка
    // ─────────────────────────────
    auto *rowLayout = new QHBoxLayout();

    QLabel *label = new QLabel("Подсветка");
    label->setStyleSheet(R"(
        color: white;
        font-size: 18px;
        background: transparent;
    )");

    toggle = new SwitchWidget();

    rowLayout->addWidget(label);
    rowLayout->addStretch();
    rowLayout->addWidget(toggle);

    // ➕ Добавляем строку в список
    mainLayout->addLayout(rowLayout);


    setLayout(mainLayout);

    // ─────────────────────────────
    // 💾 Загружаем сохранённое состояние
    // ─────────────────────────────
    bool savedState = loadState();
    toggle->setChecked(savedState);

    // 🔁 Реакция на переключение
    connect(toggle, &SwitchWidget::toggled, this, [&](bool enabled) {
        updateLed(enabled);
        saveState(enabled);
    });

    // 🖼️ Загружаем фон ОДИН РАЗ
    background.load(":/background.png");

    // 📐 Размер окна = размер картинки
    resize(background.size());
    setFixedSize(background.size());


    // ─────────────────────────────
    // 🧩 Трей
    // ─────────────────────────────
    tray = new QSystemTrayIcon(this);

    // ─────────────────────────────
    // берём иконку из системной темы
    // ─────────────────────────────
    QIcon icon = QIcon::fromTheme("preferences-desktop-keyboard");
    if (icon.isNull()) {
        icon = QIcon::fromTheme("ibus-keyboard"); // запасной вариант
    }
    tray->setIcon(icon);

    tray->setToolTip("PROXMIKO x tools");


    // ─────────────────────────────
    // Меню трея
    // ─────────────────────────────
    trayMenu = new QMenu(this);

    actionToggle = new QAction("Подсветка", this);
    actionToggle->setCheckable(true);
    actionToggle->setChecked(toggle->isChecked());

    actionShow = new QAction("Открыть", this);
    actionQuit = new QAction("Выход", this);

    trayMenu->addAction(actionToggle);
    trayMenu->addSeparator();
    trayMenu->addAction(actionShow);
    trayMenu->addAction(actionQuit);

    tray->setContextMenu(trayMenu);
    tray->show();

    // ─────────────────────────────
    // из трея → в UI
    // ─────────────────────────────
    connect(actionToggle, &QAction::toggled, this, [&](bool enabled){
        if (toggle->isChecked() != enabled)
            toggle->setChecked(enabled);
});

    // ─────────────────────────────
    // из UI → в трей
    // ─────────────────────────────
    connect(toggle, &SwitchWidget::toggled, this, [&](bool enabled){
        if (actionToggle->isChecked() != enabled)
            actionToggle->setChecked(enabled);
});

    // ─────────────────────────────
    // Показ окна
    // ─────────────────────────────
    connect(actionShow, &QAction::triggered, this, [&](){
    show();
    raise();
    activateWindow();
});

    // ─────────────────────────────
    // Выход
    // ─────────────────────────────
    connect(actionQuit, &QAction::triggered, this, [&](){
    tray->hide();
    qApp->quit();
});


}

// ─────────────────────────────
// 🔧 Управление подсветкой
// ─────────────────────────────
void MainWindow::updateLed(bool enabled)
{
    if (enabled)
        QProcess::execute("xset", {"led", "3"});
    else
        QProcess::execute("xset", {"-led", "3"});
}

// ─────────────────────────────
// 💾 Сохранение состояния
// ─────────────────────────────
void MainWindow::saveState(bool enabled)
{
    QSettings settings("PROXMIKO", "x-tools");
    settings.setValue("backlight", enabled);
}

bool MainWindow::loadState()
{
    QSettings settings("PROXMIKO", "x-tools");
    return settings.value("backlight", false).toBool();
}

// ─────────────────────────────
// 🎨 Рисуем фон
// ─────────────────────────────
void MainWindow::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    p.setRenderHint(QPainter::SmoothPixmapTransform, true);

    p.drawPixmap(0, 0, background);
}

#include <QCloseEvent>

void MainWindow::closeEvent(QCloseEvent *event)
{
    hide();        // прячем окно
    event->ignore(); // НЕ закрываем программу
}
