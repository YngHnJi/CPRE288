/**
 * @file movement.c
 * @brief C file for functions related with movement combining with UART to send messages
 * @author Younghoon Ji, Emily Kinne
 * @date Nov 26, 2018
 *
 */
#include "movement.h"

void move_forward(oi_t *sensor_data, int dist)
{
    oi_update(sensor_data);
    int count = 0;
    oi_setWheels(130, 130);
    while (count < dist)
    {
        oi_update(sensor_data);

        //check whether the robot is in destination or not
        check_dest(sensor_data);
        //Before move, check the line and cliff first
        if (linedetector(sensor_data))
        {
            move_backward(sensor_data, 100);
            oi_setWheels(0, 0);
            break;
        }

        //detect the collision by bump sensor and its data sends by putty
        else if (sensor_data->bumpLeft || sensor_data->bumpRight
                || (sensor_data->bumpLeft && sensor_data->bumpRight))
        {
            if (sensor_data->bumpLeft && sensor_data->bumpRight)
            {
                uart_sendStr("Double Bumper\n\r");
                lcd_printf("BUMP!!");
            }

            else if (sensor_data->bumpLeft)
            {
                uart_sendStr("Left Bumper\n\r");
                lcd_printf("BUMP!!");
            }
            else if (sensor_data->bumpRight)
            {
                uart_sendStr("Right Bumper\n\r");
                lcd_printf("BUMP!!");
            }
            oi_setWheels(0, 0);
            move_backward(sensor_data, 50);
            break;
        }

        count += sensor_data->distance;
    }
    oi_setWheels(0, 0);
}

void move_backward(oi_t *sensor, int centermeter)
{
    int sum = 0;
    int placement = centermeter;

    oi_setWheels(-100, -100);
    while (sum < placement)
    {
        oi_update(sensor);
        sum -= sensor->distance;
    }
    oi_setWheels(0, 0);
}

void turn_clockwise(oi_t *sensor, int degrees)
{
    int sum = 0;

    if (0 <= degrees && degrees <= 360)
    { //turn right
        oi_setWheels(-250, 250); //right wheel__left wheel

        while (sum < degrees)
        {
            oi_update(sensor);
            sum -= sensor->angle; //negative angle subtracted from sum
        }
        oi_setWheels(0, 0);
    }
    sum = 0;
}

void turn_counterclockwise(oi_t *sensor, int degrees)
{
    int sum = 0;

    if (0 <= degrees && degrees <= 360)
    { //turn left
        oi_setWheels(250, -250); //right wheel__left wheel

        while (sum < degrees)
        {
            oi_update(sensor);
            sum += sensor->angle; //positive angle added to sum
        }
        oi_setWheels(0, 0);
    }
    sum = 0;
}

int linedetector(oi_t *sensor)
{
    int warning = 0;
    oi_update(sensor);
    uint16_t FL_data = sensor->cliffFrontLeftSignal;
    uint16_t FR_data = sensor->cliffFrontRightSignal;
    uint16_t L_data = sensor->cliffLeftSignal;
    uint16_t R_data = sensor->cliffRightSignal;

    //line detection part
    if ((FL_data > 2765 && FL_data < 2915)
            || (FR_data > 2765 && FR_data < 2915))
    {
        warning = 1;
        if ((FL_data > 2765 && FL_data < 2915)
                && (FR_data > 2765 && FR_data < 2915))
        {
            uart_sendStr("Front Tape\n\r");
            lcd_printf("TAPE!!");
        }
        else if ((FL_data > 2765 && FL_data < 2915) && (FR_data < 2765))
        {
            uart_sendStr("Left Tape\n\r");
            lcd_printf("TAPE!!");
        }
        else if ((FR_data > 2765 && FR_data < 2915) && (FL_data < 2765))
        {
            uart_sendStr("Right Tape\n\r");
            lcd_printf("TAPE!!");
        }
        else if (FL_data > 2765 && FL_data < 2915)
        {
            uart_sendStr("Front Tape\n\r");
        }
        else if (FR_data > 2765 && FR_data < 2915)
        {
            uart_sendStr("TAPE\n\r");
        }

    }

    if ((FL_data > 3100) || (FR_data > 3100) || (R_data > 3100)w || (L_data > 3100))
    {
            //warning = 1;
            if (FL_data > 3100)
            {
                uart_sendStr("Front LEFT destination\n\r");
                lcd_printf("DESTINATION!!");
            }
            else if (FR_data > 3100)
            {
                uart_sendStr("Front RIGHT destination\n\r");
                lcd_printf("DESTINATION!!");
            }
            else if (R_data > 3100)
            {
                uart_sendStr("RIGHT destination\n\r");
                lcd_printf("DESTINATION!!");
            }
            else if (L_data > 3100)
            {
                uart_sendStr("LEFT destination\n\r");
                lcd_printf("DESTINATION!!");
            }
        }

        else if (FL_data < 805 || FR_data < 905 || L_data < 755 || R_data < 755)
        {
            warning = 1;
            if (FL_data < 805 && FR_data < 905)
            {
                uart_sendStr("Front Edge\n\r");
                lcd_printf("DROP!!");
            }
            else if (L_data < 755 || FL_data < 805)
            {
                uart_sendStr("Left Edge\n\r");
                lcd_printf("DROP!!");
            }
            else if (R_data < 755 || FR_data < 905)
            {
                uart_sendStr("Right Edge\n\r");
                lcd_printf("DROP!!");
            }
        }
        return warning;

    }

    void check_dest(oi_t *sensor) //detect black colored floor
    {
        uint16_t FL_data = sensor->cliffFrontLeftSignal;
        uint16_t FR_data = sensor->cliffFrontRightSignal;
        uint16_t L_data = sensor->cliffLeftSignal;
        uint16_t R_data = sensor->cliffRightSignal;

        //If it hits a line
        if (FL_data > 980 && FL_data < 1100)
        {
            uart_sendStr("Front Left is in the square\n\r");
        }
        if (FR_data > 940 && FR_data < 980)
        {
            uart_sendStr("Front Right is in the square\n\r");
        }
        if (R_data > 850 && R_data < 900)
        {
            uart_sendStr("Right is in the square\n\r");
        }
        if (L_data > 1100 && L_data < 1250)
        {
            uart_sendStr("Left is in the square\n\r");
        }
    }
