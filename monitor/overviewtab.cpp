#include "overviewtab.h"

#include <QGridLayout>
#include <QPushButton>
#include <QStandardItemModel>
#include <QTableView>
#include <QtDebug>
OverviewTab::OverviewTab(QWidget *parent) : QWidget(parent) {
    //
    initGui();
}

void OverviewTab::initGui() {
    //    table = new QTableWidget(10, 3, this);
    //    const char *data[] = {"speed",    "servo", "p", "i", "d",
    //                          "throttle", "p",     "i", "d", ""};
    //    for (int i = 0; i < 9; ++i) {
    //        QTableWidgetItem *item = new QTableWidgetItem();
    //        item->setText(data[i]);
    //        item->setFlags(item->flags() & ~Qt::ItemIsEditable);
    //        table->setItem(i, 0, item);

    //        item = new QTableWidgetItem();
    //        item->setFlags(item->flags() & ~Qt::ItemIsEditable);
    //        table->setItem(i, 1, item);
    //    }
    //    QPushButton *bt = new QPushButton("set", table);
    //    table->setCellWidget(9, 2, bt);
    //    QGridLayout *layout = new QGridLayout(this);
    //    layout->addWidget(table);
    //    this->setLayout(layout);
    table = new QTableView(this);
    const char *data[] = {"speed",    "servo", "p", "i", "d",
                          "throttle", "p",     "i", "d", ""};
    model = new QStandardItemModel(table);
    table->setModel(model);
    for (int i = 0; i < 9; ++i) {
        QStandardItem *item = new QStandardItem(data[i]);
        item->setEditable(false);
        model->setItem(i, 0, item);

        item = new QStandardItem();
        item->setEditable(false);
        model->setItem(i, 1, item);
    }  // QPushButton *bt = new QPushButton("set", table);
    // table->setCellWidget(9, 2, bt);
    QGridLayout *layout = new QGridLayout(this);
    bt = new QPushButton("set", table);
    layout->addWidget(bt);
    layout->addWidget(table);
    this->setLayout(layout);
}

// slot to update info
void OverviewTab::updateinfo(char *buf) {
    // if (table->itemAt(0, 0) == nullptr) qDebug() << "fuck" << endl;
    bt->setText("897987987");
    model->item(0, 1)->setText("buf");
    table->viewport()->update();
    qDebug() << model->item(0, 1)->text() << endl;
    qDebug() << buf << endl;
}
