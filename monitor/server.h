#ifndef SERVER_H
#define SERVER_H

#include <QObject>

class Server : public QObject {
    Q_OBJECT
   public:
    Server();
    void receiveloop();
    void sendsetting();
};

#endif  // SERVER_H
