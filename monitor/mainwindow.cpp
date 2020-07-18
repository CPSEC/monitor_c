#include "mainwindow.h"

#include <QGridLayout>
#include <QTableWidget>
#include <thread>

#include "./ui_mainwindow.h"
#include "overviewtab.h"
#include "server.h"

// using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    initGui();
    initThread();
    initSignalSlot();
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::initGui() {
    this->tabs = new QTabWidget(this);
    const char *data[] = {"overview", "speed", "servo", "throttle"};
    this->overviewtab = new OverviewTab();
    tabs->addTab(new OverviewTab(tabs), "overview");
    for (int i = 1; i < 4; ++i) {
        tabs->addTab(new QWidget(tabs), data[i]);
    }

    QWidget *center = new QWidget(this);
    QGridLayout *layout = new QGridLayout(center);
    layout->addWidget(tabs);
    center->setLayout(layout);
    this->setCentralWidget(center);
}

void MainWindow::initThread() {
    this->serv = new Server();
    std::thread serv_th(&Server::receiveloop, serv);
    serv_th.detach();
}

void MainWindow::initSignalSlot() {
    connect(this->serv, &Server::update, this->overviewtab,
            &OverviewTab::updateinfo);
}
