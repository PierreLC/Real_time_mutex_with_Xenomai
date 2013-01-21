Real_time_mutex_with_Xenomai
============================

Filename: rt_mutex_xenomai.c                                                                           
                
Purposet: Test and demonstrate how to use real time mutex in Xenomai. 

Date:     January 2013

Comments: "Xenomai is a real-time development framework cooperating with the Linux kernel,
in order to provide a pervasive, interface-agnostic, hard real-time support
to user-space applications, seamlessly integrated into the GNU/Linux environment."
(source: www.xenomai.org)
This short program aims to demonstrate how to use real time mutex in Xenomai. 
It is tested on a ARM developement platform embedding a minimal linux system.
A RS-232 to USB cable allows to controle the board from the development computer.
The module is build using a cross-toolchaine created with Buildroot. 
