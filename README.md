##Hardware
###System
Early prototypes that tested line following and remote control functionality utilized the SparkFun RedBot chassis. This allowed electronics to be easily attached to the chassis and for new concepts to be tested before designing and building a final chassis. The SparkFun RedBot was used in Version 1 of the robot with Version 1 of the Source Code in the run-off competition December 4th, 2015. A school chassis was used; however it carried some major issues.
The Chassis Retailed at over $35.00. This is unacceptable in the final design.
The Chassis was too high off of the ground to successfully collect the payload.
The line following sensor was only able to be attached utilizing a single screw in addition to hot glue.
The second version of the IAV chassis solves all of the above problems with the first generation chassis. The design can be manufactured utilizing a laser engraver and any material strong enough to support the weight of the vehicle. It could in theory be manufactured using acrylic plastic, aluminum, or cardboard. This gives flexibility to fix the cost issue. The second generation chassis will ride fairly close to the ground. It is low enough to allow for the payload retrieval subassembly to capture a tennis ball from the pedestal while sitting on top. It does this by mounting wheels above the main chassis itself and effectively hanging from the center of the wheels.
A laser cut plan was used for the second generation chassis. Wheel bays are cut from the left and right of the vehicle. A front section is cut to allow for the line following sensor to be installed. Mounts for the motors and wheels are cut as small rectangles near the wheel bays. The top contains circular screw holes for a ball bearing to serve as a rear wheel, and rectangles are cut to mount the payload retrieval subassembly. This early revision contains an error in the sensor mount that cuts the screw holes for the sensor mount out of the chassis.
The Integrated Autonomous Vehicle utilizes multiple distinct programming layers allowing for abstraction, organization, and reusability. The final IAV code runs on top of line following and remote control receiver components that are non-specific to the specific task. These components were built on a low-level output hardware abstraction layer (HAL) insulates line following and remote control code from the underlying hardware specifics. PID is also abstracted into its own low-level component in order to allow for reusability. Low-level components and libraries run on top of the Arduino software platform, which runs on top of the ATMEGA328 process.
Special care is taken to ensure that the PID loop runs at a precise interval of 10ms. This matters because it is impossible to tune the derivative component accurately if the time between error measurements is inconsistent. This is not an issue for a program where the main loop contains only a PID loop; however, the program also contains code to read from the radio receiver and to process commands. As a result, special care is taken to ensure consistent execution of the control loop.
The line following algorithm utilizes a piece of control theory known as Proportional-Integral-Derivative (PID) control. The integral piece is not used in this application, so it is sometimes referred to as just PD control. The right describes the control loop in block-diagram form. Measured displacement from being centered on the line is used to calculate a difference in motor power between left and right motors. This is added to the initial speed for one motor and subtracted from the other in order to rotate the vehicle such that it veers back onto the line.

### Bill of Materials (BOM)
![BOM](docs/bom.png)

[Click Here to Download BOM](docs/DOM.csv)

### Score over Time

In the TSA IAV competition, one of the largest contributing factors to score is time.

While this is pretty straight-forward, the effect of time on the Integrated Autonomous Vehicle (IAV) cannot be overlooked. The score decreases over time in a linear fashion. This shapes decisions made about the IAV because it must complete the course quickly in order to receive more points.

![score_over_time](docs/score_over_time.png)

##Software
###Architecture

The Integrated Autonomous Vehicle utilizes multiple distinct programming layers allowing for abstraction, organization, and reusability. The final IAV code runs on top of line following and remote control receiver components that are non-specific to the specific task. These components were built on a low-level output hardware abstraction layer (HAL) insulates line following and remote control code from the underlying hardware specifics. PID is also abstracted into its own low-level component in order to allow for reusability. Low-level components and libraries run on top of the Arduino software platform, which runs on top of the ATMEGA328 process.

![dependency_overview](docs/dependency_overview.png)

###Scheduling

Special care is taken to ensure that the PID loop runs at a precise interval of 10ms. This matters because it is impossible to tune the derivative component accurately if the time between error measurements is inconsistent. This is not an issue for a program where the main loop contains only a PID loop; however, the program also contains code to read from the radio receiver and to process commands. As a result, special care is taken to ensure consistent execution of the control loop.

![scheduling](docs/scheduling.png)

###Control Theory

The line following algorithm utilizes a piece of control theory known as Proportional-Integral-Derivative (PID) control. The integral piece is not used in this application, so it is sometimes referred to as just PD control. The right describes the control loop in block-diagram form. Measured displacement from being centered on the line is used to calculate a difference in motor power between left and right motors. This is added to the initial speed for one motor and subtracted from the other in order to rotate the vehicle such that it veers back onto the line.

![Line following block diagram](docs/LineFollowing%20Block%20Diagram.png)

###System Flow Chart

![program overview](docs/Program%20Overview%20Flowchart.png)

