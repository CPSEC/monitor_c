#ifndef SERVER_H
#define SERVER_H

#include <QObject>

class Server : public QObject {
    Q_OBJECT
   public:
    Server();
    void receiveloop();
    void readJson(int &fd);

    void sendsetting();
    void writeJson(int &fd);

   signals:
    void update(char *buf);
};

#endif  // SERVER_H
