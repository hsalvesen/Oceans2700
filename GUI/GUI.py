import PySimpleGUI as sg
from UARTcomms import UARTcomms
import time

class GUI:
    def __init__(self):
        
        self.big_font = ("Trebuchet MS", 30)
        self.small_font = ("Trebuchet MS", 15)
        
        self.description_string = ""
        self.description_display_string = ""
        self.description_begin_time = time.time_ns()
        self.description_delay_ns = 50000000

        self.feedback_string = "Hello, World!"

        self.button_colours = [False, False, False, False]

        self.layout = [
            [sg.T("Ocean's 2700", key="Title", text_color="#eeeeee", font=("consolas", 40), background_color="#1e1e1e", grab=True)],
            [sg.Multiline(size=(30, 5), key='DescriptionBox', default_text=self.description_display_string,
                          font=("consolas", 20), text_color="#11ff11", background_color="#111111", no_scrollbar=True)],
            [sg.Text("", size=(20, 1), font=("consolas", 35), justification='c', key="FeedbackBox")],
            [[sg.Button(str(i), size=(3, 2), button_color=("red", "red"), font=self.big_font, key="Button"+str(i)) for i in range(4)]]
        ]
        
        
        self.window = sg.Window("Ocean's 2700", self.layout, size=(800,500), element_justification='c', margins=(30,10), background_color="#1e1e1e", element_padding=5)
        
    def set_description_box(self, text: str, delay_ns: int=50000000):
        self.description_string = text
        self.description_display_string = ""
        self.description_begin_time = time.time_ns()
        self.description_delay_ns = delay_ns

    def update_description(self):
        if self.description_delay_ns:
            self.description_display_string = self.description_string[
                0:min(
                    len(self.description_string), 
                    int((time.time_ns()-self.description_begin_time)/self.description_delay_ns)
                )
            ]
        else:
            self.description_display_string = self.description_string

        self.window['DescriptionBox'].update(self.description_display_string)

    def set_feedback_box(self, text: str):
        self.feedback_string = text
        self.window['FeedbackBox'].update(self.feedback_string)

    def initial_refresh(self):
        event, values = self.window.read(timeout=10)

    def enable_button(self, button_n: int):
        self.button_colours[button_n] = True
        self.window["Button" + str(button_n)].update(button_color=("green", "green"))

    def main_update_loop(self) -> int:
        event, _ = self.window.read(timeout=10)
        if event == sg.WIN_CLOSED:
            print("Closing")
            return 1
        self.update_description()
        return 0
    
if __name__ == "__main__":
    gui = GUI()
    gui.initial_refresh()
    gui.set_description_box("The money is held inside of this safe. Use the robot to help crack it open and steal the money within.")
    gui.set_feedback_box("Hi")
    gui.enable_button(2)
    while (True):
        if gui.main_update_loop():
            break

