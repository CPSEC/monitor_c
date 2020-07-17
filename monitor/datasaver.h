#ifndef DATASAVER_H
#define DATASAVER_H

#include <QObject>

class queue;

class Datasaver : public QObject {
    Q_OBJECT
   public:
    Datasaver();
    // run(queue* q);
};

#endif  // DATASAVER_H
