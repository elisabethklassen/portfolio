import datetime
from calendar_calendar import Calendar

def main():
    calendar = Calendar()
    command = ''
    while command != 'quit':
        command = input("Please enter a command: ")
    
        if command == 'add':
            name = input("Event name: ")
            description = input("Event description: ")
            date_string = input("Event date (yyyy/mm/dd): ")
            start_time_string = input("Event start time (hh:mm): ")
            end_time_string = input("Event end time (hh:mm): ")
            date = datetime.datetime.strptime(date_string, '%Y/%m/%d')
            date = date.date()
            start_time = datetime.datetime.strptime(start_time_string, '%H:%M')
            start_time = start_time.time()
            end_time = datetime.datetime.strptime(end_time_string, '%H:%M')
            end_time = end_time.time()
            calendar.add_event(date, start_time, end_time, name, description)
            print(calendar)

        if command == 'delete':
            name = input("Name of event to delete: ")
            calendar.delete_event_by_name(name)
            print(calendar)

if __name__ == "__main__":
    main()