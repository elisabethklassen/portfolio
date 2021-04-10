import datetime
from calendar_event import Event

class Day(object):
    def __init__(self, d):
        self.events = []
        self.date = d

    def add_event(self, start_time, end_time, name, description):
        new_event = Event(start_time, end_time, name, description)
        self.events.append(new_event)
        return new_event

    def __str__(self):
        representation = ''
        for event in self.events:
            representation += str(event)
            representation += '\n'
        return representation