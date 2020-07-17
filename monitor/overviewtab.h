#ifndef OVERVIEWTAB_H
#define OVERVIEWTAB_H

#include <QObject>
#include <QTableWidget>
#include <QWidget>

class OverviewTab : public QWidget {
    Q_OBJECT
   public:
    explicit OverviewTab(QWidget *parent = nullptr);
    QTableWidget *table;

    void initGui();

   signals:
};

#endif  // OVERVIEWTAB_H
