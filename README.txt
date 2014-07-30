game in progress:

Sprite system under development to allow for easy creation and management of objects in game.

Features so far:

creation
cloning
movement
deletion
priorities
collisions
automatic Collision compensation
flipping
color keys

TODO:
add rotation point manipulation //done!
add srcrect manipulation//delayed because who the fuck uses it?
add animation support //done ish
add relative movement //kinda done

Alpha now done, but it's terrible. 

TODO FIRST: fix the alpha so that it is easy to clean up memory. 
Use share counts for both surface and texture to determine when to free them and the sprite. 
Have extra user flag to say if it's a user made image.  Remove getImage.

Ensure that deletions happen correctly.
Ensure that count is updated correctly.
Ensure that all sprites keep their own images!