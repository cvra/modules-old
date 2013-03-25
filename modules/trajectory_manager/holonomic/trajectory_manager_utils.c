#include <holonomic/trajectory_manager_utils.h>
#include <scheduler.h>
#include <quadramp.h>
#include <ramp.h>s

/** set (quad)ramps max speeds et max acc @todo : accesseurs individuels*/
void holonomic_init_ramps(struct h_trajectory *traj, double s_acc, double o_acc, 
                            double a_speed, double a_acc)
{
    /** @todo :les vrais inits ? */
    struct quadramp_filter * q_a;
    struct ramp_filter *r_s,*r_o;
    q_a = traj->csm_angle->consign_filter_params;
    r_s = traj->csm_speed->consign_filter_params;
    r_o = traj->csm_omega->consign_filter_params;
    
    /** Initialisation du quadramp pour l'angle */
    quadramp_set_1st_order_vars(q_a, ABS(a_speed), ABS(a_speed));
    quadramp_set_2nd_order_vars(q_a, ABS(a_acc), ABS(a_acc));
    
    /** Initialisation du ramp de vitesse et de vitesse angulaire */
    ramp_set_vars(r_s, ABS(s_acc), ABS(s_acc));
    ramp_set_vars(r_o, ABS(o_acc), ABS(o_acc));
    /** @todo : ajouter le do_quadramp */
}

void holonomic_trajectory_manager_event(void * param)
{
    struct h_trajectory *traj = (struct h_trajectory *) param;
    double x = holonomic_position_get_x_double(traj->position);
    double y = holonomic_position_get_y_double(traj->position);
    /** The speed consign, the angle consign and the angular speed (omega) consign */ 
    int32_t s_consign = 0, a_consign = 0, o_consign = 0;

    /* step 1 : process new commands to quadramps */
    switch (traj->moving_state) {
         case MOVING_STRAIGHT:
            o_consign = 0;
            a_consign = 0;
            // Pour v : demander un ramp (on donne comme position la distance par rapport a la destination
            break;
         //case MOVING_CIRCLE:
            //o_consign = 0;
            //// Pour v : Attention à la rotation. Quadramp (calculer la longueur de l'arc) 
            ////Pour la direction : faire les maths
            //break;
        default:
                s_consign = 0;
                o_consign = 0;
                //d_consign = get current position;
            break;

        //d_consign = (int32_t)(v2pol_target.r * (traj->position->phys.distance_imp_per_mm));
        //d_consign += rs_get_distance(traj->robot);

        ///* angle consign */
        ///* Here we specify 2.2 instead of 2.0 to avoid oscillations */
        //a_consign = (int32_t)(v2pol_target.theta *
                      //(traj->position->phys.distance_imp_per_mm) *
                      //(traj->position->phys.track_mm) / 2.2);
        //a_consign += rs_get_angle(traj->robot);
}
    /* step 2 : update state, or delete event if we reached the
     * destination */
    if (holonomic_robot_in_xy_window(traj, traj->d_win)) {
            holonomic_delete_event(traj);
        }

    /* step 3 : send the processed commands to cs */

    //EVT_DEBUG(E_TRAJECTORY,"EVENT XY d_cur=%" PRIi32 ", d_consign=%" PRIi32 ", d_speed=%" PRIi32 ", "
          //"a_cur=%" PRIi32 ", a_consign=%" PRIi32 ", a_speed=%" PRIi32,
          //rs_get_distance(traj->robot), d_consign, get_quadramp_distance_speed(traj),
          //rs_get_angle(traj->robot), a_consign, get_quadramp_angle_speed(traj));

    cs_set_consign(traj->csm_angle, a_consign);
    //cs_set_consign(traj->csm_distance, d_consign);
}

/** near the target (dist in x,y) ? */
uint8_t holonomic_robot_in_xy_window(struct h_trajectory *traj, double d_win)
{
    double x1 = traj->xy_target.x;
    double y1 = traj->xy_target.y;
    double x2 = holonomic_position_get_x_double(traj->position);
    double y2 = holonomic_position_get_y_double(traj->position);
    return (sqrt ((x2-x1) * (x2-x1) + (y2-y1) * (y2-y1)) < d_win);
    
}

/** returns true if the robot is in an area enclosed by a certain angle 
  * @todo */
uint8_t holonomic_robot_in_angle_window(struct h_trajectory *traj, double a_win_rad)
{
    double a = traj->a_target;

    return (a < a + a_win_rad/2 && a > a - a_win_rad/2);
}

/** remove event if any @todo */
void holonomic_delete_event(struct h_trajectory *traj)
{
    //set_quadramp_speed(traj, traj->d_speed, traj->a_speed);
    //set_quadramp_acc(traj, traj->d_acc, traj->a_acc);
    //if ( traj->scheduler_task != -1) {
        //DEBUG(E_TRAJECTORY, "Delete event");
        //scheduler_del_event(traj->scheduler_task);
        //traj->scheduler_task = -1;
    //}
}

/** schedule the trajectory event */
void holonomic_schedule_event(struct h_trajectory *traj)
{
    if ( traj->scheduler_task != -1) {
        DEBUG(E_TRAJECTORY, "Schedule event, already scheduled");
    }
    else {
        traj->scheduler_task =
            scheduler_add_periodical_event_priority(&holonomic_trajectory_manager_event,
                                (void*)traj,
                                TRAJ_EVT_PERIOD, 30);
    }
}

/** do a modulo 2.pi -> [-Pi,+Pi], knowing that 'a' is in [-3Pi,+3Pi] */
double holonomic_simple_modulo_2pi(double a)
{
    if (a < -M_PI) {
        a += M_2PI;
    }
    else if (a > M_PI) {
        a -= M_2PI;
    }
    return a;
}

/** do a modulo 2.pi -> [-Pi,+Pi] */
double holonomic_modulo_2pi(double a)
{
    double res = a - (((int32_t) (a/M_2PI)) * M_2PI);
    return holonomic_simple_modulo_2pi(res);
}


