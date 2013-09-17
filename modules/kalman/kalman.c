#include <kalman.h>



struct kalman_state{
    
    vector mu;          /**< mean */
    vector sigma;       /**< covariance */

    vector mu_bel;      /**< mean belief */
    vector sigma_bel;   /**< covariance belief */

};

/** Kalman filter structure contains all the constant parameters */
struct kalman_filter{
    
    matrix A;           /**< state transition matrix */
    matrix B;           /**< control to state transform */
    matrix C;           /**< measurement to state transform */

    matrix Q;           /**< measurement error covariance */
    matrix R;           /**< control error covariance */

    //matrix At;          /**< transpose of A for less computation time */
    //matrix Ct;          /**< transpose of C for less computation time */
};


/** Extendend Kalman filter structure contains all the constant parameters.
 *  The extended Kalman filter is for cases, where the state doesn't
 *  linearly depend on its previous state, the control actions or
 *  the measurements.
 */
struct kalman_filter_ext{
    
    vector (*g)(vector*, vector*);      /**< state prediction function.
                                          returns mu belief and takes 
                                          control and mu(t-1) as arguments. */
    
    vector (*h)(vector*);               /**< measurement prediction.
                                          mu_bel as argument */

    matrix G;                           /**< Jacobian of g(u, mu) */
    matrix H;                           /**< Jacobian of h(mu_bel) */

    matrix Q;                           /**< measurement error covariance */
    matrix R;                           /**< control error covariance */

    //matrix Gt;
    //matrix Ht;
}



/** A Kalman control update only affects the belief of the state,
 * because it only depends on the previous state and the control
 * action. It increases the variance of the state's belief in
 * any case.
 */
void kalman_control_update(struct kalman_state *s,
                            struct kalman_filter *f,
                            vector control){
    /* Pseudo code:
     *
     *    s->mu_bel = f->A * s->mu_bel + f->B * control;
     * s->sigma_bel = f->A * s->sigma_bel * f->At + f->R;
     *
     */
}

/** A Kalman measurement update calculates the current state and
 * its variance with the current belief and a measurement.
 * The belief's variance should decrease.
 */
void kalman_measurement_update(struct kalman_state *s,
                                struct kalman_filter *f,
                                vector measurement){

    /* Pseudo code:
     *
     * matrix K; //(Kalman gain)
     *            K = s->sigma_bel * f->Ct * inv(f->C * s->sigma_bel * f->Ct + f->Q);
     *        s->mu = s->mu_bel + K * (measurement - f->C * s->mu_bel);
     *     s->sigma = s->sigma_bel - K * f->C * s->sigma_bel;
     *
     *    s->mu_bel = s->mu;
     * s->sigma_bel = s->sigma;
     *
     */

}



void kalman_control_update_ext(struct kalman_state *s,
                                struct kalman_filter_ext *f,
                                vector control){

    /* Pseudo code:
     *
     *    s->mu_bel = f->g(&control, &s->mu_bel);
     * s->sigma_bel = f->G * s->sigma_bel * f->Gt + f->R;
     *
     */

}




void kalman_measurement_update_ext(struct kalman_state *s,
                                    struct kalman_filter_ext *f,
                                    vector measurement){

    /* Pseudo code:
     *
     * matrix K; //Kalman gain
     *
     *            K = s->sigma_bel * f->Ht * inv(f->H * s->sigma_bel * f->Ht + f->Q);
     *        s->mu = s->mu_bel + K * (measurement - f->h(&s->mu_bel));
     *     s->sigma = s->sigma_bel - K * f->H * s->sigma_bel;
     *
     *    s->mu_bel = s->mu;
     * s->sigma_bel = s->sigma;
     * 
     */

}
