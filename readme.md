# AwesomeScheduler

AwesomeScheduler is a high-level scheduler powered by C++11 and Boost.  
_____________________________________________________________________________  

**Starting : end-user sends a request to dispacher**  
 - dispatcher.cpp : Dispacher receiving work requests  
 - end-user.cpp : End-user sending work requests  

**Front-end processing in dispacher**  
 - In progress  

**Software running in each worker (multi-thread monitoring)**  
 - Planified  

**Move a job from one machine to another**  
 - Planified  

**Miscellanous**  
 - task_properties.cpp : XML parser for work requests  
 - task[x].xml : Work unit properties for a task "x"  
_____________________________________________________________________________  

For more informations see "GSI-README" file from Bernard Glonneau  

### Version
0.0.1

### Techologies
AwesomeScheduler uses a number of open source projects to work properly:  
* [C++] - compiled programming language  
* [Boost] - set of libraries for the C++ programming language  
* [OpenMP] - api that supports multi-platform shared memory multiprocessing programming  
* [MPI] - standardized and portable message-passing system  

### Installation  
You need GCC, Boost and CMake installed :  

```sh
$ git clone http://gitlab.etude.eisti.fr/TeamAwesome/AwesomeScheduler.git
$ cd AwesomeScheduler
$ source build.sh
```

### Development
First Tab:  
```sh
$ ./Dispatcher
```

Second Tab:  
```sh
$ ./EndUser
```

### Todos
 - Frond-end processing in dispatcher
 - Software running in each worker (multi-process monitoring)
 - Software running in each worker (multi-thread monitoring)
 - Add the possibility to move a job from one machine to another
 - Complete this readme

License
----
MIT

[//]: # (These are reference links used in the body of this note and get stripped out when the markdown processor does its job. There is no need to format nicely because it shouldn't be seen.)

   [C++]: <http://www.cplusplus.com/>
   [Boost]: <http://www.boost.org/>
   [OpenMP]: <http://openmp.org/wp/>
   [MPI]: <https://www.mpich.org/>

