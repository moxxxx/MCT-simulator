MCT-Simulator
Team Number: 34
Yukun Tian, Jojo Duan, April Yu,


## Project Summary

<img src="https://user-images.githubusercontent.com/19592124/115156080-a7531580-a050-11eb-8683-ec88edf616bf.png" width="250"><img src="https://user-images.githubusercontent.com/19592124/115156082-aa4e0600-a050-11eb-8122-a53c1769b58d.png" width="250">

Image1.1 					image1.2

Our MCT-simulator simulates the Denas device (image 1.1). We have a display screen, a power button, up/down/right/left button, back button, menu button, ok button, skinpoint button.

 When users press the power button, the screen displays the menu (image 1.2). Users have 3 options. 

Once users select Program, it is directed to the secondary menu where users can choose treatment programs that are predefined (image 1.3). Once users select one of the programs, users are directed to a page where users can edit the power level they want in the treatment (image1.4). The default Power Level is 50. Once users select power level by clicking the left/right button, press OK to confirm. If OK is not pressed, it uses the default power level. 

Once users click the skinpoint button, which means users have applied their skin on the machine. Treatment started, the screen displayed the current info of the treatment program (image 1.5). During the treatment users are able to change the power level and are able to **exit the program by clicking Back/Menu/Skinpoint buttons**. (or Power Button to shut down) 

Once users exit a program or program time out, it returns the menu.


![3](https://user-images.githubusercontent.com/19592124/115156088-b1751400-a050-11eb-99b9-0665d9e5fe38.png | width=250)
![4](https://user-images.githubusercontent.com/19592124/115156090-b33ed780-a050-11eb-9364-39ef899e7ff1.png  | width=250)


(image 1.3)				    (image 1.4)

If users select to view the records, GUI shows up to 5 records from history(image 1.6).

The last thing is Battery Override panel, where testers can test the system behavior under every power level(image 1.7).  



![5](https://user-images.githubusercontent.com/19592124/115156098-be920300-a050-11eb-80ff-a2b9198ea2ce.png | width=250)
![6](https://user-images.githubusercontent.com/19592124/115156119-d10c3c80-a050-11eb-8d3a-4d8560acfc86.png | width=250)
![7](https://user-images.githubusercontent.com/19592124/115156101-c0f45d00-a050-11eb-8176-78806458ac95.png  | width=250)


(image 1.5)				(image 1.6)			(image 1.7)


## 


## Design Summary: 

Our MCT-Simulator consists of the following classes: OS class, DenasGUI class, TreatmentProgram class and Battery class. 

**OS Class** is responsible to create treatment programs and update the current information to GUI, and handle the request that is sent by GUI.

**DenasGUI Class**  is the graphic interface that users can interact with the OS.

**TreatmentProgram Class** represents the treatment that MCT-simulator provides to users, it was created by the OS and has its lifecycle.

 

**Battery Class** is a GUI for testers to override the battery level for testing purposes. It does not store any information about battery level, OS owns the battery level. 

Our MCT-Simulator is inspired by the MVC design pattern. The Models are OS class and TreatmentProgram Class. The View is Denas GUI where users interact directly. We do not have a controller class as Qt QObjects are communicated by signal and slot. Therefore, we treat the main function as our controller. By placing all connection functions between GUI and OS into the main function we can treat the main function as a controller class.

We also use the Mediator Design Pattern as the core design of our MCT-simulator. OS is the mediator where it handles all the changes that are made by users (externally) or the programs (internally).
