#ifndef _KALMAN_H
#define _KALMAN_H

struct kalman_state;
struct kalman_filter;
struct kalman_filter_ext;


/** Initialize the filter */
void kalman_init(struct kalman_filter *p);

/** Update the belief due to a control action */
void kalman_control_update(struct kalman_state *s,
                            struct kalman_filter *f,
                            vector control);

/** Update the state with a measurement */
void kalman_measurement_update(struct kalman_state *s,
                                struct kalman_filter *f,
                                vector measurement);

/** Update the belief due to a control action */
void kalman_control_update_ext(struct kalman_state *s,
                                struct kalman_filter_ext *f,
                                vector control);

/** Update the state with a measurement */
void kalman_measurement_update_ext(struct kalman_state *s,
                                    struct kalman_filter_ext *f,
                                    vector measurement);

#endif
