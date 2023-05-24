from UARTcomms import *
from GUI import GUI
from gui_state_machine import *

if __name__ == "__main__":
    # Initialise the GUI State Machine and update it until the window is closed
    g = GUIStateMachine(GUI(), UARTcomms(debug=True), UARTcomms(debug=True), UARTcomms(debug=True), UARTcomms(debug=True))
    while not g.do_state():
        pass
        