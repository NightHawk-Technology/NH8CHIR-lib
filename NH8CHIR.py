import time

channels = [0x00, 0x40, 0x10, 0x50, 0x20, 0x60, 0x30, 0x70]

class NH8CHIR:
    def __init__(self, i2c, address):
        self.i2c = i2c
        self.address = address
        
    def read(self, channel):
        command_byte = channels[channel]
        
        self.i2c.writeto(self.address, bytes([command_byte^ 0x80]))
        time.sleep_ms(5) # default is 5ms
        
        data = self.i2c.readfrom(self.address, 2)
        
        result = (data[0] << 8) | data[1]
        return result