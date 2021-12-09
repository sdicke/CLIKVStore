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
	long fsize = 0;
	input.reserve(argc -1);
	if (argc > 0){
		for (long i = 1; i < argc; ++i){
			const std::string temp(argv[i]);
			input.emplace_back(temp);
		}
	}
	filename = input.at(0);
	if (std::filesystem::exists(input.at(0))){
		fsize = std::filesystem::file_size(input.at(0));
	}
	if (input.at(1) == "set"){
		set(filename, fsize, input.at(2), input.at(3));
	}
	else if (input.at(1) == "get"){
		get(filename, fsize, input.at(2));
	}
	else if (input.at(1) == "search"){
		search(filename, fsize, input.at(2));
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
