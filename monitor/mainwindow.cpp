#include "mainwindow.h"

#include <QGridLayout>
#include <QTableWidget>

#include "./ui_mainwindow.h"
#include "overviewtab.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    initGui();
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::initGui() {
    QTabWidget *tabs = new QTabWidget(this);
    const char *data[] = {"overview", "speed", "servo", "throttle"};
    tabs->addTab(new OverviewTab(this), "overview");
    for (int i = 1; i < 4; ++i) {
        tabs->addTab(new QWidget(tabs), data[i]);
    }

    QWidget *center = new QWidget(this);
    QGridLayout *layout = new QGridLayout(center);
    layout->addWidget(tabs);
    center->setLayout(layout);
    this->setCentralWidget(center);
}
