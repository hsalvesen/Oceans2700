import serial

class UARTcomms:
    def __init__(
            self, 
            port="COM16", 
            baudrate=115200, 
            start_sentinel=[0xAA, 0xBB],
            end_sentinel=[0xBB, 0xAA],
            debug=False
        ):
        self.debug = debug
        if self.debug:
            print("Opening dummy serial connection")
        else:
            self.serial_port = serial.Serial(
                port=port, 
                baudrate=baudrate, 
                bytesize=8, 
                timeout=2,
                stopbits=serial.STOPBITS_ONE
            )
        self.start_sentinel = start_sentinel
        self.end_sentinel = end_sentinel
        self.codes = {
        }
        self.result = b""
    
    def send_msg(self, payload: list):
        """ 
        Sends a payload over the serial port, bookended by the sentinel bytes
        Arguments: 
            payload: a list of bytes to be sent
        """
        if self.debug:
            print(self.start_sentinel + payload + self.end_sentinel)
        else:
            self.serial_port.write(bytes(self.start_sentinel + payload + self.end_sentinel))

    def read_line(self) -> str:
        if self.debug:
            result = bytearray()
            result.extend(map(ord, input()))

        else:
            while self.serial_port.in_waiting:
                self.result += self.serial_port.read(1)
            result = self.result
            if self.result:
                # print(type(self.result[-1]))
                if self.result[-1] == ord('['):
                    self.result = b""
        return result

