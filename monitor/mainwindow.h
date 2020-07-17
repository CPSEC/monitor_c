#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class QTabWidget;
class OverviewTab;
class Server;

class MainWindow : public QMainWindow {
    Q_OBJECT

   public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

   private:
    Ui::MainWindow *ui;

    QTabWidget *tabs;
    OverviewTab *overviewtab;
    Server *serv;
    void initGui();
    void initThread();
    void initSignalSlot();
};
#endif  // MAINWINDOW_H
