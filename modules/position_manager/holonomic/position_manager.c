/*  
 *  Copyright Droids Corporation, Microb Technology, Eirbot (2005)
 * 
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 *  Revision : $Id: position_manager.c,v 1.6.4.7 2009-05-18 12:27:26 zer0 Exp $
 *
 */

//#include <string.h>
//#include <math.h>

//#include <holonomic/position_manager.h>

///** initialization of the robot_position pos, everthing is set to 0 */
//void holonomic_position_init(struct holonomic_robot_position *pos)
//{
    //memset(pos, 0, sizeof(struct holonomic_robot_position));
//}


///** @brief Call an encoder pointer :
 //*
 //* This function reads the pointer to the encoder function and if the pointer 
 //* is not null call the encoder function and return its result. If it is null,
 //* then return 0.
 //*
 //* @param [in] rs The robot_system instance.
 //*
 //* @return The value of the encoder if defined, 0 otherwise.
 //*/
//static inline uint32_t safe_getencoder(int32_t (*f)(void *), void * param)
//{
    //int32_t (*f_tmp)(void *);
    //void* param_tmp;
    //f_tmp = f;
    //param_tmp = param;
    //if (f_tmp) {
        //return f_tmp(param_tmp);
    //}
    //return 0;
//}


///** Set a new robot position */
//void holonomic_position_set(struct holonomic_robot_position *pos, int16_t x, int16_t y, int16_t a_deg)
//{
    //pos->pos_d.a = (a_deg * M_PI)/ 180.0;
    //pos->pos_d.x = x;
    //pos->pos_d.y = y;
    //pos->pos_s16.x = x;
    //pos->pos_s16.y = y;
    //pos->pos_s16.a = a_deg;
//}


///** 
 //* Set the physical parameters of the robot : 
 //*  - number of impulsions for 1 mm (distance)
 //*  - number of impulsions for 1 degree (angle)
 //*/
//void holonomic_position_set_physical_params(struct holonomic_robot_position *pos, double beta[static 3],
                  //double wheel_radius[static 3], double wheel_distance[static 3],
                  //int32_t encoder_resolution){

    //pos->geometry.wheel_sum_distance = 0.0;

    //int i;
    //for(i = 0; i < 3; i++){
        //pos->geometry.beta[i] = beta[i];

        //pos->geometry.cos_beta[i] = cos(beta[i]);
        //pos->geometry.sin_beta[i] = sin(beta[i]);

        //pos->geometry.wheel_radius[i] = wheel_radius[i];
        //pos->geometry.wheel_distance[i] = wheel_distance[i];

        //pos->geometry.wheel_sum_distance += wheel_distance[i];

        //pos->geometry.encoder_resolution = encoder_resolution;
    //}
//}

//void holonomic_position_set_mot_encoder(struct holonomic_robot_position *pos,
                                        //int32_t (*motor_encoder[static 3])(void *),
                                        //void *motor_encoder_param[static 3]){
    //int i;
    //for(i = 0; i < 3; i++){
        //pos->motor_encoder[i] = motor_encoder[i];
        //pos->motor_encoder_param[i] = motor_encoder_param[i];
    //}
//}

//void holonomic_position_set_update_frequency(struct holonomic_robot_position *pos, float frequency){
    //pos->update_frequency = frequency;
//}


//float holonomic_position_get_instant_translation_speed(struct holonomic_robot_position *pos){
    //return pos->speed;
//}

//double holonomic_position_get_instant_rotation_speed(struct holonomic_robot_position *pos){
    //double d_a;

    //d_a = pos->pos_d.a - pos->previous_pos_d.a;

    //return d_a * pos->update_frequency; 
//}

//int32_t holonomic_position_get_translation_speed_int(void *data){
    //struct holonomic_robot_position *pos = data;
    //return (int32_t)holonomic_position_get_instant_translation_speed(pos);
//}

//int32_t holonomic_position_get_rotation_speed_int(void *data){
    //struct holonomic_robot_position *pos = data;
    //return (int32_t)holonomic_position_get_instant_rotation_speed(pos);
//}

//float holonomic_position_get_theta_v(struct holonomic_robot_position *pos){
    //return pos->theta_v;
//}

//int32_t holonomic_position_get_theta_v_int(void *data){
    //struct holonomic_robot_position *pos = data;
    //return TO_DEG(holonomic_position_get_theta_v(pos));
//}

///** 
 //* Process the absolute position (x,y,a) depending on the delta on
 //* virtual encoders since last read, and depending on physical
 //* parameters. The processed position is in mm.
 //* @todo : Angle entre -M_PI et M_PI + le mettre qqpart dans les commentaire
 //*/
//void holonomic_position_manage(struct holonomic_robot_position *pos)
//{
    //double sum_wheel_steps_dist = 0.0;
    //double sum_cos_steps_dist = 0.0;
    //double sum_sin_steps_dist = 0.0;

    //int i;
    //for(i = 0; i < 3; i++){
        //const int32_t new_enc_val = safe_getencoder(pos->motor_encoder[i], pos->motor_encoder_param[i]);
        //const int32_t enc_steps = new_enc_val - pos->encoder_val[i];

        //pos->encoder_val[i] = new_enc_val;
        //pos->delta_enc[i] = enc_steps;

        //const int32_t neg_steps = - enc_steps;

        //sum_wheel_steps_dist += neg_steps * pos->geometry.wheel_radius[i];
        //sum_cos_steps_dist += pos->geometry.cos_beta[i] * neg_steps * pos->geometry.wheel_radius[i];
        //sum_sin_steps_dist += pos->geometry.sin_beta[i] * neg_steps * pos->geometry.wheel_radius[i];
    //}

    //const double new_a = pos->pos_d.a
                       //- M_TWOPI / (double)pos->geometry.encoder_resolution *
                         //sum_wheel_steps_dist / pos->geometry.wheel_sum_distance
                       //- M_PI_2;

    //const double delta_x = (M_TWOPI * 2./3. * sum_cos_steps_dist) / (double)pos->geometry.encoder_resolution;
    //const double delta_y = (M_TWOPI * 2./3. * sum_sin_steps_dist) / (double)pos->geometry.encoder_resolution;

    //pos->speed = sqrt(delta_x*delta_x + delta_y*delta_y) * pos->update_frequency;
    ///** @todo @bug IT DOES NOT WORK */
    //pos->theta_v = atan2(delta_y, delta_x);

    ///* Conversion to table-coordinates: */
    //const double cos_a = cos(new_a);
    //const double sin_a = sin(new_a);
    //const double new_x = pos->pos_d.x + cos_a*delta_x - sin_a*delta_y;
    //const double new_y = pos->pos_d.y + sin_a*delta_x + cos_a*delta_y;

    ///* Setting the new position in double */
  //pos->previous_pos_d.x = pos->pos_d.x;
  //pos->previous_pos_d.y = pos->pos_d.y;
  //pos->previous_pos_d.a = pos->pos_d.a;
    ////pos->previous_pos_d = pos->pos_d;

    //pos->pos_d.x = new_x;
    //pos->pos_d.y = new_y;
    //pos->pos_d.a = new_a;
    
    ///* Setting the new position in integer */
    //pos->pos_s16.x = (int16_t)new_x;
    //pos->pos_s16.y = (int16_t)new_y;
    //pos->pos_s16.a = (int16_t)(new_a * 180.0/M_PI);
//}


//void holonomic_position_set_x_s16(struct holonomic_robot_position *pos, int16_t x){
    //pos->pos_s16.x = x;
    //pos->pos_d.x = (double)x;
//}

//void holonomic_position_set_y_s16(struct holonomic_robot_position *pos, int16_t y){
    //pos->pos_s16.y = y;
    //pos->pos_d.y = (double)y;
//}

//void holonomic_position_set_a_s16(struct holonomic_robot_position *pos, int16_t a){
    //pos->pos_s16.a = a;
    //pos->pos_d.a = (double)a;
//}

///**
 //* returns current x
 //*/
//int16_t holonomic_position_get_x_s16(struct holonomic_robot_position *pos)
//{
    //return pos->pos_s16.x;
//}

///**
 //* returns current y
 //*/
//int16_t holonomic_position_get_y_s16(struct holonomic_robot_position *pos)
//{
    //return pos->pos_s16.y;
//}

///**
 //* returns current alpha
 //*/
//int16_t holonomic_position_get_a_deg_s16(struct holonomic_robot_position *pos)
//{
    //return pos->pos_s16.a;
//}

//int32_t holonomic_position_get_a_deg_s32(void *data)
//{
    //struct holonomic_robot_position *pos = data;
    //return (int32_t) pos->pos_s16.a;
//}

///********* double */

///**
 //* returns current x
 //*/
//double holonomic_position_get_x_double(struct holonomic_robot_position *pos)
//{
    //return pos->pos_d.x;
//}
//float holonomic_position_get_x_float(struct holonomic_robot_position *pos)
//{
    //return (float)pos->pos_d.x;
//}

///**
 //* returns current y
 //*/
//double holonomic_position_get_y_double(struct holonomic_robot_position *pos)
//{
    //return pos->pos_d.y;
//}
//float holonomic_position_get_y_float(struct holonomic_robot_position *pos)
//{
    //return (float)pos->pos_d.y;
//}

//vect2_cart holonomic_position_get_xy_vect(struct holonomic_robot_position *pos)
//{
    //vect2_cart r;
    //r.x = (float)pos->pos_d.x;
    //r.y = (float)pos->pos_d.y;
    //return r;
//}
///**
 //* returns current alpha
 //*/
//double holonomic_position_get_a_rad_double(struct holonomic_robot_position *pos)
//{
    //return pos->pos_d.a;
//}

///**
 //* returns current alpha
 //*/
//float holonomic_position_get_a_rad_float(struct holonomic_robot_position *pos)
//{
    //return (float)(pos->pos_d.a);
//}



#include <string.h>
#include <math.h>

#include <holonomic/position_manager.h>

/** initialization of the robot_position pos, everthing is set to 0 */
void holonomic_position_init(struct holonomic_robot_position *pos)
    
{
    memset(pos, 0, sizeof(struct holonomic_robot_position));
}


/** @brief Call an encoder pointer :
 *
 * This function reads the pointer to the encoder function and if the pointer 
 * is not null call the encoder function and return its result. If it is null,
 * then return 0.
 *
 * @param [in] rs The robot_system instance.
 *
 * @return The value of the encoder if defined, 0 otherwise.
 */
static inline uint32_t safe_getencoder(int32_t (*f)(void *), void * param)
{
    int32_t (*f_tmp)(void *);
    void * param_tmp;
    f_tmp = f;
    param_tmp = param;
    if (f_tmp) {
        return f_tmp(param_tmp);
    }
    return 0;
}


/** Set a new robot position */
void holonomic_position_set(struct holonomic_robot_position *pos, int16_t x, int16_t y, int16_t a_deg)
{
    pos->pos_d.a = (a_deg * M_PI)/ 180.0;
    pos->pos_d.x = x;
    pos->pos_d.y = y;
    pos->pos_s16.x = x;
    pos->pos_s16.y = y;
    pos->pos_s16.a = a_deg;
}


/** 
 * Set the physical parameters of the robot : 
 *  - number of impulsions for 1 mm (distance)
 *  - number of impulsions for 1 degree (angle)
 */
void holonomic_position_set_physical_params(struct holonomic_robot_position *pos, double beta[static 3],
                  double wheel_radius[static 3], double wheel_distance[static 3],
                  int32_t encoder_resolution){

    pos->geometry.wheel_sum_distance = 0.0;

    int i;
    for(i = 0; i < 3; i++){
        pos->geometry.beta[i] = beta[i];

        pos->geometry.cos_beta[i] = cos(beta[i]);
        pos->geometry.sin_beta[i] = sin(beta[i]);

        pos->geometry.wheel_radius[i] = wheel_radius[i];
        pos->geometry.wheel_distance[i] = wheel_distance[i];

        pos->geometry.wheel_sum_distance += wheel_distance[i];

        pos->geometry.encoder_resolution = encoder_resolution;
    }
}

void holonomic_position_set_mot_encoder(struct holonomic_robot_position *pos,
                                        int32_t (*motor_encoder[static 3])(void *),
                                        void *motor_encoder_param[static 3]){
    int i;
    for(i = 0; i < 3; i++){
        pos->motor_encoder[i] = motor_encoder[i];
        pos->motor_encoder_param[i] = motor_encoder_param[i];
    }
}

void holonomic_position_set_update_frequency(struct holonomic_robot_position *pos, float frequency){
    pos->update_frequency = frequency;
}


float holonomic_position_get_instant_translation_speed(struct holonomic_robot_position *pos){
    return pos->speed;
}

double holonomic_position_get_instant_rotation_speed(struct holonomic_robot_position *pos){
    double d_a;

    d_a = pos->pos_d.a - pos->previous_pos_d.a;

    return d_a * pos->update_frequency; 
}

int32_t holonomic_position_get_translation_speed_int(void *data){
    struct holonomic_robot_position *pos = data;
    return (int32_t)holonomic_position_get_instant_translation_speed(pos);
}

int32_t holonomic_position_get_rotation_speed_int(void *data){
    struct holonomic_robot_position *pos = data;
    return (int32_t)holonomic_position_get_instant_rotation_speed(pos);
}

float holonomic_position_get_theta_v(struct holonomic_robot_position *pos){
    return pos->theta_v;
}

int32_t holonomic_position_get_theta_v_int(void *data){
    struct holonomic_robot_position *pos = data;
    return TO_DEG(holonomic_position_get_theta_v(pos));
}

/** 
 * Process the absolute position (x,y,a) depending on the delta on
 * virtual encoders since last read, and depending on physical
 * parameters. The processed position is in mm.
 * @todo : Angle entre -M_PI et M_PI + le mettre qqpart dans les commentaire
 */
void holonomic_position_manage(struct holonomic_robot_position *pos)
{
    int32_t new_encoder_val[3];
    int32_t encoder_steps[3];
    double new_x, new_y, new_a;
    double delta_x, delta_y;
    double sum_wheel_steps_distance = 0.0;
    double sum_cos_steps_distance = 0.0, sum_sin_steps_distance = 0.0;
    int i;

    for(i = 0; i < 3; i++){
        new_encoder_val[i] = - safe_getencoder(pos->motor_encoder[i],
                                               pos->motor_encoder_param[i]);

        encoder_steps[i] = new_encoder_val[i] - pos->encoder_val[i];
        pos->delta_enc[i] = encoder_steps[i];
        pos->encoder_val[i] = new_encoder_val[i];

        sum_wheel_steps_distance += encoder_steps[i] * pos->geometry.wheel_radius[i];
        sum_cos_steps_distance += pos->geometry.cos_beta[i] * encoder_steps[i] * 
                                  pos->geometry.wheel_radius[i];

        sum_sin_steps_distance += pos->geometry.sin_beta[i] * encoder_steps[i] 
                                  * pos->geometry.wheel_radius[i];
    }

    new_a = pos->pos_d.a - 2.0 * M_PI / (double)pos->geometry.encoder_resolution
            * sum_wheel_steps_distance / pos->geometry.wheel_sum_distance;

    delta_x = 2.0 * M_PI * 2. / 3. / (double)pos->geometry.encoder_resolution * sum_cos_steps_distance;
    delta_y = 2.0 * M_PI * 2. / 3. / (double)pos->geometry.encoder_resolution * sum_sin_steps_distance;

    pos->speed = sqrt(delta_x * delta_x + delta_y * delta_y) * pos->update_frequency;
    /** @todo @bug IT DOES NOT WORK */
    pos->theta_v = atan2(delta_y, delta_x);

    /* Conversion to table-coordinates: */
    double cos_a = cos(new_a - M_PI_2);
    double sin_a = sin(new_a - M_PI_2);

    new_x = pos->pos_d.x + cos_a * delta_x - sin_a * delta_y;
    new_y = pos->pos_d.y + sin_a * delta_x + cos_a * delta_y;

    /* Setting the new position in double */
    pos->previous_pos_d.x = pos->pos_d.x;
    pos->previous_pos_d.y = pos->pos_d.y;
    pos->previous_pos_d.a = pos->pos_d.a;
    pos->pos_d.x = new_x;
    pos->pos_d.y = new_y;
    pos->pos_d.a = new_a;
    
    /* Setting the new position in integer */
    pos->pos_s16.x = (int16_t)new_x;
    pos->pos_s16.y = (int16_t)new_y;
    pos->pos_s16.a = (int16_t)(new_a * (180.0/(M_PI)));
}


void holonomic_position_set_x_s16(struct holonomic_robot_position *pos, int16_t x){
    pos->pos_s16.x = x;
    pos->pos_d.x = (double)x;
}

void holonomic_position_set_y_s16(struct holonomic_robot_position *pos, int16_t y){
    pos->pos_s16.y = y;
    pos->pos_d.y = (double)y;
}

void holonomic_position_set_a_s16(struct holonomic_robot_position *pos, int16_t a){
    pos->pos_s16.a = a;
    pos->pos_d.a = (double)a;
}

/**
 * returns current x
 */
int16_t holonomic_position_get_x_s16(struct holonomic_robot_position *pos)
{
    return pos->pos_s16.x;
}

/**
 * returns current y
 */
int16_t holonomic_position_get_y_s16(struct holonomic_robot_position *pos)
{
    return pos->pos_s16.y;
}

/**
 * returns current alpha
 */
int16_t holonomic_position_get_a_deg_s16(struct holonomic_robot_position *pos)
{
    return pos->pos_s16.a;
}

int32_t holonomic_position_get_a_deg_s32(void *data)
{
    struct holonomic_robot_position *pos = data;
    return (int32_t) pos->pos_s16.a;
}

/********* double */

/**
 * returns current x
 */
double holonomic_position_get_x_double(struct holonomic_robot_position *pos)
{
    return pos->pos_d.x;
}
float holonomic_position_get_x_float(struct holonomic_robot_position *pos)
{
    return (float)pos->pos_d.x;
}

/**
 * returns current y
 */
double holonomic_position_get_y_double(struct holonomic_robot_position *pos)
{
    return pos->pos_d.y;
}
float holonomic_position_get_y_float(struct holonomic_robot_position *pos)
{
    return (float)pos->pos_d.y;
}

vect2_cart holonomic_position_get_xy_vect(struct holonomic_robot_position *pos)
{
    vect2_cart r;
    r.x = (float)pos->pos_d.x;
    r.y = (float)pos->pos_d.y;
    return r;
}
/**
 * returns current alpha
 */
double holonomic_position_get_a_rad_double(struct holonomic_robot_position *pos)
{
    return pos->pos_d.a;
}

/**
 * returns current alpha
 */
float holonomic_position_get_a_rad_float(struct holonomic_robot_position *pos)
{
    return (float)(pos->pos_d.a);
}
