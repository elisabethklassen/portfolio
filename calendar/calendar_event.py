import datetime

class Event(object):
    def __init__(self, st, et, n, d):
        self.start_time = st
        self.end_time = et
        self.name = n
        self.description = d

    def modify_attribute(self, attribute, new_value):
        if attribute == 'start_time':
            self.start_time = new_value
        elif attribute == 'end_time':
            self.end_time = new_value
        elif attribute == 'name':
            self.name = new_value
        elif attribute == 'description':
            self.description = new_value

    def __str__(self):
        representation = self.name + ': ' + self.description + '\n' + str(self.start_time) + '-' + str(self.end_time)
        return representation