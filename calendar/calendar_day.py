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

    def find_event_by_name(self, name):
        for event in self.events:
            if event.name == name:
                return event
        return None

    def modify_event_by_name_if_exists(self, name, attribute, new_value):
        for event in self.events:
            if event.name == name:
                event.modify_attribute(attribute, new_value)

    def delete_event_by_name_if_exists(self, name):
        event = self.find_event_by_name(name)
        if event:
            self.events.remove(event)

    def __str__(self):
        representation = ''
        for event in self.events:
            representation += str(self.date) + '\n'
            representation += str(event)
            representation += '\n'
        return representation