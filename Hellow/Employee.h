
#include "stdafx.h"
#include "VirtualModel.h"
class 	Employee : public VirtualModel {
public:
	std::string firstName;
	std::string lastName;
	double pay;
	
public:
	Employee():VirtualModel(0,0) {}
	Employee(const std::string& aFirstName,
		const std::string& aLastName,
		double aPay) : VirtualModel(3, 3)
	{
		this->firstName = aFirstName;
		this->lastName = aLastName;
		this->pay = aPay;
	}
};
