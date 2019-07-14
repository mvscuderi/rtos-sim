# Discrete Event Simulator For RTOS Scheduler
  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;

## Overview
This program simulates real-time operating system scheduling using three different scheduling algorithms:   
- Rate-Monotic [RMS]
- Earliest Deadline First [EDF]
- First In First Out [FIFO]
  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;

## Repository Setup
There are three folders in the repository:
- bin  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Executables are placed here when testing using the DICE Framework
- src   
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
All sources files are here.  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
RMS &nbsp;&nbsp;&nbsp;:: &nbsp;&nbsp;&nbsp;rms.cpp  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
EDF &nbsp;&nbsp;&nbsp;&nbsp;:: &nbsp;&nbsp;&nbsp;edf.cpp  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
FIFO &nbsp;&nbsp;&nbsp;:: &nbsp;&nbsp;&nbsp;fifo.cpp  
- test  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
Test subdirectories in DICE Framework for easy unit testing.  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;

## Running the Simulator
### File Setup

Every Individual Test Subdirectory should include two files "setup.txt" and
"arrivals.txt" where the inputs for your simulation are defined. 

Your output should contain a time trace for your simulation as explained below. 

<b>I- Setup</b>  

The file setup.txt consists of three parts:
 -Part1: One line (i.e., the first line in the file) which is a positive
integer that sets the number of tasks "n_tasks" that the RTOS should schedule.

 -Part2: "n_tasks" lines that define the tasks that the system should schedule.
Every line has the format:

    <task_id>  <frequency>

Where < task_id > is a positive non-zero integer and < frequency > is the period
of the task < task_id >.

 - Part3: One line that contains a positive integer defining the context
   switching overhead. This overhead can equal zero. This overhead should be
   simulated when the execution of a given task is interrupted by a higher
   priority task


For example, "setup "a system with 2 tasks and scheduler overhead of 1 unit
will look like:    

    2  
    1 100  
    2 50   
    1  


<b>II- Arrivals</b>  
The input file arrivals.txt consists of 2 parts 

 -Part1: One line (i.e., the first line in the file) which is a positive
integer that sets the number of events "n_events" your simulator will trace.

 -Part2: "n_events" lines that define the events the simulator will trace.
Every line has the format: 

    <time> <task_id> <execution_time> <deadline>

where:  
<b>< time ></b> is a positive integer representing the time unit when the event occurs. 
<b>< task_id ></b> is a positive integer that is less than or equal < n_tasks > defining the task_id for the event.  
<b>< execution_time ></b> is non-zero positive integer representing the time required to execute the task that associates this event.  
<b>< deadline ></b> is non-zero positive integer representing the time by which this
event should complete execution.

For example, using the setup.txt example shown above, arrivals.txt can look like:  

    3  
    0 1 20 100  
    1 2 10 50  
    60 2 10 100  

III- Output 
Standard output contains the simulation trace for the system defined in
setup.txt and arrivals.txt. As the simulator is implemented as a discrete
events system, we are only interested in the moment when the task being
executed changes.  

Every line of output has the format:

    <time> <task-id>.<task-instance>

Note: There should be a SINGLE space " " between these three fields.

<b>< time ></b> is the time when the simulator switches tasks. 

<b>< task-id ></b> is the id of task that will start execution.

<b>< task-instance></b> is a non zero positive integer representing each subsequent
instance for the task "task-id". The value of "task-instance" should start by 1
, and be incremented by 1 for every task.  

Two special values of "task-id" are reserved for the context switching overhead and the
idle execution. These values are: '0' for the context switching overhead and "-1" for
idle execution.

For example, given the above values for setup.txt and arrivals.txt, using a RMS or EDF schedules, the output should be:  
   

    0   1.1  
    1   0.1  
    2   2.1  
    12  1.1  
    31 -1.1  
    60  2.2  
    70 -1.2

### Individual Testing
- Compile chosen algorithm using G++
- Command line argument:   

        file.exe    setup.txt   arrivals.txt

### DICE Framework Testing
- Execute makeme in /src/ folder
- Run dxtest command from /test/ folder  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;

## Features & Implementation 
- Context switching overhead of zero or non-zero values
- Task preemption support  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;

## Future Development
- Add metric system to evaluate the best scheduler performance for specific task sets.

