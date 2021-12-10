#include <iostream>
#include <filesystem>
#include <fstream>
#include <string>
#include <vector>

void set(const std::string &file, const std::string &key, const std::string &value);
void get(const std::string &file, const std::string &key);
void delete_entry(const std::string &file,const std::string &key);
void search(const std::string &file, const std::string &key);
bool exists(const std::string &file, const std::string &key);

int main(int argc, char **argv){
	std::vector<std::string> input;
	std::string filename;
	std::string command;
	std::string key;
	input.reserve(argc -1);
	if (argc > 0){
		for (long i = 1; i < argc; ++i){
			const std::string temp(argv[i]);
			input.emplace_back(temp);
		}
	}
	if (input.size() < 3){
		std::cerr << "clikv needs at least three arguments: FILE COMMAND KEY." << std::endl;;
		std::cerr << "Available commands are: set get search" << std::endl;
		return 1;
	}
	filename = input.at(0);
	command = input.at(1);
	key = input.at(2);
	const bool datafile = std::filesystem::exists(filename);
	if (command == "set"){
		if (input.size() < 4){
			std::cerr << "The set command needs a VALUE argument." << std::endl;
			return 1;
		}
		const std::string value = input.at(3);
		set(filename, key, value);
	}
	else if (command == "get"){
		if (datafile){
			get(filename, key);
		}
	}
	else if (command == "search"){
		search(filename, key);
	}
	return 0;
}

void delete_entry(const std::string &file, const std::string &key){
	std::ifstream in(file, std::ios::binary);
	std::ofstream out(file, std::ios::binary);
	std::string content;
	while (in.good()){
		std::string line;
		std::getline(in, line);
		if (line.starts_with(key)){
			line = "";
		}
		content += line;
	}
	out.write(content.c_str(), content.size());
}

void set(const std::string &file, const std::string &key, const std::string &value){
	if (exists(file, key)){
		delete_entry(file, key);
	}
	std::ofstream stream(file, std::ios::app);
	const std::string line = key + " " + value + "\n";
	const long length = key.size() + value.size() + 3;
	stream.write(line.c_str(), length);
}

void get(const std::string &file, const std::string &key){
	std::ifstream stream(file, std::ios::in);
	std::string buffer;
	while (stream.good()){
		std::getline(stream, buffer);
	}
	key.size();
}

void search(const std::string &file, const std::string &key){
	if (exists(file, key)){
		std::cout << "found" << std::endl;
	}
	else{
		std::cout << "not found" << std::endl;
	}
}

bool exists(const std::string &file, const std::string &key){
	std::ifstream stream(file, std::ios::binary);
	//char buffer[fsize];
	std::string content;
	while (stream.good()){
		std::getline(stream, content);
		//const std::string temp(buffer);
		if (content.starts_with(key)){
			return true;;
		}
	}
	return false;
}
