#include "auto/auto.hpp"
#include "lemlib/api.hpp" // IWYU pragma: keep
#include "main.h"
#include "2813X_Functions/subsystem.hpp"
#include "pros/device.hpp"
#include "pros/misc.h"
#include "pros/motors.h"
#include "pros/rtos.hpp"
#include "Selector/Selector.hpp"
#include "setup.hpp"
#include <cstdio>
#include "liblvgl/draw/lv_draw_img.h"
#include "pros/apix.h"

lemlib::ExpoDriveCurve throttle_curve(3, // joystick deadband out of 127
                                     10, // minimum output where drivetrain will move out of 127
                                     1.019 // expo curve gain
);

// TEST

//true(紅隊、skill) & falses(藍隊)
bool team;

bool off = true;


/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
	printf("//Initialize//\n");
	chassis.calibrate();
	pros::Task task([&](){
		while(true){
			// 測試區域
			// printf("OuO");
			pros::delay(50);
		}
	});

	chassis.setBrakeMode(pros::E_MOTOR_BRAKE_HOLD);
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {
	printf("//Disabled//\n");
}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {
	printf("//Competition_Initialize//\n");
	const char* autons[] = {"Left", "Solo", "Right", "Special"};
	Teamselector::init(2, autons);
}

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous() {
	printf("//AutonomousProgram//\n");
	off = true;
	switch (Teamselector::get_auton()) {
		case 0:
			printf("Skill\n");
			team = true; //true(紅隊、skill) & falses(藍隊)
			Skill::skill();
			break;
		case 1:
			printf("RedLeft\n");
			team = true; //true(紅隊、skill) & falses(藍隊)
			Red::left();
			break;
		case 2:
			printf("RedSolo\n");
			team = true; //true(紅隊、skill) & falses(藍隊)
			Red::solo();
			break;
		case 3:
			printf("RedRight\n");
			team = true; //true(紅隊、skill) & falses(藍隊)
			Red::right();
			break;
		case 4:
			printf("RedSpecial\n");
			team = true; //true(紅隊、skill) & falses(藍隊)
			Red::special();
			break;
		case -1:
			printf("BlueLeft\n");
			team = false; //true(紅隊、skill) & falses(藍隊)
			Blue::left();
			break;
		case -2:
			printf("BlueSolo\n");
			team = false; //true(紅隊、skill) & falses(藍隊)
			Blue::solo();
			break;
		case -3:
			printf("BlueRight\n");
			team = false; //true(紅隊、skill) & falses(藍隊)
			Blue::right();
			break;
		case -4:
			printf("BlueSpecial\n");
			team = false; //true(紅隊、skill) & falses(藍隊)
			Blue::special();
			break;
	}
}

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
void opcontrol() {
	printf("//opcontrol//\n");
	off = false;
	chassis.setBrakeMode(pros::motor_brake_mode_e::E_MOTOR_BRAKE_COAST);
	controller.clear();

	pros::Task teamSW([&](){
		while (true) {
			Teamselector::teamSW(false);
			pros::delay(10);
		}
	});
	while(true){
		chassis.arcade(controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y), controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X), false, 0.51);
		pros::delay(10);
	}
}