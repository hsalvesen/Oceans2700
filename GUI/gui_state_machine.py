from UARTcomms import *
from GUI import GUI

class GUIStateMachine:
    def __init__(self, 
        gui: GUI, 
        module0: UARTcomms, 
        module1: UARTcomms,
        module2: UARTcomms,
        module3: UARTcomms
    ):
        self.gui = gui
        self.uart_comms = [module0, module1, module2, module3]

        self.state = "Init"

    def next_state(self, state: str):
        self.state = state
        self.init_state()

    def init_state(self):
        if self.state == "Module0":
            self.gui.set_description_box("The money is held inside of this safe. Use the robot to help crack it open and steal the money within.")
            self.gui.set_feedback_box("")
        elif self.state == "Module1":
            self.gui.enable_button(0)
            self.gui.set_description_box("It seems someone is jamming our communications. Luckily our robot has a morse code transmitter. Tap the robot's IMU to send the message")
            self.gui.set_feedback_box("Safe Opened")
        elif self.state == "Module2":
            self.gui.enable_button(1)
            self.gui.set_description_box("The police have started to mobilise. Lets try to jam their communications. Adjust the magnetic field until the board's lights tell you where to shine your torch")
        elif self.state == "Module3":
            self.gui.enable_button(2)
            self.gui.set_description_box("Quick - disable the alarm system before the guards get notified - Look at the STM to see which wires need to be pressed.")
        elif self.state == "Done":
            self.gui.enable_button(3)
            self.gui.set_description_box("Congratulations. You're out")
            self.gui.set_feedback_box("RUN!")
    
    def do_state(self) -> int:
        if self.state == "Init":
            self.gui.initial_refresh()
            self.next_state("Module0")
            return 0
        
        elif self.state == "Module0":
            line = self.uart_comms[0].read_line()
            if len(line):
                if line[-1] == 93:
                    self.next_state("Module1")

        elif self.state == "Module1":
            line = self.uart_comms[1].read_line()
            if len(line):
                if line[-1] == 91:
                    self.gui.set_feedback_box("Wrong")
                elif line[-1] == 93:
                    self.gui.set_feedback_box("Success")
                    self.next_state("Module2")
                else:
                    self.gui.set_feedback_box(''.join([chr(c) for c in line]))
        
        elif self.state == "Module2":
            line = self.uart_comms[2].read_line()
            if len(line):
                if line[-1] == 91:
                    self.gui.set_feedback_box("Wrong")
                elif line[-1] == 93:
                    self.gui.set_feedback_box("Success")
                    self.next_state("Module3")
        
        elif self.state == "Module3":
            line = self.uart_comms[3].read_line()
            if len(line):
                if line[-1] == 91:
                    self.gui.set_feedback_box("Wrong")
                elif line[-1] == 93:
                    self.gui.set_feedback_box("Success")
                    self.next_state("Done")
                elif line[-1] == 94:
                    self.gui.set_feedback_box("")

        return self.gui.main_update_loop()