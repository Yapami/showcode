#include <iostream>
#include <vector>
#include <algorithm>
#include <random>

const uint8_t NUMBER_OF_DIGITS = 4;

void create_number(std::vector<uint8_t>&);
void string_to_int(const std::string&, std::vector<uint8_t>& arr);
bool verify_is_number(const std::string&);
std::string user_input_number();
bool verify_user_number(const std::string&);
void compare_numbers(const std::vector<uint8_t>&, const std::vector<uint8_t>&,
	unsigned short&, unsigned short&);

int main()
{
	std::vector<uint8_t> arr_generate_number(NUMBER_OF_DIGITS),
		arr_input_number(NUMBER_OF_DIGITS);
	std::string input;
	unsigned short iter{};

	create_number(arr_generate_number);

	std::cout << iter + 1 << ") ";
	++iter;

	for (;;) {
		unsigned short bulls{}, cows{};
		std::string input = user_input_number();
		string_to_int(input, arr_input_number);
		compare_numbers(arr_generate_number, arr_input_number, bulls,
			cows);
		std::cout << "Bulls: " << bulls << "\t"
			<< "Cows: " << cows << std::endl
			<< std::endl;
		if (bulls == NUMBER_OF_DIGITS) {
			std::cout << "Game over. You are winner!" << std::endl;
			break;
		}
		std::cout << iter + 1 << ") ";
		++iter;
	}
	std::cout << std::endl;

	system("pause");
	return 0;
}

bool verify_user_number(const std::string& Number)
{
	for (uint8_t i = 0; i < NUMBER_OF_DIGITS; ++i) {
		int temp = Number[i];
		for (uint8_t j = i + 1; j < NUMBER_OF_DIGITS; ++j) {
			if (temp == Number[j]) {
				return true;
			}
		}
	}
	return false;
}

void create_number(std::vector<uint8_t>& arr)
{
	std::vector<uint8_t> temp(9);
	for (uint8_t i = 1; i <= 9; ++i) {
		temp[i - 1] = i;
	}
	std::random_device rd;
	std::mt19937 g(rd());
	std::shuffle(begin(temp), end(temp), g);
	for (uint8_t i = 0; i < NUMBER_OF_DIGITS; ++i) {
		arr[i] = temp[i];
	}
}

bool verify_is_number(const std::string& Number)
{
	for (uint8_t i = 0; i < NUMBER_OF_DIGITS; ++i) {
		if (std::isdigit(Number[i])) {
			if (Number[i] == '0') {
				return true;
			}
			continue;
		}
		return true;
	}
	return false;
}

std::string user_input_number()
{
	std::string Get_Value;

	for (;;) {
		std::cin >> Get_Value;
		if (verify_is_number(Get_Value)) {
			std::cout
				<< "String has to have digits only from 1 to 9!"
				<< std::endl;
			continue;
		}
		if (Get_Value.size() != 4) {
			std::cout
				<< "Number has to have four digits from 1 to 9!"
				<< std::endl;
			continue;
		}
		if (verify_user_number(Get_Value)) {
			std::cout
				<< "Each digit in number has to be unique from 1 to 9."
				<< std::endl;
			continue;
		}
		return Get_Value;
	}
}

void string_to_int(const std::string& Number, std::vector<uint8_t>& arr)
{
	char temp[1]{};
	for (uint8_t i = 0; i < NUMBER_OF_DIGITS; ++i) {
		temp[0] = { Number[i] };
		arr[i] = atoi(temp);
	}
}

void compare_numbers(const std::vector<uint8_t>& ArrNumber,
	const std::vector<uint8_t>& ArrInput,
	unsigned short& bulls, unsigned short& cows)
{
	bulls = cows = 0;
	for (uint8_t i = 0; i < NUMBER_OF_DIGITS; ++i) {
		int temp = ArrNumber[i];
		for (uint8_t j = 0; j < NUMBER_OF_DIGITS; ++j) {
			if (ArrNumber[i] == ArrInput[j] && i == j) {
				bulls++;
				continue;
			}
			if (ArrNumber[i] == ArrInput[j]) {
				cows++;
			}
		}
	}
}