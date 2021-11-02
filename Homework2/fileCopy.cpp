#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <cerrno>

int main(int argc, char** argv){
	
	//check if amount of file is right
	if(argc < 3){
		std::cerr << "No source and destination files" << std::endl;
		exit(1);
	}
	
	//get source file path
	const char* sourcePath = argv[1];

	//open source file
	int source = open(sourcePath, O_RDONLY);
	
	//check if file was not open because of error
	if(source < 0){
		std::cerr << "Could not open file because of error " << errno << std::endl;
		exit(errno);
	}
	
	//get destination file path
	const char* destinationPath = argv[2];

	//open destination file path
        int destination = open(destinationPath, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP);
	
	//check if file was not open because of error
        if(destination < 0){
                std::cerr << "Could not open file because of error " << errno << std::endl;
                exit(errno);
        }
		
	//get the logical size of source file using lseek
	off_t logicalSizeOfSource = lseek(source, 0, SEEK_END);
	
	//check error when we use lseek
	if(logicalSizeOfSource < 0){
		std::cerr << "Seek Error" << std::endl;
		exit(errno);
	}
	
	//print the logical size of source file
	std::cout << "Logical size of source file is " << logicalSizeOfSource << std::endl;
	
	off_t holeOfSource = 0;
        size_t physicalSizeOfSource = 0;
	size_t sizeOfHoles = 0;

	//get the physical size of source file
	while(sizeOfHoles + physicalSizeOfSource != logicalSizeOfSource){
		
		//get the size from beginning to first byte of data	
		off_t dataOfSource = lseek(source, holeOfSource, SEEK_DATA);
		
		//check error when we use lseek
		if(dataOfSource < 0){
			std::cerr << "Seek Error" << std::endl;
			exit(errno);
		}

		//get the size of hole
		off_t holeAmount = dataOfSource - holeOfSource;

		//get the size from beginning to first byte of hole
		holeOfSource = lseek(source, dataOfSource, SEEK_HOLE);

		//check error when we use lseek
		if(holeOfSource < 0){
                        std::cerr << "Seek Error" << std::endl;
                        exit(errno);
                }

		//get the full size of holes
		if(holeAmount > 0){
			sizeOfHoles += holeAmount;
		}

		//get the size of data
		off_t dataAmount = holeOfSource - dataOfSource;
		
		//get the physical size of source file
		if(dataAmount > 0){
			physicalSizeOfSource += dataAmount;
		}
	}
	
	//print the physical size of source file
	std::cout << "Physical size of source file is " << physicalSizeOfSource << std::endl;
	
	std::cout << std::endl;

	off_t holeOfDestination = 0;
	off_t logicalSizeOfDestination = 0;
	size_t physicalSizeOfDestination = 0;

	//start copying file
	while(true){

		//get the size from beginning to first byte of data	
	       	off_t dataOfDestination = lseek(source, holeOfDestination, SEEK_DATA);

		//check error when we use lseek
                if(dataOfDestination < 0){
                        std::cerr << "Seek Error" << std::endl;
                        exit(errno);
                }
		
		//get the size of hole
		off_t holeAmount = dataOfDestination - holeOfDestination;

		//copy hole from source to destination file
		if(holeAmount > 0){
			logicalSizeOfDestination = lseek(destination, holeAmount, SEEK_END);
		}

		//stop copying because of reaching the end of source file
		if(logicalSizeOfSource == logicalSizeOfDestination){
			break;
		}

		//get the size from beginning to first byte of hole
		holeOfDestination = lseek(source, dataOfDestination, SEEK_HOLE);
		
		//check error when we use lseek		
		if(holeOfDestination < 0){
                        std::cerr << "Seek Error" << std::endl;
                        exit(errno);
                }
		
		//get the size of data
		off_t dataAmount = holeOfDestination - dataOfDestination;

		//copy data from source to destination file
		if(dataAmount > 0){
			
			//allocate a buffer to read from file
			char* buffer = new char[dataAmount + 1];
			
			//return the cursor to the beginning of data
			dataOfDestination = lseek(source, dataOfDestination, SEEK_SET);
			
			//check error when we use lseek
               		if(dataOfDestination < 0){
                        	std::cerr << "Seek Error" << std::endl;
                        	exit(errno);
                	}

			//read bytes from source file into buffer
			int readBytes = read(source, buffer, dataAmount);

			//error while reading
			if(readBytes < 0){
				std::cerr << "Could not read file because of error " << errno << std::endl;
                        	exit(errno);
			}

			//write bytes from buffer to destination file
			int writeBytes = write(destination, buffer, readBytes);

			//error while writeing
                	if(writeBytes < 0){
                        	std::cerr << "Could not write buffer because of error " << errno << std::endl;
                        	exit(errno);
                	}

			//release used memory
	        	delete [] buffer;
			
			//get the physical size of destination file
			physicalSizeOfDestination += dataAmount;

			//get the logical size of destination file
			logicalSizeOfDestination = lseek(destination, 0, SEEK_END);

			//check error when we use lseek
                        if(logicalSizeOfDestination < 0){
                                std::cerr << "Seek Error" << std::endl;
                                exit(errno);
                        }
	
			//stop copying because of reaching the end of source file
			if(logicalSizeOfSource == logicalSizeOfDestination){
                        	break;
                	}
		}
	}
	
	//print the logical size of destination file
	std::cout << "Logical size of destination file is " << logicalSizeOfDestination << std::endl;

	//print the physical size of destinatin file
	std::cout << "Physical size of destination file is " << physicalSizeOfDestination << std::endl;
	
	//close the source file
	int closeSource = close(source);
	
	//error when close source file
	if(closeSource < 0){
		std::cerr << "Something went wrong when close file" << std::endl;
		exit(errno);
	}

	//close the destination file
	int closeDestination = close(destination);
	
	//error when close destinatin file
	if(closeDestination < 0){
                std::cerr << "Something went wrong when close file" << std::endl;
                exit(errno);
        }

	return 0;
}

