#include <iostream>
#include <chrono>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <algorithm>

// START - Utils

std::vector<std::string> split(std::string str, char delim)
{
	std::vector<std::string> splitted;

	for (int i = 0, start_index = 0, end_index = 0; i <= str.size(); i++)
	{
		if (str[i] == delim || i == str.size())
		{
			std::string sub_str = "";
			end_index = i;

			sub_str.append(str, start_index, end_index - start_index); //D000141|Janny|Doe|80.38|fmarkt.de|25.12.17|23:17:17
			start_index = end_index + 1;

			splitted.push_back(sub_str);
		}
	}

	return splitted;
}

// END - Utils

class Transaction
{
public:
	std::string acc_nb;
	std::string fname;
	std::string lname;
	double amt;
	std::string merchant;
	std::string timestamp;

	Transaction(
		std::string acc_nb,
		std::string fname,
		std::string lname,
		double amt,
		std::string merchant,
		std::string timestamp)
		: acc_nb(acc_nb),
		  fname(fname),
		  lname(lname),
		  amt(amt),
		  merchant(merchant),
		  timestamp(timestamp){};

	void print()
	{	//showpoint -> shows the point, fixed->Sets the floatfield format flag for the str stream to fixed (float same lenghth as precision says)
		//setprecision -> Sets the decimal precision
		std::cout << std::setw(15) << std::right << "Account Nb:";
		std::cout << std::setw(50) << std::right << acc_nb << std::endl;

		std::cout << std::setw(15) << std::right << "First Name:";
		std::cout << std::setw(50) << std::right << fname << std::endl;

		std::cout << std::setw(15) << std::right << "Last Name:";
		std::cout << std::setw(50) << std::right << lname << std::endl;

		std::cout << std::setw(15) << std::right << "Amount:";
		std::cout << std::fixed << std::showpoint;
		std::cout << std::setw(44) << std::right << std::setprecision(2) << "EUR " << amt << std::endl;  //leh 46 m4 44?

		std::cout << std::setw(15) << std::right << "Merchant:";
		std::cout << std::setw(50) << std::right << merchant << std::endl;

		std::cout << std::setw(15) << std::right << "Date Time:";
		std::cout << std::setw(50) << std::right << timestamp << std::endl;
	};
};

class TransactionList
{
private:
	std::vector<Transaction> transactions;

public:
	TransactionList()
	{
		transactions = {};   //da 34an lw 3mlt intialization w m7tt4 file?  (by5le el vector transactions el howa asln m3mol yb2a fade?)
	};

	TransactionList(std::string filename)
	{
		parseFile(filename); //da copy constructor 34an a2ra el file?
	};							//emta yb2a fe ; w emta la?

	std::vector<Transaction>::iterator begin()
	{
		return transactions.begin();
	};

	std::vector<Transaction>::iterator end()
	{
		return transactions.end();
	};

	TransactionList sort()
	{
		std::sort(transactions.begin(), transactions.end(), [&, this](const Transaction &t1, const Transaction &t2) -> bool	
				  { return TransactionComp(t1, t2); });					 
																		//wa5d el parameters mnen?
		return *this;
	};   //leh fe ; hna w mfe4 fel functions el t7t?
	//const (promising not to modify the string) and by reference (the actual string not a copy)
	bool TransactionComp(Transaction t1, Transaction t2)
	{
		std::string idntifier[] = {t1.acc_nb.substr(0, 1), t2.acc_nb.substr(0, 1)};    //eh [] dol? array, da awl rkm?

		int acc_no[] = {std::stoi(t1.acc_nb.substr(1)), std::stoi(t2.acc_nb.substr(1))}; // da keda tane rkm?

		if(idntifier[0] > idntifier[1])
			return true;
		else if (idntifier[0] == idntifier[1] && acc_no[0] > acc_no[1])
			return true;
		else 
			return false;
	}

	void parseRecord(std::string record)
	{
		if (this == nullptr)
			*this = TransactionList();  // eh lzmtha? maho lw mfe4 line m4 hyge hna asln

		std::vector<std::string> record_items = split(record, '|');

		transactions.push_back(
			Transaction(
				record_items[0],
				record_items[1],
				record_items[2],
				std::stod(record_items[3]),
				record_items[4],
				(record_items[5] + ";" + record_items[6])));   // mynf34 + el mfrod
	}

	void parseFile(std::string filename)
	{
		if (this == nullptr)
			*this = TransactionList();    //m3mol fel constructor asln leh a3ml kda?. leh m4 hy5o4 3l try b3dha 3ade?

		try
		{
			std::ifstream trans(filename);   // m4 hya5od location eh file?
			trans.is_open();
			std::string line;
			while (std::getline(trans, line))
			{
				parseRecord(std::string(line.c_str()));				// 7wlnah leh l cstr?
			}
			trans.close();
		}
		catch (const std::exception &e)	//fen el throw? leh const?
		{
			std::cout << "Some error occured!" << std::endl;
		}
	}
};
