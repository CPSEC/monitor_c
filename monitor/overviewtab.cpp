#include "overviewtab.h"

#include <QGridLayout>
#include <QPushButton>
OverviewTab::OverviewTab(QWidget *parent) : QWidget(parent) {
    //
    initGui();
}

void OverviewTab::initGui() {
    table = new QTableWidget(10, 3, this);
    const char *data[] = {"speed",    "servo", "p", "i", "d",
                          "throttle", "p",     "i", "d", ""};
    for (int i = 0; i < 10; ++i) {
        QTableWidgetItem *item = new QTableWidgetItem();
        item->setText(data[i]);
        item->setFlags(item->flags() & ~Qt::ItemIsEditable);
        table->setItem(i, 0, item);

        item = new QTableWidgetItem();
        item->setFlags(item->flags() & ~Qt::ItemIsEditable);
        table->setItem(i, 1, item);
    }
    QPushButton *bt = new QPushButton("set", table);
    table->setCellWidget(9, 2, bt);
    QGridLayout *layout = new QGridLayout(this);
    layout->addWidget(table);
    this->setLayout(layout);
}
