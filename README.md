# Closh.c COSC 315 - Mini Project 1

The C program ‘closh’ works by taking the inputs program, count, run type (parallel or sequential), and timeout. For the program input, we created a test program ‘HelloWorld’, which can be used as the argument with the syntax “./HelloWorld”. However, hostname, pwd, echo, etc are all options that could be used as the program name being inputted as well. The next input - count - decides how many of the named processes are going to be created, accepting an integer from 1 to 9. The following input asks the user for a character, ‘s’ or ‘p’, to choose if the created processes are to run in sequence or in parallel respectively. Finally, it asks if you would like to define a timeout value. The inputted integer 0-9 denotes the seconds after which the processes will time out and be terminated; an inputted value of 0 results in no timeout. The whole program is to take in a process and run it for a specific count either sequentially or concurrently in parallel and to do this for a specific time 1-9 seconds or until it is finished.


## Getting Started

1. Clone this repository to your local machine.
2. Run the program by using the command "./closh"
3. Input a program (in our example, we use the argument "./HelloWorld")
4. Input a count, specifying the number of times you want it to execute (1-9)
5. Input a character, s or p, denoting if you want to to run sequentially or in parallel respectively
6. Input a timeout value (0 if no timeout) to specify a time after which the process should be force closed (1-9)

## Built With

* [C](https://www.gnu.org/software/libc/manual/pdf/libc.pdf) - Programming Language
* [Linux - Debian](https://www.debian.org/doc/) - OS/Terminal 
* [GCC](https://gcc.gnu.org/onlinedocs/gcc-9.2.0/gcc/) - How we compiled our C programs
* [Vim](https://www.vim.org/docs.php) - IDE
* [Visual Studio Code](https://code.visualstudio.com/docs) - IDE used for .md files

## Contributers

* Benjamin Tisserand @UBCbent
* Courtney Gosselin @CourtneyGosselin
* Alex Qin @QinAlex
* Dr. Apurva Narayan provided base closh.c code seen in the closh-starter.tar.gz file
