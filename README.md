SIMPLE SHELL PROJECT
DONE BY : 
Ayoub Farhi git : senpai1282
email : farhi.ayoub.hamza@gmail.com

description : 
this is a peer learning project for the famous Simple Shell.
task 1 : create a code tht passe the betty checks.
learning objectifs

- the PID AND PPID 
the pid is a number as an id assigned to a function or a system call to identifie each parent son relationship between functions and system call, the most common use of it is something like as we know when we shut dont a program we end up having it running on the backroud (zombie func) so in order to make sure to cmpletely shut down the pogram we need to locate the PID of the main func or system call and shut it downthis way we shut down all the functions and system calls under that particular function which mean shuting down a program. We can also use it to call a certain function back and here we also need the PPID .
- what is the relationship between a pid and PPID :
THE PID is always the parent id which is unique for each function and a system call and its the PPID of the system call or function parent and i goes down like that.
Lets take an exemple we have a system call with the pid=1 and ppid=12.
under this system call there exist 2 other functions with a pid and a ppid. For the 2 functions the pid would be the PPID parent which is ppid=12.
and if there is another functions under the 2 ones each func would take a PPID of the function parent before it and use it as aPID and not the pid of the first system call.
so lets say the we want to shut down all the functions at once we gonna just have to shut down the function with hthe pid=1.
but if we want to shut down a funtion under the system call but not the whole program we need to allocate the pid of that function and shut it down, this way that function and all the function  under it will automatically be shut down because the ppid of the function that we selected is endeed the pid of the functions under it and we go onward.
