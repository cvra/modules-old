#include <holonomic/trajectory_manager_utils.h>
#include <scheduler.h>



void holonomic_trajectory_manager_event(void * param)
{
    struct h_trajectory *traj = (struct h_trajectory *)param;
    //x = position_get_x_double(traj->position);
    //y = position_get_y_double(traj->position);
    //double speed = position_get_x_double(traj->position);
    //double direction = position_get_y_double(traj->position);
    //double omega = position_get_a_rad_double(traj->position);
    int32_t s_consign = 0, d_consign = 0, o_consign = 0;

    /* These vectors contain target position of the robot in
     * its own coordinates */ 
    //vect2_cart v2cart_pos; // ?
    //vect2_pol v2pol_target;

    /* step 1 : process new commands to quadramps */

    switch (traj->moving_state) {
         MOVING_STRAIGHT:
            o_consign = 0;
            // Pour v : demander un quadramp (on donne comme position la distance par rapport a la destination
            // pour la drection : trigo entre position initial et position final
            break;
         MOVING_CIRCLE:
            o_consign = 0;
            // Pour v : Attention à la rotation. Quadramp (calculer la longueur de l'arc) 
            //Pour la direction : faire les maths
            break;
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

    //cs_set_consign(traj->csm_angle, a_consign);
    //cs_set_consign(traj->csm_distance, d_consign);
}

/** near the target (dist in x,y) ? */
uint8_t holonomic_robot_in_xy_window(struct h_trajectory *traj, double d_win)
{
    double x1 = traj->xy_target.x;
    double y1 = traj->xy_target.y;
    double x2 = position_get_x_double(traj->position);
    double y2 = position_get_y_double(traj->position);
    return (sqrt ((x2-x1) * (x2-x1) + (y2-y1) * (y2-y1)) < d_win);
    
}

/** near the angle target in radian ? Only valid if
 *  traj->target.pol.angle is set (i.e. an angle command, not an xy
 *  command)
 * @todo  */
uint8_t holonomic_robot_in_angle_window(struct h_trajectory *traj, double a_win_rad)
{
    double a;

    /////* convert relative angle from imp to rad */
    ////a = traj->target.pol.angle - rs_get_angle(traj->robot);
    ////a /= traj->position->phys.distance_imp_per_mm;
    ////a /= traj->position->phys.track_mm;
    ////a *= 2.;
    //return ABS(a) < a_win_rad;
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

