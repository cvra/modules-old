% TODO : - rotation about an arbitrary point

clc;
clear all;

% cd 'D:\MATTUX\CVRA\Eurobot 2013\holonome';

tic;
time = 0;

% modèle simple : 120° entre chaque roue, rayon de roue variable

% SYSTEM CONSTANTS (GEOMETRY) VVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVV
beta1 = ( 60-0) * pi/180;
beta2 = (180-0) * pi/180;
beta3 = (300-0) * pi/180;

% r1 = 0.040*1.2;
% r2 = 0.059*1.3;
% r3 = 0.078*1.4;
% 
% D1 = 0.20;
% D2 = D1*1.4;
% D3 = D1*1.8;

r1 = 0.09;
r2 = 0.09;
r3 = 0.09;

D1 = 0.20;
D2 = D1;
D3 = D1;

% centers of wheels
c1_x = cos(beta1)*D1;
c1_y = sin(beta1)*D1;
c1_z = r1;

c2_x = cos(beta2)*D2;
c2_y = sin(beta2)*D2;
c2_z = r2;

c3_x = cos(beta3)*D3;
c3_y = sin(beta3)*D3;
c3_z = r3;

% VARIABLES VVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVV
pos_x = -1;
pos_y = 0;
pos_z = 1/3 * (c1_z + c2_z + c3_z);

heading = -55 * pi/180; % default: 90

speed_value = 0.75;                 % m/s
speed_angle = -90 * pi/180;         % rad
speed_angle_variation = 50 * pi/180;         % rad/s

angular_speed_value = -90 * pi/180;   % rad/s

rot_point_x = 0;
rot_point_y = 5;

theta1 = 0;
theta2 = 0;
theta3 = 0;

omega1 = 0;
omega2 = 0;
omega3 = 0;
omega1_r = 0;
omega2_r = 0;
omega3_r = 0;
omega1_t = 0;
omega2_t = 0;
omega3_t = 0;

steps1 = 0;
steps2 = 0;
steps3 = 0;
steps_turn = 1024;

sim_pos_x = pos_x;
sim_pos_y = pos_y;
sim_pos_z = pos_z + 0.01;
sim_heading = heading;
sim_posit_x = 0;
sim_posit_y = 0;

action_t = 1;
action_r = 1;

c = 0;

% MAIN LOOP VVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVV
while (1)  %(c < 300)
    t = toc;
    dt = 1/(10);
   %dt = t - time;
    time = t;
    
    steps1 = 0;
    steps2 = 0;
    steps3 = 0;
    
    % TRANSLATION
    if action_t == 1

        speed_angle = speed_angle + speed_angle_variation * dt;

        pos_x = pos_x + cos(speed_angle)*speed_value*dt;
        pos_y = pos_y + sin(speed_angle)*speed_value*dt;

        omega1_t = speed_value / r1 * cos(-speed_angle+heading+beta1-pi/2);
        omega2_t = speed_value / r2 * cos(-speed_angle+heading+beta2-pi/2);
        omega3_t = speed_value / r3 * cos(-speed_angle+heading+beta3-pi/2);
        
        steps1 = steps1 + omega1_t * dt * steps_turn;
        steps2 = steps2 + omega2_t * dt * steps_turn;
        steps3 = steps3 + omega3_t * dt * steps_turn;
        
        % Formules de conversions d'angles pour la commande des moteurs
        % 
        % angle direction-moteur =
        % - angle table-direction
        % + angle table-robot
        % + angle robot-moteur
        %
        % angle table-moteur =
        % + angle table-robot
        % + angle robot-moteur
        
    end
    
    % ROTATION AROUND SELF
    if action_r == 1
        
        heading = heading + angular_speed_value * dt;
        
        omega1_r = -angular_speed_value * D1 / r1;
        omega2_r = -angular_speed_value * D2 / r2;
        omega3_r = -angular_speed_value * D3 / r3;
        
        steps1 = steps1 + omega1_r * dt * steps_turn;
        steps2 = steps2 + omega2_r * dt * steps_turn;
        steps3 = steps3 + omega3_r * dt * steps_turn;
        
    end
    
    omega1 = omega1_t + omega1_r;
    omega2 = omega2_t + omega2_r;
    omega3 = omega3_t + omega3_r;
    
    theta1 = theta1 + omega1*dt;
    theta2 = theta2 + omega2*dt;
    theta3 = theta3 + omega3*dt;
        
    
    
    % actual centers of wheels
    p1_x = c1_x*cos(heading) - c1_y*sin(heading) + pos_x;
    p1_y = c1_x*sin(heading) + c1_y*cos(heading) + pos_y;
    p1_z = c1_z;

    p2_x = c2_x*cos(heading) - c2_y*sin(heading) + pos_x;
    p2_y = c2_x*sin(heading) + c2_y*cos(heading) + pos_y;
    p2_z = c2_z;

    p3_x = c3_x*cos(heading) - c3_y*sin(heading) + pos_x;
    p3_y = c3_x*sin(heading) + c3_y*cos(heading) + pos_y;
    p3_z = c3_z;
    
    % CONSOLE VVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVV
    
    sim_heading = sim_heading -(steps1*r1+steps2*r2+steps3*r3)...
                /(D1+D2+D3)...
                /steps_turn;    % OKAY!!!
    
    mov_x_internal = cos(beta1)*steps1*r1/steps_turn ...
                   + cos(beta2)*steps2*r2/steps_turn ...
                   + cos(beta3)*steps3*r3/steps_turn;
    mov_y_internal = sin(beta1)*steps1*r1/steps_turn ...
                   + sin(beta2)*steps2*r2/steps_turn ...
                   + sin(beta3)*steps3*r3/steps_turn;
    
    mov_x_internal = mov_x_internal *2/3;
    mov_y_internal = mov_y_internal *2/3;
    
    sim_posit_x = sim_posit_x + cos(sim_heading-pi/2)*mov_x_internal - sin(sim_heading-pi/2)*mov_y_internal;
    sim_posit_y = sim_posit_y + sin(sim_heading-pi/2)*mov_x_internal + cos(sim_heading-pi/2)*mov_y_internal;
    
    clc;
    fprintf('steps1: %09.1f \n', steps1);
    fprintf('steps2: %09.1f \n', steps2);
    fprintf('steps3: %09.1f \n', steps3);
    fprintf('Da: %09.1f \n', -(steps1*r1+steps2*r2+steps3*r3)/(D1+D2+D3)/steps_turn);
    
    % DRAW ROBOT VVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVV
    
    % origin
    clf;
    plot3(0, 0, 0, '+k', 'Linesmoothing','on');
    hold on;
    
    % grey grid
    for l = -1.4:0.1:1.4
        plot3([l l], [-1.0 1.0], [0.0 0.0], '-', 'Color',[0.8,0.8,0.8], 'Linesmoothing','on');
    end
    for r = -0.9:0.1:0.9
        plot3([-1.5 1.5], [r r], [0.0 0.0], '-', 'Color',[0.8,0.8,0.8], 'Linesmoothing','on');
    end
    
    % plot table
    plot3([-1.5 1.5 1.5 -1.5 -1.5], ...
          [-1 -1 1 1 -1], ...
          [0 0 0 0 0], '-k', 'Linesmoothing','on');

    % plot chassis
    plot3([p1_x p2_x p3_x p1_x], ...
          [p1_y p2_y p3_y p1_y], ...
          [p1_z p2_z p3_z p1_z], '.-b', 'Linesmoothing','on');

    % plot heading and direction
    quiver3(pos_x, pos_y, pos_z, ...
            cos(heading), sin(heading), 0, ...
            0.12, ...
            'k-', 'LineWidth',1);
    quiver3(pos_x, pos_y, pos_z, ...
            cos(speed_angle), sin(speed_angle), 0, ...
            speed_value, ...
            'g-', 'LineWidth',1);
    plot3(pos_x, pos_y, pos_z,'ok', 'Linesmoothing','on');
    quiver3(sim_pos_x+sim_posit_x, sim_pos_y+sim_posit_y, sim_pos_z, ...
            cos(sim_heading), sin(sim_heading), 0, ...
            0.12, ...
            'r-', 'LineWidth',2);

    % plot wheels
    points = 12;
    angles1 = [0:2*pi/points:2*pi] + theta1;
    angles2 = [0:2*pi/points:2*pi] + theta2;
    angles3 = [0:2*pi/points:2*pi] + theta3;
    va1 = [sin(-heading-beta1);cos(-heading-beta1);0];
    vb1 = [0;0;1];
    wheel1_x = p1_x + r1*cos(angles1)*va1(1) + r1*sin(angles1)*vb1(1);
    wheel1_y = p1_y + r1*cos(angles1)*va1(2) + r1*sin(angles1)*vb1(2);
    wheel1_z = p1_z + r1*cos(angles1)*va1(3) + r1*sin(angles1)*vb1(3);
    va2 = [sin(-heading-beta2);cos(-heading-beta2);0];
    vb2 = [0;0;1];
    wheel2_x = p2_x + r2*cos(angles2)*va2(1) + r2*sin(angles2)*vb2(1);
    wheel2_y = p2_y + r2*cos(angles2)*va2(2) + r2*sin(angles2)*vb2(2);
    wheel2_z = p2_z + r2*cos(angles2)*va2(3) + r2*sin(angles2)*vb2(3);
    va3 = [sin(-heading-beta3);cos(-heading-beta3);0];
    vb3 = [0;0;1];
    wheel3_x = p3_x + r3*cos(angles3)*va3(1) + r3*sin(angles3)*vb3(1);
    wheel3_y = p3_y + r3*cos(angles3)*va3(2) + r3*sin(angles3)*vb3(2);
    wheel3_z = p3_z + r3*cos(angles3)*va3(3) + r3*sin(angles3)*vb3(3);

    plot3(wheel1_x, wheel1_y, wheel1_z, '.-k', 'Linesmoothing','on');
    plot3([wheel1_x(1) p1_x], [wheel1_y(1) p1_y], [wheel1_z(1) p1_z], '.-k', 'LineWidth',1, 'Linesmoothing','on');
    plot3(wheel2_x, wheel2_y, wheel2_z, '.-b', 'Linesmoothing','on');
    plot3([wheel2_x(1) p2_x], [wheel2_y(1) p2_y], [wheel2_z(1) p2_z], '.-b', 'LineWidth',1, 'Linesmoothing','on');
    plot3(wheel3_x, wheel3_y, wheel3_z, '.-r', 'Linesmoothing','on');
    plot3([wheel3_x(1) p3_x], [wheel3_y(1) p3_y], [wheel3_z(1) p3_z], '.-r', 'LineWidth',1, 'Linesmoothing','on');

    axis equal;
    xlim('manual');
    ylim('manual');
    zlim('manual');
    xlim([-1.5 1.5]);
    ylim([-1.0 1.0]);
    zlim([0 0.4]);
    
   %set(gcf, 'Position', [100 100 1280 720]);
    
    pause(1/500);
    
   %set(gcf,'PaperUnits','inches','PaperPosition',[0 0 16/1.25 9/1.25]);
   %filename = sprintf('fig/fig_%04d', c);
   %saveas(gcf, filename, 'png');
   
    c = c+1;
    
   %break
       
end


