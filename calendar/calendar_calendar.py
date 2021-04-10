import datetime
from calendar_day import Day

class Calendar(object):
    def __init__(self):
        self.days = []

    def add_day(self, date):
        new_day = Day(date)
        self.days.append(new_day)
        return new_day

    def add_event(self, date, st, et, name, description):
        added = False
        for day in self.days:
            if date == day.date:
                day.add_event(st, et, name, description)
                added = True
        if added == False:
            new_day = self.add_day(date)
            new_day.add_event(st, et, name, description)

    def modify_event_by_name(self, name, attribute, new_value):
        if attribute == 'day':
            event = None
            for day in self.days:
                event = day.find_event_by_name(name)
                if event:
                    day.delete_event_by_name_if_exists(event.name)
            if event:
                self.add_event(new_value, event.start_time, event.end_time, event.name, event.description)
        for day in self.days:
            day.modify_event_by_name_if_exists(name, attribute, new_value)

    def delete_event_by_name(self, name):
        for day in self.days:
            day.delete_event_by_name_if_exists(name)

    def delete_day(self, day):
        self.days.remove(day)

    def __str__(self):
        representation = ''
        for day in self.days:
            representation += str(day)
            representation += '\n'
        return representation