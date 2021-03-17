/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Robot.h"

#include <iostream>
#include <frc/WPILib.h>

#include <frc/smartdashboard/SmartDashboard.h>

void Robot::RobotInit() {
  m_chooser.SetDefaultOption(kAutoNameDefault, kAutoNameDefault);
  m_chooser.AddOption(kAutoNameCustom, kAutoNameCustom);
  frc::SmartDashboard::PutData("Auto Modes", &m_chooser);

  frc::SmartDashboard::PutNumber("Shooter", 0);
  frc::SmartDashboard::PutNumber("Elevator", 0);
  frc::SmartDashboard::PutNumber("Transfer", 0);
  frc::SmartDashboard::PutNumber("Intake", 0);
}

/**
 * This function is called every robot packet, no matter the mode. Use
 * this for items like diagnostics that you want ran during disabled,
 * autonomous, teleoperated and test.
 *
 * <p> This runs after the mode specific periodic functions, but before
 * LiveWindow and SmartDashboard integrated updating.
 */
void Robot::RobotPeriodic() {}

/**
 * This autonomous (along with the chooser code above) shows how to select
 * between different autonomous modes using the dashboard. The sendable chooser
 * code works with the Java SmartDashboard. If you prefer the LabVIEW Dashboard,
 * remove all of the chooser code and uncomment the GetString line to get the
 * auto name from the text box below the Gyro.
 *
 * You can add additional auto modes by adding additional comparisons to the
 * if-else structure below with additional strings. If using the SendableChooser
 * make sure to add them to the chooser code above as well.
 */
void Robot::AutonomousInit() {
  m_autoSelected = m_chooser.GetSelected();
  // m_autoSelected = SmartDashboard::GetString("Auto Selector",
  //     kAutoNameDefault);
  std::cout << "Auto selected: " << m_autoSelected << std::endl;

  if (m_autoSelected == kAutoNameCustom) {
    // Custom Auto goes here
  } else {
    // Default Auto goes here
  }
}

void Robot::AutonomousPeriodic() {
  if (m_autoSelected == kAutoNameCustom) {
    // Custom Auto goes here
  } else {
    // Default Auto goes here
  }
}

void Robot::TeleopInit() {}

void Robot::TeleopPeriodic() {
  //Drive the robot
  xbox.setSquareScale(square);
  if (xbox.GetAButton()) {
    square = !square;
  }
  driveTrain.TankDrive(-xbox.GetRawAxis(1), -xbox.GetRawAxis(5));

  //Activate Limelight tracking
  if (xbox.GetYButton()) {
    while (xbox.GetYButton()) {}
    limelight.set("ledMode", 3); //LED on
    if (limelight.get("tv") == 1) { //If target detected
      float maxAngle = 29.8;
      while(limelight.get("tx") != 0 && !xbox.GetYButton()) {
        driveTrain.ArcadeDrive(0, -limelight.get("tx") / maxAngle);
      }
    }
    limelight.set("ledMode", 1); //LED off
  }
  TankDrive(-xbox.GetLeftDriveTrain(), -xbox.GetRightDriveTrain());
  shooter.Set(frc::SmartDashboard::GetNumber("Shooter", 0));
  elevator.Set(frc::SmartDashboard::GetNumber("Elevator", 0));
  transfer.Set(frc::SmartDashboard::GetNumber("Transfer", 0));
  intake.Set(frc::SmartDashboard::GetNumber("Intake", 0));
}

void Robot::TestPeriodic() {}

#ifndef RUNNING_FRC_TESTS
int main() { return frc::StartRobot<Robot>(); }
#endif
