#include <iostream>
#include <filesystem>
#include <fstream>
#include <string>
#include <vector>

void set(const std::string &file, const long fsize, const std::string &key, const std::string &value);
void get(const std::string &file, const long fsize, const std::string &key);
void delete_entry(const std::string &file, const long fsize, const std::string &key);
void search(const std::string &file, const long fsize, const std::string &key);
bool exists(const std::string &file, const long fsize, const std::string &key);

int main(int argc, char **argv){
	std::vector<std::string> input;
	std::string filename;
	std::string command;
	std::string key;
	long fsize = 0;
	input.reserve(argc -1);
	if (argc > 0){
		for (long i = 1; i < argc; ++i){
			const std::string temp(argv[i]);
			input.emplace_back(temp);
		}
	}
	filename = input.at(0);
	command = input.at(1);
	key = input.at(2);
	if (input.size() < 3){
		std::cerr << "clikv needs at least three arguments: FILE COMMAND KEY." << std::endl;;
		std::cerr << "Available commands are: set get search" << std::endl;
	}
	if (std::filesystem::exists(filename)){
		fsize = std::filesystem::file_size(filename);
	}
	if (command == "set"){
		if (input.size() < 4){
			std::cerr << "The set command needs a VALUE argument." << std::endl;
		}
		const std::string value = input.at(3);
		set(filename, fsize, key, value);
	}
	else if (command == "get"){
		get(filename, fsize, key);
	}
	else if (command == "search"){
		search(filename, fsize, key);
	}
	return 0;
}

void delete_entry(const std::string &file, const long fsize, const std::string &key){
	std::ifstream in(file, std::ios::binary);
	std::ofstream out(file, std::ios::binary);
	char buffer[fsize + 1];
	std::string content;
	while (in.good()){
		in.getline(buffer, fsize);
		std::string line = buffer;
		if (line.starts_with(key)){
			line = "";
		}
		content += line;
	}
	out.write(content.c_str(), content.size());
}

void set(const std::string &file, const long fsize, const std::string &key, const std::string &value){
	if (exists(file, fsize, key)){
		delete_entry(file, fsize, key);
	}
	std::ofstream stream(file, std::ios::app);
	const std::string line = key + " " + value + "\n";
	const long length = key.size() + value.size() + 3;
	stream.write(line.c_str(), length);
}

void get(const std::string &file, const long fsize, const std::string &key){
	std::ifstream stream(file, std::ios::binary);
	char buffer[fsize];
	while (stream.good()){
		stream.getline(buffer, fsize);
		const std::string temp(buffer);
		if (temp.starts_with(key)){
			const std::string value = temp.substr(key.length());
			std::cout << value.substr(1) << std::endl;
			break;
		}
	}
}

void search(const std::string &file, const long fsize, const std::string &key){
	if (exists(file, fsize, key)){
		std::cout << "found" << std::endl;
	}
	else{
		std::cout << "not found" << std::endl;
	}
}

bool exists(const std::string &file, const long fsize, const std::string &key){
	std::ifstream stream(file, std::ios::binary);
	char buffer[fsize];
	while (stream.good()){
		stream.getline(buffer, fsize);
		const std::string temp(buffer);
		if (temp.starts_with(key)){
			return true;;
		}
	}
	return false;
}
