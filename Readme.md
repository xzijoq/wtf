Contains Version Info Also
-------------------------

# Repo 
- !!! note HERE

        ## Objective
        - this repo deals with networking
        - this branch deals with working with asio
        - each commmit it a milestone towards learning the objective
        - to view various learning steps, follow each commit
        - some discription about commit may be found in this file



# This commit
- !!! note Features and purpose
        ## Async1 write , read, print close

        - !!! tip Fully functional chat room
              - both client and server works 
              - multiuser 
              - server works with telnet and other thinings
              - basic ssl support started 
 
- !!! Todo Limitations
  
        - can only work with console input on posix
          - 
        - no proper nick name or colors implemented
        - lacks any advanced features 
        - !!! warning lacks TLS
              - !!! tip has basic version of SSl With certificate verification 
                    - just started out on implementation
              - or any other encryption
              - some m inor problem with client winding up after server closes
# What
- !!! help overload of async_read_until from the DOCS is not working
- !!! danger bug : WILL CRASH SERVER
      - !!! tip Partially resolved WILL NOT CRASH ANYMORE
            - via:the Objects send a shared pointer to handler
            - still need to take care of mannullay updating the data structure (if any) which holds the shared pointers 
            - !!! tip need better way to cancel, stickey cancel
      - !!! help THe Problem
            -  what if a call-back is qued up before we wrap up and destroy the object with buffers and socket
            - not only is it undefined behavoiur to reference destroyed object
            - it will call close and delte twice which will crash the server

# Todo
- !!! todo how?
        - how to bind client port to a scoket without specifying the protocol, which can be determined by dns resolution which ever matches
        - handlerviz.pl tool icluded to visualize post process handler tracking
          - customize it
        - 