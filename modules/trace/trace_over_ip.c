#include <stdio.h>
#include <string.h>

#include <fcntl.h>
#include <sys/socket.h>
#ifdef COMPILE_ON_ROBOT
#include <ucos_ii.h>
#include <tasks.h>
#else
#include <unistd.h>
#include <pthread.h>
#include <arpa/inet.h>
#endif

#include "trace.h"
#include "trace_over_ip.h"


#ifdef COMPILE_ON_ROBOT
OS_STK trace_stk[TRACE_TASK_STACKSIZE];
#endif

static int tcp_listen_port;
static int trace_freq = 1;
static int udp_send_socket = -1;

static bool is_number(char c)
{
    return (c >= '0' && c <= '9');
}

static void setup_trace_variables(char *buf)
{
    trace_var_disable_all();
    trace_freq = 1;
    // for each line
    char *lstart = buf;
    while (lstart != NULL) {
        char *line = lstart;
        char *lend = lstart;
        while (*lend != '\n' && *lend != '\r' && *lend != '\0')
            lend++;
        if (*lend != '\0')
            lstart = lend + 1;
        else
            lstart = NULL;
        *lend = '\0';
        if (is_number(*line)) {
            sscanf(line, "%d", &trace_freq);
        } else {
            trace_var_enable_by_name(line);
        }
    }
    if (trace_freq <= 0)
        trace_freq = 1;
}

static void accept_new_connection(int conn)
{
    static char setup_buf[300];
    int new_conn;
    struct sockaddr_in addr;
    socklen_t addr_len = sizeof(addr);
    if ((new_conn = accept(conn, (struct sockaddr *)&addr, &addr_len)) < 0) {
        return;
    }
    // close current udp socket
    if (udp_send_socket != -1)
        close(udp_send_socket);
    udp_send_socket = -1;

    int flags = fcntl(new_conn,F_GETFL,0);
    fcntl(new_conn, F_SETFL, flags & ~O_NONBLOCK);

    // fill setup_buf
    int remaining_sz = sizeof(setup_buf) - 1; // -1 for 0-terminator
    char *bufp = setup_buf;
    while (remaining_sz > 0) {
        int sz = read(new_conn, bufp, remaining_sz);
        if (sz <= 0) {
            break;
        }
        remaining_sz -= sz;
        bufp += sz;
    }
    *bufp = '\0';
    if (bufp == setup_buf)
        return;

    setup_trace_variables(setup_buf);

    int s;
    if ((s = socket(AF_INET, SOCK_DGRAM, 0)) >= 0) {
        addr.sin_port = htons(tcp_listen_port);
        if (connect(s, (struct sockaddr *)&addr, sizeof(addr)) != -1) {
            udp_send_socket = s;
        }
    }
}

void trace_task(void *arg)
{
    printf("thread task started\n");
    // setup tcp listen
    int listenfd = socket(AF_INET, SOCK_STREAM, 0);
    if (listenfd < 0) {
        printf("trace task: socket error\n");
        return;
    }
    int flags = fcntl(listenfd,F_GETFL,0);
    fcntl(listenfd, F_SETFL, flags | O_NONBLOCK);
    struct sockaddr_in serv_addr;
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(tcp_listen_port);
    int yes = 1;
    setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int));
    if (bind(listenfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        printf("trace task: socket bind error\n");
        return;
    }
    listen(listenfd,1);
    while (1) {
        // check tcp for new connection
        accept_new_connection(listenfd);
        // write variables to buffer
        static char send_str[300];
        trace_var_output(send_str, sizeof(send_str));
        // send udp
        if (udp_send_socket != -1) {
            write(udp_send_socket, send_str, strlen(send_str));
        }
#ifdef COMPILE_ON_ROBOT
        OSTimeDly(OS_TICKS_PER_SEC / trace_freq);
#else // COMPILE_ON_ROBOT
        usleep(1000000/trace_freq);
#endif // COMPILE_ON_ROBOT
    }
}


void trace_over_ip_init(int port)
{
    tcp_listen_port = port;

#ifdef COMPILE_ON_ROBOT
    OSTaskCreateExt(trace_task,
                    NULL,
                    &trace_stk[TRACE_TASK_STACKSIZE-1],
                    TRACE_TASK_PRIORITY,
                    TRACE_TASK_PRIORITY,
                    &trace_stk[0],
                    TRACE_TASK_STACKSIZE,
                    NULL, 0);
#else // COMPILE_ON_ROBOT
    static pthread_t thread;
    pthread_create(&thread, NULL, (void *(*)(void *))trace_task, NULL);
#endif // COMPILE_ON_ROBOT
}
