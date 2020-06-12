#include <iostream>
#include <string>
#include <map>
#include <set>
#include <iomanip>
#include <exception>

using namespace std;

class Date {
public:
    Date(const string& str)
    {
        stringstream ss(str);
        char c;
        ss >> year >> c;
        if (c != '-')
            throw runtime_error("Wrong date format: " + str);
        ss >> month;
        ss >> c;
        if (c != '-')
            throw runtime_error("Wrong date format: " + str);
        ss >> day;
        if (!ss || !ss.eof())
            throw runtime_error("Wrong date format: " + str);
        if (!(GetMonth() > 0 && GetMonth() <= 12))
            throw runtime_error("Month value is invalid: " + to_string(GetMonth()));
        if (!(GetDay() > 0 && GetDay() <= 31))
            throw runtime_error("Day value is invalid: " + to_string(GetDay()));
    }

    int GetYear() const
    {
        return year;
    }

    int GetMonth() const
    {
        return month;
    }

    int GetDay() const
    {
        return day;
    }

private:
    int year = 0;
    int month = 0;
    int day = 0;
};

bool operator<(const Date& lhs, const Date& rhs)
{
    if (lhs.GetYear() < rhs.GetYear())
        return true;
    else if ((lhs.GetYear() == rhs.GetYear()) && lhs.GetMonth() < rhs.GetMonth())
        return true;
    else if (lhs.GetYear() == rhs.GetYear() && lhs.GetMonth() == rhs.GetMonth()
        && lhs.GetDay() < rhs.GetDay())
        return true;
    return false;
}

class Database {
public:
    void    AddEvent(const Date& date, const string& event)
    {
        events[date].insert(event);
    }

    bool    DeleteEvent(const Date& date, const string& event)
    {
        if (!events[date].count(event)) // &&&&&&&??????
            return false;
        else
        {
            events[date].erase(event);
            return true;
        }
    }

    int     DeleteDate(const Date& date) // прочитать еще раз и проверить
    {
        if (events.count(date) != 0){
            int n = events[date].size(); // считаем количество событий в дате
            events.erase(date);
            return n;
        }

        return 0;
    }

    void    Find(const Date& date)
    {
        for (const auto& s : events[date])
            cout << s << endl;
    }

    void    Print() const
    {
        for (const auto& s : events) // DB
        {
            for(const auto& n : s.second) // set<string<
            {
                cout << setw(4) << setfill('0');
                cout << s.first.GetYear() << '-';
                cout << setw(2) << setfill('0');
                cout << s.first.GetMonth() << '-';
                cout << setw(2) << setfill('0');
                cout << s.first.GetDay() << ' ';
                cout << n << endl;
            }
        }
    }

private:
    map<Date, set<string>> events;
};

int main()
{
    Database db;
    string command;
    try
    {
        while (getline(cin, command))
        {
            stringstream ss(command);
            string com; //считаная команда

            ss >> com;
            if (com == "Add") {
                string tmp_date; //преобразовать в данные типа Date
                string event; // Событие прикрепленное к датеж

                ss >> tmp_date;
                Date date(tmp_date);
                ss >> event;
                db.AddEvent(date, event); //добавил event в базу данных (сохранил)
            }
            else if (com == "Del")
            {
                string tmp_date;

                ss >> tmp_date;
                Date date(tmp_date);

                if (!ss.eof()) // если еще что то осталось, тогда это команда "DeleteEvent"
                {
                    string event;
                    ss >> event;
                    if (db.DeleteEvent(date, event))
                        cout << "Deleted successfully" << endl;
                    else
                        cout << "Event not found" << endl;
                }
                else
                {
                    int tmp;

                    tmp = db.DeleteDate(date);
                    cout << "Deleted " + to_string(tmp) + " events" << endl;
                }
            }
            else if (com == "Find")
            {
                string tmp_date;

                ss >> tmp_date;
                Date date(tmp_date);
                db.Find(date);
            }
            else if (com == "Print")
            {
                db.Print();
            }
            else if (!com.empty())
            {
                throw runtime_error("Unknown command: " + com);
            }

        }
    }
    catch (exception& ex)
    {
        cout << ex.what() << endl;
        return 0;
    }
    return 0;
}
