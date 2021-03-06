/**
 * @file Agenda.cpp
 * @brief Agenda implementacion
 */

#include "Agenda.hpp"

Agenda::Agenda(int H, int N, int D)
{
    notebook = vector<Offis>(D+1, Offis(N, hours(H, pair<int, int>(0, 0))));
}

Agenda::~Agenda()
{}

int Agenda::consult_model(int app_day, int id_offi, int app_hour) const
{
    int size = notebook.size();
    if ((notebook[app_day%(size)][id_offi-1][app_hour-1]).second == -1) return 1;
    return 2;
}

int Agenda::consult_first_value(int app_day, int id_offi, int app_hour) const
{
    int size = notebook.size();  // D+1
    return (notebook[app_day%size][id_offi-1][app_hour-1]).first;
}

int Agenda::consult_second_value(int app_day, int id_offi, int app_hour) const
{
    int size = notebook.size();  // D+1
    return (notebook[app_day%(size)][id_offi-1][app_hour-1]).second;
}

void Agenda::modify_first_value(int first_value, int can_day, int id_offi, int can_hour)
{
    int size = notebook.size();
    (notebook[can_day%(size)][id_offi-1][can_hour-1]).first = first_value;
}

void Agenda::modify_second_value(int second_value, int can_day, int id_offi, int can_hour)
{
    int size = notebook.size();
    (notebook[can_day%size][id_offi-1][can_hour-1]).second = second_value;
}

void Agenda::advance_days(int limit_day, int pre_reg_day, int reg_day, int K)
{
    Iterator it = reqs_done.end();
    int size_1 = notebook.size();  // D+1
    int size_2 = notebook[0].size(); // N
    int size_3 = notebook[0][0].size(); // H
    for (int i = pre_reg_day; i < reg_day; ++i) 
    {
	for (int j = 1; j <= size_2; ++j) 
        {
	    for (int k = 1; k <= size_3; ++k) 
            {
                int id_app = (notebook[i%(size_1)][j-1][k-1]).first;
                int copy = id_app;
                (notebook[i%(size_1)][j-1][k-1]).first = 0;
		if (copy > 0) 
                {
                    Appointment app(i, j, k, copy);
		    reqs_done.insert(it, app);
		}
	    }
	 }
    }
    while (not reqs_done.empty() and reqs_done.front().consult_app_day() < limit_day) 
        reqs_done.pop_front();
}

void Agenda::set_non_working(int app_day, int id_offi, int app_hour)
{
    int size = notebook.size();  // D+1
    int i = app_day%(size);
    int j = id_offi;
    int k = app_hour;
    (notebook[i][j-1][k-1]).first = -1;
}

void Agenda::add_apps_alive(int app_day, int id_offi, int app_hour, int& app_id, int second_value) 
{
    int size = notebook.size();
    int i = app_day%(size);
    int j = id_offi;
    int k = app_hour;
    (notebook[i][j-1][k-1]).first = app_id; 
    (notebook[i][j-1][k-1]).second = second_value;
// 	cout << "he añadido la cita " << app_id << " en el día " << app_day << " hora " << k << " con el funcionario " << j << endl;
	
}

void Agenda::consult_app_done(int d1, int d2)
{
    Iterator it = reqs_done.begin();
    int size = notebook.size();  // D+1
    while (it != reqs_done.end())
    {
        int day = it->consult_app_day();
        if (day >= d1 and day <= d2) it->write_app();
	++it;
    }
}

void Agenda::consult_app_alive(int d1, int d2)
{
    int size_1 = notebook.size();  // D+1
    int size_2 = notebook[0].size(); // N
    int size_3 = notebook[0][0].size(); // H
    for (int i = d1; i <= d2; ++i) 
    {
	for (int j = 1; j <= size_2; ++j)
        {
            for (int k = 1; k <= size_3; ++k) 
            {
                int id;
                id = (notebook[i%size_1][j-1][k-1]).first;
                if (id > 0) 
                {
                    cout << i << " " << j << " " << k << " " << id << endl;
                }
	    }
	}
    }
    cout << endl;
}

