#ifndef THREADREC1_H
#define THREADREC1_H

#include <QThread>
#include <QObject>
#include <QString>
#include "can_config.h"
#include <errno.h>
#include <getopt.h>
#include <libgen.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>
#include <stdint.h>
#include <signal.h>
#include <net/if.h>

#include <sys/ioctl.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/uio.h>

#include <linux/can.h>
#include <linux/can/raw.h>
#define BUF_SIZ	(255)

class ThreadRec1: public QThread
{
    Q_OBJECT
public:
    ThreadRec1(int argc, char** pstr);
    virtual ~ThreadRec1();
    void run();
    void print_usage(char *prg);
    int add_filter(u_int32_t id, u_int32_t mask);
    int MyRecieve(int argc, char **argv);
//	bool m_bHex;
public slots:
    void stop();
    signals:
    void mesRecv1(QString);
private:
    int	s;
    int	running;
    struct can_filter *filter;
    int filter_count;
    char** m_argv;
    int m_argc;
};

extern int optind, opterr, optopt;
enum {
    VERSION_OPTION1 = CHAR_MAX + 1,
    FILTER_OPTION1,
};
typedef void (*sighandler_t)(int);
extern sighandler_t signal(int signum, sighandler_t handler);
#endif
