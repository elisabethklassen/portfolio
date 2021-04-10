import datetime

class Event(object):
    def __init__(self, st, et, n, d):
        self.start_time = st
        self.end_time = et
        self.name = n
        self.description = d

    def __str__(self):
        representation = self.name + ': ' + self.description + '\n' + str(self.start_time) + '-' + str(self.end_time)
        return representation