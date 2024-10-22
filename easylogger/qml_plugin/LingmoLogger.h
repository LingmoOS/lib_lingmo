#pragma once

#include "elog.h"

#include <QObject>
#include <qobjectdefs.h>

// Forward declaration of the C++ class
class LingmoLogger: public QObject {
    Q_OBJECT
    public:
        explicit LingmoLogger(QObject *parent = nullptr);
        
};