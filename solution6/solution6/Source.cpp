#include <iostream>
#include "IntervalTree.hpp"

void PrintHelp()
{
	std::cout << "1. Add doctor(ID)." << std::endl;
	std::cout << "2. Add appointment." << std::endl;
	std::cout << "3. Check for free." << std::endl;
	std::cout << "4. Exit." << std::endl;
}

void AddDoctor(std::vector<unsigned>& doctors)
{
	unsigned docID;
	std::cin >> docID;
	doctors.push_back(docID);
	std::cout << "Doc added." << std::endl;
}

void AddAppoitment(ITree<float, unsigned>& schedule)
{
	unsigned docID;
	float st, end;
	std::cout << "ID/start/end." << std::endl;
	std::cin >> docID >> st >> end;
	schedule.Insert(st, end, docID);
	std::cout << "Appointment rdy." << std::endl;
}

void CheckForFree(ITree<float, unsigned>& schedule, std::vector<unsigned>& doctors)
{
	std::vector<Interval<float, unsigned>> appointments;
	float st;
	std::cin >> st;
	schedule.SearchDot(st, appointments);

	std::cout << "Busy docs:" << std::endl;
	size_t size = appointments.size();
	for (size_t i = 0; i < size; ++i)
	{
		std::cout << appointments[i].val << std::endl;
	}
	std::cout << "Endof 'Busy docs':" << std::endl;
	std::cout << "All docs:" << std::endl;
	size = doctors.size();
	for (size_t i = 0; i < size; ++i)
	{
		std::cout << doctors[i] << std::endl;
	}
	std::cout << "Endof 'All docs':" << std::endl;
}

int main()
{
	std::vector<unsigned> doctors;
	ITree<float, unsigned> schedule(0, 24);
	bool exit = false;
	unsigned choice, tmpDoc;
	while (!exit)
	{
		PrintHelp();
		std::cin >> choice;
		if (!std::cin)
			return 0;

		switch (choice)
		{
		case 1:
			AddDoctor(doctors);
			break;
		case 2:
			AddAppoitment(schedule);
			break;
		case 3:
			CheckForFree(schedule, doctors);
			break;
		case 4: exit = true;
			break;
		default: std::cout << "Again! :)" << std::endl;
			break;
		}
	}

	return 0;
}