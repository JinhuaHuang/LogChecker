#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

int main(int argc, char* argv[])
{	
	cout << "# " << argv[0] << " mode        " << " options" << endl;
	cout << endl;
	cout << "# " << argv[0] << " GET_FILE    " << " read_file write_file remove_file string0 ..." << endl;
	cout << "# " << argv[0] << " REMOVE_FILE " << " read_file write_file remove_file string0 ..." << endl;
	cout << endl;

	int item = 0;
	
	if (argc > 1)
	{
		char mode[36];

		strncpy(mode, argv[1], 36);
		if (strncmp(mode, "GET_FILE", 8) == 0)
		{
			item = 1;
		}
	}		
	
	if (item == 1)
	{
		if (argc < 6)
		{			
			exit(1);
		}
		string read_file, write_file, remove_file;	
		int nstrings = argc - 5;
		vector<string> vt_string(nstrings);

		read_file = argv[2];
		write_file = argv[3];
		remove_file = argv[4];
		for (int i = 0; i < nstrings; ++i)
		{
			vt_string[i] = argv[5+i];
		}

		fstream fs_read, fs_write, fs_remove;
		char line[4096];

		fs_read.open(read_file.c_str(), fstream::in | fstream::out);
		fs_write.open(write_file.c_str(), fstream::in | fstream::out | fstream::trunc);
		fs_remove.open(remove_file.c_str(), fstream::in | fstream::out | fstream::trunc);

		while (fs_read.getline(line, 4096))
		{
			bool got = false;
			for (int i = 0; i < nstrings; ++i)
			{
				if (strstr(line, vt_string[i].c_str()))
				{
					got = true;
					break;
				}
			}
			
			if (got == true)
			{
				fs_write << line << endl;
			}
			else
			{
				fs_remove << line << endl;
			}
		}

		fs_read.close();
		fs_write.close();
		fs_remove.close();

		cout << "Finished get file!" << endl;
		return 0;
	}
}
