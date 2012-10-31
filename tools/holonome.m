% TODO : - rotation about an arbitrary point

clc;
clear all;

cd 'D:\MATTUX\CVRA\Eurobot 2013\holonome';

tic;
time = 0;

% SYSTEM CONSTANTS (GEOMETRY) VVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVV
alpha1 = ( 70-0) * pi/180;
alpha2 = (180-0) * pi/180;
alpha3 = (290-0) * pi/180;

rad1 = 0.050;
rad2 = 0.068;
rad3 = 0.050;

% centers of wheels
c1_x = 0.1;
c1_y = 0.1;
c1_z = rad1;

c2_x = -0.2;
c2_y = 0;
c2_z = rad2;

c3_x = 0.1;
c3_y = -0.1;
c3_z = rad3;

% VARIABLES VVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVV
pos_x = -1;
pos_y = 0;
pos_z = 1/3 * (c1_z + c2_z + c3_z);

heading = -90 * pi/180;

speed_value = 0.50;                 % m/s
speed_angle = -90 * pi/180;         % rad
speed_angle_variation = 50 * pi/180;         % rad/s

angular_speed_value = -30 * pi/180;   % rad/s

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

action_t = 1;
action_r = 1;

c = 0;

% MAIN LOOP VVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVV
while (1)  %(c < 300)
    t = toc;
   %dt = 1/(30);
    dt = t - time;
    time = t;
    
    % TRANSLATION
    if action_t == 1

        speed_angle = speed_angle + speed_angle_variation  * dt;

        omega1_t = speed_value / rad1 * cos(-speed_angle+heading+alpha1-pi/2);
        omega2_t = speed_value / rad2 * cos(-speed_angle+heading+alpha2-pi/2);
        omega3_t = speed_value / rad3 * cos(-speed_angle+heading+alpha3-pi/2);

        pos_x = pos_x + cos(speed_angle)*speed_value*dt;
        pos_y = pos_y + sin(speed_angle)*speed_value*dt;
        
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
        
        r1 = sqrt( c1_x^2 + c1_y^2 );
        r2 = sqrt( c2_x^2 + c2_y^2 );
        r3 = sqrt( c3_x^2 + c3_y^2 );
        
        omega1_r = -angular_speed_value * r1 / rad1 * cos(-alpha1+atan2(c1_y,c1_x));
        omega2_r = -angular_speed_value * r2 / rad2 * cos(-alpha2+atan2(c2_y,c2_x));
        omega3_r = -angular_speed_value * r3 / rad3 * cos(-alpha3+atan2(c3_y,c3_x));
        
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

    % plot wheels
    points = 12;
    angles1 = [0:2*pi/points:2*pi] + theta1;
    angles2 = [0:2*pi/points:2*pi] + theta2;
    angles3 = [0:2*pi/points:2*pi] + theta3;
    va1 = [sin(-heading-alpha1);cos(-heading-alpha1);0];
    vb1 = [0;0;1];
    wheel1_x = p1_x + rad1*cos(angles1)*va1(1) + rad1*sin(angles1)*vb1(1);
    wheel1_y = p1_y + rad1*cos(angles1)*va1(2) + rad1*sin(angles1)*vb1(2);
    wheel1_z = p1_z + rad1*cos(angles1)*va1(3) + rad1*sin(angles1)*vb1(3);
    va2 = [sin(-heading-alpha2);cos(-heading-alpha2);0];
    vb2 = [0;0;1];
    wheel2_x = p2_x + rad2*cos(angles2)*va2(1) + rad2*sin(angles2)*vb2(1);
    wheel2_y = p2_y + rad2*cos(angles2)*va2(2) + rad2*sin(angles2)*vb2(2);
    wheel2_z = p2_z + rad2*cos(angles2)*va2(3) + rad2*sin(angles2)*vb2(3);
    va3 = [sin(-heading-alpha3);cos(-heading-alpha3);0];
    vb3 = [0;0;1];
    wheel3_x = p3_x + rad3*cos(angles3)*va3(1) + rad3*sin(angles3)*vb3(1);
    wheel3_y = p3_y + rad3*cos(angles3)*va3(2) + rad3*sin(angles3)*vb3(2);
    wheel3_z = p3_z + rad3*cos(angles3)*va3(3) + rad3*sin(angles3)*vb3(3);

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
    
    set(gcf, 'Position', [100 100 1280 720]);
    
    pause(1/50);
    
   %set(gcf,'PaperUnits','inches','PaperPosition',[0 0 16/1.25 9/1.25]);
   %filename = sprintf('fig/fig_%04d', c);
   %saveas(gcf, filename, 'png');
   
    c = c+1;
    
   %break
       
end