/* 
 * file io using standard C++ stream, 
 * similar to the unix version C code, but
 * portable to non-unix platforms.
 */

#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

/* Test fstream's
 * open(), close()
 * read(), write()
 * tellg(), tellp()
 * seekg(), seekp()
 */
void
test_fio(string& str)
{
	char data1[] = "ABCDEF";
	char data2[] = "abcdefg";

	int n1, n2;
	n1 = sizeof(data1);
	n2 = sizeof(data2);

	// truncate if exist.
	fstream fs;
	fs.open(str, ios_base::in |
		     ios_base::out |
		     ios_base::trunc);

	// show start with offset 0
	cout << "start read offset: "
	     << fs.tellg()
	     << endl;

	cout << "start write offset: "
	     << fs.tellp()
	     << endl;

	// do write, need to check return, todo
	fs.write(data1, n1);

	// showing both position changed
	cout << "read offset: "
	     << fs.tellg()
	     << endl;
	cout << "write offset: "
	     << fs.tellp()
	     << endl;

	// still "both" changed, even if we only
	// call seekp(), not seekg()
	fs.seekp(100, ios_base::beg);
	cout << "read offset: "
	     << fs.tellg()
	     << endl;
	cout << "write offset: "
	     << fs.tellp()
	     << endl;

	// do write, need to check return, todo
	fs.write(data2, n2);
	cout << "read offset: "
	     << fs.tellg()
	     << endl;
	cout << "write offset: "
	     << fs.tellp()
	     << endl;

	// read out the first data chunk
	char* buf = new char[100];
	fs.seekg(0, ios_base::beg);
	fs.read(buf, 10);
	// read sets the error within the object, and
	// object itself has ! operator defined.
	if (fs) { // read OK, was able to read all 10 bytes.
		cout << "read offset: "
	     	     << fs.tellg()
	             << endl;
		cout << "write offset: "
	     	     << fs.tellp()
	     	     << endl;
		cout << "file data read: "
	     	     << buf
	     	     << endl;
	} else {
		cout << "file data read failed "
	     	     << endl;
		return;
	}

	memset(buf, '\0', 10);
	fs.seekg(100, ios_base::beg);
	fs.read(buf, 10);
	if (fs.gcount() > 0) { 
		// read OK, but if check only fs, we have to
		// be able to read all 10 bytes.
		// so use gcount() instead

		// notice the offset becomes -1 here, as
	 	// we over-read past EOF, interesting.
		cout << "read offset: "
	     	     << fs.tellg()
	             << endl;
		cout << "write offset: "
	     	     << fs.tellp()
	     	     << endl;
		cout << "file data read: "
	     	     << buf
	     	     << endl;
	} else {
		cout << "file data read failed "
	     	     << endl;
		return;
	}

	delete[] buf;

	// close is optional, automatically close when
	// fs object is destroyed. 
	fs.close();
}

int main()
{
	string file_name("test_cpp");
	test_fio(file_name);
	return 0;
}

