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

    def delete_event_by_name(self, name):
        for day in self.days:
            day.delete_event_by_name_if_exists(name)

    def __str__(self):
        representation = ''
        for day in self.days:
            representation += str(day)
            representation += '\n'
        return representation