Contains Version Info Also
-------------------------

# Repo 
- !!! note 

        ## Objective
        - this repo deals with networking
        - this branch deals with working with asio
        - each commmit it a milestone towards learning the objective
        - to view various learning steps, follow each commit
        - some discription about commit may be found in this file



# This commit
- !!! note Can do
        ## working partially async version 

        - !!! tip can handel string messages of any size
              - works by appending size header to string
        - ==CHANGE:== uses aync_read and aync_write
- !!! note limitation
        ## Here Fluffy Fluffy

        - can only work with strings
        - ==DONE:== session struct should be split into 2: read and write
        - !!! error aync?
              - the server run ios.run() and reset()
        - !!! error give error
       
              - terminate called after throwing an instance of 'std::system_error'
                what():  remote_endpoint: Transport endpoint is not connected
                Aborted (core dumped)
              - Most likely as server cant accept connections fast enough as it run ioc.run and reset in the same loop as it accpets
                  - If connetions are made with some time delay it always succeds
              - !!! tip error seeems to have gone away after a full split of struct: Even after ran in loop

# Todo
- !!! todo how?
        - how to bind client to a scoket without specifying the protocol, which can be determined by dns resolution which ever matches