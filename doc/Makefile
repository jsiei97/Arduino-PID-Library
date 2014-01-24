
#http://martin-thoma.com/how-to-draw-a-finite-state-machine/

STATE=state_BigPWM

$(STATE).png: $(STATE).gv
	dot -Tpng $(STATE).gv -o $(STATE).png

clean:
	rm $(STATE).png

