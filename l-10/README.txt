To compile:
$ make

-------------------------------------------------------------------

To clean:
$ make clean

-------------------------------------------------------------------

To run:
- COMMAND = any unix command
- arg = args that go with the following command or just args

$ cd
$ cd ~
$ cd mydir
$ cd ..
$ cd /usr/bin
$ cd ~/mydir

$ cat file1.txt file2.txt

$ COMMAND < input.txt
$ COMMAND > output.txt
$ COMMAND >> output.txt
$ COMMAND < input.txt > output.txt
$ COMMAND >> output.txt < input.txt

$ cd mydir
$ COMMAND1
$ COMMAND2 >> output.txt
$ COMMAND3 arg1 arg2 > output.txt
$ COMMAND4 arg1 arg2 < input.txt
$ COMMAND5 arg1 > output.txt < input.txt
$ COMMAND6 arg1 arg2 < input.txt >> output.txt

$ exit

referenced project3 pdf for list of commands 
