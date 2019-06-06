#include <cstdio>
#include <dirent.h>
#include <cassert>
#include <string>
#include <cstdlib>
using namespace std;

void sub(string path) {
	DIR *tmp = opendir(path.c_str());
	struct dirent *tmpp;
	string order;
	string new_path(path.begin()+7, path.end());
	while(tmpp = readdir(tmp)) {
		if((tmpp->d_name)[0] == '.')
			continue;
		else if(tmpp->d_type == 4) {
			order = "mkdir server/" + new_path + tmpp->d_name;
			system(order.c_str());
			printf("%s", new_path.c_str());
			printf("%s\n", tmpp->d_name);
			sub(path + tmpp->d_name + "/");
		}
		else {
			if(tmpp->d_type == 10)
				order = "cp -P " + path + tmpp->d_name + " server/" + new_path;
			else
				order = "cp " + path + tmpp->d_name + " server/" + new_path;
			system(order.c_str());
			printf("%s", new_path.c_str());
			printf("%s\n", tmpp->d_name);
		}
	}
}

int main(void) {
	string path = "client/";
	sub(path);
	return 0;
}
