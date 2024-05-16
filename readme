

Steps to make divert-loop working
=

1. Sudo ipfw add 65000 allow ip from any to any

2. Sudo ipfw add 300 divert 5000 all from any to [my IP:192.168.159.130] 2000

3. Sudo ipfw add 400 divert 5000 tcp from [my IP] to any

4. sudo	ipfw add 30 divert 5000 ip from any to 192.168.159.130

5. Sudo ipfw add 40 divert 5000 ip from 192.168.159.130 to any

6. Sudo ipfw add 65000 allow ip from any to any

7. Then run sudo ./divert-loop 5000 and enter the password.

Steps to make block_allICMP running

1. Replace file block_allICMP.c with the file shared for block all incoming ICMP packets.

2. set ipfw rules for forwarding packets on specific port number on my ip address as shown above. Once the rules are set, you don't need to reset it.

3. Replace the makefile and run command "make all" to execute the changes done to block_allICMP to reflect it and generate .o executable files

5. run executable file with "./block_allICMP 5000" command. here 5000 is selected port number.

6. start another terminal or a new terminal on host and ping you Freebsd VM IP. It should not print anything.
To test it you can remove the condition if (iph->ip_p !=1) which is that if the protocol os anything other than ICMP, it is going to send it to the socket. Else it will block it.

Note: In the code, if you remove the print statement and just execute the if condition with I protocol != 1, you will see that there is no output on pinging after executing ./block_allICMP 50
Steps to make block_inICMP running

1. Replace file block_inICMP.c with the file shared for block all incoming ICMP packets.

2. set ipfw rules for forwarding packets on specific port number on my ip address as shown above. Once the rules are set, you don't need to reset it.

3. No need to Replace the makefile again as the one contains commands for both the files. You just need to run command "make all" to execute the changes done to block_inICMP to reflect it and generate .o executable files

5. run executable file with "./block_inICMP 5000" command. here 5000 is selected port number.

6. start another terminal and ping your Freebsd VM IP. It should print only the icmp reply packets. For the result, I have printed the protocol which is 1. 
