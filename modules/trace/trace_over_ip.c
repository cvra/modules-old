#include <lwip/udp.h>
#include <ucos_ii.h>

#include <tasks.h>

#include "trace.h"
#include "trace_over_ip.h"

OS_STK trace_stk[TRACE_TASK_STACKSIZE];

static int tcp_listen_port;
static struct udp_pcb *udp_conn;
static int trace_freq;

static bool is_number(char c)
{
    return (c >= '0' && c <= '9');
}

static void setup_trace_variables(char *buf)
{
    trace_var_disable_all();
    // for each line
    char *lstart = buf;
    while (lstart != NULL) {
        char *line = lstart;
        char *lend = lstart;
        while (*lend != '\n' && *lend != '\0')
            lend++;
        if (lend != '\0')
            lstart = lend + 1;
        else
            lstart = NULL;
        *lend = '\0';
        if (is_number(*line)) {
            sscanf(line, "%d", &trace_freq);
        } else {
            trace_var_enable(trace_var_lookup(line));
        }
    }
}

static void accept_new_connection(struct netconn *conn)
{
    static char setup_buf[300];

    err_t err;
    struct netconn *newconn;
    err = netconn_accept(conn, &newconn);

    ip_addr_t ipaddr;


    // fill setup_buf

    setup_trace_variables(setup_buf);

    udp_conn = udp_new();
    int src_port = tcp_listen_port;
    int dest_port = tcp_listen_port;
    udp_bind(udp_conn, IP_ADDR_ANY, src_port);
    udp_connect(udp_conn, &ipaddr, dest_port);
}

void trace_task(void *arg)
{
    // setup tcp listen

    // int listenfd = socket(AF_INET, SOCK_STREAM | SOCK_NONBLOCK, 0);

    struct netconn *listen_conn;
    listen_conn = netconn_new(NETCONN_TCP);
    netconn_bind(listen_conn, NULL, 23);
    netconn_listen(listen_conn);
    netconn_set_nonblocking(listen_conn, 1);
    while (1) {
        // check tcp for new connection
        accept_new_connection(listen_conn);
        // write variables to buffer
        char *send_str = trace_var_output();
        // send udp
        struct pbuf *p;
        p = pbuf_alloc(PBUF_TRANSPORT, strlen(send_str), PBUF_REF);
        p->payload = send_str;
        udp_send(udp_conn, p); // TODO use netconn api!!!

        OSTimeDly(OS_TICKS_PER_SEC / trace_freq);
    }
}


void trace_over_ip_init(int port)
{
    tcp_listen_port = port;
    OSTaskCreateExt(trace_task,
                    NULL,
                    &trace_stk[TRACE_TASK_STACKSIZE-1],
                    TRACE_TASK_PRIORITY,
                    TRACE_TASK_PRIORITY,
                    &trace_stk[0],
                    TRACE_TASK_STACKSIZE,
                    NULL, 0);
}
