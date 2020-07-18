#ifndef OVERVIEWTAB_H
#define OVERVIEWTAB_H

#include <QObject>
#include <QWidget>

class QTableView;
class QStandardItemModel;
class QPushButton;

class OverviewTab : public QWidget {
    Q_OBJECT
   public:
    explicit OverviewTab(QWidget *parent = nullptr);
    QTableView *table;
    QStandardItemModel *model;
    QPushButton *bt;

    void initGui();

   signals:
   public slots:
    void updateinfo(char *buf);
};

#endif  // OVERVIEWTAB_H
