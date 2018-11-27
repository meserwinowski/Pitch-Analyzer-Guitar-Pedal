'''
Pitch Analyzer Guitar Pedal GUI
Sends UART Commands to control LED fretboard

Built upon kivy framework
=========================
'''

import sys
import time as time_t
import serial
from time import time
from kivy.app import App
from os.path import dirname, join
from kivy.lang import Builder
from kivy.properties import NumericProperty, StringProperty, BooleanProperty,\
    ListProperty
from kivy.clock import Clock
from kivy.uix.screenmanager import Screen
from kivy.core.text import LabelBase

LabelBase.register(name="HeavyData", fn_regular="heavy_data.ttf")

# Configure the serial connections (the parameters differs on the device you
# are connecting to)
ser = serial.Serial(
    port='COM9',
    baudrate=9600,
    parity=serial.PARITY_NONE,
    stopbits=serial.STOPBITS_ONE,
    bytesize=serial.EIGHTBITS
)

ser.isOpen()


class ShowcaseScreen(Screen):
    fullscreen = BooleanProperty(False)

    def add_widget(self, *args):
        if 'content' in self.ids:
            return self.ids.content.add_widget(*args)
        return super(ShowcaseScreen, self).add_widget(*args)

    def btn_play(self):
        print("You clicked play on lessons")

    def write_bright_rgb(self, bright_val, r_val, g_val, b_val):
        ser.write(serial.to_bytes([int(bright_val),
                                   int(r_val),
                                   int(g_val),
                                   int(b_val)]))
        time_t.sleep(0.05)
        while ser.inWaiting() > 0:
            out = (ser.read(1))
            print(out)

    def write_speed(self, *args):
        ser.write(serial.to_bytes([int(args[1])]))
        time_t.sleep(0.1)
        while ser.inWaiting() > 0:
            out = (ser.read(1))
            print(out)

    def write_color_change(self):
        ser.write(serial.to_bytes([0x02]))
        time_t.sleep(0.1)
        while ser.inWaiting() > 0:
            out = (ser.read(1))
            print(out)

    def write_dummy(self):
        ser.write(serial.to_bytes([0x00]))
        time_t.sleep(0.1)
        while ser.inWaiting() > 0:
            out = (ser.read(1))
            print(out)

    def write_scale(self, text):
        scale = 0x00
        if (text == 'None'):
            scale = 0x00
        elif (text == 'Pentatonic- Ionian'):
            scale = 0x01
        elif (text == 'Pentatonic- Dorian'):
            scale = 0x02
        elif (text == 'Pentatonic- Phrygian'):
            scale = 0x03
        elif (text == 'Pentatonic- Mixolydian'):
            scale = 0x04
        elif (text == 'Pentatonic- Aeolian'):
            scale = 0x05
        elif (text == 'Diatonic- Ionian'):
            scale = 0x06
        elif (text == 'Diatonic- Dorian'):
            scale = 0x07
        elif (text == 'Diatonic- Phrygian'):
            scale = 0x08
        elif (text == 'Diatonic- Lydian'):
            scale = 0x09
        elif (text == 'Diatonic- Mixolydian'):
            scale = 0x0A
        elif (text == 'Diatonic- Aeolian'):
            scale = 0x0B
        elif (text == 'Diatonic- Locrian'):
            scale = 0x0C

        ser.write(serial.to_bytes([scale]))
        time_t.sleep(0.1)
        while ser.inWaiting() > 0:
            out = (ser.read(1))
            print(out)

    def write_root(self, text):
        root = 0x00
        if (text == 'None'):
            root = 0x00
        elif (text == 'F'):
            root = 0x01
        elif (text == 'F#/Gb'):
            root = 0x02
        elif (text == 'G'):
            root = 0x03
        elif (text == 'G#/Ab'):
            root = 0x04
        elif (text == 'A'):
            root = 0x05
        elif (text == 'A#/Bb'):
            root = 0x06
        elif (text == 'B'):
            root = 0x07
        elif (text == 'C'):
            root = 0x08
        elif (text == 'C#/Db'):
            root = 0x09
        elif (text == 'D'):
            root = 0x0A
        elif (text == 'D#/Eb'):
            root = 0x0B
        elif (text == 'E'):
            root = 0x0C

        ser.write(serial.to_bytes([root]))
        time_t.sleep(0.1)
        while ser.inWaiting() > 0:
            out = (ser.read(1))
            print(out)


class ShowcaseApp(App):

    index = NumericProperty(-1)
    current_title = StringProperty()
    time = NumericProperty(0)
    show_sourcecode = BooleanProperty(False)
    sourcecode = StringProperty()
    screen_names = ListProperty([])
    hierarchy = ListProperty([])
    icon = r"./data\guitar.png"

    def build(self):
        self.title = 'Pitch Analyzer Guitar Pedal'
        Clock.schedule_interval(self._update_clock, 1 / 60.)
        self.screens = {}
        self.available_screens = ['Main Menu', 'Mirror Mode', 'Lessons']
        self.screen_names = self.available_screens
        curdir = dirname(__file__)
        self.available_screens = [join(curdir, 'data', 'screens',
            '{}.kv'.format(fn).lower()) for fn in self.available_screens]
        self.go_next_screen()

    def on_pause(self):
        return True

    def on_resume(self):
        pass

    def on_current_title(self, instance, value):
        self.root.ids.spnr.text = value

    def go_previous_screen(self):
        self.index = (self.index - 1) % len(self.available_screens)
        screen = self.load_screen(self.index)
        sm = self.root.ids.sm
        sm.switch_to(screen, direction='right')
        self.current_title = screen.name
        self.update_sourcecode()
        self.mode_switch()

    def go_next_screen(self):
        self.index = (self.index + 1) % len(self.available_screens)
        screen = self.load_screen(self.index)
        sm = self.root.ids.sm
        sm.switch_to(screen, direction='left')
        self.current_title = screen.name
        self.update_sourcecode()
        self.mode_switch()

    def go_screen(self, idx):
        self.index = idx
        self.root.ids.sm.switch_to(self.load_screen(idx), direction='left')
        self.update_sourcecode()
        self.mode_switch()

    def go_hierarchy_previous(self):
        ahr = self.hierarchy
        if len(ahr) == 1:
            return
        if ahr:
            ahr.pop()
        if ahr:
            idx = ahr.pop()
            self.go_screen(idx)

    def load_screen(self, index):
        if index in self.screens:
            return self.screens[index]
        screen = Builder.load_file(self.available_screens[index])
        self.screens[index] = screen
        return screen

    def read_sourcecode(self):
        fn = self.available_screens[self.index]
        with open(fn) as fd:
            return fd.read()

    def update_sourcecode(self):
        if not self.show_sourcecode:
            self.root.ids.sourcecode.focus = False
            return
        self.root.ids.sourcecode.text = self.read_sourcecode()
        self.root.ids.sv.scroll_y = 1

    def mode_switch(self):
        # Write the change mode command
        if(self.index != 0):
            ser.write(serial.to_bytes([0x01, self.index, 0x00, 0x00, 0x00]))
            time_t.sleep(0.1)
            while ser.inWaiting() > 0:
                out = (ser.read(1))
                print(out)

    def mode_switch_w_scale_root(self):
        # Write the change mode command
        if(self.index != 0):
            ser.write(serial.to_bytes([0x01, self.index]))
            time_t.sleep(0.1)
            while ser.inWaiting() > 0:
                out = (ser.read(1))
                print(out)

    def _update_clock(self, dt):
        self.time = time()


if __name__ == '__main__':
    ports = ['COM%s' % (i + 1) for i in range(256)]
    result = []
    for port in ports:
        try:
            s = serial.Serial(port)
            s.close()
            result.append(port)
        except (OSError, serial.SerialException):
            pass
    ShowcaseApp().run()
